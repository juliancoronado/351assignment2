#include "MemManager.h"

MemManager::MemManager(int memSize, int pageSize) : processes(), memMap()
{
	this->memSize = memSize;
	clock = 0;
	numProcesses = 0;
	this->pageSize = pageSize;
	numPages = memSize / pageSize;
}

MemManager::~MemManager()
{
	memMap.clear();
}

void MemManager::readFile(string filename, int pageSize) 
{
	ifstream infile; //create read in file handler
	string line; //current line in file
	Process newProcess; //holds the new process we obtain from the input file
	int components; //number of components for each process

	infile.open(filename);	//open file

	if (!infile.is_open())	//error check
	{
		cout << "File open error.\n";
		return;
	}

	infile >> numProcesses;	//read number of processes

	while (!infile.eof()) //process file. may not need to be a loop depending on design for calling this function
	{
		infile >> newProcess.pid;
		infile >> newProcess.arrivalTime >> newProcess.burstTime;
		infile >> components;

		for(int i = 0; i < components; i++)
		{
			int temp;
			infile >> temp;
			newProcess.memCost += temp;
		}

		newProcess.numPages = ceil(newProcess.memCost / float(pageSize)); // Seems to be working, may produce wrong answer
		newProcess.running = false;
		newProcess.terminated = false;

		//cout << newProcess.pid << endl << newProcess.arrivalTime << endl << newProcess.burstTime << endl << newProcess.memCost
		//<< endl << newProcess.numPages << endl << endl;

		listProcesses.push_back(newProcess);

		getline(infile, line); // Move on to next line

		newProcess = {}; // Clear struct
	}

	infile.close();
}

const void MemManager::writeFile()
{
	ofstream outfile;	//create output file handler
	outfile.open("output1.txt");	//open output file
}

void MemManager::initMap()
{
	Process nullProc; // Used to initialize map, pid of -1 means no process in that spot
	nullProc.pid = -1;

	for(int i = 0; i < numPages; i++)
	{
		memMap.insert(pair<int, Process>(i, nullProc));
	}
}

const vector<Process> MemManager::getReadyProcesses()
{
	vector<Process> temp;

	for(Process &current : listProcesses)
	{
		if(current.arrivalTime == clock) // If clock is equal to arrival time
		{
			temp.push_back(current);
		}
	}

	return temp;
}

const void MemManager::printQueue(queue<Process> copyProcessQueue)
{
	cout << "\tInput Queue:[";
	while(!copyProcessQueue.empty())
	{
		cout << copyProcessQueue.front().pid;
		if(!(copyProcessQueue.size() == 1))
		{
			cout << " ";
		}
		copyProcessQueue.pop();
	}
	cout << "]\n";
}

void MemManager::pushArrivals(vector<Process> &readyProcesses)
{
	for(int i = 0; i < readyProcesses.size(); i++)
	{
		processes.push(readyProcesses[i]);
		cout << "\n\tProcess " << readyProcesses[i].pid << " arrives\n";
		printQueue(processes); 
	}
}

void MemManager::allocateProcess(Process memProcess)
{
	int freeFrames = 0;
	int start = 0;
	int end = 0;

	int numPages = memProcess.numPages; // Holds how many pages we need allocate

	for(int i = 0; i < listProcesses.size(); i++)
	{
		if(memProcess.pid == listProcesses[i].pid)
		{
			listProcesses[i].finishTime = clock + listProcesses[i].burstTime;
			listProcesses[i].running = true;
			break;
		}
	}

	for(int i = 0; i < memMap.size(); i++)
	{
		if(memMap.at(i).pid == -1)
		{
			memMap.at(i) = memProcess; // Allocate the process
			numPages--; // Decrement the number of pages the process needs
		}

		if(numPages == 0)
		{
			break; //If we are done allocating, break from loop
		}
	}
}

const void MemManager::printMemMap(int pageSize)
{
	int acc = 0;
	int pageNum = 1;
	int adder;

	vector<int> pageCounts(listProcesses.size(), 1); 

	switch (pageSize)
	{
	case 100:
		adder = 99;
		break;
	
	case 200:
		adder = 199;
		break;
	
	case 400:
		adder = 399;
		break;

	default:
		adder = 100;
		break;
	}

	cout << "\tMemory Map: \n";

	for (int i = 0; i < memMap.size(); i++)
	{
		if(memMap[i].pid != -1) // If the current process at memMap[i] is not empty
		{
			int currProcId = memMap[i].pid;

			while(i < memMap.size() && memMap.at(i).pid == currProcId)
			{
				cout << '\t' << acc << "-" << acc+adder << ": Process " << memMap[i].pid << ", Page " << pageCounts[currProcId-1] << endl;
				acc += pageSize;
				i++;
				pageCounts[currProcId-1]++;
			}

			i--; // i is incremented too many times, decrement to counter
		}
		else
		{
			int freeFrameOutput = acc;
			cout << '\t' << freeFrameOutput << "-";

			while(i < memMap.size() && memMap.at(i).pid == -1)
			{
				acc += pageSize;
				i++;
			}

			i--; // i is incremented one too many times, decrement to counter

			if(i < memMap.size())
			{
				cout << acc-1 << ": Free Frame(s)" << endl;
			}
			else
			{
				cout << acc+99 << endl;
			}
		}	
	}
}

const vector<Process> MemManager::getFinishedProcesses(int clock)
{
	vector<Process> temp;

	for(Process &current: listProcesses)
	{
		if(clock == current.finishTime && current.running)
		{
			current.terminated = true;
			temp.push_back(current);
		}
	}

	return temp;
}

void MemManager::deallocateProcess(Process memProcess)
{
	Process removeProcess;
	removeProcess.pid = -1;

	cout << "\tProcess " << memProcess.pid << " completes\n";

	for(int i = 0; i < memMap.size(); i++)
	{
		if(memMap[i].pid == memProcess.pid)
		{
			memMap[i] = removeProcess;
		}
	}
}

const int MemManager::countFreePages()
{
	int freePages;

	for(int i = 0; i < memMap.size(); i++)
	{
		if(memMap.at(i).pid == -1)
		{
			freePages++;
		}
	}

	return freePages;
}

const void MemManager::checkSimulationComplete(bool& done)
{
	for(int i = 0; i < listProcesses.size(); i++)
	{
		if(!listProcesses[i].terminated) // If a process has not been terminated
		{
			done = false; // We are not done
			return;
		}
	}

	done = true; // If every process has been marked as terminated, we are done
}

void MemManager::simulate()
{
	Process memProcess;
	bool clockOutput = false; // Used to output the clock only once
	bool done = false; // boolean variable used to exit the simulator when complete
	int freePages;

	initMap(); // Initialize map to empty

	while(!done)
	{
		vector<Process> readyProcesses = getReadyProcesses(); // Get the ready processes according to the clock

		if (!readyProcesses.empty()) // If the list of ready processes is not empty, we have another event
		{
			cout << "\nt = " << clock << ": ";
			clockOutput = true; // We have outputted the clock, do not need to output a second time

			pushArrivals(readyProcesses); // Push the newly arrived processes to the processes queue

			freePages = countFreePages();

			while (processes.front().numPages <= freePages && !processes.empty()) // While we can allocate processes and there are processes to allocate
			{
				memProcess = processes.front(); // Get the process at front of queue
				cout << "\tMM moves Process " << memProcess.pid << " to memory\n";

				processes.pop(); // Remove the process just allocated from the queue
				printQueue(processes);
				allocateProcess(memProcess); // Allocate process that was removed from queue
				printMemMap(pageSize);
				freePages = countFreePages(); // Update number of free pages
			}
		}

		vector<Process> finishedProcesses = getFinishedProcesses(clock); // Get the finished process according to the clock

		for (int i = 0; i < finishedProcesses.size(); i++)
		{
			if(!clockOutput)
			{
				cout << "\nt = " << clock << ": \n";
				clockOutput = true;
			}

			deallocateProcess(finishedProcesses[i]); // Deallocate the finished process

			if(!processes.empty() && processes.front().numPages <= countFreePages()) // Checks if we can allocate after deallocating a process
			{
				memProcess = processes.front(); // Get the process at front of queue
				cout << "\tMM moves Process " << memProcess.pid << " to memory\n";

				processes.pop(); // Remove the process just allocated from the queue
				printQueue(processes);
				allocateProcess(memProcess); // Allocate process that was removed from queue
				printMemMap(pageSize);
			}

			printMemMap(pageSize);
		}

		readyProcesses.clear();
		finishedProcesses.clear();
		clockOutput = false;

		clock++;

		checkSimulationComplete(done); // Check if we are done
	}
}