# Requirements

1. Overview
    1. Objectives: Why are we doing this project? What is the purpose?
The objectives of this project are to design, build and test a brushed DC motor controller. The motor should spin at a constant speed and the operator can specify the desired set point. Educationally, we are learning how to interface a DC motor, how to measure speed using input capture, and how to implement a digital controller running in the background.

    2. Process: How will the project be developed?
The project will be developed using the EK-TM4C123GXL or EK-TM4C1294XL LaunchPad. There will be two switches that the operator will use to specify the desired speed of the motor. The system will be built on a solderless breadboard and run on the usual USB power. The system may use the on board switches or off-board switches. A hardware/software interface will be designed that allows software to control the DC motor. There will be at least five hardware/software modules: tachometer input, switch input, motor output, LCD output, and the motor controller.  The process will be to design and test each module independently from the other modules. After each module is tested, the system will be built and tested.
 
    3. Roles and Responsibilities: Who will do what?  Who are the clients?
We are the engineers and the TA is the client. One of us will build and test the sensor system. The other will build the actuator and switch input. Both of us will work on the controller.
 
    4. Interactions with Existing Systems: How will it fit in?
​The system will use the microcontroller board, a solderless breadboard, and the DC motor shown in Figure 4.1. The wiring connector for the DC motor is described in the PCB Artist sch file. It will be powered using the USB cable.
 
    5. Terminology: Define terms used in the document.
For the terms integral controller, PWM, board support package, back emf, torque, time constant, and hysteresis, see textbook for definitions.
 
    6. Security: How will intellectual property be managed?
The system may include software from TivaWare and from the book. No software written for this project may be transmitted, viewed, or communicated with any other EE445L student past, present, or future. It is the responsibility of our team to keep our EE445L lab solutions secure.
 
2. Function Description
    1. Functionality: What will the system do precisely?
If all buttons are released, then the motor should spin at a constant speed. If switch 1 is pressed and released, the desired speed should increase by 5 rps, up to a maximum of 40 rps. If switch 2 is pressed and released, the desired speed should decrease by 5 rps, down to a minimum of 0 rps.
Both the desired and actual speeds should be plotted on the color LCD as a function of time.
 
    2. Scope: List the phases and what will be delivered in each phase.
Phase 1 is the preparation; phase 2 is the demonstration; and phase 3 is the lab report. Details can be found in the lab manual.
 
    3. Prototypes: How will intermediate progress be demonstrated?
A prototype system running on the EK-TM4C123GXL or EK-TM4C1294XL LaunchPad and solderless breadboard will be demonstrated. Progress will be judged by the preparation, demonstration and lab report.
 
    4. Performance: Define the measures and describe how they will be determined.
The system will be judged by three qualitative measures. First, the software modules must be easy to understand and well-organized. Second, the system must employ an integral controller running in the background. There should be a clear and obvious abstraction, separating the state estimator, user interface, the controller and the actuator output. Backward jumps in the ISR are not allowed. Third, all software will be judged according to style guidelines. Software must follow the style described in Section 3.3 of the book. There are three quantitative measures. First, the average speed error at a desired speed of 60 rps will be measured. The average error should be less than 5 rps. Second, the step response is the time it takes for the new speed to hit 60 rps after the set point is changed from 40 to 60 rps. Third, you will measure power supply current to run the system. There is no particular need to minimize controller error, step response, or system current in this system.
 
    5. Usability: Describe the interfaces. Be quantitative if possible.
There will be two switch inputs. The tachometer will be used to measure motor speed. The DC motor will operate under no load conditions,
 
    6. Safety: Explain any safety requirements and how they will be measured.
​Figure 4.2 shows that under a no load condition, the motor current will be less than 100 mA. However, under heavy friction this current could be 5 to 10 times higher. Therefore, please run the motors unloaded. Connecting or disconnecting wires on the protoboard while power is applied will damage the microcontroller. Operating the circuit without a snubber diode will also damage the microcontroller.
 
3. Deliverables
    1. Reports: How will the system be described?
A lab report described below is due by the due date listed in the syllabus. This report includes the final requirements document.
 
    2. Audits: How will the clients evaluate progress?
The preparation is due at the beginning of the lab period on the date listed in the syllabus.
 
    3. Outcomes: What are the deliverables? How do we know when it is done?
There are three deliverables: preparation, demonstration, and report.
