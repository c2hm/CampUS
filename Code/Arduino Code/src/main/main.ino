#include <Servo.h>
#include <Dynamixel2Arduino.h>

#if defined(ARDUINO_OpenCR) // When using official ROBOTIS board with DXL circuit.
  // For OpenCR, there is a DXL Power Enable pin, so you must initialize and control it.
  #define DXL_SERIAL   Serial3
  #define DEBUG_SERIAL Serial
  const uint8_t DXL_DIR_PIN = 84; // OpenCR Board's DIR PIN.
#endif

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

//Movement modes
#define WAIT_MODE 0
#define EXTENSION_MODE 1
#define RETRACTION_MODE 2
uint8_t mode = WAIT_MODE;

//Useful functions for movement sequence
void tests_moteurs(Servo servo, int angle);
void finish(Dynamixel2Arduino dxl, int id); //Reset velocity to 0
void extension(Dynamixel2Arduino dxl, int id, int speed); //leg extension
void retraction(Dynamixel2Arduino dxl, int id, int speed); //leg retraction
void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction, int speed); //Completes a full step forward or backwards
void encoderPosition(Dynamixel2Arduino dxl, int id);


Servo servo_test = Servo();
int angle = 0;

const uint8_t DXL_ID2 = 2;
const uint8_t DXL_ID9 = 9;
const uint8_t DXL_ID23 = 23;
const uint8_t DXL_ID3 = 3;

const float DXL_PROTOCOL_VERSION = 2.0;
int motor_position;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

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

  //Steppers
  pinMode(BDPIN_DXL_PWR_EN, OUTPUT);
  digitalWrite(BDPIN_DXL_PWR_EN, HIGH);

  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID2);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID2);
  dxl.setOperatingMode(DXL_ID2, OP_POSITION);
  dxl.torqueOn(DXL_ID2);

  dxl.setGoalPosition(DXL_ID2, 0);

  delay(5000);
  dxl.torqueOff(DXL_ID2);
  dxl.setOperatingMode(DXL_ID2, OP_VELOCITY);
  dxl.torqueOn(DXL_ID2);
}

void loop() {
  encoderPosition(dxl, DXL_ID2);
  if (angle != 180)
  {
      angle++;
    
  }
  tests_moteurs(servo_test, angle);

  DEBUG_SERIAL.println(mode);
  DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID2));
  if(mode == WAIT_MODE){
    extension(dxl,DXL_ID2,-10);
    DEBUG_SERIAL.println(mode);
  }

  if(mode == EXTENSION_MODE && motor_position>=2048){
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID2));
    finish(dxl,DXL_ID2);
    delay(500);
    retraction(dxl, DXL_ID2,-10);
  }
  if(mode == RETRACTION_MODE && motor_position<2048){
    DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID));
    finish(dxl,DXL_ID2);
    delay(500);
    extension(dxl, DXL_ID2,-10);
  }
}

void tests_moteurs(Servo servo, int angle)
{
  servo.write(angle);
  //DEBUG_SERIAL.println(servo.read());
}

void finish(Dynamixel2Arduino dxl, int id){
  dxl.setGoalVelocity(id,0);
  mode = WAIT_MODE;
}

void extension(Dynamixel2Arduino dxl, int id, int speed){         //speed in percentage
  dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
  mode = EXTENSION_MODE;
  
}

void retraction(Dynamixel2Arduino dxl, int id, int speed){         //speed in percentage
  dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
  mode = RETRACTION_MODE;
}

void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction, int speed){
  if(direction<0){
    speed = speed*-1;
  }

  
  dxl.setGoalVelocity(idFL,speed,UNIT_PERCENT);
  do{
    encoderPosition(dxl,idFL);
  }while(motor_position<2048);
  dxl.setGoalVelocity(idFL,0);

  dxl.setGoalVelocity(idRR,-speed,UNIT_PERCENT);
  do{
    encoderPosition(dxl,idRR);
  }while(motor_position<2048);
  dxl.setGoalVelocity(idRR,0);

  dxl.setGoalVelocity(idFR,-speed,UNIT_PERCENT);
  do{
    encoderPosition(dxl,idFR);
  }while(motor_position<2048);
  dxl.setGoalVelocity(idFR,0);

  dxl.setGoalVelocity(idRL,speed,UNIT_PERCENT);
  do{
    encoderPosition(dxl,idRL);
  }while(motor_position<2048);
  dxl.setGoalVelocity(idRL,0);

  delay(500);
  dxl.setGoalVelocity(idFL,speed,UNIT_PERCENT);
  dxl.setGoalVelocity(idRR,-speed,UNIT_PERCENT);
  dxl.setGoalVelocity(idFR,-speed,UNIT_PERCENT);
  dxl.setGoalVelocity(idRL,speed,UNIT_PERCENT);

  do{
    encoderPosition(dxl,idFL);
  }while(motor_position>2048);
  
  dxl.setGoalVelocity(idFL,0);
  dxl.setGoalVelocity(idRR,0);
  dxl.setGoalVelocity(idFR,0);
  dxl.setGoalVelocity(idRL,0);
}

void encoderPosition(Dynamixel2Arduino dxl, int id){
  motor_position = dxl.getPresentPosition(id);
  if(motor_position<0){
    motor_position = motor_position*-1;
  }
  motor_position = motor_position % 4096;
}
