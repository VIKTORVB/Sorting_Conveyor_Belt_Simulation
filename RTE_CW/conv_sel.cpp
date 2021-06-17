/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Conveyor Select
*/
#include "interface.h"
/*Define the conveyor select function*/

int conv_Select(void) {  // when called, return a random number between 1 and 2 (belt 1/belt 2)
	srand(time(NULL));
	int conv_sel = rand() % 2 + 0;
	return conv_sel;

}