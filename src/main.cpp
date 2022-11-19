#include <Arduino.h>
//#include <Esp.h> // ESP Integration
//#include <SoftwareSerial.h>
#include "dpm86CTRL.h"

SoftwareSerial SoftSerial(2,3); // Rx = 2; Tx = 3

dpm86CTRL DPM;

void setup() {
  Serial.begin(9600);//(115200);
  //SoftSerial.begin(9600);
  
  DPM.init();
}

void loop() {

  Serial.print("Communication(1): ");
  Serial.print(":01w10=1200.\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  SoftSerial.write(":01w10=1200.\n"); //command address write volt = 12 fastresponse end

  delay(1000);

  Serial.print("Communication(2): ");
  Serial.print(":01w10=1000.\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  SoftSerial.write(":01w10=1000.\n"); //command address write volt = 12 fastresponse end

  delay(1000);

  Serial.print("Communication(3): ");
  Serial.print(":01w10=600.\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  SoftSerial.write(":01w10=600.\n"); //command address write volt = 12 fastresponse end

  delay(1000);

  Serial.print("Communication(4): ");
  Serial.print("5V Over Libary"); //command address write volt = 12 fastresponse end
  Serial.println();
  
  DPM.loop(); 
  DPM.setVoltage(5);

  delay(1000);
}