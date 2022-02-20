/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <Dynamixel2Arduino.h>

// Please modify it to suit your hardware.
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560) // When using DynamixelShield
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DXL_SERIAL   Serial
  #define DEBUG_SERIAL soft_serial
  const uint8_t DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN
#elif defined(ARDUINO_SAM_DUE) // When using DynamixelShield
  #define DXL_SERIAL   Serial
  #define DEBUG_SERIAL SerialUSB
  const uint8_t DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN
#elif defined(ARDUINO_SAM_ZERO) // When using DynamixelShield
  #define DXL_SERIAL   Serial1
  #define DEBUG_SERIAL SerialUSB
  const uint8_t DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN
#elif defined(ARDUINO_OpenCM904) // When using official ROBOTIS board with DXL circuit.
  #define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
  #define DEBUG_SERIAL Serial
  const uint8_t DXL_DIR_PIN = 22; //OpenCM9.04 EXP Board's DIR PIN. (28 for the DXL port on the OpenCM 9.04 board)
#elif defined(ARDUINO_OpenCR) // When using official ROBOTIS board with DXL circuit.
  // For OpenCR, there is a DXL Power Enable pin, so you must initialize and control it.
  // Reference link : https://github.com/ROBOTIS-GIT/OpenCR/blob/master/arduino/opencr_arduino/opencr/libraries/DynamixelSDK/src/dynamixel_sdk/port_handler_arduino.cpp#L78
  #define DXL_SERIAL   Serial3
  #define DEBUG_SERIAL Serial
  const uint8_t DXL_DIR_PIN = 84; // OpenCR Board's DIR PIN.    
#else // Other boards when using DynamixelShield
  #define DXL_SERIAL   Serial1
  #define DEBUG_SERIAL Serial
  const uint8_t DXL_DIR_PIN = 2; // DYNAMIXEL Shield DIR PIN
#endif
 

const uint8_t DXL_ID9 = 9;
const uint8_t DXL_ID2 = 2;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl9(DXL_SERIAL, DXL_DIR_PIN);
Dynamixel2Arduino dxl2(DXL_SERIAL, DXL_DIR_PIN);

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
    pinMode(BDPIN_DXL_PWR_EN, OUTPUT);
    digitalWrite(BDPIN_DXL_PWR_EN, HIGH);
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  while(!DEBUG_SERIAL);

  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl9.begin(57600);
  dxl2.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl9.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl2.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl9.ping(DXL_ID9);
  dxl2.ping(DXL_ID2);

  // Turn off torque when configuring items in EEPROM area
  dxl9.torqueOff(DXL_ID9);
  dxl9.setOperatingMode(DXL_ID9, OP_POSITION);
  dxl9.torqueOn(DXL_ID9);

  dxl2.torqueOff(DXL_ID2);
  dxl2.setOperatingMode(DXL_ID2, OP_POSITION);
  dxl2.torqueOn(DXL_ID2);
  
  // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
  dxl9.writeControlTableItem(PROFILE_VELOCITY, DXL_ID9, 30);
  dxl2.writeControlTableItem(PROFILE_VELOCITY, DXL_ID2, 30);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Please refer to e-Manual(http://emanual.robotis.com/docs/en/parts/interface/dynamixel_shield/) for available range of value. 
  // Set Goal Position in RAW value
  
  dxl9.setGoalPosition(DXL_ID9, 512);
  dxl2.setGoalPosition(DXL_ID2, 512);
  
  int i_present_position = 0;
  float f_present_position = 0.0;

  while (abs(512 - i_present_position) > 10)
  {
    f_present_position = dxl9.getPresentPosition(DXL_ID9, UNIT_DEGREE);
    i_present_position = dxl9.getPresentPosition(DXL_ID9);
    DEBUG_SERIAL.print("Present_Position(raw) : ");
    DEBUG_SERIAL.println(i_present_position);
  }
  delay(500);

  // Set Goal Position in DEGREE value
  dxl9.setGoalPosition(DXL_ID9, 5.7, UNIT_DEGREE);
  dxl2.setGoalPosition(DXL_ID2, 5.7, UNIT_DEGREE);
  
  while (abs(5.7 - f_present_position) > 2.0)
  {
    f_present_position = dxl9.getPresentPosition(DXL_ID9, UNIT_DEGREE);
    i_present_position = dxl9.getPresentPosition(DXL_ID9);
    DEBUG_SERIAL.print("Present_Position(raw) : ");
    DEBUG_SERIAL.println(i_present_position);
  }
  delay(500);
}
