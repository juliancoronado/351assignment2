#include <iostream>
#include <fstream>
#include "MemManager.h"

using namespace std;

void MemManager::readFile(string filename) 
{
	MemManager manager;
	ifstream infile;	//create read in file handler
	infile.open(filename + ".txt");	//open file

	if (!infile.is_open())	//error check
		cout << "File open error.\n";

	while (!infile.eof())	//process file. may not need to be a loop depending on design for calling this function
	{
		infile >> manager.numProcesses;	//read

	}

	infile.close();
}

void MemManager::writeFile()
{
	ofstream outfile;	//create output file handler
	outfile.open("output1.txt");	//open output file

}