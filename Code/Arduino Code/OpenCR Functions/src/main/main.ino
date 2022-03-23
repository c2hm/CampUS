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

#define PIN_FRONT_LEFT_SERVO_PWM 5
#define PIN_FRONT_RIGHT_SERVO_PWM 9
#define PIN_REAR_LEFT_SERVO_PWM 3
#define PIN_REAR_RIGHT_SERVO_PWM 6

//Movement modes
#define WAIT_MODE 0
#define EXTENSION_MODE 1
#define RETRACTION_MODE 2
uint8_t mode = WAIT_MODE;


Servo servo_test = Servo();
int angle = 0;

#define DXL_ID_REAR_LEFT 4
#define DXL_ID_REAR_RIGHT 9
#define DXL_ID_FRONT_LEFT 23
#define DXL_ID_FRONT_RIGHT 3

#define FRONT_LEFT_RETRACTED 873
#define FRONT_RIGHT_RETRACTED 3256
#define REAR_LEFT_RETRACTED 0
#define REAR_RIGHT_RETRACTED 1010

#define FRONT_LEFT_EXTENDED 3459
#define FRONT_RIGHT_EXTENDED 626
#define REAR_LEFT_EXTENDED 0
#define REAR_RIGHT_EXTENDED 3358

#define FRONT_LEFT_RAISED 2422
#define FRONT_RIGHT_RAISED 1688
#define REAR_LEFT_RAISED 0
#define REAR_RIGHT_RAISED 2257

#define FRONT_LEFT_LOW 4200
#define FRONT_RIGHT_LOW 1688
#define REAR_LEFT_LOW 0
#define REAR_RIGHT_LOW 2257

#define PIN_FL_ELECTRO 11
#define PIN_FR_ELECTRO 10
#define PIN_RL_ELECTRO 13
#define PIN_RR_ELECTRO 12

#define RETRACTED 0
#define EXTENDED 1
#define RAISED 2

int nbTurnsFront;
int nbTurnsRear;
int frontLeftMode;
int frontRightMode;
int rearLeftMode;
int rearRightMode;

const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Servo servomotors[4] = {};

#include "functions.h"

void setup() {

  //Associate magnets
  pinMode(PIN_FL_ELECTRO, OUTPUT);
  pinMode(PIN_FR_ELECTRO,OUTPUT);
  pinMode(PIN_RL_ELECTRO, OUTPUT);
  pinMode(PIN_RL_ELECTRO, OUTPUT);

  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);


  digitalWrite(13,HIGH);

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
  dxl.setOperatingMode(DXL_ID_FRONT_LEFT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_FRONT_LEFT);

  dxl.torqueOff(DXL_ID_FRONT_RIGHT);
  dxl.setOperatingMode(DXL_ID_FRONT_RIGHT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_FRONT_RIGHT);
  
  dxl.torqueOff(DXL_ID_REAR_LEFT);
  dxl.setOperatingMode(DXL_ID_REAR_LEFT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_REAR_LEFT);
  
  dxl.torqueOff(DXL_ID_REAR_RIGHT);
  dxl.setOperatingMode(DXL_ID_REAR_RIGHT, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID_REAR_RIGHT);


  nbTurnsFront=0;
  nbTurnsRear=0;
}

void loop() {
  
      
      /*//Front left magnet off
      extensionFrontLeft(dxl,DXL_ID_FRONT_LEFT, 1);
      delay(1000);
      //Front left magnet on

      //Front right magnet off
      extensionFrontRight(dxl,DXL_ID_FRONT_RIGHT, 1);
      nbTurnsFront++;
      delay(1000);
      //Front right magnet on

      retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT, 1);
      retractionFrontRight(dxl,DXL_ID_FRONT_RIGHT, 1);
      extensionRearLeft(dxl,DXL_ID_REAR_LEFT, 1);
      extensionRearRight(dxl,DXL_ID_REAR_RIGHT, 1);

      nbTurnsRear++;
      delay(1000);
      //Rear left magnet off
      retractionRearLeft(dxl,DXL_ID_REAR_LEFT, 1);
      delay(1000);
      //Rear left magnet on
      
      //Rear right magnet off
      retractionRearRight(dxl, DXL_ID_REAR_RIGHT, 1);
      delay(1000);
      //Rear right magnet on*/

  //robotStep(dxl,DXL_ID_FRONT_LEFT,DXL_ID_FRONT_RIGHT,DXL_ID_REAR_LEFT,DXL_ID_REAR_RIGHT,1);
}
