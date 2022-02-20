//https://www.instructables.com/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/

#include <Arduino.h>
#include "order.h"
#include "parameters.h"
#include "slave.h"

//Prototypes
void get_messages_from_serial();
void home();
void stop();
void servo();


bool is_connected = false; ///< True if the connection with the master is available

void setup() {

  Serial.begin(115200);

  // Wait until the arduino is connected to master
  while(!is_connected)
  {
    // write_order(HELLO);
    // wait_for_bytes(1, 1000);
    get_messages_from_serial();
  }

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
          home();
          if(DEBUG)
          {
            write_order(HOME);
          }
          break;
        }

        case STOP:
        {
          write_order(RECEIVED);
          stop();
          if(DEBUG)
          {
            write_order(STOP);
          }
          break;
        }

        case SERVO:
        {
          
          //reads parameter
          int servo_angle = read_i16(); //doit ajouter vérification, car passe direct au travers

          write_order(RECEIVED); 
          servo();
          if(DEBUG)
          {
            write_order(SERVO);
            write_i16(servo_angle);
          }
          break;
        }

  			// Unknown order
  			default:
          write_order(ERROR);
          write_i16(404);
  				return;
      }
      
    }
    
  }
}

/********************************************
 * 
 * Functions to be called when an order is processed
 * 
 * ********************************************/
void home()
{

  //homing procedure

  write_order(HOME_END); 
}

void stop()
{

  //stopping procedure

  write_order(STOP_END);
  
}

void servo()
{
  //move servo to servo_angle
  write_order(SERVO_END);
  
  
}