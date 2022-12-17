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
//void t1Callback();
void t2Callback();
void t3Callback();

//Tasks
//Task t1(2000, 10, &t1Callback);
Task t2(1000, TASK_FOREVER, &t2Callback);
Task t3(2000, TASK_FOREVER, &t3Callback);

Scheduler runner;

/*
void t1Callback() {
    Serial.print("t1: ");
    Serial.println(millis());
    
    if (t1.isFirstIteration()) {
      runner.addTask(t3);
      t3.enable();
      Serial.println("t1: enabled t3 and added to the chain");
    }
    
    if (t1.isLastIteration()) {
      t3.disable();
      runner.deleteTask(t3);
      t2.setInterval(500);
      Serial.println("t1: disable t3 and delete it from the chain. t2 interval set to 500");
    }
}*/

void t2Callback() {

  Serial.println("Task2");

  DPM.setVoltage(cnt);

  cnt++;
    
}

void t3Callback() {

    Serial.print("++++++++++++++++++++++++++++++++++++++++++++++++++++ Task 3: ");
    Serial.println(millis());
  
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
    runner.init();
  Serial.println("Initialized scheduler");
  
  //runner.addTask(t1);
  //Serial.println("added t1");
  
  runner.addTask(t2);
  Serial.println("added t2");

  runner.addTask(t3);
  Serial.println("added t3");

  delay(1000);
  
  //t1.enable();
  //Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");
  t3.enable();
  Serial.println("Enable t3");

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