namespace book_sizes {
	const int AUTHOR_SIZE = 100;
	const int TITLE_SIZE = 100;
	const int CATEGORY_SIZE = 30;
}

extern const char* bookCategories[];
extern const int bookCategoriesCount;

struct Book {
	char author[book_sizes::AUTHOR_SIZE];
	char title[book_sizes::TITLE_SIZE];
	int year;
	double price;
	char category[book_sizes::CATEGORY_SIZE];
};

void initBook(struct Book* book);
void printBook(struct Book* book);

float compareTitles(Book& first, Book& second);
float compareAuthors(Book& first, Book& second);
float compareYears(Book& first, Book& second);
float comparePrices(Book& first, Book& second);
float compareCategory(Book& first, Book& second);