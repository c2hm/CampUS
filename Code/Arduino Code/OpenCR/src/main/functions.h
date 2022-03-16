#include <Servo.h>
#include <Dynamixel2Arduino.h>

int motor_position;
//Useful functions for movement sequence
void finish(Dynamixel2Arduino dxl, int id); //Complete

void extensionFrontLeft(Dynamixel2Arduino dxl, int id, int speed);
void extensionFrontRight(Dynamixel2Arduino dxl, int id, int speed);
void extensionRearLeft(Dynamixel2Arduino dxl, int id, int speed);
void extensionRearRight(Dynamixel2Arduino dxl, int id, int speed);

void retractionFrontLeft(Dynamixel2Arduino dxl, int id, int speed);
void retractionFrontRight(Dynamixel2Arduino dxl, int id, int speed);
void retractionRearLeft(Dynamixel2Arduino dxl, int id, int speed);
void retractionRearRight(Dynamixel2Arduino dxl, int id, int speed);

void raiseLeg(Dynamixel2Arduino dxl, int id, int speed, int positionRaised);
void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction, int speed);
void encoderPosition(Dynamixel2Arduino dxl, int id);
int encoderCount(Dynamixel2Arduino dxl, int id);
void findLegMode(Dynamixel2Arduino dxl, int id);
void adjustPosition(Dynamixel2Arduino dxl, int id);

//void controlMagnet(bool switch, int magnet);
//void home();
//activation modes for magnets (on/off) and legs' current position (extended, retracted, raised)
//void resetEncoder(int id, Dynamixel2Arduino dxl);


void setServoPosition(Servo servo, int angle);
int getServoPosition(Servo servo);

/*
 * Sets stepper speed to 0
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void finish(Dynamixel2Arduino dxl, int id){
  dxl.setGoalVelocity(id,0);
}

/*
 * Fully extends front left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionFrontLeft(Dynamixel2Arduino dxl, int id, int speed){
  dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
  do{encoderPosition(dxl,id);}while(motor_position<FRONT_LEFT_EXTENDED);
  finish(dxl,id);
  frontLeftMode = EXTENDED;
}

/*
 * Fully extends front right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionFrontRight(Dynamixel2Arduino dxl, int id, int speed){
  dxl.setGoalVelocity(id,-speed,UNIT_PERCENT);
  do{encoderPosition(dxl,id);}while(motor_position<FRONT_RIGHT_EXTENDED || motor_position> FRONT_RIGHT_RETRACTED);
  finish(dxl,id);
  frontRightMode = EXTENDED;
}

/*
 * Fully extends rear left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionRearLeft(Dynamixel2Arduino dxl, int id, int speed){
  dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
  do{encoderPosition(dxl,id);}while(motor_position<REAR_LEFT_EXTENDED);
  finish(dxl,id);
  rearLeftMode = EXTENDED;
}

/*
 * Fully extends rear right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionRearRight(Dynamixel2Arduino dxl, int id, int speed){
  dxl.setGoalVelocity(id,-speed,UNIT_PERCENT);
  do{encoderPosition(dxl,id);}while(motor_position>REAR_RIGHT_EXTENDED||motor_position<REAR_RIGHT_EXTENDED);
  finish(dxl,id);
  rearRightMode = EXTENDED;
}


/*
 * Fully retracts front left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void retractionFrontLeft(Dynamixel2Arduino dxl, int id, int speed){
  if(frontLeftMode==RAISED){
    dxl.torqueOff(id);
    dxl.setOperatingMode(id,OP_POSITION);
    dxl.torqueOn(id);

    encoderPosition(dxl, id);
    int difference = motor_position - FRONT_LEFT_RETRACTED;
    dxl.setGoalPosition(id, dxl.getPresentPosition(id)-difference);

    dxl.torqueOff(id);
    dxl.setOperatingMode(id,OP_VELOCITY);
    dxl.torqueOn(id);
  }
  else{
    dxl.setGoalVelocity(id,speed,UNIT_PERCENT);
    do{encoderPosition(dxl,id);}while(motor_position<FRONT_LEFT_RETRACTED||motor_position >FRONT_LEFT_EXTENDED);
  
    finish(dxl,id);
  }
  
  frontLeftMode = RETRACTED;
}

/*
 * Fully retracts front right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void retractionFrontRight(Dynamixel2Arduino dxl, int id, int speed){
  if(frontLeftMode==RAISED){
    dxl.torqueOff(id);
    dxl.setOperatingMode(id,OP_POSITION);
    dxl.torqueOn(id);

    encoderPosition(dxl, id);
    int difference = motor_position - FRONT_RIGHT_RETRACTED;
    dxl.setGoalPosition(id, dxl.getPresentPosition(id)-difference);

    dxl.torqueOff(id);
    dxl.setOperatingMode(id,OP_VELOCITY);
    dxl.torqueOn(id);
  }
  else{
    dxl.setGoalVelocity(id,-speed,UNIT_PERCENT);
    do{encoderPosition(dxl,id);}while(motor_position<FRONT_RIGHT_RETRACTED||motor_position >FRONT_RIGHT_EXTENDED);
  
    finish(dxl,id);
  }
  
  frontRightMode = RETRACTED;
}



/*
 * Fully retracts rear right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void retractionRearRight(Dynamixel2Arduino dxl, int id, int speed){
    dxl.setGoalVelocity(id,-speed,UNIT_PERCENT);
    do{encoderPosition(dxl,id);}while(motor_position>REAR_RIGHT_RETRACTED);
  
    finish(dxl,id);
  
  rearRightMode = RETRACTED;
}

/*
 * Fully raises front left leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseFrontLeft(Dynamixel2Arduino dxl, int id){
      encoderPosition(dxl, id);
      
      int difference = motor_position-FRONT_LEFT_RAISED;
      
      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_POSITION);
      dxl.torqueOn(id);

      dxl.setGoalPosition(id, dxl.getPresentPosition(id)-difference);

      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_VELOCITY);
      dxl.torqueOn(id);

  frontLeftMode = RAISED;
}

/*
 * Fully raises front right leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseFrontRight(Dynamixel2Arduino dxl, int id){
      encoderPosition(dxl, id);
      
      int difference = motor_position-FRONT_RIGHT_RAISED;
      
      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_POSITION);
      dxl.torqueOn(id);

      dxl.setGoalPosition(id, dxl.getPresentPosition(id)-difference);

      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_VELOCITY);
      dxl.torqueOn(id);
   frontRightMode = RAISED;
}

/*
 * Fully raises rear left leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseRearLeft(Dynamixel2Arduino dxl, int id){
      encoderPosition(dxl, id);
      
      int difference = motor_position-REAR_LEFT_RAISED;
      
      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_POSITION);
      dxl.torqueOn(id);

      dxl.setGoalPosition(id, dxl.getPresentPosition(id)-difference);

      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_VELOCITY);
      dxl.torqueOn(id);
  rearLeftMode = RAISED;
}

/*
 * Fully raises rear right leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseRearRight(Dynamixel2Arduino dxl, int id){
      encoderPosition(dxl, id);
      
      int difference = motor_position-REAR_RIGHT_RAISED;
      
      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_POSITION);
      dxl.torqueOn(id);

      dxl.setGoalPosition(id, dxl.getPresentPosition(id)-difference);

      dxl.torqueOff(id);
      dxl.setOperatingMode(id, OP_VELOCITY);
      dxl.torqueOn(id);
      
  rearRightMode = RAISED;
}
/*
 *This function completes one full robot step in the inputede direction 
 * 
 * @param dxl dynamixel object for motor control
 * @param idFL robot's front left motor id
 * @param idFR robot's front right motor id
 * @param idRL robot's rear left motor id
 * @param idRR robot's rear right motor id
 * @param direction movement direction (±1)
 * @param speed desired speed for motor movement (in percentage)
 */
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

/*
 * Reads the encoder value of selected motor to find the position in a single motor turn
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void encoderPosition(Dynamixel2Arduino dxl, int id){
  motor_position = dxl.getPresentPosition(id);
  motor_position = abs(motor_position) % 4096;
}

/*
 * Reads and returns the encoder value of selected motor
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * 
 * @return encoder value
 */
int encoderCount(Dynamixel2Arduino dxl, int id){
  return dxl.getPresentPosition(id);
}

void setServoPosition(Servo servo, int angle){
  servo.write(angle);

  delay(200);
}

int getServoPosition(Servo servo){
  return servo.read();
}




/*
 * Finds if a leg is extended, raised or retracted
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void findLegMode(Dynamixel2Arduino dxl, int id){
    encoderPosition(dxl, id);

    if(id==DXL_ID_REAR_LEFT){
      if(abs(motor_position - REAR_LEFT_RETRACTED) < abs(motor_position - REAR_LEFT_EXTENDED) && abs(motor_position - REAR_LEFT_RETRACTED) < abs(motor_position - REAR_LEFT_RAISED)){
        rearLeftMode = RETRACTED;
      }
      else if(abs(motor_position - REAR_LEFT_EXTENDED) <abs(motor_position - REAR_LEFT_RETRACTED)  && abs(motor_position - REAR_LEFT_EXTENDED) < abs(motor_position - REAR_LEFT_RAISED)){
        rearLeftMode = EXTENDED;
      }
      else if(abs(motor_position - REAR_LEFT_RAISED) <abs(motor_position - REAR_LEFT_RETRACTED)  && abs(motor_position - REAR_LEFT_RAISED) < abs(motor_position - REAR_LEFT_EXTENDED)){
        rearLeftMode = RAISED;
      }
    }
    else if(id==DXL_ID_REAR_RIGHT){
      if(abs(motor_position - REAR_RIGHT_RETRACTED) < abs(motor_position - REAR_RIGHT_EXTENDED) && abs(motor_position - REAR_RIGHT_RETRACTED) < abs(motor_position - REAR_RIGHT_RAISED)){
        rearRightMode = RETRACTED;
      }
      else if(abs(motor_position - REAR_RIGHT_EXTENDED) <abs(motor_position - REAR_RIGHT_RETRACTED)  && abs(motor_position - REAR_RIGHT_EXTENDED) < abs(motor_position - REAR_RIGHT_RAISED)){
        rearRightMode = EXTENDED;
      }
      else if(abs(motor_position - REAR_RIGHT_RAISED) <abs(motor_position - REAR_RIGHT_RETRACTED)  && abs(motor_position - REAR_RIGHT_RAISED) < abs(motor_position - REAR_RIGHT_EXTENDED)){
        rearRightMode = RAISED;
      }
    }
    else if(id==DXL_ID_FRONT_LEFT){
      if(abs(motor_position - FRONT_LEFT_RETRACTED) < abs(motor_position - FRONT_LEFT_EXTENDED) && abs(motor_position - FRONT_LEFT_RETRACTED) < abs(motor_position - FRONT_LEFT_RAISED)){
        frontLeftMode = RETRACTED;
      }
      else if(abs(motor_position -FRONT_LEFT_EXTENDED) <abs(motor_position - FRONT_LEFT_RETRACTED)  && abs(motor_position -FRONT_LEFT_EXTENDED) < abs(motor_position - FRONT_LEFT_RAISED)){
        frontLeftMode = EXTENDED;
      }
      else if(abs(motor_position - FRONT_LEFT_RAISED) <abs(motor_position - FRONT_LEFT_RETRACTED)  && abs(motor_position - FRONT_LEFT_RAISED) < abs(motor_position - FRONT_LEFT_EXTENDED)){
        frontLeftMode = RAISED;
      }
    }
    else if(id==DXL_ID_FRONT_RIGHT){
      if(abs(motor_position - FRONT_RIGHT_RETRACTED) < abs(motor_position - FRONT_RIGHT_EXTENDED) && abs(motor_position - FRONT_RIGHT_RETRACTED) < abs(motor_position - FRONT_RIGHT_RAISED)){
        frontRightMode = RETRACTED;
      }
      else if(abs(motor_position - FRONT_RIGHT_EXTENDED) <abs(motor_position - FRONT_RIGHT_RETRACTED)  && abs(motor_position - FRONT_RIGHT_EXTENDED) < abs(motor_position - FRONT_RIGHT_RAISED)){
        frontRightMode = EXTENDED;
      }
      else if(abs(motor_position - FRONT_RIGHT_RAISED) <abs(motor_position - FRONT_RIGHT_RETRACTED)  && abs(motor_position - FRONT_RIGHT_RAISED) < abs(motor_position - FRONT_RIGHT_EXTENDED)){
        frontRightMode = RAISED;
      }
    }

}

/*
 * Adjusts the selected leg's position to match a mode (extended, retracted, raised)
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void adjustPosition(Dynamixel2Arduino dxl, int id){
  
  int difference;
  encoderPosition(dxl,id);
  
  dxl.torqueOff(id);
  dxl.setOperatingMode(id, OP_POSITION);
  dxl.torqueOn(id);
  
  switch(id){
    
    case DXL_ID_FRONT_LEFT:
      DEBUG_SERIAL.println("Bon ID trouvé");
      
      switch(frontLeftMode){
          case EXTENDED:
            DEBUG_SERIAL.println("Bon mode trouvé");
            difference = motor_position-FRONT_LEFT_EXTENDED;
            DEBUG_SERIAL.print("Différence: ");
            DEBUG_SERIAL.println(difference);
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
          case RETRACTED:
            difference = motor_position-FRONT_LEFT_RETRACTED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
           case RAISED:
            difference = motor_position-FRONT_LEFT_RAISED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
           default:
            break;
      }
      break;

    case DXL_ID_FRONT_RIGHT:
      switch(frontRightMode){
          case EXTENDED:
            difference = motor_position-FRONT_RIGHT_EXTENDED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
          case RETRACTED:
            difference = motor_position-FRONT_RIGHT_RETRACTED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
           case RAISED:
            difference = motor_position-FRONT_RIGHT_RAISED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
           default:
            break;
      }
      break;

      case DXL_ID_REAR_LEFT:
      switch(rearLeftMode){
          case EXTENDED:
            difference = motor_position-REAR_LEFT_EXTENDED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
          case RETRACTED:
            difference = motor_position-REAR_LEFT_RETRACTED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
           case RAISED:
            difference = motor_position-REAR_LEFT_RAISED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
           default:
            break;
      }
      break;

      case DXL_ID_REAR_RIGHT:
      switch(rearRightMode){
          case EXTENDED:
            difference = motor_position-REAR_RIGHT_EXTENDED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
          case RETRACTED:
            difference = motor_position-REAR_RIGHT_RETRACTED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
            
          case RAISED:
            difference = motor_position-REAR_RIGHT_RAISED;
            dxl.setGoalPosition(id,dxl.getPresentPosition(id)-difference);
            break;
           default:
            break;
      }
      
      
      break;
  }
  dxl.torqueOff(id);
  dxl.setOperatingMode(id, OP_VELOCITY);
  dxl.torqueOn(id);
}
