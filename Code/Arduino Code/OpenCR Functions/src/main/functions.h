#include <Servo.h>
#include <Dynamixel2Arduino.h>

int motor_position;
//Useful functions for movement sequence
void extensionFrontLeft(Dynamixel2Arduino dxl, int id, int direction);
void extensionFrontRight(Dynamixel2Arduino dxl, int id, int direction);
void extensionRearLeft(Dynamixel2Arduino dxl, int id, int direction);
void extensionRearRight(Dynamixel2Arduino dxl, int id, int direction);

void retractionFrontLeft(Dynamixel2Arduino dxl, int id, int direction);
void retractionFrontRight(Dynamixel2Arduino dxl, int id, int direction);
void retractionRearLeft(Dynamixel2Arduino dxl, int id, int direction);
void retractionRearRight(Dynamixel2Arduino dxl, int id, int direction);

void raiseFrontLeft(Dynamixel2Arduino dxl, int id, int direction);
void raiseFrontRight(Dynamixel2Arduino dxl, int id, int direction);
void raiseRearLeft(Dynamixel2Arduino dxl, int id, int direction);
void raiseRearRight(Dynamixel2Arduino dxl, int id, int direction);

void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction, int speed);
void encoderPosition(Dynamixel2Arduino dxl, int id);
int encoderCount(Dynamixel2Arduino dxl, int id);
void findLegMode(Dynamixel2Arduino dxl, int id);
void adjustPosition(Dynamixel2Arduino dxl, int id);

void controlMagnet(bool power, int magnet);
void home(Servo servo[]);

//activation modes for magnets (on/off) and legs' current position (extended, retracted, raised)
//void resetEncoder(int id, Dynamixel2Arduino dxl);


void setServoPosition(Servo servo, int angle);
int getServoPosition(Servo servo);

/*
 * Fully extends front left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionFrontLeft(Dynamixel2Arduino dxl, int id, int direction){
  if(direction>=0){
    dxl.setGoalPosition(id, nbTurnsFront*4096+FRONT_LEFT_EXTENDED);
  }
  else{
    dxl.setGoalPosition(id, nbTurnsFront*4096+FRONT_LEFT_EXTENDED);
  }
  
  frontLeftMode = EXTENDED;
}

/*
 * Fully extends front right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionFrontRight(Dynamixel2Arduino dxl, int id, int direction){
  if(direction>=0){
    dxl.setGoalPosition(id, -nbTurnsFront*4096+FRONT_RIGHT_EXTENDED);
  }
  else{
    dxl.setGoalPosition(id, -nbTurnsFront*4096-FRONT_RIGHT_EXTENDED);
  }
  frontRightMode = EXTENDED;
}

/*
 * Fully extends rear left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionRearLeft(Dynamixel2Arduino dxl, int id, int direction){
  if(direction>=0){
    dxl.setGoalPosition(id, nbTurnsRear*4096+REAR_LEFT_EXTENDED);
  }
  else{
    dxl.setGoalPosition(id, nbTurnsRear*4096-REAR_LEFT_EXTENDED);
  }
  rearLeftMode = EXTENDED;
}

/*
 * Fully extends rear right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void extensionRearRight(Dynamixel2Arduino dxl, int id, int direction){
  if(direction>=0){
    dxl.setGoalPosition(id, -nbTurnsRear*4096-(4096-REAR_RIGHT_EXTENDED));
  }
  else{
    dxl.setGoalPosition(id, -nbTurnsRear*4096+REAR_RIGHT_EXTENDED);
  }
  rearRightMode = EXTENDED;
}


/*
 * Fully retracts front left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void retractionFrontLeft(Dynamixel2Arduino dxl, int id, int direction){
  if(nbTurnsFront==0){
    dxl.setGoalPosition(id, FRONT_LEFT_RETRACTED);
  }
  else if(direction>=0){
    dxl.setGoalPosition(id, nbTurnsFront*4096+FRONT_LEFT_RETRACTED);
  }
  else{
    dxl.setGoalPosition(id, nbTurnsFront*4096-FRONT_LEFT_RETRACTED);
  }
  
  frontLeftMode = RETRACTED;
}

/*
 * Fully retracts front right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void retractionFrontRight(Dynamixel2Arduino dxl, int id, int direction){
  if(nbTurnsFront==0){
    dxl.setGoalPosition(id, FRONT_RIGHT_RETRACTED);
  }
  else if(direction>=0){
    dxl.setGoalPosition(id, -nbTurnsFront*4096+FRONT_RIGHT_RETRACTED);
  }
  else{
    dxl.setGoalPosition(id, -nbTurnsFront*4096-FRONT_RIGHT_RETRACTED);
  }
  
  frontRightMode = RETRACTED;
}


/*
 * Fully retracts rear left leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void retractionRearLeft(Dynamixel2Arduino dxl, int id, int direction){
  if(nbTurnsRear==0){
    dxl.setGoalPosition(id, REAR_LEFT_RETRACTED);
  }
  else if(direction>=0){
    dxl.setGoalPosition(id, nbTurnsRear*4096+REAR_LEFT_RETRACTED);
  }
  else{
    dxl.setGoalPosition(id, nbTurnsRear*4096-REAR_LEFT_RETRACTED);
  }
  
  rearLeftMode = RETRACTED;
}

/*
 * Fully retracts rear right leg
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 */
void retractionRearRight(Dynamixel2Arduino dxl, int id, int direction){
  if(nbTurnsRear==0){
    dxl.setGoalPosition(id, REAR_RIGHT_RETRACTED);
  }
  else if(direction>=0){
    dxl.setGoalPosition(id, -nbTurnsRear*4096-REAR_RIGHT_RETRACTED);
  }
  else{
    dxl.setGoalPosition(id, -nbTurnsRear*4096+REAR_RIGHT_RETRACTED);
  }
  
  rearRightMode = RETRACTED;
}

/*
 * Fully raises front left leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseFrontLeft(Dynamixel2Arduino dxl, int id, int direction){
    if(direction>=0){
    dxl.setGoalPosition(id, nbTurnsFront*4096+FRONT_LEFT_RAISED);
  }
  else{
    dxl.setGoalPosition(id, nbTurnsFront*4096-FRONT_LEFT_RAISED);
  }
    frontLeftMode = RAISED;
}

/*
 * Fully raises front right leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseFrontRight(Dynamixel2Arduino dxl, int id, int direction){
   if(direction>=0){
    dxl.setGoalPosition(id, -nbTurnsFront*4096+FRONT_RIGHT_RAISED);
  }
  else{
    dxl.setGoalPosition(id, -nbTurnsFront*4096-FRONT_RIGHT_RAISED);
  }
   frontRightMode = RAISED;
}

/*
 * Fully raises rear left leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseRearLeft(Dynamixel2Arduino dxl, int id, int direction){
  if(direction>=0){
    dxl.setGoalPosition(id, nbTurnsRear*4096+REAR_LEFT_RAISED);
  }
  else{
   dxl.setGoalPosition(id, nbTurnsRear*4096-REAR_LEFT_RAISED);
  }
  rearLeftMode = RAISED;
}

/*
 * Fully raises rear right leg 
 * 
 * @param dxl dynamixel object for motor control
 * @param id motor's id
 * @param speed wanted leg's speed (in percentage)
 */
void raiseRearRight(Dynamixel2Arduino dxl, int id, int direction){
  if(direction>=0){
   dxl.setGoalPosition(id, -nbTurnsRear*4096-REAR_RIGHT_RAISED);
  }
  else{
    dxl.setGoalPosition(id, -nbTurnsRear*4096+REAR_RIGHT_RAISED);
  }
  
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
void robotStep(Dynamixel2Arduino dxl, int idFL,int idFR,int idRL,int idRR,int direction){
    if(direction >=0){
      //Rear left magnet off
      retractionRearLeft(dxl,idRL, direction);
      delay(1000);
      //Rear left magnet on
      
      //Rear right magnet off
      retractionRearRight(dxl, idRR, direction);
      delay(1000);
      //Rear right magnet on
      
      //Front left magnet off
      extensionFrontLeft(dxl,idFL, direction);
      delay(1000);
      //Front left magnet on

      //Front right magnet off
      extensionFrontRight(dxl,idFR, direction);
      nbTurnsFront++;
      delay(1000);
      //Front right magnet on

      retractionFrontLeft(dxl,idFL, direction);
      retractionFrontRight(dxl,idFR, direction);
      extensionRearLeft(dxl,idRL, direction);
      extensionRearRight(dxl,idRR, direction);

      nbTurnsRear++;
      delay(1000);
      
    }
    else{
      
    }
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

void home(Servo servomotors[]){      //angle servo[19(126deg),2(117deg),4(74deg),20(71deg)]
/*servomotors[FRONT_LEFT_SERVO];
servomotors[FRONT_RIGHT_SERVO];
servomotors[REAR_LEFT_SERVO];
servomotors[REAR_RIGHT_SERVO];*/
}

void controlMagnet(bool power, int pinmagnet){
  pinMode(pinmagnet, OUTPUT);

  if(power = 1){  
    digitalWrite(pinmagnet, HIGH); 
  }
  
  if(power = 0){  
    digitalWrite(pinmagnet, LOW); 
  }  
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
}
