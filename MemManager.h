#include "Header.h"

// Class used to represent our memory manager
// memMap is used as the primary data structure to represent our memory
// The key the page in memory and the value is the Process at that page


class MemManager {

private:
	queue <Process> processes;
	int memSize;
	map <int, Process> memMap;
	int clock;
	int numProcesses;
	int pageSize;

	vector<Process> listProcesses;
	int numPages;

	void initMap();
	void pushArrivals(vector<Process> &readyProcesses);
	void allocateProcess(Process memProcess);
	void deallocateProcess(Process memProcess);
	
	const void printMemMap(int);
	const int countFreePages();
	const void checkSimulationComplete(bool& done);
	const vector<Process> getFinishedProcesses(int clock);
	const vector<Process> getReadyProcesses();
	const void printQueue(queue<Process> copyProcessQueue);

public:

    MemManager(int memSize, int pageSize);
    ~MemManager();

	void readFile(string fileName, int pageSize);
	const void writeFile();

	void simulate();
};