# Requirements document
1. Overview
	1. Objectives: Why are we doing this project? What is the purpose? 
	The objectives of this project are to design, build and test a soda/beer can cooler and monitor.

	2. Process: How will the project be developed? 
	The project will be developed using the TM4C123 board and ST7735 display. There will be at least two temperature-setting buttons and a 'begin cooling' button that the operator can use to control the system. The system will also make use of one or more thermoelectric cooling plates to lower the temperature of the can. In addition, there will be a temperature sensor to monitor the current temperature of the can. The system will be built on a printed circuit board and run off a battery supply. Depending on current draw, we may also design an AC adapter connection. The initial design will be prototyped and tested on a breadboard, then constructed on a printed circuit board. 

	3. Roles and Responsibilities: Who will do what?  Who are the clients?
	EE445L students are the engineers and the TA is the client. For this project, 

	Jon Ambrose will be responsible for circuit design layout and DAC sampling.

	John Starich will be responsible for button and temperature interfacing.

	4. Interactions with Existing Systems: How will it fit in?
	The system will be use the TM4C123 chip, ST7735 display, a printed circuit board, a temperature sensor, thermoelectric cooling plates, and control buttons. Power will be supplied by a 7.4V Li-ion battery and potentially a AC/DC adapter.

	5. Terminology: Define terms used in the document.
	Thermoelectric cooler - cooling plates that operate when voltage put across them, they pump cold to one side and heat to another

	6. Security: How will intellectual property be managed?
	The system may include software from StellarisWare and from the book. No software written for this project may be transmitted, viewed, or communicated with any other EE445L student past, present, or future (other than the lab partner of course). It is the responsibility of the team to keep its EE445L lab solutions secure.

2. Function Description
	1. Functionality: What will the system do precisely?
	The basic purpose of the system will be to cool down soda cans so we can drink chilled beverages. The basic process is the user sets the temperature they wish to cool the can to, starts the cooling system, and waits for it to finish!
	A monitoring output will be displayed to the LCD screen. The user may see the current temperature, desired temperature, and possibly time remaining. Two buttons will be used for setting the temperature and another button will start and stop the cooling process. When the cooler is done, it will indicate on the screen that it has finished and the user may then consume the chilled beverage.

	2. Scope: List the phases and what will be delivered in each phase.
	Phase 1 is prototype and test; phase 2 is the PCB layout and ordering; and phase 3 is assembly and demonstration.

	3. Prototypes: How will intermediate progress be demonstrated?
	A prototype system running on the TM4C123 board and solderless breadboard will be demonstrated. Progress will be judged through multiple lab sessions with the TA’s.

	4. Performance: Define the measures and describe how they will be determined.
	Cooling time - How long the system takes to cool a can to the desired temperature.
	Accuracy - How accurate the temperature readings are.
	Reliability – How consistently the can is cooled from and to the same temperatures.

	5. Usability: Describe the interfaces. Be quantitative if possible.
	There will be a master power switch for the battery. There will be temperature set switches and a start/stop switch. One LCD display, one temperature sensor, and at least one thermoelectric cooling plate.

	6. Safety: Explain any safety requirements and how they will be measured.
	The cooler should not run too hot (since they produce both hot and cold) and it should be easy to use without dangling wires.

3. Deliverables
	1. Reports: How will the system be described?
	A lab report described below is due by the due date listed in the syllabus. This report includes the final requirements document.

	2. Audits: How will the clients evaluate progress?
	The preparation is due at the beginning of the lab period on the date listed in the syllabus.

	3. Outcomes: What are the deliverables? How do we know when it is done?
	There are three deliverables: preparation, demonstration, and report.

