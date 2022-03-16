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

#define PIN_FRONT_LEFT_SERVO_PWM 11
#define PIN_FRONT_RIGHT_SERVO_PWM 10
#define PIN_REAR_LEFT_SERVO_PWM 9
#define PIN_REAR_RIGHT_SERVO_PWM 6

//Movement modes
#define WAIT_MODE 0
#define EXTENSION_MODE 1
#define RETRACTION_MODE 2
uint8_t mode = WAIT_MODE;


Servo servo_test = Servo();
int angle = 0;

#define DXL_ID_REAR_LEFT 2
#define DXL_ID_REAR_RIGHT 9
#define DXL_ID_FRONT_LEFT 23
#define DXL_ID_FRONT_RIGHT 3

#define FRONT_LEFT_RETRACTED 1463
#define FRONT_RIGHT_RETRACTED 2806
#define REAR_LEFT_RETRACTED 0
#define REAR_RIGHT_RETRACTED 1123

#define FRONT_LEFT_EXTENDED 3348
#define FRONT_RIGHT_EXTENDED 826
#define REAR_LEFT_EXTENDED 0
#define REAR_RIGHT_EXTENDED 3288

#define FRONT_LEFT_RAISED 2422
#define FRONT_RIGHT_RAISED 1688
#define REAR_LEFT_RAISED 0
#define REAR_RIGHT_RAISED 2257



#define RETRACTED 0
#define EXTENDED 1
#define RAISED 2

int frontLeftMode;
int frontRightMode;
int rearLeftMode;
int rearRightMode;

const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Servo servomotors[4] = {};

#include "functions.h"

void setup() {
  //Associate pins
  pinMode(PIN_FRONT_LEFT_SERVO_PWM, INPUT);
  pinMode(PIN_FRONT_RIGHT_SERVO_PWM,INPUT);
  pinMode(PIN_REAR_LEFT_SERVO_PWM, INPUT);
  pinMode(PIN_REAR_RIGHT_SERVO_PWM, INPUT);

  
  //Servomotors
  

  servomotors[FRONT_LEFT_SERVO].attach(PIN_FRONT_LEFT_SERVO_PWM);
  servomotors[FRONT_RIGHT_SERVO].attach(PIN_FRONT_RIGHT_SERVO_PWM);
  servomotors[REAR_LEFT_SERVO].attach(PIN_REAR_LEFT_SERVO_PWM);
  servomotors[REAR_RIGHT_SERVO].attach(PIN_REAR_RIGHT_SERVO_PWM);

  //Steppers
  pinMode(BDPIN_DXL_PWR_EN, OUTPUT);
  digitalWrite(BDPIN_DXL_PWR_EN, HIGH);

  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(57600);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID_FRONT_LEFT);
  dxl.ping(DXL_ID_FRONT_RIGHT);
  dxl.ping(DXL_ID_REAR_LEFT);
  dxl.ping(DXL_ID_REAR_RIGHT);

  // Turn off torque when configuring items in EEPROM area
  /*dxl.torqueOff(DXL_ID2);
  dxl.setOperatingMode(DXL_ID2, OP_POSITION);
  dxl.torqueOn(DXL_ID2);
  dxl.setGoalPosition(DXL_ID2, 0);*/

  dxl.torqueOff(DXL_ID_FRONT_LEFT);
  dxl.setOperatingMode(DXL_ID_FRONT_LEFT, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_FRONT_LEFT);

  dxl.torqueOff(DXL_ID_FRONT_RIGHT);
  dxl.setOperatingMode(DXL_ID_FRONT_RIGHT, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_FRONT_RIGHT);
  
  dxl.torqueOff(DXL_ID_REAR_LEFT);
  dxl.setOperatingMode(DXL_ID_REAR_LEFT, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_REAR_LEFT);
  
  dxl.torqueOff(DXL_ID_REAR_RIGHT);
  dxl.setOperatingMode(DXL_ID_REAR_RIGHT, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_REAR_RIGHT);

  DEBUG_SERIAL.println("Extension depart");
  extensionRearRight(dxl, DXL_ID_REAR_RIGHT, 10);
  DEBUG_SERIAL.println("Extension complete");
  //adjustPosition(dxl, DXL_ID_FRONT_LEFT);
  retractionRearRight(dxl, DXL_ID_REAR_RIGHT, 10);
}

void loop() {
  DEBUG_SERIAL.println("WTF");
}
