The communication is based on the Robust Arduino Serial Protocol in Python:
https://github.com/araffin/python-arduino-serial

To protocol is based on a master and slave relation. Therefore the arduino only speaks to when it is talked to by the python controller.
This system insures that the communication is synchronized and that no message is lost. Also, all messages are 8bit which insures the arduino buffer serial will not overflow

There are two types of messages :
    Orders (8bit integer) : defines the type of request or response; can be immediately followed by a parameter 
    Parameters (8bit integer) : Optional number representing a precision of an order 
  
    Ex : Order : LEFT_MOTOR ; Parameter : 40; Output : Give a 30 rad/s speed to the motor 
 
 Sequence of communication:
    Paring: 
    The python controller sends order HELLO every few moments until a HELLO order is returned by the arduino.
   
    Action request order :
    Python controller sends order and waits for RECEIVED order returned by the arduino.
    Optional : Sends parameter and waits for RECEIVED order returned by the arduino.
    Python controller waits for finished order type of order returned by the arduino.
    
    Information request order :
    Python controller sends order and waits for RECEIVED order returned by the arduino.
    Python controller waits for parameter
    
    If RECEIVED order is not received by the python controller, the order or paramter is either resent or an error is raised.
  
  
