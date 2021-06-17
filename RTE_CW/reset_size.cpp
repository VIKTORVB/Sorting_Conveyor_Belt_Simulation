/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Reset Size
*/
#include "interface.h"
/*Define the reset size sensor function*/
void resetSizeSensors(int conveyor) {
	if (conveyor == 0 or conveyor == 1) { //When conveyor is active
		sensorStatus[conveyor] = "No object"; //Clear the sensor	 
	}
}