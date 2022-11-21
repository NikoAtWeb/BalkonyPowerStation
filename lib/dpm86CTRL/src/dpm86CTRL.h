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
      void setup(int _EnPin, int _RxPin, int _TxPin); // with SoftSerial PIN definition
      void setup(int _EnPin);                         // only enable pin
      void loop();                                    // read from Bus
      void setVoltage(int _voltage);                  // set voltage of DPM86xx
      void sendOUT();//(int _voltage);                  // send command to DPM86xx

      int _EnPin;
      int _voltage;

  private:
    int _addr;
    int _RxPin;
    int _TxPin;
    String  _cmd, _v, _sendOut;
};

#endif