# Contents of the folders
    Arduino Code : Code for the openCR and the template on Arduino mega
    Pthon controller : Code for the user interface and setup of pyqt5 on pycharm

# Behavior of the robot 
Wake up of the robot : 

    Robot goes in default stance, activates magnets and waits for cmd
    
Python code point of view for the communications below :

    Mode 1 : Automatic

        Home button (default stance) : send home cmd
        wait for end message

        To add action : Input distance and angle and press add
        add up to 10 actions
        Then press start to send cmd
        wait for end message

    Mode 2 : Semi-automatic

        Home button (default stance) : send home cmd
        wait for end message

        Input angle and press enter to send cmd
        wait for end message

        button to go forward
        button to go backward
        In both case : send command to move when pressed and send cmd to stop when depressed
        Robot completes sequence before stopping
        wait for end message

    Mode 3 : Manual

        Home button (default stance) : send home cmd
        wait for end message

        For each motor : (4 stepper (0-180 deg) and 4 stepper (360 deg))
        Magnet of leg must be turned off
        Button to turn clockwise
        Button to turn anti-clockwise
        In both case : send command to move when pressed and send cmd to stop when depressed

        For each magnet :
        Check box to enable/disable
        To disable a magnet, at least 3 magnets must be enabled (security factor)

# Communication protocol
The communication is based on the Robust Arduino Serial Protocol in Python:
https://github.com/araffin/python-arduino-serial

To protocol is based on a master and slave relation. Therefore the arduino only speaks to when it is talked to by the python controller.
This system insures that the communication is synchronized and that no message is lost. Also, all messages are 8bit which insures the arduino buffer serial will not overflow

There are two types of messages :

    Orders (8bit integer) : defines the type of request or response; can be immediately followed by a parameter 
    Parameters (8bit integer) : Optional number representing a precision of an order 
    Ex : Order : LEFT_MOTOR ; Parameter : 40; Output : Give a 40 rad/s speed to the motor 
 
 Sequence of communication :
 
   Paring: 
   The python controller sends order HELLO every few moments until a HELLO order is returned by the arduino.
   
   Action request order :
   Python controller sends order and waits for RECEIVED order returned by the arduino.
   Optional : Sends parameter and waits for RECEIVED order returned by the arduino.
   Python controller waits for finished order type of order returned by the arduino.
    
   Information request order :
   Python controller sends order and waits for RECEIVED order returned by the arduino.
   Python controller waits for parameter then sends RECEIVED order.
    
   If RECEIVED order is not received by the python controller, the order or paramter is either resent or an error is raised.
   
![Diagramme sans nom](https://user-images.githubusercontent.com/61423054/155046882-bd427d14-defc-4da7-bac2-dcbce39e5b85.png)
    
