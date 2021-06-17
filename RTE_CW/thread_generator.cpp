/*
* Module code: ENG620 - 2020/21
* Title: Conveyor Belt Control System Simulation
* Students: 900615 & 901070
* Threads
*/
#include "interface.h"

// periodically call the system counter function
void generate_thread_Counter(std::future<void> futureObj, function<void()> func)  // function to be called by a thread accepts the function that has to be periodically called and the future for that function
{
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) // while the future is not ready and returns timeout
	{
		auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000);  // generate a 1 second delay time
		func();                                                                       // call the recived function
		std::this_thread::sleep_until(x);                                             // sleep for one second
	}
}
// periodically call scheduling function
void generate_thread_Scheduling(std::future<void> futureObj, function<void()> func)
{
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(40);    // generate a 40 milisecond delay time
		func();
		std::this_thread::sleep_until(x);
	}
}
// periodically call simulation function
void generate_thread_Simulation(std::future<void> futureObj, function<void()> func) 
{
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(6000);  // generate a 6 second delay time
		func();
		std::this_thread::sleep_until(x);
	}
}