#include <Arduino.h>
//#include <Esp.h> // ESP Integration
//#include <SoftwareSerial.h>
#include "dpm86CTRL.h"
#include <TaskScheduler.h>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++

SoftwareSerial SoftSerial(2,3); // Rx = 2; Tx = 3
dpm86CTRL DPM;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variables

int cnt = 5;
float t_act = 80;
float v_act = 0;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// Tasks

// Callback methods prototypes

void tFastCallback();
void tSlowCallback();

//Tasks

Task tFast(1000, TASK_FOREVER, &tFastCallback);
Task tSlow(5000, TASK_FOREVER, &tSlowCallback);

Scheduler runner;

void tFastCallback() {

  Serial.println("");
  Serial.println(" +++++++++++ Start Fast - Task +++++++++++++++++++++");

  DPM.setVoltage(cnt);

  cnt++;
  
  Serial.println("");
  Serial.println(" +++++++++++ End Fast - Task +++++++++++++++++++++++");
}

void tSlowCallback() 
{
  Serial.println("");
  Serial.println(" +++++++++++ Start Slow - Task +++++++++++++++++++++");

  t_act = DPM.readTemp();

  Serial.print("Temperature is: ");
  Serial.print(t_act);
  Serial.println("°C");
  
  Serial.println("");
  Serial.println(" +++++++++++ End Slow - Task +++++++++++++++++++++++");

}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// Setup

void setup() {
  Serial.begin(9600);//(115200);

  // DPM
  DPM.adress("01"); // define Adress here
  DPM.setup(7);     // define Pins here
  DPM.begin();      // start Serial connection
  DPM.setVoltage(3);

  // Tasks
  runner.init(); // init runner
  Serial.println("Initialized scheduler");
  
  runner.addTask(tFast); // add Task
  Serial.println("added tFast");

  runner.addTask(tSlow); // add Task
  Serial.println("added tSlow");

  delay(1000);
  
  // enable tasks
  tFast.enable(); 
  Serial.println("Enabled tFast");
  tSlow.enable();
  Serial.println("Enable tSlow");

}

void loop() {
  
  runner.execute();
  DPM.handle();
  if (cnt >12)
  {
      cnt = 5; 
  }
 /*
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


  delay(5000);

  DPM.setCurrent(1);

  delay(5000); 

  t_act = DPM.readTemp();

  Serial.print("Temperature is: ");
  Serial.print(t_act);
  Serial.println("°C");*/

}