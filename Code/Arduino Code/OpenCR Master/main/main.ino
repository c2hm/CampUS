
//https://www.instructables.com/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/

#include <Arduino.h>
#include "order.h"
#include "parameters.h"
#include "slave.h"
#include <Servo.h>
#include <Dynamixel2Arduino.h>
#include "definitions.h"
#include "functions.h"


//Prototypes
void get_messages_from_serial();
void homeMaster();
int get_param();
void auto_distance(int dist);
void auto_reverse(int dist);
void set_angle(int paramAngle);
void semi_auto_state(int state);
void servo_avant_droit(int state);
void servo_avant_gauche(int state);
void servo_arriere_droit(int state);
void servo_arriere_gauche(int state);
void moteur_avant_droit(int state);
void moteur_avant_gauche(int state);
void moteur_arriere_droit(int state);
void moteur_arriere_gauche(int state);
void electroaimant_avant_droit(int state);
void electroaimant_avant_gauche(int state);
void electroaimant_arriere_droit(int state);
void electroaimant_arriere_gauche(int state);

bool is_connected = false; ///< True if the connection with the master is available

int ERROR_PARAM = -1000;

void setup() {

  Serial.begin(9600);//Pour bluetooth deacendre a 9600, code python aussi

  // Wait until the arduino is connected to master
  while(!is_connected)
  {
    get_messages_from_serial();
  }
  init(servomotors,dxl);
}

void loop() 
{
  get_messages_from_serial();
  
}

/********************************************
 * 
 * Communication processing
 * 
 * ********************************************/
void get_messages_from_serial()
{
  if(Serial.available() > 0)
  {
    // The first byte received is the instruction
    Order order_received = read_order();

    if(order_received == HELLO)
    {
      // If the cards haven't say hello, check the connection
      if(!is_connected)
      {
        is_connected = true;
        write_order(HELLO);
      }
      else
      {
        // If we are already connected do not send "hello" to avoid infinite loop
        write_order(ALREADY_CONNECTED);
      }
    }
    else if(order_received == ALREADY_CONNECTED)
    {
      is_connected = true;
    }
    else
    {
      //Processes the order
      switch(order_received)
      {
        case HOME:
        {
          write_order(RECEIVED);
          homeMaster();
          break;
        }

        case AUTO_DISTANCE:
        {
          //reads parameter
          write_order(RECEIVED); 

          int dist = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          
          if (dist >= -1000 && dist <= 1000)
          {
            write_order(RECEIVED); 
            auto_distance(dist);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
          

          break;
        }

        case AUTO_REVERSE:
        {
          write_order(RECEIVED); 

          int dist = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          
          if (dist >= -1000 && dist <= 1000)
          {
            write_order(RECEIVED); 
            auto_reverse(dist);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
  
          break;
        }

        case ANGLE:
        {
          write_order(RECEIVED);

          //reads parameter
          angle = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial

          if (angle >= 0 && angle<=360)
          {
            write_order(RECEIVED); 
            set_angle(angle);
          }
          else 
          {
            write_order(ERROR1); 
          }
 
          break;
        }

        case SEMI_AUTO_STATE:
        {
          write_order(RECEIVED);

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial

          if (state==-1 || state==1)
          {
            write_order(RECEIVED); 
            semi_auto_state(state);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
 
          break;
        }


        case SERVO_AVANT_DROIT:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial

          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            servo_avant_droit(state);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
        
        }
        
        case SERVO_AVANT_GAUCHE:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
           if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            servo_avant_gauche(state);
          }
          else 
          {
              
            write_order(ERROR1);
          }
        
          break;
        }

        case SERVO_ARRIERE_DROIT:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            servo_arriere_droit(state);
          }
          else 
          {
            write_order(ERROR1); 
          }
        
          break;
        }

        case SERVO_ARRIERE_GAUCHE:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            servo_arriere_gauche(state);
          }
          else 
          {
            write_order(ERROR1);
          }
        
          break;
        }

        case MOTEUR_AVANT_DROIT:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            moteur_avant_droit(state);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
        
        
          break;
        }
        
        case MOTEUR_AVANT_GAUCHE:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            moteur_avant_gauche(state);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
        
        
          break;
        }

        case MOTEUR_ARRIERE_DROIT:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            moteur_arriere_droit(state);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
        
          break;
        }   

        case MOTEUR_ARRIERE_GAUCHE:
        {

          write_order(RECEIVED); 

          //reads parameter
          int state = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (state == -1 || state==1)
          {
            write_order(RECEIVED); 
            moteur_arriere_gauche(state);
          
          }
          else 
          {
            write_order(ERROR1); 
          }
        
          break;
        }

        case ELECTROAIMANT_AVANT_DROIT:
        {
          
          int state = get_param();
          Serial.flush();
          if (state==-1 || state==1)
          {
            write_order(RECEIVED);
            electroaimant_avant_droit(state);
          }
          else
          {
            write_order(ERROR1); 
          }

          break;
        }    

        case ELECTROAIMANT_AVANT_GAUCHE:
        {
          write_order(RECEIVED);
          int state = get_param();
          Serial.flush();
          if (state==-1 || state==1)
          {
            write_order(RECEIVED);
            electroaimant_avant_gauche(state);
          }
          else
          {
            write_order(ERROR1); 
          }

          break;
        }    



        case ELECTROAIMANT_ARRIERE_DROIT:
        {
          write_order(RECEIVED);
          int state = get_param();
          Serial.flush();
          if (state==-1 || state==1)
          {
            write_order(RECEIVED);
            electroaimant_arriere_droit(state);
          }
          else
          {
            write_order(ERROR1); 
          }
          
          break;
        }    


        case ELECTROAIMANT_ARRIERE_GAUCHE:
        {
          write_order(RECEIVED);
          int state = get_param();
          Serial.flush();
          if (state==-1 || state==1)
          {
            write_order(RECEIVED);
            electroaimant_arriere_gauche(state);
          }
          else
          {
            write_order(ERROR1); 
          }
          
          break;
        }    



        // Unknown order
        default:
          write_order(ERROR1);
          return;
      }
      
    }
    
  }
}

int get_param()
{
  unsigned long start_time = millis();
  while(Serial.available() < 1)
  {
    delay(0.1);
    if (millis() - start_time > 3000)
    {
        return ERROR_PARAM; 
    }
  }
  return read_i8();
}

/********************************************
 * 
 * Functions to be called when an order is processed
 * 
 * ********************************************/
void homeMaster()
{

  //homing procedure
  home(servomotors,dxl);
  write_order(FINISHED); 
}

void auto_distance(int dist)
{

  //starting procedure to move
  
  

  write_order(FINISHED); 
  
}

void auto_reverse(int dist)
{

  //stopping procedure to move in reverse

  write_order(FINISHED); 
  
}

void set_angle(int ParamAngle)
{
 //utiliser la variable angle pour bouger les servomoteurs
 
  write_order(FINISHED); 
}

void semi_auto_state(int state)
{
  robotStep(dxl,state);
  write_order(FINISHED); 
}
void servo_avant_droit(int state)
{
 controlMagnet(0,PIN_FR_ELECTRO);
 delay(200);
 if(state==1)
  {
    angle = angle - angleToAdd;
    servomotors[FRONT_RIGHT_SERVO].write(FRONT_RIGHT_SERVO_HOME + angle);
  }
  else
  {
    angle = angle + angleToAdd;
    servomotors[FRONT_RIGHT_SERVO].write(FRONT_RIGHT_SERVO_HOME + angle);
  }
  write_order(FINISHED);
}

void servo_avant_gauche(int state)
{
  controlMagnet(0,PIN_FL_ELECTRO);
  delay(200);
  if(state==1)
  {
    angle = angle - angleToAdd;
    servomotors[FRONT_LEFT_SERVO].write(FRONT_LEFT_SERVO_HOME + angle);
  }
  else
  {
    angle = angle + angleToAdd;
    servomotors[FRONT_LEFT_SERVO].write(FRONT_LEFT_SERVO_HOME + angle);
  }
   write_order(FINISHED);  
}

void servo_arriere_droit(int state)
{
  controlMagnet(0,PIN_RR_ELECTRO);
  delay(200);
  if(state==1)
  {
    angle = angle - angleToAdd;
    servomotors[REAR_RIGHT_SERVO].write(REAR_RIGHT_SERVO_HOME + angle);
  }
  else
  {
    angle = angle + angleToAdd;
    servomotors[REAR_RIGHT_SERVO].write(REAR_RIGHT_SERVO_HOME + angle);
  }
    write_order(FINISHED);
}

void servo_arriere_gauche(int state)
{
  controlMagnet(0,PIN_RL_ELECTRO);
  delay(200);
  if(state==1)
  {
    angle = angle + angleToAdd;
    servomotors[REAR_LEFT_SERVO].write(REAR_LEFT_SERVO_HOME + angle);
  }
  else
  {
    angle = angle - angleToAdd;
    servomotors[REAR_LEFT_SERVO].write(REAR_LEFT_SERVO_HOME + angle);
  }
    write_order(FINISHED);
}

void moteur_avant_droit(int state)
{
//  digitalWrite(PIN_FR_ELECTRO,LOW);
//  if(state==1)
//  {
//    if(frontRightMode == RETRACTED)
//    {
//      raiseFrontRight(dxl, DXL_ID_FRONT_RIGHT);
//      nbTurnsFront++;
//    }
//    else if(frontRightMode == RAISED)
//    {
//      extensionFrontRight(dxl, DXL_ID_FRONT_RIGHT, state);
//    }
//    else if(frontRightMode == EXTENDED)
//    {
//      retractionFrontRight(dxl, DXL_ID_FRONT_RIGHT, state);
//    }
//  }
//  else
//  {
//    if(frontRightMode == RETRACTED)
//    {
//      raiseFrontRight(dxl, DXL_ID_FRONT_RIGHT);
//      nbTurnsFront--;
//    }
//    else if(frontRightMode == RAISED)
//    {
//      extensionFrontRight(dxl, DXL_ID_FRONT_RIGHT, state);
//    }
//    else if(frontRightMode == EXTENDED)
//    {
//      retractionFrontRight(dxl, DXL_ID_FRONT_RIGHT, state);
//    }
//  }
//    write_order(FINISHED);
//}
//
//void moteur_avant_gauche(int state)
//{
//  if(state==1)
//  {
//    //avancer
//  }
//  else
//  {
//    //reculer
//  }
//    write_order(FINISHED);
}

void moteur_arriere_droit(int state)
{
  if(state==1)
  {
    //avancer
  }
  else
  {
    //reculer
  }
    write_order(FINISHED);
  
}

void moteur_arriere_gauche(int state)
{
  
  if(state==1)
  {
    //avancer
  }
  else
  {
    //reculer
  }
    write_order(FINISHED);
}

void electroaimant_avant_droit(int state)
{
  digitalWrite(PIN_FR_ELECTRO,LOW);
  if(state==1)
  {
    digitalWrite(PIN_FR_ELECTRO,HIGH);
  }
  else
  {
    digitalWrite(PIN_FR_ELECTRO,LOW);
  }
    write_order(FINISHED);
}

void electroaimant_avant_gauche(int state)
{
  digitalWrite(PIN_FL_ELECTRO,LOW);
  if(state==1)
  {
    digitalWrite(PIN_FL_ELECTRO,HIGH);
  }
  else
  {
    digitalWrite(PIN_FL_ELECTRO,LOW);
  }
    write_order(FINISHED);
}

void electroaimant_arriere_droit(int state)
{
  digitalWrite(PIN_RR_ELECTRO,LOW);
  if(state==1)
  {
    digitalWrite(PIN_RR_ELECTRO,HIGH);
  }
  else
  {
    digitalWrite(PIN_RR_ELECTRO,LOW);
  }
    write_order(FINISHED);
}

void electroaimant_arriere_gauche(int state)
{
  digitalWrite(PIN_RL_ELECTRO,LOW);
  if(state==1)
  {
    digitalWrite(PIN_RL_ELECTRO,HIGH);
  }
  else
  {
    digitalWrite(PIN_RL_ELECTRO,LOW);
  }
    write_order(FINISHED);
}
