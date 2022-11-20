//#include <Arduino.h>
#include "dpm86CTRL.h"
#include "dpm86config.h"

dpm86CTRL::dpm86CTRL()
{
  // define dpm
  SoftwareSerial SoftSerial(2,3); // Rx = 2; Tx = 3
}
void dpm86CTRL::init()
{
  debugSerialBegin(9600);
  #ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.begin(9600);  // only for HardwareSerial, like ESP32
  #else
    dpmSerialSoft.begin(9600);    // only for SoftwareSerial, like Arduino Uno
  #endif
}
void dpm86CTRL::setup(int _RxPin, int _TxPin)
{
  debugSerialBegin(9600);
  #ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.begin(9600);  // only for HardwareSerial, like ESP32
  #else
    SoftwareSerial SoftSerial(_RxPin,_TxPin); // Rx = 2; Tx = 3
    //dpmSerialSoft.begin(9600);    // only for SoftwareSerial, like Arduino Uno

  #endif
}
void dpm86CTRL::loop()
{
  // read incoming message and print it on debug port
}
void dpm86CTRL::setVoltage(int _voltage)
{
  sendOUT(_voltage);
}

void dpm86CTRL::sendOUT(int _voltage)
{ // command address write volt = 12 fastresponse end
// Example: :01w10=1200.\n

  _cmd  = ":";
  _addr = 01;
  _v    =  String(_voltage*100);
  _sendOut = _cmd + "01" + "w" +"10="+_v + "." + "\n";
  
  // print on Debug Port
  debugSerialPrint("Send Command to DPM86: ");
  debugSerialPrintln(_sendOut);

#ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.print(_sendOut);
#else
    dpmSerialSoft.print(_sendOut);
#endif
}