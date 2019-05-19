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
	ofstream outFile;

	vector<Process> listProcesses;
	int numPages;

	void initMap();
	vector<Process> getFinishedProcesses(int clock);
	vector<Process> getReadyProcesses();
	void printQueue(queue<Process> copyProcessQueue);
	void pushArrivals(vector<Process> &readyProcesses);
	void allocateProcess(Process memProcess);
	void deallocateProcess(Process memProcess);
	void printMemMap(int);
	int countFreePages();
	double calcTurnAroundTime();
	void checkSimulationComplete(bool& done);

public:

    MemManager(int memSize, int pageSize);
    ~MemManager();

	void readFile(string fileName, int pageSize);
	void writeFile();

	void simulate();
};