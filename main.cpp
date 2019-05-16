#include "Header.h"
#include "MemManager.h"

int main()
{
	int memorySize;
	int pageSize;
	string inputFile;
	
	cout << "This program simulates memory management." << endl;
	cout << "Memory Size > ";
	cin >> memorySize;

	while(true) {
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Memory Size > ";
			cin >> memorySize;
		}
		if(!cin.fail()) break;
	}

	do {
		cout << "Page Size (1: 100, 2: 200, 3: 400) > ";
		cin >> pageSize;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while(pageSize != 1 && pageSize != 2 && pageSize != 3);

	cout << "Input the name of the file you would like to process." << endl;
	cin >> inputFile;

	switch (pageSize) {
	case 1:
		pageSize = 100;
		break;
	case 2:
		pageSize = 200;
		break;

	case 3:
		pageSize = 300;
		break;
	default:
		cout << "Invalid selection, defaulting to 100." << endl;
		pageSize = 100;
	}

	MemManager memManager(memorySize, pageSize);

	memManager.readFile(inputFile, pageSize);

	memManager.simulate();
	//system("PAUSE");
	return 0;
}