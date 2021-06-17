/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: Size sensor
*/
#include "interface.h"
///*Define the read size sensor function*/

int sensor_previous = 0; // variable to hold the previous state of the sensor
int sensor = 0;  // variable to hold the current state of the sensor
int flagsensorOne[2][2] = { {0,0} ,{0,0 } };   // 2d arrays to hold the sensor event triggers for both conveyors
int flagsensorTwo[2][2] = { {0,0} ,{0,0 } };
int flagBothSensors[2][2] = { {0,0} ,{0,0 } };


int readSizesensors(int conveyor)
{
    for (int i = 0; i < 2; i++)  // check both values of the array for the set convayor
    {
        if (flagsensorOne[conveyor][i] == timing_counter) // if the event trigger of the first sensor is equall to the current counter value
        {
            flagsensorOne[conveyor][i] = 0;               // reset the event trigger
            sensorStatus[conveyor] = "Sensor one flag";   // flag the first sensor
            return 1;                                     // return a one
            
        }
        if (flagsensorTwo[conveyor][i] == timing_counter )// do the same for the second sensor and both sensors
        {
            flagsensorTwo[conveyor][i] = 0;
            sensorStatus[conveyor] = "Sensor two flag";
            return 2;
            
        }
        if (flagBothSensors[conveyor][i] == timing_counter )
        {
            flagBothSensors[conveyor][i] = 0;
            sensorStatus[conveyor] = "Both sensors flag";
            return 3;
            
        }
        else                                             // if no event triggers match the current counter return 0
        {
            return 0;
            
        }
    }
}


void Loop_Count_Sensors(int i, int conveyor, int object) // depending on the 
{
    switch (object)
    {
    case 0: // when the object is small

        if (timing_counter + 2 >= timeConveyor + 1 )  // if the smallest event trigger is larger than the maximum value of the counter
        {
            flagsensorOne[conveyor][i] = (timing_counter + 2) - timeConveyor ;  // set the event for the first sensor and roll over the counter
            flagsensorTwo[conveyor][i] = (timing_counter + 5) - timeConveyor ;  // set the event for the second sensor and roll over the counter
        }
        else if (timing_counter + 5 >= timeConveyor + 1 ) // if the largest event trigger is larger than the maximum value of the counter
        {
            flagsensorOne[conveyor][i] = (timing_counter + 2); // set the event for the first sensor 
            flagsensorTwo[conveyor][i] = (timing_counter + 5) - timeConveyor ; // set the event for the second sensor and roll over the counter
        }
        if (timing_counter + 5 <= timeConveyor ) // if the event trigger is smaller than the maximum value of the counter
        {
            flagsensorOne[conveyor][i] = timing_counter + 2;  // set the event for the first sensor 
            flagsensorTwo[conveyor][i] = timing_counter + 5;  // set the event for the second sensor 
        }
        break;

    case 1:  // when the object is large do the same process, but insted of the second sensor set the event for both sensors
        if (timing_counter + 2 >= timeConveyor + 1)
        {
            flagsensorOne[conveyor][i] = (timing_counter + 2) - timeConveyor ;
            flagBothSensors[conveyor][i] = (timing_counter + 5) - timeConveyor ;
        }
        else if (timing_counter + 5 >= timeConveyor + 1)
        {
            flagsensorOne[conveyor][i] = (timing_counter + 2);
            flagBothSensors[conveyor][i] = (timing_counter + 5) - timeConveyor ;
        }
        if (timing_counter + 5 <= timeConveyor )
        {
            flagsensorOne[conveyor][i] = timing_counter + 2;
            flagBothSensors[conveyor][i] = timing_counter + 5;
        }
        break;
    }
}


int track_object_numb_sensors(int conveyor, int object)
{
    for (int i = 0; i < 2; i++) // check both values of the array for the set convayor
    {
        if (flagsensorOne[conveyor][i] == 0 && flagsensorTwo[conveyor][i] == 0 && flagBothSensors[conveyor][i] == 0) // if there is a free space in all arrays
        {
            Loop_Count_Sensors(i, conveyor, object); // call function to set the new event trigger and pass to it the free position in the array, the conveyor ,and the type of object

            return 1; 
        }
    }return 0;  // if not return 0
}

void size_sensor_logic(int Conveyor)
{
    resetSizeSensors(Conveyor); // reset the size sensor for the conveyor
    sensor = readSizesensors(Conveyor); // read the size sensor for the conveyor

    if (sensor == 1) // if it returns a one
    {
        sensor_previous = sensor;  // save the value in a variable
    }
    if ((sensor == 3) && (sensor_previous == 1)) // if the first sensor has been set and the current sensor value is 3
    {
        sensor_previous = 0; // reset the previous value
        if (track_object_numb_count(Conveyor) == 1) // check if there is free space on the conveyor for a large object
        {
            bigObjects[Conveyor] ++;  // if there is increment the object counter and set the event triggers for the count sensor
        }
    }
    if ((sensor == 2) && (sensor_previous == 1)) // if the first sensor has been set and the current sensor value is 2
    {
        sensor_previous = 0;// reset the previous value
        if (track_object_numb_gate(Conveyor) == 1)// check if there is free space on the conveyor for a small object
        {
            smallObjects[Conveyor]++; // if there is increment the object counter and set the event trigger for the gate
        }
    }
}
