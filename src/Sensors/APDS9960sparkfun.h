#pragma once



#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

#include "..\Filter\MinFilter.h"
#include "..\Signals\TimeStep.h"


class APDS9960SPK{
private:
    static SparkFun_APDS9960 apds;
    static uint8_t proximity_data;
    static uint16_t threshold;
    static MinFilter<10> minF;
    static TimeStep timeStep;
    static float minimum;

public:
    static bool Initialize(uint8_t threshold) {//timeout in milliseconds and threshold is minimum for detection (0 is far away, 255 is touching)
         Wire.begin();

        Wire.setSCL(19);
        Wire.setSDA(18);
        APDS9960SPK::threshold = threshold;
        
        apds = SparkFun_APDS9960();
bool check1 = false; 
bool check2 = false;
bool check3 = false;
       

        
//while (!Serial) {
   // ; // wait for serial port to connect. Needed for native USB
  //}
       delay(10);

        if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
    check1 = true;
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  } 
  
 if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }else { check2 = true;
  }
if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
    check3 = true;
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
  Serial.println("waiting for sensor...");
  delay(250);
  Serial.println("wait over, sensor should be ready");
  if (check1&&check2&&check3) {
    return true;
  } else {
    return false;
  }
    }

    static bool isBooped(){
        uint8_t proxDat;
         apds.readProximity(proxDat);
       if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
    Serial.println(proxDat);
  }
        
        if(timeStep.IsReady()){
            minimum = minF.Filter(proximity_data);
        }

        return proximity_data > threshold;
    }

    static uint8_t GetValue(){
        if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
  }

        return proximity_data;
    }
    
    static uint16_t GetBrightness(){

uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

        if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }

            if (  !apds.readAmbientLight(ambient_light) ||
        !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    Serial.print("Ambient: ");
    Serial.print(ambient_light);
    Serial.print(" Red: ");
    Serial.print(red_light);
    Serial.print(" Green: ");
    Serial.print(green_light);
    Serial.print(" Blue: ");
    Serial.println(blue_light);
  }

        return ambient_light;
    }
};
SparkFun_APDS9960 APDS9960SPK::apds;
uint8_t APDS9960SPK::proximity_data;
uint16_t APDS9960SPK::threshold;

MinFilter<10> APDS9960SPK::minF = MinFilter<10>(false);
TimeStep APDS9960SPK::timeStep = TimeStep(5);
float APDS9960SPK::minimum = 0.0f;
