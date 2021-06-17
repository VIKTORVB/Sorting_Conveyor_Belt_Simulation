/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Gate timer
*/
#include "interface.h"
/*Define the gate timer function*/


int objects[2][2] = { {0,0}, {0,0} };  // 2d array to store the event triggers of objects currently on each conveyor
int smallObjectsRejected[2];   // array to store objects rejected
int timing_counter = 1;  // counter integer
int conveyor;  // conveyor selection

void Set_Event_Gate(int i, int conveyor)
{
    if ((timing_counter + timeSandG) >= timeConveyor + 1 )  // check if there is need for the event trigger to be rolled over the counter
    {
        objects[conveyor][i] = (timing_counter + timeSandG) - timeConveyor ;  // if there is set the event and roll over
    }
    else if ((timing_counter + timeSandG) < timeConveyor )
    {
        objects[conveyor][i] = timing_counter + timeSandG; // if there isnt just set the event
    }
}

int track_object_numb_gate(int conveyor)
{
    for (int i = 0; i < 2; i++)
    {
        if (objects[conveyor][i] == 0) // check if there is any free space on the conveyor
        {
            Set_Event_Gate(i,conveyor);  // if there is pass it to the timer event setting function
            return 1; // and return 1
        }
    }return 0;  // if there is no space return 0
}


void Request_Close_Gate(int conveyor)
{
    for (int i = 0; i < 2; i++)
    {
        if (objects[conveyor][i] == timing_counter)  // run trough the event array and check if any event is now
        {
            gateStatus[conveyor] = "gate closed";// if it is close gate
            smallObjects[conveyor]--;  // remove object from counter
            smallObjectsRejected[conveyor]++;  // increment rejected objects
            objects[conveyor][i] = 0;  // make the place on the convayor availabe again
        }
    }
}


void Counter_System()
{
    gateStatus[0] = "gate opened";  // on every count of the counter open the gate
    gateStatus[1] = "gate opened";
    Request_Close_Gate(0); // check the gate on the first conveyor on every increment of the counter
    Request_Close_Gate(1); // check the gate on the second conveyor on every increment of the counter
    timing_counter++;
    if (timing_counter > timeConveyor)  // if counter reaches its maximum value reset it
    {
        timing_counter = 1;
    }
}