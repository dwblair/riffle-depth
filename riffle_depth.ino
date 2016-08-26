#include "LowPower.h"         //https://github.com/rocketscream/Low-Power
#include <Wire.h>
#include <SPI.h>
#include <DS3232RTC.h>        //http://github.com/JChristensen/DS3232RTC
#include<stdlib.h>
#include <SD.h>
#include <Time.h>  

//sleeping stuff
#define sleep_intervals 1

#define sleepytime 1000 // millis
//RTC stuff
//RTC_DS3231 RTC;


//led
#define led 9

//voltage stuff
#define voltageAnalogMeasurePin A3
#define voltageReadCircuitSwitch 4


// debugging -- only do Serial output if debuggin
#define debug 1 // 0: don't print anything out; 1: print out debugging statements

#define sensorBoard 8 // the pin that powers the 555 subcircuit

#define chipSelect 7
#define SDpower 6

#define analog_pin A0

long pulseCount = 0;  //a pulse counter variable

unsigned long pulseTime,lastTime, duration, totalDuration;

int samplingPeriod=4; // the number of seconds to measure 555 oscillations


double freq; // 

void setup() {

if(debug) Serial.begin(9600);

// indicate successful startup

for (int i=0;i<3;i++) {
  digitalWrite(led, HIGH);   
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

  // RTC setup

 setSyncProvider(RTC.get);
    //Serial << F("RTC Sync");
    //if (timeStatus() != timeSet) Serial << F(" FAIL!");
    //Serial << endl;

    
  

  /// SD setup
  
  
  pinMode(SDpower,OUTPUT);
    digitalWrite(SDpower,LOW);

    delay(1000);
    
     if (!SD.begin(chipSelect)) {
  if (debug) Serial.println("Card failed, or not present");

   // indicate SD problem with fast blink
    while(1) {
      digitalWrite(led,HIGH);
      delay(200);
      digitalWrite(led,LOW);
       delay(200);
    }
  }

  
  
  if (debug) Serial.begin(9600);
  
  // begin I2C protocol (necessary for RTC, and any other I2C on board
  Wire.begin();



  
  // RTC -------------------------
  //initialize_RTC(); // NOTE: need to initialize I2C first -- but also for any other I2C library
  
  // set mode for voltage circuit control pin, and turn the circuit off
  pinMode(voltageReadCircuitSwitch,OUTPUT);
  pinMode(sensorBoard,OUTPUT);  
  pinMode(led, OUTPUT);     
  
  //digitalWrite(sensorBoard,LOW); //turns on the 555 timer and thermistor subcircuit
  uint8_t i;
  
  //measure the input voltage 
  digitalWrite(voltageReadCircuitSwitch, HIGH); //turn on voltage measurement circuit
  digitalWrite(sensorBoard,HIGH);
  
  // wait a moment to let things settle
  
}

void loop () {

static time_t tLast;
    time_t t;
    tmElements_t tm;

t = now();
  // RTC test

    
  

  
  // Onboard temp from the RTC
 float rtcTemp = RTC.temperature() / 4.;


  digitalWrite(sensorBoard,LOW);
  
  // measure an analog battery
  int analog_value = analogRead(analog_pin);


  // depth sensor

  delay(2000); // give time for 555 to recover


  pulseCount=0; //reset the pulse counter
  totalDuration=0;  //reset the totalDuration of all pulses measured
  
  attachInterrupt(1,onPulse,RISING); //attach an interrupt counter to interrupt pin 0 (digital pin #2) -- the only other possible pin on the 328p is interrupt pin #1 (digital pin #3)
  
  pulseTime=micros(); // start the stopwatch
  
  delay(samplingPeriod*1000); //give ourselves samplingPeriod seconds to make this measurement, during which the "onPulse" function will count up all the pulses, and sum the total time they took as 'totalDuration' 
 
  detachInterrupt(1); //we've finished sampling, so detach the interrupt function -- don't count any more pulses
  
  
  if (pulseCount>0) { //use this logic in case something went wrong
  
  double durationS=totalDuration/double(pulseCount)/1000000.; //the total duration, in seconds, per pulse (note that totalDuration was in microseconds)
  
  // print out stats
  /*
  Serial.print("sampling period=");
  Serial.print(samplingPeriod);
    Serial.print(" sec; #pulses=");
  Serial.print(pulseCount);
  Serial.print("; duration per pulse (sec)=");
  Serial.println(durationS,8);
*/

  freq=1./durationS;
  

  }

  digitalWrite(sensorBoard,HIGH);

  
  
  // make a string for assembling the data to log:
  String dataString = "";
  
  // dataString += String(unixNow);
//  dataString += now.unixtime();
  //dataString += ",";
  dataString += year();
  dataString += "-";
  dataString += padInt(month(), 2);
  dataString += "-";
  dataString += padInt(day(), 2);
  dataString += " ";
  dataString += padInt(hour(), 2);
  dataString += ":";
  dataString += padInt(minute(), 2);
  dataString += ":";
  dataString += padInt(second(), 2);
  dataString += ",";
  char buffer[10];
  dataString += dtostrf(rtcTemp, 5, 2, buffer);
  dataString += ",";
  dataString += dtostrf(freq, 5, 2, buffer);

  
  
  
  if(debug) Serial.println(dataString);
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
   

  //indicate successful write with short blink
  digitalWrite(led, HIGH);   
  delay(40);
  digitalWrite(led, LOW);

  }
  // if the file isn't open, pop up an error:
  else {
    if (debug) Serial.println("error opening datalog.txt");
  }
  
// sleep for a while
if (debug==0) {
sleep_for_8s_interval(sleep_intervals);

}
else {
delay(sleepytime);
  
}
    
}
  

String padInt(int x, int pad) {
  String strInt = String(x);
  
  String str = "";
  
  if (strInt.length() >= pad) {
    return strInt;
  }
  
  for (int i=0; i < (pad-strInt.length()); i++) {
    str += "0";
  }
  
  str += strInt;
  
  return str;
}

String int2string(int x) {
  // formats an integer as a string assuming x is in 1/100ths
  String str = String(x);
  int strLen = str.length();
  if (strLen <= 2) {
    str = "0." + str;
  } else if (strLen <= 3) {
    str = str.substring(0, 1) + "." + str.substring(1);
  } else if (strLen <= 4) {
    str = str.substring(0, 2) + "." + str.substring(2);
  } else {
    str = "-9999";
  }
  
  return str;
}

void sleep_for_8s_interval(int numIntervals) { // will power down for numIntervals * 8 seconds 

for (int i=0;i<numIntervals;i++) {
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

}



void onPulse()
{
  pulseCount++;
  //Serial.print("pulsecount=");
  //Serial.println(pulseCount);
  lastTime = pulseTime;
  pulseTime = micros();
  duration=pulseTime-lastTime;
  totalDuration+=duration;
  //Serial.println(totalDuration);
}
