#include "book.h"

struct Library {
	Book** books;
	int numberOfBooks;
	int capacity;
};

void initLibrary(Library& library);

void addNewBook(Library& library);
void insertNewBook(Library& library);

void addBook(Library& library, Book* book);
void insertBook(Library& library, Book* book);


void increaseLibrary(Library& library);

void printLibrary(Library& library);
void printLibraryWithSorting(Library& library);

void sortLibrary(Library& library, float(*comparators)(Book&, Book&), int type_choise);
void countByCategory(Library& library);
void deleteBook(Library& library);

void removeLibrary(Library& library);
void clearLibrary(Library& library);