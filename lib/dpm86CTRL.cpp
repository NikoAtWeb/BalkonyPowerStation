#include "Arduino.h"
#include "dpm86CTRL.h"

dpm86CTRL::dpm86CTRL(HardwareSerial * SerialConnection)
{
  // init SerialConnection
  _serial = SerialConnection;
}

void dpm86CTRL::begin(uint32_t baud)
{
  //Serial.begin(baud);
  _serial->begin(baud);
}

void dpm86CTRL::sendOUT()
{ // command address write volt = 12 fastresponse end

  _cmd  = ":";
  _addr = 01;
  _v    =  String(_voltage*100);
  _sendOut = _cmd + String(01) + "w" + _v + "," + "\r\n";

  //dpmSerial.print(_sendOut);

}