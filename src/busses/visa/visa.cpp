#include "rohdeschwarz/busses/visa/visa.hpp"
using namespace rohdeschwarz::busses::visa;


// std lib
#include <cerrno>


Visa::Visa(std::string resource, unsigned int connection_timeout_ms)
{
  // check for visa
  if (!_visa.isVisa())
  {
    auto error_code = make_error_code(std::errc::not_connected);
    throw system_error(error_code, "Error loading visa shared library");
  }

  // get default visa resource manager
  if (!openDefaultResourceManager())
  {
    auto error_code = make_error_code(std::errc::not_connected);
    throw system_error(error_code, "Error retrieveing VISA default Resource Manager.");
  }


  if (!openInstrument(resource, connection_timeout_ms))
  {
    closeResourceManager();

    // throw exception
    auto error_code = make_error_code(std::errc::not_connected);
    throw system_error(error_code, "Error connecting to instrument");
  }
}


Visa::~Visa()
{
  closeInstrument();
  closeResourceManager();
}


std::string Visa::endpoint() const
{
  return _resource;
}


int Visa::timeout_ms() const
{
  // get timeout
  ViAttrState value = -999;
  attribute(VI_ATTR_TMO_VALUE, &value);

  // convert to int
  return int(value);
}

bool Visa::setTimeout(int timeout_ms)
{
  return setAttribute(VI_ATTR_TMO_VALUE, ViAttrState(timeout_ms)) >= VI_SUCCESS;
}


bool Visa::readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize)
{
  _status = _visa.viRead(
    _instrument,
    ViPBuf(buffer),
    ViUInt32(bufferSize),
    ViPUInt32(readSize)
  );
  return isError();
}


bool Visa::writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize)
{
  _status = _visa.viWrite(
    _instrument,
    ViBuf(data),
    ViUInt32(dataSize),
    ViPUInt32(writeSize)
  );
  return isError();
}


bool Visa::attribute(ViAttr name, ViAttrState* value) const
{
  auto status = _visa.viGetAttribute(_instrument, name, value);
  return status >= VI_SUCCESS;
}


bool Visa::setAttribute(ViAttr name, ViAttrState value)
{
  _status = _visa.viSetAttribute(_instrument, name, value);
  return isError();
}


ViStatus Visa::status() const
{
  return _status;
}


std::string Visa::statusMessage() const
{
  // get description
  ViChar description[1000];
  ViStatus status = _visa.viStatusDesc(
    _instrument,
    _status,
    description
  );

  // success?
  if (status < VI_SUCCESS)
  {
    // visa error
    return std::string();
  }

  // return std::string
  return std::string(description);
}


bool Visa::isError() const
{
  return _status < VI_SUCCESS;
}


bool Visa::isResourceManager() const
{
  return _resource_manager != VI_NULL;
}


bool Visa::openDefaultResourceManager()
{
  _status = _visa.viOpenDefaultRM(&_resource_manager);
  return !isError();
}


bool Visa::closeResourceManager()
{
  // check if resource manager exists
  if (!isResourceManager())
  {
    // nothing to close
    return true;
  }

  // close
  ViObject rm_obj = ViObject(_resource_manager);
  _status = _visa.viClose(rm_obj);
  if (isError())
  {
    // error
    return false;
  }

  // clear
  _resource_manager = VI_NULL;
  return !isError();
}


bool Visa::isInstrument() const
{
  return _instrument != VI_NULL;
}


bool Visa::openInstrument(std::string resource, unsigned int timeout_ms)
{
  // save resource for use in endpoint()
  _resource = resource;

  // open instrument connection
  ViRsrc   visaResource = ViRsrc(_resource.c_str());
  ViUInt32 visaMode     = VI_NULL;
  ViUInt32 visaTimeout  = ViUInt32(timeout_ms);
  _status = _visa.viOpen(
    _resource_manager,
    visaResource,
    visaMode,
    visaTimeout,
    &_instrument
  );
  return !isError();
}


bool Visa::closeInstrument()
{
  // check if instrument exists
  if (!isInstrument())
  {
    // nothing to close
    return true;
  }

  // close
  ViObject instrument_obj = ViObject(_instrument);
  _status = _visa.viClose(instrument_obj);
  if (isError())
  {
    // error
    return false;
  }

  // clear
  _instrument = VI_NULL;
  return !isError();
}
