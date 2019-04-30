#include "Header.h"


class MemManager {

private:
	std::queue <Process> processes;
	int memSize;
	std::map <int, Process> memMap;
	int clock = 100;
	int numProcesses;

public:
	void readFile(std::string fileName);
	void writeFile();
};