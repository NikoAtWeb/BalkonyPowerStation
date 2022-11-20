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
      void init();
      void loop();
      void setVoltage(int _voltage);
      void sendOUT();

  private:

    int _voltage;
    int _addr;
    String  _cmd, _v, _sendOut;
};

#endif