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
      void init(); // without PIN definition for SERIAL
      void setup(int _RxPin, int _TxPin); // with SoftSerial PIN definition
      void loop();
      void setVoltage(int _voltage);
      void sendOUT(int _voltage);

  private:

    int _voltage;
    int _addr;
    int _RxPin;
    int _TxPin;
    String  _cmd, _v, _sendOut;
};

#endif