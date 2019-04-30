#include "Header.h"


class MemManager {

private:
	queue <Process> processes;
	int memSize;
	map <int, Process> memMap;
	int clock;
	int numProcesses;

public:

    MemManager();
    ~MemManager();

	void readFile(string fileName, int pageSize);
	void writeFile();
};