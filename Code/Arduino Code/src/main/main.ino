#include <Servo.h>

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

void tests_moteurs(Servo servo, int angle);

Servo servo_test = Servo();
int angle = 0;

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

  
  servo_test.attach(PIN_FRONT_LEFT_SERVO_PWM);
  digitalWrite(PIN_FRONT_LEFT_SERVO_POWER, HIGH);
  
}

void loop() {
  if (angle != 180)
  {
      angle++;
    
  }
  tests_moteurs(servo_test, angle);
}

void tests_moteurs(Servo servo, int angle)
{
  servo.write(angle);
}
