#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"
#include "functions.h"

void setup() {
  init(servomotors,dxl);
}

void loop() {
 DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID_FRONT_RIGHT));
}
