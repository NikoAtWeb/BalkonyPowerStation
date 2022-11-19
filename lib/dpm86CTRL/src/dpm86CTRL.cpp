//#include <Arduino.h>
#include "dpm86CTRL.h"
#include "dpm86config.h"

dpm86CTRL::dpm86CTRL(HardwareSerial * SerialConnection)
{
  // init SerialConnection
  //_serial = SerialConnection;
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

void dpm86CTRL::sendOUT()
{ // command address write volt = 12 fastresponse end

  _cmd  = ":";
  _addr = 01;
  _v    =  String(_voltage*100);
  _sendOut = _cmd + String(01) + "w" + _v + "," + "\r\n";

#ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.print(_sendOut);
#else
    dpmSerialSoft.print(_sendOut);
#endif
}