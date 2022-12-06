//#include <Arduino.h>
#include "dpm86CTRL.h"
#include "dpm86config.h"

#define read  "r"
#define write  "w"

dpm86CTRL::dpm86CTRL()//(int adress)
{
  /*
  _addr = adress;
  if (_addr <10)
  {
    _ad = "0" + String(_addr);
  }
  else
  {
    _ad = String(_addr);
  }*/

}
  //
  // ====================================================================================
  //
void dpm86CTRL::adress(String adress)
{
  _ad = adress;
}
  //
  // ====================================================================================
  //
void dpm86CTRL::begin()
{
  debugSerialBegin(9600);
  #ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.begin(9600);  // only for HardwareSerial, like ESP32
  #else
    dpmSerialSoft.begin(9600);    // only for SoftwareSerial, like Arduino Uno
  #endif
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setup(int _EnPin, int _RxPin, int _TxPin)
{ // well, needs to be checked how to define SoftwareSerial Pins in Lib
  #ifdef HARDWARE_SERIAL_ENABLE
    // nothing to do
  #else
    SoftwareSerial SoftSerial(_RxPin,_TxPin); // Rx = 2; Tx = 3
  #endif
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setup(int EnPin)
{
  _EnPin = EnPin; // swap to internal variable
  pinMode(_EnPin, OUTPUT);
  digitalWrite(_EnPin, LOW);
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setVoltage(int voltage)
{ 
  _voltage = voltage;

  _v = String(_voltage*100);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++

  sendOUT(write, "10", _v);

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  while (_response == false){
    SetResponse();
  }
  _response = false;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setCurrent(int current)
{ 
  _current = current;

   _c = String(_current*100);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++

  sendOUT(write, "11", _c);

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  while (_response == false){
    SetResponse();
  }
  _response = false;
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
float dpm86CTRL::readVoltage()
{
  sendOUT(read, "30", "0");

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  while (_response == false){
    SetResponse();
  }
  _response = false;
  return 0; // test
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
float dpm86CTRL::readCurrent()
{
  sendOUT(read, "31", "0");

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  while (_response == false){
    SetResponse();
  }
  _response = false;
  return 0; // test
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
float dpm86CTRL::readTemp()
{
  sendOUT(read, "33", "0");

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  while (_response == false){
    SetResponse();
  }
  _response = false;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  String _valResp = _incomeStr;

  _valResp.remove(1,5); // remove 5 character starting from 1

  _valResp = "14.2653"; // für den Test; wird gelöscht
  float _ValOut = _value.toFloat();

  return _ValOut; // test
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
  String dpm86CTRL::SetResponse()
{
  // read incoming message and print it on debug port
    while(dpmSerialSoft.available( ) > 0) //  It will only send data when the received data is greater than 0.  
  {  
    // ++++++++++ READ incoming Message +++++++++++++++

    _incomeStr = dpmSerialSoft.readString();

    //++++++++++ debug incoming Message +++++++++++++++
    
    debugSerialPrint("Receive: ");
    debugSerialPrintln(_incomeStr);

    _response = true; // income complete

  } //end while
} // end loop
  //
  // ====================================================================================
  //
void dpm86CTRL::sendOUT(String _cmd, String _set, String _value)//(int _voltage)
{ // command address write volt = 12 fastresponse end
  // Example: :01w10=1200.\n

  String _start  = ":";

  _sendOut = _start + _ad + _cmd + _set + "=" + _value + "." + "\n";
  
  // print on Debug Port
  debugSerialPrint("Send Command to DPM86: ");
  debugSerialPrintln(_sendOut);

  // ++++++++++++++++++++++++++++++++++++++++++++++++
  // Start enable write Pin

  digitalWrite(_EnPin, HIGH);

  // +++++++++++++++++++++++++++++++++++++++++++++++++
  // Send to MAX485

#ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.flush;
    dpmSerialHard.print(_sendOut);
#else
    dpmSerialSoft.flush();
    dpmSerialSoft.print(_sendOut);
#endif

  // ++++++++++++++++++++++++++++++++++++++++++++++++
  // Stop enable write Pin

  digitalWrite(_EnPin, LOW);

  // +++++++++++++++++++++++++++++++++++++++++++++++++
}