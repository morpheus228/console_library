#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "library.h"
#include "other.h" 
#include "entering.h"

using namespace std;

int countLinesInFile(char* fileName) {
	unsigned int numberOfLines = 0;
	char ch;
	FILE* file = fopen(fileName, "r");
	while (EOF != (ch = getc(file))) {
		if (ch == '\n')
			numberOfLines++;
	}
	fclose(file);
	return numberOfLines;
}

void loadLibraryFromFile(Library& library) {
	printf("\n"); printDivLine();
	printf("Enter name of file where you want to read library...\n"); printDivLine();
	char fileName[256];
	cin.getline(fileName, 256);

	FILE* file = fopen(fileName, "r");
	if (file) {
		int linesCount = countLinesInFile(fileName);
		if (linesCount == 0) {
			printDivLine(); printf("File with library is empty\n"); printDivLine();
		}
		else {
			clearLibrary(library);
			for (int i = 0; i < linesCount; i++) {
				Book* book = new Book();
				fscanf(file, "%s %s %d %lf %s", &(*book).title, &(*book).author, &(*book).year, &(*book).price, &(*book).category);

				strcpy_s((*book).title, book_sizes::TITLE_SIZE, decoding((*book).title));
				strcpy_s((*book).author, book_sizes::AUTHOR_SIZE, decoding((*book).author));
				strcpy_s((*book).category, book_sizes::CATEGORY_SIZE, decoding((*book).category));
				addBook(library, book);
			}
			fclose(file);
			printDivLine(); printf("Library was updated by \'%s\' file (%d books)\n", fileName, linesCount); printDivLine();
		}
	}
	else {
		printDivLine(); printf("Error while opening this file!\n"); printDivLine();
	}
	printf("\n");
}


void loadLibraryToFile(Library& library) {
	printf("\n");

	if (library.numberOfBooks == 0) {
		printDivLine(); printf("There aren't books in library!\n"); printDivLine();
	}

	else {
		printDivLine();
		printf("Enter name of file where you want to write library...\n"); printDivLine();
		char fileName[256];
		cin.getline(fileName, 256);

		FILE* file = fopen(fileName, "w");
		if (file) {
			for (int i = 0; i < library.numberOfBooks; i++) {
				Book book = *library.books[i];
				fprintf(file, "%s %s %d %.2lf %s\n", encoding(book.title), encoding(book.author), book.year, book.price, encoding(book.category));
			}

			fclose(file);
			printDivLine(); printf("Library was saved to \'%s\'\n", fileName); 	printDivLine();
		}
		else {
			printDivLine(); printf("This file name is unvalid!\n"); printDivLine();
		}
	}
	printf("\n");
}