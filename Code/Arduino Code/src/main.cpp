#include <Arduino.h>
#include "../lib/OpenCR-master/arduino/opencr_arduino/opencr/libraries/Servo/src/Servo.cpp"

#define FRONT_LEFT_SERVO 0
#define FRONT_RIGHT_SERVO 1
#define REAR_LEFT_SERVO 2
#define REAR_RIGHT_SERVO 3

#define PIN_FRONT_LEFT_SERVO_POWER 13
#define PIN_FRONT_LEFT_SERVO_PWM 11
#define PIN_FRONT_RIGHT_SERVO_POWER 12
#define PIN_FRONT_RIGHT_SERVO_PWM 10
#define PIN_REAR_LEFT_SERVO_POWER 8
#define PIN_REAR_LEFT_SERVO_PWM 9
#define PIN_REAR_RIGHT_SERVO_POWER 7
#define PIN_REAR_RIGHT_SERVO_PWM 6

void tests_moteurs(Servo servo);

void setup() {
  //Associate pins
  pinMode(PIN_FRONT_LEFT_SERVO_POWER, OUTPUT);
  pinMode(PIN_FRONT_LEFT_SERVO_PWM, INPUT);

  pinMode(PIN_FRONT_RIGHT_SERVO_POWER,OUTPUT);
  pinMode(PIN_FRONT_RIGHT_SERVO_PWM,INPUT);

  pinMode(PIN_REAR_LEFT_SERVO_POWER,OUTPUT);
  pinMode(PIN_REAR_LEFT_SERVO_PWM, INPUT);

  pinMode(PIN_REAR_RIGHT_SERVO_POWER, OUTPUT);
  pinMode(PIN_REAR_RIGHT_SERVO_PWM, INPUT);

  //Servomotors
  Servo servomotors[4] = {};

  servomotors[FRONT_LEFT_SERVO].attach(PIN_FRONT_LEFT_SERVO_PWM);
  servomotors[FRONT_RIGHT_SERVO].attach(PIN_FRONT_RIGHT_SERVO_PWM);
  servomotors[REAR_LEFT_SERVO].attach(PIN_REAR_LEFT_SERVO_PWM);
  servomotors[REAR_RIGHT_SERVO].attach(PIN_REAR_RIGHT_SERVO_PWM);

  Servo servo_test = Servo();
  servo_test.attach(PIN_FRONT_LEFT_SERVO_PWM);

  tests_moteurs(servo_test);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void tests_moteurs(Servo servo)
{
  printf("%d",servo.read());
}