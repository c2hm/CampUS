#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"
#include "functions.h"

void setup() {
  init(servomotors,dxl);
}

void loop() {
 robotStep(dxl,-1);
 //robotStep(dxl,-1);
}
