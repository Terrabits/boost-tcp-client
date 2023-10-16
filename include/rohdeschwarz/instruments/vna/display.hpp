/**
 * \file display.hpp
 * \brief rohdeschwarz::instruments::vna::Display definition
 */


#ifndef ROHDESCHWARZ_INSTRUMENTS_VNA_DISPLAY_HPP
#define ROHDESCHWARZ_INSTRUMENTS_VNA_DISPLAY_HPP


// std lib
#include <string>


namespace rohdeschwarz::instruments::vna
{


// forward declare Vna
class Vna;


/**
 * \brief Object-oriented display control
 *
 * In remote control mode, the display can be turned on, off,
 * or manually updated via SCPI commands.
 *
 * `Display` provides object-oriented control of these settings.
 */
class Display
{

public:

  /**
   * \brief Constructor
   *
   * \param[in] vna a pointer to the underlying `Vna` instance
   */
  Display(Vna* vna);


  // display on / off

  /**
   * \brief queries whether display is on
   */
  bool isOn();


  /**
   * \brief sets display on value
   *
   * \param[in] on new display on value
   */
  void setOn(bool on = true);


  /**
   * \brief sets display off value
   *
   * \param[in] off new display off value
   */
  void setOff(bool off = true);


  // manual display update

  /**
   * \brief queries manual display update value
   */
  bool isManualUpdate();


  /**
   * \brief sets manual display update
   *
   * \param[in] manual manual display update value
   */
  void setManualUpdate(bool manual = true);


  /**
   * \brief manually updates the display
   *
   * To work, `update` requires manual display update mode
   */
  void update();


  // remote mode

  /**
   * \brief set instrument to local mode
   */
  void local();


  /**
   * \brief set instrument to remote mode
   */
  void remote();


private:
  Vna* _vna;


  // helpers

  /**
   * \brief query display update setting
   *
   * This function uses SCPI command query
   * `SYST:DISP:UPD?`
   */
  std::string updateSetting();


  /**
   * \brief set display update setting
   *
   * This function uses SCPI command
   * `SYST:DISP:UPD <value>`
   *
   * \param[in] value display update SCPI setting as a `C` string
   */
  void setUpdateSetting(const char* value);


  /**
   * \brief set display update setting
   *
   * This function uses SCPI command
   * `SYST:DISP:UPD <value>`
   *
   * \param[in] value display update SCPI setting as a `C++` string
   */
  void setUpdateSetting(const std::string& value);


};  // class Display


}       // namespace rohdeschwarz::instruments::vna
#endif  // ROHDESCHWARZ_INSTRUMENTS_VNA_DISPLAY_HPP
