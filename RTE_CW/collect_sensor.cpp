/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Collect Sensor
*/
#include "interface.h"
/*Define the read collect sensor function*/

int countSensor[2][2] = { {0,0},{0,0} }; // 2d array to store the event triggers of objects currently on each conveyor
int bigObjectsCollected[2] = { 0,0 }; // array to store objects collected

void readCountSensor(int conveyor)
{
    for (int i = 0; i < 2; i++)
    {
        if (countSensor[conveyor][i] == timing_counter)  // run trough the event array and check if any event is now
        {
            bigObjects[conveyor]--;  // remove object from counter
            bigObjectsCollected[conveyor]++; // increment collected objects
            countSensor[conveyor][i] = 0; // make the place on the convayor availabe again
        }
    }
}

void count_sensor_event(int conveyor,int i)
{
    if ((timing_counter + timeGandC) >= timeConveyor + 1) // check if there is need for the event trigger to be rolled over the counter
    {
        countSensor[conveyor][i] = (timing_counter + timeGandC) - timeConveyor; // if there is set the event and roll over
    }
    else if ((timing_counter + timeGandC) < timeConveyor)
    {
        countSensor[conveyor][i] = timing_counter + timeGandC; // if there isnt just set the event
    }
}

int track_object_numb_count(int conveyor)
{
    for (int i = 0; i < 2; i++)
    {
        if (countSensor[conveyor][i] == 0) // check if there is any free space on the conveyor
        {
            count_sensor_event(conveyor,i); // if there is pass it to the timer event setting function
            return 1;
        }
    }return 0; // if there is no space return 0
}