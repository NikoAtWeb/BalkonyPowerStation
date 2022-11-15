#include <Arduino.h>
//#include <Esp.h> // ESP Integration
#include <SoftwareSerial.h>
//#include "dpm86CTRL.h"

SoftwareSerial mySerial(2,3); // Rx = 2; Tx = 3


void setup() {
  Serial.begin(9600);//(115200);
  mySerial.begin(9600);
  //Serial2.begin(9600);
}

void loop() {

  Serial.print("Communication(1): ");
  Serial.print(":01w10=1200.\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  mySerial.write(":01w10=1200.\n"); //command address write volt = 12 fastresponse end

  delay(1000);

  Serial.print("Communication(2): ");
  Serial.print(":01w10=1200,\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  mySerial.write(":01w10=1200,\n"); //command address write volt = 12 fastresponse end

  delay(1000);

  Serial.print("Communication(3): ");
  Serial.print(":01w10=1200,\r\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  mySerial.write(":01w10=1200,\r\n"); //command address write volt = 12 fastresponse end

  delay(1000);

  Serial.print("Communication(4): ");
  Serial.print(":01w10=1200,\r\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  mySerial.write(':01w10=1200,\r\n'); //command address write volt = 12 fastresponse end

  delay(1000);
  
  Serial.print("Communication(5): ");
  Serial.print(":01w10=1200.\n"); //command address write volt = 12 fastresponse end
  Serial.println();
  // Serial2
  mySerial.print(":01w10=1200.\n"); //command address write volt = 12 fastresponse end

  delay(1000);
}