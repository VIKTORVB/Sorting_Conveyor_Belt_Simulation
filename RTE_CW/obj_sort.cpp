/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Object Sorting
*/
#include "interface.h"
/*Define the object sorting function*/

int obj_Sorting(void) { // when called, return random number between 1 and 2 (large/small)
	srand(time(NULL)+ 16);
	int sel_obj = rand() % 2 + 0;
		return sel_obj;

}