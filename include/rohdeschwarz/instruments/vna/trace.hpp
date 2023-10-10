/**
 * \file trace.hpp
 * \brief RsVisa::Trace definition
 */


#ifndef RS_VISA_TRACE_HPP
#define RS_VISA_TRACE_HPP


// std lib
#include <complex>
#include <string>
#include <vector>


namespace RsVisa
{


// forward declarations
class Znx;

/**
 * \brief Object-oriented trace control
 *
 * `Trace` provides object-oriented control of an existing trace
 * via VISA and SCPI commands
 */
class Trace
{

public:

  // life cycle

  /**
   * \brief Constructor
   *
   * \param[in] znx Pointer to underlying `Znx` instance
   * \param[in] name Name of existing trace to control as C style string
   */
  Trace(Znx* znx, const char* name);


  /**
   * \brief Constructor
   *
   * \param[in] znx Pointer to underlying `Znx` instance
   * \param[in] name Name of existing trace to control as C++ style string
   */
  Trace(Znx* znx, const std::string& name);


  /**
   * \brief Trace name
   */
  std::string name() const;


  /**
   * \brief Make trace the active trace
   *
   * Some SCPI commands apply to the active trace in a channel.
   * `select` makes this trace the active trace in its channel.
   */
  void select();


  // parameter

  /**
   * \brief Gets the measurement parameter for this trace
   *
   * `parameter` returns the measurement parameter for this trace (e.g. `S21`).
   * See the table [String Identifiers for Measurement Results](https://www.rohde-schwarz.com/webhelp/ZNA_HTML_UserManual_en/Content/e75d49e2a14541c5.htm#d843242e110746) for a complete list of possible parameters.
   */
  std::string parameter();


  /**
   * \brief Sets the measurement parameter for this trace
   *
   * See the table [String Identifiers for Measurement Results](https://www.rohde-schwarz.com/webhelp/ZNA_HTML_UserManual_en/Content/e75d49e2a14541c5.htm#d843242e110746) for a complete list of possible parameters.
   *
   * \param[in] parameter Measurement parameter as a C style string
   */
  void setParameter(const char* parameter);


  /**
   * \brief Sets the measurement parameter for this trace
   *
   * See the table [String Identifiers for Measurement Results](https://www.rohde-schwarz.com/webhelp/ZNA_HTML_UserManual_en/Content/e75d49e2a14541c5.htm#d843242e110746) for a complete list of possible parameters.
   *
   * \param[in] parameter Measurement parameter as a C++ style string
   */
  void setParameter(const std::string& parameter);


  // format

  /**
   * \brief Queries the trace format
   *
   * See the [table of formats](https://www.rohde-schwarz.com/webhelp/ZNA_HTML_UserManual_en/Content/132d40cd4d1d43c4.htm#d843242e119475) from the ZNA manual for possible formats.
   */
  std::string format();


  /**
   * \brief Sets the trace format
   *
   * See the [table of formats](https://www.rohde-schwarz.com/webhelp/ZNA_HTML_UserManual_en/Content/132d40cd4d1d43c4.htm#d843242e119475) from the ZNA manual for possible formats.
   *
   * \param[in] format Trace format as a C style string
   */
  void setFormat(const char* format);


  /**
   * \brief Sets the trace format
   *
   * See the [table of formats](https://www.rohde-schwarz.com/webhelp/ZNA_HTML_UserManual_en/Content/132d40cd4d1d43c4.htm#d843242e119475) from the ZNA manual for possible formats.
   *
   * \param[in] format Trace format as a C++ style string
   */
  void setFormat(const std::string& format);


  /**
   * \brief Queries the index of the measurement channel for this trace
   */
  unsigned int channel();


  // diagram

  /**
   * \brief Queries the index of the diagram for this trace
   */
  unsigned int diagram();


  /**
   * \brief Adds trace to diagram
   *
   * \param[in] diagram Index of diagram to add trace to
   */
  void setDiagram(unsigned int diagram);


  // data

  /**
   * \brief Returns formatted Y values from the last measurement of this trace
   */
  std::vector<double> y();


  /**
   * \brief Returns unformatted Y values from the last measurement of this trace
   *
   * Most unformatted trace parameters are measured and stored as complex
   * values (e.g. `S21`). Note that some parameters, however, are purely
   * real (e.g. Power Added Efficiency [PAE]).
   */
  std::vector<std::complex<double>> y_complex();


private:

  Znx*        _znx;
  std::string _name;


};


}       // RsVisa
#endif  // RS_VISA_TRACE_HPP
