#include <Servo.h>
#include <Dynamixel2Arduino.h>

int motor_position;
//Useful functions for movement sequence
void tests_moteurs(Servo servo, int angle);
void finish(Dynamixel2Arduino dxl, int id); //Reset velocity to 0
void extension(Dynamixel2Arduino dxl, int id, int speed); //leg extension
void retraction(Dynamixel2Arduino dxl, int id, int speed); //leg retraction
void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction, int speed); //Completes a full step forward or backwards
void encoderPosition(Dynamixel2Arduino dxl, int id);
void setServoPosition(Servo servo, int angle);
int getServoPosition(Servo servo);


void finish(Dynamixel2Arduino dxl, int id){
  dxl.setGoalVelocity(id,0);
}

void extension(Dynamixel2Arduino dxl, int id, int speed){         //speed in percentage
  dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
}

void retraction(Dynamixel2Arduino dxl, int id, int speed){         //speed in percentage
  dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
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

void setServoPosition(Servo servo, int angle){
  servo.write(angle);

  delay(200);
}

int getServoPosition(Servo servo){
  return servo.read();
}
