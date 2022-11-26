//#include <Arduino.h>
#include "dpm86CTRL.h"
#include "dpm86config.h"

dpm86CTRL::dpm86CTRL()
{
  // define dpm
  // SoftwareSerial SoftSerial; // Rx = 2; Tx = 3

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
void dpm86CTRL::SetResponse()
{
  // read incoming message and print it on debug port
    while(dpmSerialSoft.available( ) > 0) //  It will only send data when the received data is greater than 0.  
  {  
    // ++++++++++ READ incoming Message +++++++++++++++

    _incomeStr = dpmSerialSoft.readString();

    //++++++++++ debug incoming Message +++++++++++++++
    
    debugSerialPrint("Receive: ");
    debugSerialPrintln(_incomeStr);

  } //end while
} // end loop
  //
  // ====================================================================================
  //
void dpm86CTRL::setVoltage(int voltage)
{ 
  _voltage = voltage;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  sendOUT();
  SetResponse();
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setCurrent(int current)
{ 
  _current = current;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  //sendOUT();
  //SetResponse();
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
void dpm86CTRL::sendOUT()//(int _voltage)
{ // command address write volt = 12 fastresponse end
  // Example: :01w10=1200.\n

  _cmd  = ":";
  _addr = 01;
  _v    =  String(_voltage*100);
  _sendOut = _cmd + "01" + "w" +"10="+_v + "." + "\n";
  
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