#include <Arduino.h>
#include "..\lib\OpenCR-master\arduino\opencr_arduino\opencr\libraries\Servo\src\Servo.h"

#define PIN_TEST_SERVO_POWER 12
#define PIN_TEST_SERVO_PWM 11

void tests_moteurs(Servo servo);

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_TEST_SERVO_POWER, OUTPUT);
  pinMode(PIN_TEST_SERVO_PWM, INPUT);
  
  Servo servo_test = Servo();
  servo_test.attach(PIN_TEST_SERVO_PWM);

  tests_moteurs(servo_test);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void tests_moteurs(Servo servo)
{
  printf("%d",servo.read());
}