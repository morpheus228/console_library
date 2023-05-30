#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "library.h"
#include "other.h"

using namespace std;

const int LibrarySize = 3;
const char* sortTypes[] = { "By title", "By author", "By year", "By price", "By category" };
const int sortTypesCount = sizeof(sortTypes) / sizeof(sortTypes[0]);

void initLibrary(Library& library) {
	library.numberOfBooks = 0;
	library.capacity = LibrarySize;
	library.books = new Book * [LibrarySize];
}

bool checkvAvailabilityOfBooks(Library& library) {
	if (library.numberOfBooks == 0) {
		printf("\n"); printDivLine();
		printf("There aren't books in library!\n");
		printDivLine(); printf("\n");
		return false;
	}
	return true;
}

void printLibrary(Library& library) {
	if (checkvAvailabilityOfBooks(library)){
		cout << endl; printDivLine();
		cout << "          $$$$$ LIBRARY: $$$$$" << endl;
		printDivLine();
		for (int i = 0; i < library.numberOfBooks; i++) {
			printBook(library.books[i]);
			printDivLine();
		}
	}
}

void addNewBook(Library& library) {
	if (library.numberOfBooks <= library.capacity) {
		insertNewBook(library);
		if (library.numberOfBooks == library.capacity) {
			increaseLibrary(library);
		}
	}
	else {
		increaseLibrary(library);
		insertNewBook(library);
	}
	printDivLine();
	printf("SUCCESS! You added new book to library!\n");
	printDivLine(); printf("\n");
}

void addBook(Library& library, Book* book) {
	if (library.numberOfBooks <= library.capacity) {
		insertBook(library, book);
		if (library.numberOfBooks == library.capacity) {
			increaseLibrary(library);
		}
	}
	else {
		increaseLibrary(library);
		insertBook(library, book);
	}
}

void insertNewBook(Library& library) {
	Book* newBook = new Book();
	initBook(newBook);
	library.numberOfBooks++;
	library.books[library.numberOfBooks - 1] = newBook;
}

void insertBook(Library& library, Book* book) {
	library.numberOfBooks++;
	library.books[library.numberOfBooks - 1] = book;
}

void increaseLibrary(Library& library) {
	Book** tmp = new Book * [library.capacity];
	int prevCap = library.capacity;
	int newCapacity = library.capacity + LibrarySize;
	for (int i = 0; i < library.capacity; i++) {
		tmp[i] = library.books[i];
	}
	delete[] library.books;
	library.books = new Book * [newCapacity];
	library.capacity = newCapacity;
	for (int i = 0; i < prevCap; i++) {
		library.books[i] = tmp[i];
	}
}

void deleteBook(Library& library) {
	if (checkvAvailabilityOfBooks(library)) {
		int bookId = 0;
		int choise = 0;

		printf("\n"); printDivLine(); printf("Which book do you want to delete:\n"); printDivLine();

		for (int i = 0; i < library.numberOfBooks; i++) {
			Book book = *(library.books[i]);
			printf("[%d] - <<%s>> %s\n", i + 1, book.title, book.author);
		}

		printDivLine(); printf("Enter ID of book, which you want to delete...\n"); printDivLine();

		while (true) {
			bool valid;
			intReading(valid, bookId);

			if (!valid) {
				printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else if (bookId <= 0 or bookId > library.numberOfBooks) {
				printDivLine(); printf("ID of book is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else break;
		}

		bookId -= 1;
		Book deleted_book = *(library.books[bookId]);

		printDivLine(); printf("Are you really want to delete <<%s>> %s?\n", deleted_book.title, deleted_book.author);
		printDivLine(); printf("Enter 1 - yes, 0 - no...\n"); printDivLine();

		while (true) {
			bool valid;
			intReading(valid, choise);

			if (!valid) {
				printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else if ((choise != 1) and (choise != 0)) {
				printDivLine(); printf("Invalid choise! Enter 1 - yes, 0 - no...\n"); printDivLine();
				continue;
			}
			else break;
		}

		if (choise == 1) {
			for (int i = bookId; i < library.numberOfBooks; i++) {
				library.books[i] = library.books[i + 1];
			}
			library.numberOfBooks--;
			printDivLine(); printf("You deleted <<%s>> %s\n", deleted_book.title, deleted_book.author); printDivLine();
		}
	}
}

float(*comparator[])(Book&, Book&) = {
	compareTitles,
	compareAuthors,
	compareYears,
	comparePrices,
	compareCategory
};

void printLibraryWithSorting(Library &library) {
	if (checkvAvailabilityOfBooks(library)) {
		int key_choise = 0;
		int type_choise = 0;
		printf("\n"); printDivLine(); printf("Choose sorting key ID:\n"); printDivLine();

		for (int i = 0; i < sortTypesCount; i++) {
			printf("[%d] - %s\n", i + 1, sortTypes[i]);
		}
		printDivLine();

		while (true) {
			bool valid;
			intReading(valid, key_choise);

			if (!valid) {
				printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else if (key_choise <= 0 or key_choise > sortTypesCount) {
				printDivLine(); printf("Entered ID is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else break;
		}

		printDivLine(); printf("Choose type of sorting ID:\n"); printDivLine();
		printf("[1] - Ascending\n"); 
		printf("[2] - Descending\n");
		printDivLine();

		while (true) {
			bool valid;
			intReading(valid, type_choise);

			if (!valid) {
				printDivLine(); printf("ERROR: Entered expression is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else if (type_choise <= 0 or type_choise > 2) {
				printDivLine(); printf("Entered ID is invalid! Try again...\n"); printDivLine();
				continue;
			}
			else break;
		}
		key_choise -= 1;
		cout << key_choise << endl;
		sortLibrary(library, comparator[key_choise], type_choise);
		printLibrary(library);
	}
}


void sortLibrary(Library& library, float(*comparators)(Book&, Book&), int type_choise) {
	Book** booksArray = library.books;
	for (int i = 1; i < library.numberOfBooks; i++) {
		for (int j = 0; j < library.numberOfBooks - 1; j++) {
			if (type_choise == 1) {
				if (comparators(*booksArray[j], *booksArray[j + 1]) > 0) {
					Book* tmpBook = booksArray[j];
					booksArray[j] = booksArray[j + 1];
					booksArray[j + 1] = tmpBook;
				}
			}
			else {
				if (comparators(*booksArray[j], *booksArray[j + 1]) < 0) {
					Book* tmpBook = booksArray[j];
					booksArray[j] = booksArray[j + 1];
					booksArray[j + 1] = tmpBook;
				}
			}
		}
	}
}

void countByCategory(Library& library) {
	printf("\n");  printDivLine();
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

	int count = 0;
	for (int i = 0; i < library.numberOfBooks; i++) {
		if (strcmp((*(library.books[i])).category, category) == 0) count++;
	}
	printDivLine(); printf("There are %d books of %s category in library\n", count, category); printDivLine();

}

void removeLibrary(Library& library) {
	for (int i = 0; i < library.numberOfBooks; i++) {
		delete library.books[i];
	}
	library.capacity = 0;
	library.numberOfBooks = 0;
	delete[] library.books;
}

void clearLibrary(Library& library) {
	library.capacity = LibrarySize;
	library.numberOfBooks = 0;
	delete[] library.books;
	library.books = new Book * [library.capacity];
}