#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"
#include "functions.h"

void setup() {
  init(servomotors,dxl);
}

void loop() {
  //delay(10000);
  //retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT,-1);
  delay(10000);
  
  extensionRearRight(dxl,DXL_ID_REAR_RIGHT);
  nbTurnsRearRight--;
  
  //Serial.println(dxl.getPresentPosition(DXL_ID_FRONT_LEFT));
 //robotStep(dxl,1);
}
