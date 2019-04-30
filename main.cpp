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
	cout << "Page Size (1: 100, 2: 200, 3: 400) > ";
	cin >> pageSize;

	cout << "Input the name of the file you would like to process." << endl;
	cout << "Please do not include a file extension, but ensure the file is a .txt file type." << endl;
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

	MemManager memManager;

	memManager.readFile(inputFile, pageSize);


	//system("PAUSE");
	return 0;
}