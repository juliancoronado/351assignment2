#pragma once
#include <queue>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct Process{
	int pid;
	int arrivalTime;
	int burstTime;	//how long a process should be in memory
	int finishedTime;
	int memCost;	//total cost of memory the process uses
	int numPages;	//memCost/pageSize
	bool running;
	bool terminated;
};