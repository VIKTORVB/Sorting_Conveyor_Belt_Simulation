/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* User Interface
*/

#include "interface.h"
int back = 0; // variable to go back in the UI
string gateStatus[2] = {"Gate opened","Gate opened"};  // string array for the status of the gates
string sensorStatus[2] = { "No object", "No object" };  // string array for the status of the sensors
int speed = 1; // declare the speed of the conveyor
int lenght = 50;  // the lenght of it
int lenghtSandG = 10;  // the distance between the size sensor and the gate
int lenghtGandC = 10;  // the distance between the gate and the count sensor
int timeConveyor = 0;  // the time it takes for an object to go from point 0 to max on the conveyor belt
int timeSandG; // the time it takes an object to move from the size sensor to the gate
int timeGandC;  // the time it takes an object to move from the gate to the count sensor
int bigObjects[2] = { 0,0 }; // array to store the current large objects on both conveyors
int smallObjects[2] = { 0,0 }; // array to store the current small objects on the conveyor

void autoConfiguration() // depending on the speed of the conveyor and the distances, calculate the timing characteristics of the conveyor
{

	timeConveyor = lenght / speed;
	timeSandG = lenghtSandG / speed;
	timeGandC = lenghtGandC / speed;

}

bool checkIfNumb(string userInput) // checks if user input is a number
{
	char newUserInputstring = 0; 
	int num = 0;
	for (int i = 0; i < userInput.length(); i++) // run trough the accepted user string
	{
		if (userInput[i] > 57 || userInput[i] < 49) // check in ACII if each of the characters represents a number
		{
			printf("Please input a number\n"); // if it does not send error message and promnt for input to exit
			printf("Press 1 to go back\n");
			while (newUserInputstring != '1')
			{
				newUserInputstring = 0;
				std::cin >> newUserInputstring;
			}
			return false; // and return false
		}
		else
		{
			return true; //if it does return true
		}
	}
}


void changeConveyorLenght()
{
	system("CLS"); // clear the creen
	string userInput; // variable string for user input
	printf("\n Please input the wanted lenght in cm \n");
	cin >> userInput; // get user input
	if (checkIfNumb(userInput) == true) // check if the input is a number
	{
		int userInputInt = stoi(userInput); // if it is push string to integer
		lenght = userInputInt; // save the value for later use
	}
}

void changeLenghtSandG()
{
	system("CLS");
	string userInput;
	printf("\n Please input the wanted distance between the second size sensor and the gate in cm\n");
	cin >> userInput;
	if (checkIfNumb(userInput) == true)
	{
		int userInputInt = stoi(userInput);
		lenghtSandG = userInputInt;
	}
}

void changeLenghtGandC()
{
	system("CLS");
	string userInput;
	printf("\n Please input the wanted distance between the gate and the collect sensor in cm\n");
	cin >> userInput;
	if (checkIfNumb(userInput) == true)
	{
		int userInputInt = stoi(userInput);
		lenghtGandC = userInputInt;
	}
}


void conveyorSettingsLogic(char userInput) // depending on the user input route to the appropriate function
{
	switch (userInput)
	{
	case '1':  changeConveyorLenght();
		break;
	case '2':  changeLenghtSandG();
		break;
	case '3':  changeLenghtGandC();
		break;
	case '4':  back = 1;
		break;
	default: printf("\n Please write a correct input");
		break;
	}
}

void printConveyorSettings()
{
	back = 0;
	char userInput = 0;
	while (back == 0)
	{
		system("CLS");
		printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");       // print out the UI
		printf("|                CONVEYOR SETTINGS                      |\n");
		printf("|                                                       |\n");
		printf("| Conveyor belt  lenght               : %-10dcm    |\n", lenght);
		printf("|                                                       |\n");
		printf("| Distance between size sensor and gate : %-8dcm    |\n", lenghtSandG);
		printf("|                                                       |\n");
		printf("| Distance between gate and collect sensor : %-8dcm |\n", lenghtGandC);
		printf("|                                                       |\n");
		printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		printf("\n 1. Conveyor lenght");
		printf("\n 2. Distance between size sensor and gate");
		printf("\n 3. Distance between gate and collect sensor");
		printf("\n 4. Back \n");
		autoConfiguration();  // set the timing parameters of the system
		cin >> userInput; // get user input
		conveyorSettingsLogic(userInput); // call routing function and pass to it the user input
	}
}


void printConveyorStatus()  // print out the current system status
{
	system("CLS");
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	printf("|                                    CONVEYOR STATUS                                       |\n");
	printf("|                                                                                          |\n");
	printf("| Sensor one Status  : %-20s    Gate One Status   :  %-10s            |\n", sensorStatus[0].c_str(),  gateStatus[0].c_str()); // transform strings to char array so that the print function can print it out
	printf("|                                                                                          |\n");            
	printf("|                                                                                          |\n");
	printf("| Sensor two Status  : %-20s    Gate Two Status   :  %-10s            |\n", sensorStatus[1].c_str(), gateStatus[1].c_str());
	printf("|                                                                                          |\n");
	printf("|                                                                                          |\n");
	printf("| Objects on conveyor One  N:  %-10d          Large objects collected N: %d            |\n", (smallObjects[0]+bigObjects[0]), bigObjectsCollected[0]);
	printf("|                    Type Small : %d                                                        |\n", smallObjects[0]);
	printf("|                    Type Big   : %d                Small objects rejected N: %d             |\n", bigObjects[0], smallObjectsRejected[0]);
	printf("|                                                                                          |\n");
	printf("|                                                                                          |\n");
	printf("| Objects on conveyor Two  N:  %-10d          Large objects collected N: %d            |\n", (smallObjects[1] + bigObjects[1]), bigObjectsCollected[1]);
	printf("|                    Type Small : %d                                                        |\n", smallObjects[1]);
	printf("|                    Type Big   : %d                Small objects rejected N: %d             |\n", bigObjects[1], smallObjectsRejected[1]);
	printf("|                                                                                          |\n");
	printf("|                                                                                          |\n");
	printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	printf("\n\n Enter 1 to Stop Simulation\n");
}
