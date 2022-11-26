#ifndef __dpm86CTRL_h__
#define __dpm86CTRL_h__

#include <Arduino.h>
#include "dpm86config.h"
//#include <HardwareSerial.h>
//#include <SoftwareSerial.h>

class dpm86CTRL {
  public:

      //dpm86CTRL(HardwareSerial * SerialConnection); // ;
      dpm86CTRL();
      void begin();                                   // Begin Serial Connection
      void setup(int EnPin, int RxPin, int TxPin); // with SoftSerial PIN definition
      void setup(int EnPin);                         // only enable pin
      void SetResponse();                                    // read from Bus
      void setVoltage(int voltage);
      void setCurrent(int current);                // set voltage of DPM86xx
      void sendOUT();//(int _voltage);                  // send command to DPM86xx

  private:
    int _addr;
    int _RxPin;
    int _TxPin;
    int _EnPin;
    int _voltage, _current;
    String  _cmd, _v, _sendOut;          String _incomeStr;
};

#endif