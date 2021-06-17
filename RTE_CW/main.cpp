/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: main.cpp - main function
*/

#include "interface.h" //Include custom library
void Schedule();
void start_system();
int motor_state; // System state variable
int comp_time = 10; // Computation time for system tick - for 1ms change it to 1
int tick; // System tick
int cycle_count = 0; // counter for minor cycle time
int cycle_time = 1; // minor cycle period - the actual value is 40
int cycle_num = 0; // number of minor cycles initialised as 0
int tmp_state = 0;	// Temporarily size sensor value



void Simulator() // simulate placing objects on the conveyor
{
	int conveyor = conv_Select();  // get random value for the conveyor
	int object = obj_Sorting();   // get random object
	int success = track_object_numb_sensors(conveyor, object);  // call function to place the object on the conveyor
}

void clear_all()  // clear the system timer and fill with zeroes all timing and counting arrays
{
	 timing_counter = 1;  
	 fill(bigObjectsCollected, bigObjectsCollected + 2, 0);
     fill(smallObjectsRejected, smallObjectsRejected + 2, 0);
	 fill(smallObjects, smallObjects + 2, 0);
	 fill(bigObjects, bigObjects + 2, 0);
	 fill(&objects[0][0], &objects[0][0] + sizeof(objects)/ sizeof(objects[0][0]), 0);
	 fill(&flagsensorTwo[0][0], &flagsensorTwo[0][0] + sizeof(flagsensorTwo)/ sizeof(flagsensorTwo[0][0]), 0);
	 fill(&flagsensorOne[0][0], &flagsensorOne[0][0] + sizeof(flagsensorOne) / sizeof(flagsensorOne[0][0]), 0);
	 fill(&flagBothSensors[0][0], &flagBothSensors[0][0] + sizeof(flagBothSensors) / sizeof(flagBothSensors[0][0]), 0);
	
}

void start_system()
{
	autoConfiguration(); // run autoconfig to set the timing parameters of the system
	char UIout;  // declare char for user input
	promise<void> simulation1;    // create promise objects for threads
	promise<void> exitSignalCounterGate;
	promise<void> exitSignalUI;
	future<void> simulation = simulation1.get_future();  // get the futures of those promises
	future<void> futureCaunterGate = exitSignalCounterGate.get_future();
	future<void> futureUI = exitSignalUI.get_future();

	thread Sim(generate_thread_Scheduling, std::move(simulation), Schedule);// generate thread pass to it the future and the function it should be running
	Sim.detach();                                                           // detach the thread so there is no need to wait for it to finish
	thread CG(generate_thread_Counter, std::move(futureCaunterGate), Counter_System);
	CG.detach();
	thread S(generate_thread_Simulation, std::move(futureUI), Simulator);     
	S.detach();                                                               
	cin >> UIout;         // while threads are running ask user for exit input
	while (UIout != '1')  // wait untill user has entered the correct input
	{
		UIout = 0;
		std::cin >> UIout;
	}
		clear_all();     // call function to clear all timers and arrays
		exitSignalCounterGate.set_value();  // set the values for the futures so the threads can exit 
		exitSignalUI.set_value();
		simulation1.set_value();
}

int main()
{
	while (1)
	{
		int userInput;  // declare variable for user input
		system("CLS"); // clear console
		printf("\n 1. Start Simulation");
		printf("\n 2. Conveyor Settings\n");
		cin >> userInput;
		if (userInput == 2)  
		{
			printConveyorSettings();  // call the settings function
		}
		else if (userInput == 1)
		{
			start_system();  // call the system start function
		}
	}
}
void Schedule()
{

		//motor_state = startMotor(); // start the motors

			//tick = system_tick(comp_time); // run system tick
			
			// Start the scheduling algorithm
			if (cycle_count != cycle_time) // if minor cycle hasn't reached it's maximum
			{
				cycle_count = cycle_count ++; // increment according to system tick
			}
			else if (cycle_count == cycle_time) // when cycle period reached
			{
				cycle_count = 0; // clear cycle count
				++cycle_num; // incrementnumber of minor cycle						
				if (cycle_num == 5) // when last cycle is reached ***
				{
					cycle_num = 0; // clear to start over
				}
			}
			switch (cycle_num) { // Cyclic Scheduling
			case 0: size_sensor_logic(0); // Read sensor on belt 0
				break;
			case 1: size_sensor_logic(1); // Read size sensor on belt 1
				break;
			case 2: printConveyorStatus(); // Update the UI
				break;
			case 3: readCountSensor(0); // Read the count sensor on belt 1
				break;
			case 4: readCountSensor(1); // Read the count sensor on belt 2
				break;
			}
	}