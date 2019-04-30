#pragma once
#include <queue>
#include <map>
#include <string>
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

class MemManager {

private:
	std::queue <Process> processes;
	int memSize;
	std::map <int, Process> memMap;
	int clock = 100;
	int numProcesses;

public:
	void readFile(string);
	void writeFile();
};