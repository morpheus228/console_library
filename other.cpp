#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

void printDivLine() {
	cout << "-----------------------------------------------------" << endl;
}

void printManual() {
	printDivLine(); printf("Enter action, which you want to do...\n"); printDivLine();
	cout << "[1] - Print library" << endl;
	cout << "[2] - Print library with sorting" << endl;
	cout << "[3] - Add new book" << endl;
	cout << "[4] - Delete book" << endl;
	cout << "[5] - Library --> File" << endl;
	cout << "[6] - File --> Library" << endl;
	cout << "[7] - Count by category" << endl;
	cout << "[8] - Exit" << endl;
	printDivLine();
}

void intReading(bool& valid, int& value) {
	char buffer[256];
	cin.getline(buffer, 256);
	int result = std::sscanf(buffer, "%d", &value);

	if (result == EOF or result == 0) valid = false;
	else valid = true;
}

void doubleReading(bool& valid, double& value) {
	char buffer[256];
	cin.getline(buffer, 256);
	int result = std::sscanf(buffer, "%lf", &value);

	if (result == EOF or result == 0) valid = false;
	else valid = true;
}

char* replace(char* Src, char char_to_replace, char new_char) {

	auto len1 = strlen(Src);

	char* string = new char[len1 + 1];

	memcpy(string, Src, len1);

	for (int i = 0; i < len1; ++i) {
		if (string[i] == char_to_replace) string[i] = new_char;
	}

	string[len1] = 0;
	return string;
}


char* encoding(char* Src) {
	return replace(Src, ' ', 'á');
}

char* decoding(char* Src) {
	return replace(Src, 'á', ' ');
}