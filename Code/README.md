# Contents of the folders :
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
    
    
    
