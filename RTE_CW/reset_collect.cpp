/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Reset Count
*/
#include "interface.h"
/*Define the reset collect sensor function*/
void resetCountSensor(int conveyor) {
	int count_senzor;
	if (conveyor == 0 or conveyor == 1)  //When conveyor is active
	{
		count_senzor = 0; //Clear the sensor
	}
}