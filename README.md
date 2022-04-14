# CampUS
University of Sherbrooke robotics project
  
  ![Isometric view](https://user-images.githubusercontent.com/98042679/154827627-ff07e487-ea2e-4c38-a949-d4acb07813e9.JPG)
  
The CampUS robot is a quadriped articulated robot. Each leg is independent and contains two degrees of freedom, but all of these allow the robot to move from all sides.   An electromagnet is attached to each leg to allow the robot to move on metal surfaces. All components are controlled by an OpenCR card programmed in C++. This program handles the low-level commands needed for the move. A user interface is used to communicate to the robot the sequences of high-level movements to be executed according to the user's intention. A Bluetooth module makes it possible to make the wireless link between the two programs. 


https://user-images.githubusercontent.com/61423054/163423675-e28aa425-6067-4ee7-8b0e-fbca73a94658.mp4

The diagram below summarizes the general architecture explained above:

 ![image](https://user-images.githubusercontent.com/61423054/163424046-3e1ea1a0-8857-4d9c-8dd7-5045ebd48828.png)



# Code

  This folder contains all the code for Python interface and the C++ Arduino controller code
  
# Conception 

  This folder contains all the prototypes created on SolidWorks and the complete assembly manual of the mechanical and electrical parts

# Demo 

  This folder contains all the videos of movement to see the motion in detail
  
# Electricity

  This folder contains the information about the OpenCR board, the protoboard and overall circuit connections
  
# Tests

  This folder contains the different test plans 


