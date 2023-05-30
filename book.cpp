#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <windows.h>
#include <cstring>
#include "book.h"
#include "other.h"

using namespace std;

const char* bookCategories[] = { "Crime", "Detective", "Science", "Distopia", "Cyberpunk" , "Fantasy" , "Romantic"};
const int bookCategoriesCount = sizeof(bookCategories) / sizeof(bookCategories[0]);

void printBook(struct Book* book) {
	printf("Name: %s\nAuthor: %s\nCategory: %s\nYear: %d\nPRice: %lf\n", (*book).title, (*book).author, (*book).category, (*book).year, (*book).price);
}

void initBook(struct Book* book) {
	int count;

	printf("\n"); printDivLine();
	printf("Enter name of the book...\n"); printDivLine();
	char title[book_sizes::TITLE_SIZE];

	while (true) {
		cin.getline(title, book_sizes::TITLE_SIZE);
		if (strcmp(title, "") == 0) { 
			printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
		}
		else break;
	}

	strcpy_s((*book).title, book_sizes::TITLE_SIZE, title);

	printDivLine();
	printf("Enter author of the book...\n"); printDivLine();
	char author[book_sizes::AUTHOR_SIZE];

	while (true) {
		cin.getline(author, book_sizes::TITLE_SIZE);
		if (strcmp(author, "") == 0) {
			printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
		}
		else break;
	}

	strcpy_s((*book).author, book_sizes::AUTHOR_SIZE, author);

	printDivLine();
	printf("Enter year of the book...\n"); printDivLine();
	int year = 0;

	while (true) {
		bool valid;
		intReading(valid, year);
		if (!valid) {
			printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
			continue;
		}
		else if (year < -5000 or year > 2022) {
			printDivLine();
			printf("Wrong year! (-5000 <= year <= 2022) Try again...\n"); printDivLine();
			continue;
		}
		else {
			book->year = year;
			break;
		};
	};

	printDivLine();
	printf("Enter price of the book...\n"); printDivLine();
	double price = 0.0;

	while (true) {
		bool valid;
		doubleReading(valid, price);

		if (!valid) {
			printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
			continue;
		}
		else if (price < 0) {
			printDivLine();
			printf("Wrong price! (price > 0) Try again...\n"); printDivLine();
			continue;
	}
		else {
			book->price = price;
			break;
		};
	};

	printDivLine();
	printf("Choose category ID of the book...\n"); printDivLine();
	for (int i = 0; i < bookCategoriesCount; i++) {
		printf("[%d] - %s\n", i + 1, bookCategories[i]);
	}
	printDivLine();
	int categoryId;

	while (true) {
		bool valid;
		intReading(valid, categoryId);

		if (!valid) {
			printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
			continue;
		}
		else if ((categoryId <= 0) or (categoryId > bookCategoriesCount)) {
			printDivLine(); printf("Entered ID is invalid! Try again...\n"); printDivLine();
			continue;
		}
		else break;
	}
	categoryId--;
	const char* category = bookCategories[categoryId];
	strcpy_s((*book).category, book_sizes::CATEGORY_SIZE, category);
}

float compareTitles(Book& first, Book& second) {
	return strcmp(first.title, second.title);
}

float compareAuthors(Book& first, Book& second) {
	return strcmp(first.author, second.author);
}

float compareYears(Book& first, Book& second) {
	return first.year - second.year;
}

float comparePrices(Book& first, Book& second){
	return first.price - second.price;
}

float compareCategory(Book& first, Book& second) {
	return strcmp(first.category, second.category);
}