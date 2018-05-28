# DC-Motor-Torque-Controller

A PID controller designed to controll current and hence the Torque of a DC Motor. This is a part of the project that is currently under review at the IROS 2018 conference. The main aim of this project was to control the torque output of a DC motor. The DC motor characteristics states that its Torque output is directly proportional to the current flowing through the motor armature. Thus a simple  PID Controller was tuned to control the current flowing through the DC Motor. The block diagram below shows the entire procedure 

![torque_1](https://user-images.githubusercontent.com/15217992/40603997-3471cfd6-627b-11e8-9bf3-36a8a7526b3b.PNG)

The output of the controller is shown below. The redline indicates the torque set point and the blue line indicates the current through the armature of the motor. 

![torque_500](https://user-images.githubusercontent.com/15217992/40604058-7167d75a-627b-11e8-8ac2-09d6530c64df.png)

Clearly the figure indicates the successful tuning of the PID controller.
