#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"
#include "functions.h"

void setup() {
  init(servomotors,dxl);
}

void loop() {
  /*delay(10000);
  retractionRearLeft(dxl,DXL_ID_REAR_LEFT,1);
  nbTurnsRearLeft++; 
  delay(10000);
  extensionRearLeft(dxl,DXL_ID_REAR_LEFT,1);*/
  //Serial.println(dxl.getPresentPosition(DXL_ID_FRONT_LEFT));
 //robotStep(dxl,1);
}
