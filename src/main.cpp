#include <Arduino.h>
#include <Esp.h> // ESP Integration
//#include <SoftwareSerial.h>
#include <HardwareSerial.h>                   // Lade Hardware Serial
#include "dpm86CTRL.h"
#include <TaskScheduler.h>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
//HardwareSerial Serial(1); // Für die Ausgabe am Serial Monitor
//HardwareSerial SerialHard(2); // 1 = USB Serial, wir können also 2 oder 3 wählen
//SoftwareSerial SoftSerial(2,3); // Rx = 2; Tx = 3
dpm86CTRL DPM;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// defines

#define c_lim  15 // maximum current

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variables

int cnt = 5;
float t_act = 80;
float v_act = 0;

float v_batt = 24;
float p_grid_act = 250;
float c_grid_act = 0;
float c_BatOut = 0;
float c_tar_raw = 0;

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
Task t_100ms(100, TASK_FOREVER, &t_100msCallback);

Scheduler runner;

void t_hrCallback() {

  Serial.println("");
  Serial.println(" +++++++++++ Start Hr - Task +++++++++++++++++++++");

  // Ask weather
  // Ask Time
  // do the enviroment stuff: sunrise/sunset, cloudiness(%), temperature ==> generate env-status

  
  Serial.println("");
  Serial.println(" +++++++++++ End Hr - Task +++++++++++++++++++++++");
}

void t_minCallback() 
{
  Serial.println("");
  Serial.println(" +++++++++++ Start min - Task +++++++++++++++++++++");
  
  // +++++ Check devices +++++++++++++++++++++++++++++++++++++++++++++
  
  // check the >DPM< 

  t_act = DPM.readTemp();

  Serial.print("Temperature is: ");
  Serial.print(t_act);
  Serial.println("°C");

  // check the battery

  // battery-stuff: read voltage, temperature and health ==> make forcast (max W) out of battery-level until next sun (env-status)
  v_batt = 25 - cnt;
  cnt--;
  Serial.print("Battery voltage is: ");
  Serial.print(v_batt);
  Serial.println("V");
  
  Serial.println("");
  Serial.println(" +++++++++++ End min - Task +++++++++++++++++++++++");

}

void t_sCallback() 
{
  //Serial.println("");
  //Serial.println(" +++++++++++ Start sec - Task +++++++++++++++++++++");

  // read actual power consumption at 230V grid

  p_grid_act = random(200,250);       // write random value to variable
    //Serial.print("p_grid_act: ");
    //Serial.println(p_grid_act);
  c_grid_act = p_grid_act/230;        // P = U*I => I = P/U
    //Serial.print("c_grid_act: ");
    //Serial.println(c_grid_act);
  c_BatOut = p_grid_act/v_batt;           // P = U*I => I = P/U = p_grid / 20V
    //Serial.print("c_BatOut: ");
    //Serial.println(c_BatOut);

  c_tar_raw = _min(c_BatOut, c_lim); // limit current
    Serial.print("c_tar_raw: ");
    Serial.println(c_tar_raw);

  DPM.setVoltage(c_tar_raw);                // A T T E N T I O N: only for Testing at desk control voltage!!!! 

  //cnt++;
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
// ========= Setup  ===========

void setup() {
  Serial.begin(115200);

  // ========= DPM
  DPM.adress("01"); // define Adress here
  DPM.setup(21);     // define Pins here
  DPM.begin();      // start Serial connection
  DPM.setVoltage(3); // start with 3V

  // ========= Tasks  ===========
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
  
  // ========= enable tasks  ===========
  t_hr.enable(); 
  Serial.println("Enabled t_hr");
  t_min.enable();
  Serial.println("Enable t_min");
  t_s.enable();
  Serial.println("Enable t_s");
  t_100ms.enable();
  Serial.println("Enable t_100ms");

// ========= Build INFORMATION ===========

  Serial.print("Build Date: ");
  Serial.println(BUILD_DATE);
  Serial.print("Build Time: ");
  Serial.println(BUILD_TIME);

}

void loop() {

  runner.execute();
  DPM.handle();
  if (cnt ==0 )
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