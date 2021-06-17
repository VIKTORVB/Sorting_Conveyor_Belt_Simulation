/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* File name: interface.h - custom header
*/

#pragma once
/*Include standtard C++ libraries*/
#ifdef _WIN32
#include <Windows.h>
#else	
#include <unistd.h>
#endif	
#include <thread>
#include<mutex>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <functional>
#include<string>
#include<future>

using namespace std;

/*Global variables*/
extern int motor;
extern int conv_sel;
extern int lenght;
extern int speed;
extern int lenghtSandG;
extern int timeSandG;
extern int timeGandC;
extern int timeConveyor;
extern int bigObjectsCollected[2] ;
extern int bigObjects[2];
extern int smallObjects[2];
extern int objects[2][2];
extern int flagsensorOne[2][2] ;
extern int flagsensorTwo[2][2] ;
extern int flagBothSensors[2][2] ;
extern int smallObjectsRejected[2];
extern string sensorStatus[2]; 
extern string gateStatus[2];
extern int timing_counter;

/*Function declerations*/

/*Sensors*/
void readCountSensor(int);
int track_object_numb_count(int);
void size_sensor_logic(int);
int track_object_numb_sensors(int, int);

/*Sensor Reser*/
void resetSizeSensors(int);
void resetCountSensor(int);

/*motor control functions*/
int startMotor(void);
int stopMotor(void);

/*Thread Generation*/
void generate_thread_Counter(std::future<void> futureObj, function<void()> func);
void generate_thread_Scheduling(std::future<void> futureObj, function<void()> func);
void generate_thread_Simulation(std::future<void> futureObj, function<void()> func);

/*User Interface*/
void printConveyorStatus(void);
void printConveyorSettings(void);
void conveyorSettingsLogic(char);
void changeLenghtSandG(void);
void changeConveyorLenght(void);
bool checkIfNumb(string);
void autoConfiguration(void);

/*Gate Timer*/
void Request_Close_Gate(int);
int track_object_numb_gate(int);
void Set_Event_Gate(int,int);

/*System Counters*/
void Counter_System(void);

/*Simulation*/
void Simulator(void);
int conv_Select(void);
int obj_Sorting(void);

/* Scheduling*/
void Schedule(void);