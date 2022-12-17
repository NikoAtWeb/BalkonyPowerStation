#include <Arduino.h>
//#include <Esp.h> // ESP Integration
//#include <SoftwareSerial.h>
#include "dpm86CTRL.h"

// ++++++++++++++++++++++++++++++++++++++++++++++++++++

SoftwareSerial SoftSerial(2,3); // Rx = 2; Tx = 3
dpm86CTRL DPM;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variables

int cnt = 5;
float t_act = 80;
float v_act = 0;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++


//DPM.setup(2,3);

void setup() {
  Serial.begin(9600);//(115200);
  DPM.adress("01"); // define Adress here
  DPM.setup(7);     // define Pins here
  DPM.begin();      // start Serial connection
  DPM.setVoltage(3);
}

void loop() {
 DPM.handle();
 if (cnt >12)
 {
    cnt = 5; 
 }
 
  delay(500);

  Serial.print("Communication: ");
  Serial.print("Set Voltage Over Libary"); //command address write volt = 12 fastresponse end
  Serial.println();
  
  DPM.setVoltage(cnt);
  cnt++;


  delay(5000);

  v_act = DPM.readVoltage();

  Serial.print("Voltage is: ");
  Serial.print(v_act);
  Serial.println("V");
/*

  delay(5000);

  DPM.setCurrent(1);

  delay(5000); */

  t_act = DPM.readTemp();

  Serial.print("Temperature is: ");
  Serial.print(t_act);
  Serial.println("°C");

}