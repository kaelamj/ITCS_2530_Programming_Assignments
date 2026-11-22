// HobbyProgram.cpp 
//Week 5 Assignment 

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std;

enum BookRating
{
	NotRated = 0,
	OneStar = 1,
	TwoStars = 2,
	ThreeStars = 3,
	FourStars= 4,
	FiveStars = 5
};
//------Function Prototypes------

void bannerMessage();
void changeConsoleColor();
void displayMenu();
void saveReport(string bookTitle, int totalPages, int endPage, int pagesRemaining, double percentageComplete, double avgTimePerPage, double timeRemaining, BookRating rating);
void displaySummary(string bookTitle, int totalPages, int endPage, int pagesRemaining, double percentageComplete, double avgTimePerPage, double timeRemaining);

void displayBookShelf(const string bookTitles[], int booksAdded);
void addBooks(string bookTitles[], int totalPages[], int currentPages[], int sessionsLogged[], int totalPagesRead[], double totalMinutesRead[],
	BookRating bookRatings[], int& booksAdded, int& selectedBook, int maxBooks);
void displayBookRating(BookRating rating);
void calculateReadingProgress(int currentPages, int totalPages, int& pagesRemaining, double& percentageComplete);

int getValidInt(string prompt, int minValue, int maxValue);
string getValidString(string prompt);
double getValidDouble(string prompt);

double calculatePercentage(int currentPage, int totalPages);
double calculateAvgTimePerPage(double totalMinutes, int pagesRead);
double calculateTimeRemaining(int remainingPages, double minutesPerPage);

int main() {

	// Variable declarations

	const int MAX_BOOKS = 5;
	int booksAdded = 0;
	int selectedBook = -1;

	string bookTitles[MAX_BOOKS] = {};
	int totalPages[MAX_BOOKS] = {};
	int currentPages[MAX_BOOKS] = {};
	int sessionsLogged[MAX_BOOKS] = {};
	int totalPagesRead[MAX_BOOKS] = {};
	double totalMinutesRead[MAX_BOOKS] = {};
	BookRating bookRatings[MAX_BOOKS] = {};
	
	int startPage = 0;
	int endPage = 0;
	double minutesRead = 0.0;

	int pagesRemaining = 0;
	double percentageComplete = 0.0;
	double avgTimePerPage = 0.0;
	double timeRemaining = 0.0;

	

	changeConsoleColor();
	bannerMessage();

	int choice = 0;
	do
	{
		// -----------------------------------------------
		//  Display Menu: Switch to handle user choices
		// Do while loop to allow for multiple selections
		// -----------------------------------------------
		displayMenu();
		choice = getValidInt("Enter your choice: ", 1, 6);

		switch (choice)
		{
		case 1:
		{
			// Check if bookshelf is empty

			if (booksAdded == 0)
			{
				cout << "Your bookshelf is empty." << endl;
				cout << "Let's add your first book!" << endl;
				addBooks(bookTitles, totalPages, currentPages, sessionsLogged, totalPagesRead, totalMinutesRead, bookRatings, booksAdded, selectedBook, MAX_BOOKS);
			}

			int bookShelfChoice = 0;
			do
			{
				cout << "1. View / Select a Book" << endl;
				cout << "2. Add a book" << endl;
				cout << "3. Main Menu" << endl;

				bookShelfChoice = getValidInt("Enter your choice: ", 1, 3);
				switch (bookShelfChoice)
				{
				case 1:
				{

					displayBookShelf(bookTitles, booksAdded);

					// lets users choose the book they'd like to view. 
					// subtract choice by 1 for array conversion.
					int bookChoice = getValidInt("Select a book by number: ", 1, booksAdded);

					selectedBook = bookChoice - 1;
					cout << "Selected book: " << bookTitles[selectedBook] << endl;

					break;
				}
				case 2:
				{
					addBooks(bookTitles, totalPages, currentPages, sessionsLogged, totalPagesRead, totalMinutesRead, bookRatings, booksAdded, selectedBook, MAX_BOOKS);
					break;
				}
				case 3:
				{
					// return to main menu
					break;
				}
				}
			} while (bookShelfChoice != 3);
			break;
		}
		case 2:
		{
			// Check if a book has been added or selected

			if (selectedBook < 0 || selectedBook >= booksAdded) {
				cout << "Please add or select a book first." << endl;
				break;
			}
			// Check if the book has been completed 
			if (sessionsLogged[selectedBook] > 0 && currentPages[selectedBook] >= totalPages[selectedBook])
			{
				cout << "You've already completed this book!" << endl;
				break;
			}

			// using a while loop to allow for multiple entries 
			char logSession = 'y';
			while (logSession == 'y' || logSession == 'Y')
			{
				// this if statement checks for previous logged entries, that way it doesn't require the user to re-enter starting page for each session. 

				if (sessionsLogged[selectedBook] == 0) {

					startPage = getValidInt("Enter the starting page: ", 0, totalPages[selectedBook] - 1);
				}
				else {

					startPage = currentPages[selectedBook];

					cout << "Starting page: " << startPage << endl;
				}

				endPage = getValidInt("Enter the ending page: ", startPage + 1, totalPages[selectedBook]);
				minutesRead = getValidDouble("Enter the total reading time in minutes: ");

				totalPagesRead[selectedBook] += endPage - startPage;
				totalMinutesRead[selectedBook] += minutesRead;
				currentPages[selectedBook] = endPage;
				sessionsLogged[selectedBook]++;

				// If statement exits loop if user already finished book

				if (endPage >= totalPages[selectedBook])
				{
					cout << "You've finished your book!" << endl;
					logSession = 'n';
				}
				else
				{
					cout << "Would you like to log another session? Enter 'Y' to continue." << endl;
					cin >> logSession;
				}
			}
			break;
		}
		case 3:
		{
			// Verify that a valid book has been selected.
			if (selectedBook < 0 || selectedBook >= booksAdded)
			{
				cout << "You must add or select a book before rating it." << endl;
				break;
			}

			// Display the selected book and current rating
			cout << "Title: " << bookTitles[selectedBook] << "|";
			displayBookRating(bookRatings[selectedBook]);

			// prompt the user to enter a rating from 1 to 5.
			int ratingChoice = getValidInt(
				"Enter a rating from 1 to 5 stars: ",
				1,
				5
			);

			// Convert the integer to the BookRating enum
			bookRatings[selectedBook] =
				static_cast<BookRating>(ratingChoice);

			cout << "Book rating saved successfully!" << endl;

			displayBookRating(bookRatings[selectedBook]);
			break;
		}
		case 4:
		{
			if (selectedBook < 0 || selectedBook >= booksAdded)
			{
				cout << "You must add or select a book before viewing the summary." << endl;
				break;
			}
			// calculations moved here from case 3 because the user can now switch between books.
			// created a function to do the calculations so they aren't repeated in cases 4 & 5.
			calculateReadingProgress(currentPages[selectedBook], totalPages[selectedBook], pagesRemaining, percentageComplete);

			// calculate the selected books avg reading time and eta
			if (totalPagesRead[selectedBook] > 0 && totalMinutesRead[selectedBook] > 0)
			{
				avgTimePerPage = calculateAvgTimePerPage(totalMinutesRead[selectedBook],totalPagesRead[selectedBook]);

				timeRemaining = calculateTimeRemaining(pagesRemaining,avgTimePerPage);
			}
			else
			{
				avgTimePerPage = 0.0;
				timeRemaining = 0.0;
			}
			// function call to display summary
			displaySummary(
				bookTitles[selectedBook],
				totalPages[selectedBook],
				currentPages[selectedBook],
				pagesRemaining,
				percentageComplete,
				avgTimePerPage,
				timeRemaining
			);

			displayBookRating(bookRatings[selectedBook]);

			break;
		}
		case 5:
		{
			// Verify that a valid book has been selected.
			if (selectedBook < 0 || selectedBook >= booksAdded)
			{
				cout << "You must add or select a book before saving a report." << endl;
				break;
			}

			// Calculate reading progress
			calculateReadingProgress(currentPages[selectedBook], totalPages[selectedBook], pagesRemaining, percentageComplete);

			// Calculate average reading time and estimated time remaining.
			if (totalPagesRead[selectedBook] > 0 && totalMinutesRead[selectedBook] > 0)
			{
				avgTimePerPage = calculateAvgTimePerPage(totalMinutesRead[selectedBook], totalPagesRead[selectedBook]);

				timeRemaining = calculateTimeRemaining(pagesRemaining, avgTimePerPage);
			}
			else
			{
				avgTimePerPage = 0.0;
				timeRemaining = 0.0;
			}

			// Save the selected book's summary to a text file.
			saveReport(
				bookTitles[selectedBook],
				totalPages[selectedBook],
				currentPages[selectedBook],
				pagesRemaining,
				percentageComplete,
				avgTimePerPage,
				timeRemaining,
				bookRatings[selectedBook]
			);

			break;  
		}
		case 6:
		{
			cout << "Exiting program." << endl;
			return 0;
		}
		default:
		{
			cout << "Invalid selection. Enter a number 1-6." << endl;
			break;
		}
		}
	} while (choice != 6);

	return 0;
}

//---------------------------------------------
//   Function to change the console color
// The system function is used to execute 
//            windows commands. 
//  Hexadecimal: backgroundColor-textColor
//---------------------------------------------

void changeConsoleColor()
{
	system("color 0B");
}

//--------------------------------------------
//        Display Welcome Banner
//--------------------------------------------

void bannerMessage()
{
	cout << "Welcome! Let's begin tracking your current book." << endl;
	cout << "This program will track your progress, find your reading speed, and estimate the time it'll take to finish your current book." << endl;
}
//---------------------------------------------
//        Function to Display Menu
//---------------------------------------------

void displayMenu()
{
	cout << "Select a menu option below: " << endl;
	cout << "1. Bookshelf" << endl;
	cout << "2. Log a reading session" << endl;
	cout << "3. Rate a title." << endl;
	cout << "4. View reading summary" << endl;
	cout << "5. Save a copy of your summary to report.txt" << endl;
	cout << "6. Exit" << endl;
}

//---------------------------------------------
//      Display BookShelf Function
//---------------------------------------------
void displayBookShelf(const string bookTitles[], int booksAdded)
{
	cout << "========== Book Shelf ===========" << endl;

	for (int i = 0; i < booksAdded; i++) {

		cout << i + 1 << ". "
			<< bookTitles[i] << endl;
	}

	cout << "=================================" << endl;
}

//---------------------------------------------
//      Display Book Ratings Function
//---------------------------------------------

void displayBookRating(BookRating rating)
{
	switch (rating)
	{
	case OneStar:
		cout << "Rating: * (1/5)" << endl;
		break;

	case TwoStars:
		cout << "Rating: ** (2/5)" << endl;
		break;

	case ThreeStars:
		cout << "Rating: *** (3/5)" << endl;
		break;

	case FourStars:
		cout << "Rating: **** (4/5)" << endl;
		break;

	case FiveStars:
		cout << "Rating: ***** (5/5)" << endl;
		break;

	case NotRated:
		cout << "Rating: Not rated yet" << endl;
		break;

	default:
		cout << "Rating: Unknown" << endl;
		break;
	}
}

//---------------------------------------------
//     Add Books Function
//---------------------------------------------

void addBooks(string bookTitles[], int totalPages[], int currentPages[], int sessionsLogged[], int totalPagesRead[], double totalMinutesRead[],
	BookRating bookRatings[], int& booksAdded, int& selectedBook, int maxBooks)
{
	// check if bookshelf is full
	if (booksAdded >= maxBooks)
	{
		cout << "Your bookshelf is full." << endl;
		return;
	}

	int remainingSlots = maxBooks - booksAdded;

	// For loop to add titles to the array.
	int numberOfBooks = getValidInt("Enter the number of books you'd like to add: ", 1, remainingSlots);
	for (int i = 0; i < numberOfBooks; i++)
	{
		cout << "Book " << booksAdded + 1 << endl;
		bookTitles[booksAdded] = getValidString("Enter the title of the book: ");
		totalPages[booksAdded] = getValidInt("Enter the total page length of the book: ", 1, INT_MAX);

		// initialize new book progress to 0 
		currentPages[booksAdded] = 0;
		sessionsLogged[booksAdded] = 0;
		totalPagesRead[booksAdded] = 0;
		totalMinutesRead[booksAdded] = 0.0;
		bookRatings[booksAdded] = NotRated;

		// select book and increment variables
		selectedBook = booksAdded;
		booksAdded++;
	}

	cout << "Book added successfully!" << endl;
}


//---------------------------------------------
//      Summary Report Display Function
//---------------------------------------------

void displaySummary(string bookTitle, int totalPages, int endPage, int pagesRemaining, double percentageComplete, double avgTimePerPage, double timeRemaining)
{
	// Displaying the summary report
	const int totalWidth = 48;
	const int leftColumn = 32;
	const int rightColumn = 16;

	cout << setfill('=') << setw(totalWidth) << "" << endl;
	cout << setfill(' ');
	cout << "Reading Progress Tracker" << endl;
	cout << setfill('=') << setw(totalWidth) << "" << endl;
	cout << setfill(' ');

	cout << left << setw(leftColumn) << "Book Information" << endl;
	cout << setfill('-') << setw(totalWidth) << "" << endl;
	cout << setfill(' ');

	cout << left << setw(leftColumn) << "Book Title: "
		<< right << setw(rightColumn) << bookTitle << endl;
	cout << left << setw(leftColumn) << "Total Page Length: "
		<< right << setw(rightColumn) << totalPages << endl;
	cout << left << setw(leftColumn) << "Current Page: "
		<< right << setw(rightColumn) << endPage << endl;
	cout << left << setw(leftColumn) << "Pages Remaining: "
		<< right << setw(rightColumn) << pagesRemaining << endl;

	cout << setfill('-') << setw(totalWidth) << "" << endl;
	cout << setfill(' ');

	cout << "Reading Progress" << endl;

	//---------------------------------------------
	//                For Loop:
	// This for loop creates a progress bar, where
	// each bar equals 5%. Truncates the percentage, 
	// loop iterates and prints '#' for each 'block'
	//  complete.
	//---------------------------------------------

	int progressBlocks = static_cast<int>(percentageComplete / 5);
	cout << "[";

	for (int i = 1; i <= 20; i++)
	{
		if (i <= progressBlocks)
		{
			cout << "#";
		}
		else
		{
			cout << "-";
		}
	}

	cout << "]";
	cout << right << setw(totalWidth - 23)
		<< fixed << setprecision(2)
		<< percentageComplete << "%" << endl;
	cout << endl;

	cout << "Reading Time Estimate" << endl;
	cout << left << setw(leftColumn) << "Average Time Per Page: "
		<< right << setw(rightColumn) << avgTimePerPage << " min" << endl;
	cout << left << setw(leftColumn) << "Estimated Time Remaining: "
		<< right << setw(rightColumn) << timeRemaining << " hours" << endl;
	cout << "\n";
	cout << setfill('=') << setw(totalWidth) << "" << endl;
	cout << setfill(' ');
}

//---------------------------------------------
//        Function to Save Report
//---------------------------------------------

void saveReport(string bookTitle, int totalPages, int endPage,
	int pagesRemaining, double percentageComplete,
	double avgTimePerPage, double timeRemaining, BookRating rating)
{
	const int totalWidth = 48;
	const int leftColumn = 32;
	const int rightColumn = 16;

	ofstream reportFile("report.txt");
	if (!reportFile)
	{
		cout << "Error: Unable to create report.txt!" << endl;
		return;
	}
	reportFile << setfill('=') << setw(48) << "" << endl;
	reportFile << setfill(' ');
	reportFile << "Reading Progress Tracker" << endl;
	reportFile << setfill('=') << setw(48) << "" << endl;
	reportFile << setfill(' ');
	reportFile << left << setw(32) << "Book Information" << endl;
	reportFile << setfill('-') << setw(48) << "" << endl;
	reportFile << setfill(' ');
	reportFile << left << setw(32) << "Book Title: "
		<< right << setw(16) << bookTitle << endl;
	reportFile << left << setw(32) << "Total Page Length: "
		<< right << setw(16) << totalPages << endl;
	reportFile << left << setw(32) << "Current Page: "
		<< right << setw(16) << endPage << endl;
	reportFile << left << setw(32) << "Pages Remaining: "
		<< right << setw(16) << pagesRemaining << endl;

	// Display the book rating in the report.

	if (rating == NotRated)
	{
		reportFile << left << setw(leftColumn) << "Book Rating: "
			<< right << setw(rightColumn) << "Not rated yet" << endl;
	}
	else
	{
		reportFile << left << setw(leftColumn) << "Book Rating: "
			<< right << setw(rightColumn) << static_cast<int>(rating)
			<< "/5" << endl;
	}

	reportFile << setfill('-') << setw(totalWidth) << "" << endl;
	reportFile << setfill(' ');

	reportFile << "Reading Progress" << endl;

	int progressBlocks = static_cast<int>(percentageComplete / 5);
	reportFile << "[";

	for (int i = 1; i <= 20; i++)
	{
		if (i <= progressBlocks)
		{
			reportFile << "#";
		}
		else
		{
			reportFile << "-";
		}
	}

	reportFile << "]";
	reportFile << right << setw(totalWidth - 23) << fixed << setprecision(2) << percentageComplete << "%" << endl;
	reportFile << endl;

	reportFile << "Reading Time Estimate" << endl;
	reportFile << left << setw(leftColumn) << "Average Time Per Page: "
		<< right << setw(rightColumn) << avgTimePerPage << " min" << endl;
	reportFile << left << setw(leftColumn) << "Estimated Time Remaining: "
		<< right << setw(rightColumn) << timeRemaining << " hours" << endl;
	reportFile << "\n";
	reportFile << setfill('=') << setw(totalWidth) << "" << endl;
	reportFile << setfill(' ');
	reportFile.close();
	cout << "Your reading summary report has been saved to report.txt!" << endl;
}


//---------------------------------------------
//        Input Validation Functions
//---------------------------------------------

int getValidInt(string prompt, int minValue, int maxValue)
{
	int value;
	cout << prompt;
	cin >> value;

	while (cin.fail() || value <  minValue || value > maxValue)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. " << prompt;
		cin >> value;
	}
	return value;
}

string getValidString(string prompt)
{
	string value;
	cout << prompt;
	getline(cin >> ws, value);
	while (value.empty())
	{
		cout << "Invalid input. " << prompt;
		getline(cin >> ws, value);
	}
	return value;
}

double getValidDouble(string prompt)
{
	double value;
	cout << prompt;
	cin >> value;
	while (cin.fail() || value <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. " << prompt;
		cin >> value;
	}
	return value;
}

//---------------------------------------------
//       Calculation Functions
//---------------------------------------------

double calculatePercentage(int currentPage, int totalPages)
{
	return (static_cast<double>(currentPage) / totalPages) * 100;
}

double calculateAvgTimePerPage(double totalMinutes, int pagesRead)
{
	if (pagesRead > 0 && totalMinutes > 0)
	{
		return totalMinutes / pagesRead;
	}
	else
	{
		return 0.0;
	}

}

double calculateTimeRemaining(int remainingPages, double minutesPerPage)
{
	return (remainingPages * minutesPerPage) / 60.0;
}
void calculateReadingProgress(int currentPages, int totalPages, int& pagesRemaining, double& percentageComplete)
{
	pagesRemaining = totalPages - currentPages;
	percentageComplete = calculatePercentage(currentPages, totalPages);
}