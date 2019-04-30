#include "MemManager.h"

MemManager::MemManager() : processes(), memMap()
{
	memSize = 0;
	clock = 0;
	numProcesses = 0;
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

	infile.open(filename + ".txt");	//open file

	if (!infile.is_open())	//error check
	{
		cout << "File open error.\n";
		return;
	}

	infile >> numProcesses;	//read number of processes

	while (!infile.eof())	//process file. may not need to be a loop depending on design for calling this function
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

		processes.push(newProcess);

		getline(infile, line); // Move on to next line

		newProcess = {}; // Clear struct
	}

	infile.close();
}

void MemManager::writeFile()
{
	ofstream outfile;	//create output file handler
	outfile.open("output1.txt");	//open output file

}