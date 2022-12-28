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

void t_hrCallback();
void t_minCallback();
void t_sCallback();
void t_100msCallback();


//Tasks

Task t_hr(3600000, TASK_FOREVER, &t_hrCallback);
Task t_min(60000, TASK_FOREVER, &t_minCallback);
Task t_s(1000, TASK_FOREVER, &t_sCallback);
Task t_100ms(100, TASK_FOREVER, &t_sCallback);

Scheduler runner;

void t_hrCallback() {

  Serial.println("");
  Serial.println(" +++++++++++ Start Hr - Task +++++++++++++++++++++");

  DPM.setVoltage(cnt);

  cnt++;
  
  Serial.println("");
  Serial.println(" +++++++++++ End Hr - Task +++++++++++++++++++++++");
}

void t_minCallback() 
{
  Serial.println("");
  Serial.println(" +++++++++++ Start min - Task +++++++++++++++++++++");

  t_act = DPM.readTemp();

  Serial.print("Temperature is: ");
  Serial.print(t_act);
  Serial.println("°C");
  
  Serial.println("");
  Serial.println(" +++++++++++ End min - Task +++++++++++++++++++++++");

}

void t_sCallback() 
{
  //Serial.println("");
  //Serial.println(" +++++++++++ Start sec - Task +++++++++++++++++++++");
  
  //Serial.println("");
  //Serial.println(" +++++++++++ End sec - Task +++++++++++++++++++++++");

}

void t_100msCallback() 
{
  //Serial.println("");
  //Serial.println(" +++++++++++ Start 100ms - Task +++++++++++++++++++++");
  
  //Serial.println("");
  //Serial.println(" +++++++++++ End 100ms - Task +++++++++++++++++++++++");

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
  
  runner.addTask(t_hr); // add Task
  Serial.println("added t_hr");

  runner.addTask(t_min); // add Task
  Serial.println("added t_min");

  runner.addTask(t_s); // add Task
  Serial.println("added t_s");

  runner.addTask(t_100ms); // add Task
  Serial.println("added t_100ms");

  delay(1000);
  
  // enable tasks
  t_hr.enable(); 
  Serial.println("Enabled t_hr");
  t_min.enable();
  Serial.println("Enable t_min");
  t_s.enable();
  Serial.println("Enable t_s");
  t_100ms.enable();
  Serial.println("Enable t_100ms");

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