
Our electrical circuit is composed of the openCR board, a custom protoboard and an arduino nano. The openCr board is the master board of the circuit that deals with communicating and giving orders to the different components. The protoboard contains the circuit and the parts necessary for the proper functioning of the components. The arduino nano is used to receive a 3.3V signal and send a 5V signal back to the mosfets.


About the Arduino plugins:

Each pins has a maximum output current of 5mA. Total output current from pins should not reach over ±120mA

Arduino's already used pins by openCR:
 - 13



About the OpenCR plugins:

The total power consumption on 12V and 5V ports should not exceed 55W.



About the circuit: 

The 12V port is used with the mosfet to give power for the electromagnets.

Two TTL ports is used for the motors. (multiple or just one can be used)

The 5V port is used for the servomotors. (Power input)

Module Bluetooth : 

Model : HC-05
