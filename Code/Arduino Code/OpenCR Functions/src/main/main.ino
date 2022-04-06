#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"



#include "functions.h"

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Servo servomotors[4] = {};

void setup() {
  init(servomotors,dxl);
}

void loop() {
  //robotStep(dxl,1);
}
