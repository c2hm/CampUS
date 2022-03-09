//https://www.instructables.com/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/

#include <Arduino.h>
#include "order.h"
#include "parameters.h"
#include "slave.h"

//Prototypes
void get_messages_from_serial();
void home();
void start();
int get_param();
void stop();
void semi_auto();
void servo(int angle);


bool is_connected = false; ///< True if the connection with the master is available

void setup() {

  Serial.begin(115200);

  // Wait until the arduino is connected to master
  while(!is_connected)
  {
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
          break;
        }

        case START:
        {
          write_order(RECEIVED);
          start();

          break;
        }

        case STOP:
        {
          write_order(RECEIVED);
          stop();
 
          break;
        }

        case SEMI_AUTO:
        {
          write_order(RECEIVED);
          semi_auto();
 
          break;
        }

        case SERVO:
        {

          write_order(RECEIVED); 

          //reads parameter
          int angle = get_param();
          Serial.flush(); //avoid multiple instaces of param in serial
          if (angle == 0)
          {
              write_order(ERROR); 
          }
          else 
          {
              write_order(RECEIVED); 
              servo(angle);
          }
        
          break;
        }

  			// Unknown order
  			default:
          write_order(ERROR);
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
        return 0; /////////////Revoir notion de l'erreur
    }
  }
  return read_i8();
}

/********************************************
 * 
 * Functions to be called when an order is processed
 * 
 * ********************************************/
void home()
{

  //homing procedure

  write_order(FINISHED); 
}

void start()
{

  //starting procedure


  write_order(FINISHED); 
  
}

void stop()
{

  //stopping procedure

  write_order(FINISHED); 
  
}

void semi_auto()
{
  delay(250);
  
  write_order(FINISHED); 
  
}

void servo(int angle)
{
  delay(250);

  if (angle == 40)
  {
    write_order(FINISHED); //to test com
  }

  //move  to angle
  
  
  
}