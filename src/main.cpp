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

// ++++++++++++++++++++++++++++++++++++++++++++++++++++


//DPM.setup(2,3);

void setup() {
  Serial.begin(9600);//(115200);
  DPM.setup(7); // define Pins here
  DPM.begin();  // start Serial connection
}

void loop() {
 
 if (cnt >=12)
 {
    cnt = 5; 
 }
 
  delay(2000);

  Serial.print("Communication: ");
  Serial.print("Set Voltage Over Libary"); //command address write volt = 12 fastresponse end
  Serial.println();
  
  DPM.setVoltage(cnt);

  cnt++;
}