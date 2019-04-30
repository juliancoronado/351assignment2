#include <iostream>
#include "Header.h"
#include <string>
using namespace std;

int main()
{
	int memorySize;
	int pageSize;
	string inputFile;
	
	cout << "This program simulates memory management." << endl;
	cout << "Memory Size > " << endl;
	cin >> memorySize;
	cout << "Page Size > 1: 100, 2: 200, 3: 400" << endl;
	cin >> pageSize;

	cout << "Input the name of the file you would like to process." << endl;
	cout << "Please do not include a file extension, but ensure the file is a .txt file type." << endl;
	cin >> inputFile;

	switch (pageSize) {
	case 1:
		
		break;
	case 2:

		break;

	case 3:

		break;
	default:
		cout << "Enter a valid input for Page Size > 1, 2, or 3." << endl;
	}

	system("PAUSE");
	return 0;
}