//#include <Arduino.h>
#include "dpm86CTRL.h"
#include "dpm86config.h"

#define _read  "r"
#define _write  "w"

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
void dpm86CTRL::handle()
{
  //int _period = 100;

  //SetResponse();
/*
  if(((unsigned long)(millis() - _time_now) > _period) && (_response == false))
    {
        _time_now = millis();
        debugSerialPrintln("An error accured!");
        _response = true;
    }
    */
    //Run other code
}
  //
  // ====================================================================================
  //
void dpm86CTRL::readResponse()
{ 
  //debugSerialPrintln("+++++++++++++++++++++++++++++++");
  //debugSerialPrintln("+++++++++++++++++++++++++++++++");
  //debugSerialPrintln("start reading response from BUS");
  // === read incoming message and print it on debug port ================================
  int _period = 150;                            // Answer timer period
  boolean _strComplete = false;                 // status bit

  _tmr = millis();                              // set timer to actual time
  String _StrIncome = "";                              // delete last String

  while(((unsigned long)(millis()) - _tmr < _period) && (_strComplete == false))
  { 
    // ========= reading income ===========

    while(dpmSerialSoft.available( ) > 0) //  read  
    {  
      // ++++++++++ READ incoming Message +++++++++++++++

      char _inChar = (char)dpmSerialSoft.read(); // read character from BUS
      
      if (_inChar == '\n')                       // if the incoming character is a newline, set a flag
      {
        //debugSerialPrintln("=============================================");
        //debugSerialPrint("Raw receive is: ");    // debug message
        //debugSerialPrintln(_StrIncome);          // debug message
        _strComplete = true;                     // stop the while
      } // end if
      else // write to income string
      {
        _StrIncome += _inChar;                   // add it to the inputString
      } // end else
    } //end while serial available
  } //end while
  
  //debugSerialPrintln("+++++++++++++++++++++++++++++++");
   _incomeStr = _StrIncome;
  //return "hello"; //_StrIncome;

}
  //
  // ====================================================================================
  //
void dpm86CTRL::SetResponse()
{
  String _ChkResp = _incomeStr;
  //String _ChkResp = "";
  String _ChkOut  = _sendOut;

  _ChkResp.trim(); // cut empty chars
  _ChkOut.trim(); // cut empty chars

  debugSerialPrint("Clear Response: ");
  debugSerialPrintln(_ChkResp);

  // remove response character
  _ChkResp.remove(6,5);
  _ChkOut.remove(6,5);

  // ++++++++++++ now check answer ++++++++++++++++++++++++++++++

  if (_ChkResp == ":" + _ad + "ok")
  {
    debugSerialPrintln("Sendout: Checked and OK");
    
  } // end if
  else if (_ChkResp == _ChkOut)
  {
        debugSerialPrintln("Read; Checked and OK");
  }
  else
  {
    debugSerialPrintln("Communication error!");
  }// end else */
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setVoltage(float voltage)
{ 
  _voltage = voltage;
  int _vINT = _voltage*100;     // DPM format: 12.45V = 1245
  _v = String((int)(_voltage*100));

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++

  sendOUT(_write, "10", _v);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
void dpm86CTRL::setCurrent(float current)
{ 
  _current = current;
  _c = String((int)(_current*1000));

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++

  sendOUT(_write, "11", _c);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
float dpm86CTRL::readVoltage()
{
  sendOUT(_read, "30", "0");

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

    String _valResp = _incomeStr;

  _valResp.remove(0,7); // remove 7 character starting from 0
  debugSerialPrint("Raw answer of voltage: ");
  debugSerialPrintln(_valResp);//(_incomeStr);
  //_valResp = "1500"; // für den Test; wird gelöscht
  float _ValOut = _valResp.toFloat();
  return _ValOut/100; // test
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
float dpm86CTRL::readCurrent()
{
  sendOUT(_read, "31", "0");

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  //while (_response == false){
    SetResponse();
  //}
  _response = true;
  return 0; // test
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //
float dpm86CTRL::readTemp()
{
  sendOUT(_read, "33", "0");

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  //while (_response == false){
    //SetResponse();
  //}

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  String _valResp = _incomeStr;

  _valResp.remove(0,7); // remove 7 character starting from 0
  debugSerialPrint("Raw answer of temperature: ");
  debugSerialPrintln(_incomeStr);
  //_valResp = "14.2653"; // für den Test; wird gelöscht
  float _ValOut = _valResp.toFloat();
  return _ValOut; // test
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
}
  //
  // ====================================================================================
  //

void dpm86CTRL::sendOUT(String _cmd, String _set, String _value)//(int _voltage)
{ // command address write volt = 12 fastresponse end
  // Example: :01w10=1200.\n

  String _start  = ":";

  _sendOut = _start + _ad + _cmd + _set + "=" + _value + "." + "\n";
  
  // print on Debug Port
  debugSerialPrintln("=============================================");
  debugSerialPrintln("");
  debugSerialPrint("Send Command to DPM86: ");
  debugSerialPrintln(_sendOut);

  // ++++++++++++++++++++++++++++++++++++++++++++++++
  // Start enable write Pin

  digitalWrite(_EnPin, HIGH);

  // +++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef HARDWARE_SERIAL_ENABLE
    dpmSerialHard.flush();
    dpmSerialHard.print(_sendOut);
#else
    dpmSerialSoft.flush();
    dpmSerialSoft.print(_sendOut);
#endif

  // ++++++++++++++++++++++++++++++++++++++++++++++++
  // Stop enable write Pin

  digitalWrite(_EnPin, LOW);

  // +++++++++++++++++++++++++++++++++++++++++++++++++
  _tmr = millis(); 

  // ===== check the answer =====
  readResponse();
  SetResponse();
  

  debugSerialPrint("How long Send-> Answer needs: ");
  debugSerialPrintln(millis()-_tmr);

}