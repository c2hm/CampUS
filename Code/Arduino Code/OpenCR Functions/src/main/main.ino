#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"


int angle = 0;

int nbTurnsFront;
int nbTurnsRear;

int frontLeftMode;
int frontRightMode;
int rearLeftMode;
int rearRightMode;
int objectif;
const float DXL_PROTOCOL_VERSION = 2.0;

#include "functions.h"

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Servo servomotors[4] = {};

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
  home(servomotors,dxl);
}

void loop() {
      /*extensionFrontLeft(dxl,DXL_ID_FRONT_LEFT,1);
      delay(1000);
      extensionFrontRight(dxl,DXL_ID_FRONT_RIGHT,1);
      delay(1000);
      retractionRearRight(dxl,DXL_ID_REAR_RIGHT,1);
      nbTurnsFront++;
      nbTurnsRear++;
      delay(3000);
      retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT,1);
      retractionFrontRight(dxl,DXL_ID_FRONT_RIGHT,1);
      extensionRearRight(dxl,DXL_ID_REAR_RIGHT,1);
      
      delay(2000);*/
      /*extensionFrontLeft(dxl,DXL_ID_FRONT_LEFT,1);
      retractionFrontLeft(dxl,DXL_ID_FRONT_LEFT,1);
      nbTurnsFront++;
      //Front left magnet off
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

  robotStep(dxl,DXL_ID_FRONT_LEFT,DXL_ID_FRONT_RIGHT,DXL_ID_REAR_LEFT,DXL_ID_REAR_RIGHT,1);
}
