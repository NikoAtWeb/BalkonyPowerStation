#ifndef dpm86CTRL_h
#define dpm86CTRL_h

#include "Arduino.h"
#include "dpm86config.h"
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

class dpm86CTRL {
  public:

      dpm86CTRL(HardwareSerial * SerialConnection); // ;
      void begin(uint32_t baud);
      //void receive();
      int setVoltage(int _voltage);
      //int getValue(int _IncomeValue);
      void sendOUT();

  private:

    int _voltage;
    int _addr;
    String  _cmd, _v, _sendOut;
    //int     _v;
    //SerialCtrl * _serial;
    HardwareSerial * _serial;
    //SoftwareSerial * _serial;
};

#endif