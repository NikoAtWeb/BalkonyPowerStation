#ifndef __dpm86CTRL_h__
#define __dpm86CTRL_h__

#include <Arduino.h>
#include "dpm86config.h"
//#include <HardwareSerial.h>
//#include <SoftwareSerial.h>

class dpm86CTRL {
  public:

      //dpm86CTRL(HardwareSerial * SerialConnection); // ;
      dpm86CTRL();//(int adress);
      void adress(String adress); 
      void begin();                                             // Begin Serial Connection
      void setup(int EnPin, int RxPin, int TxPin);              // with SoftSerial PIN definition
      void setup(int EnPin);                                    // only enable pin   
      void handle();
      void SetResponse();                                       // read response from Bus
      void setVoltage(float voltage);                             // set voltage output of DPM86xx
      void setCurrent(float current);                             // set current output of DPM86xx
      float readVoltage();
      float readCurrent();
      float readTemp();
      String readFromBus();
      void readResponse();
      void sendOUT(String _cmd, String _set, String _value);    // send command to DPM86xx

  private:
    int _addr;
    int _RxPin;
    int _TxPin;
    int _EnPin;
    float _voltage, _current;
    String  _cmd, _ad, _set, _value, _v, _c, _sendOut;          
    String _incomeStr;
    boolean _response;
    unsigned long _tmr = 0, _time_now;
};

#endif