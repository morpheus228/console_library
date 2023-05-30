#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "library.h"
#include "entering.h"
#include "other.h"

using namespace std;

int main() {
	Library library;
	initLibrary(library);
	bool run = true;
	
	while (run) {
		bool valid;
		int choise = 0;
		printManual();

		intReading(valid, choise);
	
		switch (choise) {
	
		case 1:
			printLibrary(library);
			break;
	
		case 2:
			printLibraryWithSorting(library);
			break;
	
		case 3:
			addNewBook(library);
			break;
			
		case 4:
			deleteBook(library);
			break;
			
		case 5:
			loadLibraryToFile(library);
			break;
			
		case 6:
			loadLibraryFromFile(library);
			break;
			
		case 7:
			countByCategory(library);
			break;

		case 8:
			run = false;
			break;
	
		default:
			std::cout << "ERROR: Unknown operation!" << std::endl;
			break;
		}
	}

	removeLibrary(library);
	system("pause");

	return 0;
}