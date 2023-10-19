#ifndef ROHDESCHWARZ_BUSSES_VISA_VISA_HPP
#define ROHDESCHWARZ_BUSSES_VISA_VISA_HPP


// rohdeschwarz
#include "rohdeschwarz/busses/bus.hpp"
#include "rohdeschwarz/busses/visa/cvisa.hpp"


// visa
#include "rs-visa/visa.h"


// std lib
#include <string>
#include <system_error>


namespace rohdeschwarz::busses::visa
{


/**
 * \brief System error exception
 *
 * This is a reference to `std::system_error` provided for convenience
 */
using system_error = std::system_error;


class Visa : public rohdeschwarz::busses::Bus
{

public:

  /**
   * \brief Constructor
   */
  Visa(std::string resource, unsigned int connection_timeout_ms = 2000);

  /**
   * \brief Destructor
   *
   * Closes the instrument connection, if open.
   */
  virtual ~Visa();


  virtual std::string endpoint() const;


  virtual int timeout_ms() const;


  virtual bool setTimeout(int timeout_ms);


  virtual bool readData(unsigned char* buffer, std::size_t bufferSize, std::size_t* readSize = nullptr);


  virtual bool writeData(const unsigned char* data, std::size_t dataSize, std::size_t* writeSize = nullptr);


  // attributes

  /**
   * \brief get VISA attribute
   */
  bool attribute(ViAttr name, ViAttrState* value) const;

  /**
   * \brief set VISA attribute
   */
  bool setAttribute(ViAttr name, ViAttrState value);


  // visa status

  /**
   * \brief Returns current ViStatus value
   */
  ViStatus status() const;

  /**
   * \brief Returns a human-friendly message for the current ViStatus value
   */
  virtual std::string statusMessage() const;

  /**
   * \brief Checks if there is a visa error
   *
   *
   */
  bool isError() const;

private:

  // visa resource
  std::string _resource;


  // visa
  CVisa     _visa;
  ViSession _resource_manager;
  ViSession _instrument;
  ViStatus  _status;


  // resource manager
  bool isResourceManager() const;
  bool openDefaultResourceManager();
  bool closeResourceManager();


  // instrument
  bool isInstrument() const;
  bool openInstrument(std::string resource, unsigned int timeout_ms);
  bool closeInstrument();


};  // class Bus


}       // rohdeschwarz::busses::visa
#endif  // ROHDESCHWARZ_BUSSES_VISA_VISA_HPP
