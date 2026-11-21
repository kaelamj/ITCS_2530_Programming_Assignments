// HobbyProgram.cpp 
//Week 5 Assignment 

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cmath> // provides isfinite for checking reading-time values. -DD

using namespace std;

// set the largest number of reading sessions the array can hold. -DD
const int MAX_SESSIONS = 1000;

// enum to classify the book length based on total pages. -DD
enum BookLength
{
	Short,
	Medium,
	Long
};

//------Function Prototypes------

void bannerMessage();
void changeConsoleColor();
void displayMenu();

// changed to show number of reading sessions logged. -DD
void saveReport(string bookTitle, int totalPages, int endPage, int pagesRemaining, const int startPages[], const int endPages[], const double minutesRead[], int sessionsLogged, double percentageComplete, double avgTimePerPage, double timeRemaining);
void displaySummary(string bookTitle, int totalPages, int endPage, int pagesRemaining, const int startPages[], const int endPages[], const double minutesRead[], int sessionsLogged, double percentageComplete, double avgTimePerPage, double timeRemaining);

int getValidInt(string prompt, int minValue, int maxValue);
string getValidString(string prompt);
double getValidDouble(string prompt);

double calculatePercentage(int currentPage, int totalPages);
double calculateAvgTimePerPage(double totalMinutes, int pagesRead);
double calculateTimeRemaining(int remainingPages, double minutesPerPage);

//added functions to classify the book length and return a string label for display. -DD
BookLength classifyBookLength(int totalPages);
string getBookLengthLabel(BookLength bookLength);

// collect session values in matching array indexes and update the number stored. -DD
void logReadingSessions(int startPages[], int endPages[], double minutesRead[], int& sessionsLogged, int capacity, int totalPages);

int main() {

	// Variable declarations

	string bookTitle;
	int totalPages = 0;
	int endPage = 0;
	int sessionsLogged = 0;

	// store each session value in matching indexes across the three arrays. -DD
	int startPages[MAX_SESSIONS] = {};
	int endPages[MAX_SESSIONS] = {};
	double minutesRead[MAX_SESSIONS] = {};

	int pagesRemaining = 0;
	int totalPagesRead = 0;
	double totalMinutesRead = 0.0;
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
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Let's start by gathering some information about your current book." << endl;
			bookTitle = getValidString("Enter the title of the book: ");
			totalPages = getValidInt("Enter the total page length of the book: ", 1, INT_MAX);  // int_max is a constant that represents the max val an integer can hold.

			// Adding a new book would overwrite previous logged sessions for right now. 
			// Variables reset when adding a new book

			endPage = 0;
			sessionsLogged = 0;

			totalPagesRead = 0;
			totalMinutesRead = 0.0;

			pagesRemaining = totalPages;
			percentageComplete = 0.0;
			avgTimePerPage = 0.0;
			timeRemaining = 0.0;

			break;
		}
		case 2:
		{
			// ---------------------------------------------
			// Selection statement in cases 2-4 ensure a
			// book has been added before anything else
			//         can be viewed or amended.
			// ---------------------------------------------

			if (bookTitle.empty() || totalPages <= 0)
			{
				cout << "Please add a book before logging a reading session." << endl;
			}
			else
			{
				cout << "Let's begin logging your reading session!" << endl;
				// add sessions to the array, then recalculate totals from its entries. -DD
				logReadingSessions(startPages, endPages, minutesRead, sessionsLogged, MAX_SESSIONS, totalPages);

				totalPagesRead = 0;
				totalMinutesRead = 0.0;
				// sum pages and minutes from every session stored for this book. -DD
				for (int i = 0; i < sessionsLogged; i++)
				{
					totalPagesRead += endPages[i] - startPages[i];
					totalMinutesRead += minutesRead[i];
				}

				if (sessionsLogged > 0)
				{
					endPage = endPages[sessionsLogged - 1];
				}

				pagesRemaining = totalPages - endPage;
				percentageComplete = calculatePercentage(endPage, totalPages);
				if (totalPagesRead > 0 && totalMinutesRead > 0)
				{
					avgTimePerPage = calculateAvgTimePerPage(totalMinutesRead, totalPagesRead);
					timeRemaining = calculateTimeRemaining(pagesRemaining, avgTimePerPage);
				}
				else
				{
					avgTimePerPage = 0.0;
					timeRemaining = 0.0;
				}
			}
			break;
		}
		case 3:
		{
			if (bookTitle.empty() || totalPages <= 0)
			{
				cout << "You must add a book before viewing the summary." << endl;
			}
			else
			{
				displaySummary(bookTitle, totalPages, endPage, pagesRemaining, startPages, endPages, minutesRead, sessionsLogged, percentageComplete, avgTimePerPage, timeRemaining);
			}
			break;
		}
		case 4:
		{
			if (bookTitle.empty() || totalPages <= 0)
			{
				cout << "You must add a book before saving a report." << endl;
			}
			else
			{
				saveReport(bookTitle, totalPages, endPage, pagesRemaining, startPages, endPages, minutesRead, sessionsLogged, percentageComplete, avgTimePerPage, timeRemaining);
			}

			break;
		}
		case 5:
		{
			cout << "Exiting program." << endl;
			return 0;
		}
		default:
		{
			cout << "Invalid selection. Enter a number 1-5." << endl;
			break;
		}
		}
	} while (choice != 5);

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
	cout << "Select a menu option below by entering the corresponding number: " << endl;
	cout << "1. Add a book" << endl;
	cout << "2. Log a reading session" << endl;
	cout << "3. View reading summary" << endl;
	cout << "4. Save a copy of your summary to report.txt" << endl;
	cout << "5. Exit" << endl;
}

//---------------------------------------------
//      Summary Report Display Function
//---------------------------------------------


void displaySummary(string bookTitle, int totalPages, int endPage, int pagesRemaining, const int startPages[], const int endPages[], const double minutesRead[], int sessionsLogged, double percentageComplete, double avgTimePerPage, double timeRemaining)
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
	cout << left << setw(leftColumn) << "Book Length Category: "
		<< right << setw(rightColumn) << getBookLengthLabel(classifyBookLength(totalPages)) << endl;
	cout << left << setw(leftColumn) << "Current Page: "
		<< right << setw(rightColumn) << endPage << endl;
	cout << left << setw(leftColumn) << "Pages Remaining: "
		<< right << setw(rightColumn) << pagesRemaining << endl;
	cout << left << setw(leftColumn) << "Reading Sessions Logged: "
		<< right << setw(rightColumn) << sessionsLogged << endl;

	cout << setfill('-') << setw(totalWidth) << "" << endl;
	cout << setfill(' ');
	// changed to show number of reading sessions logged. -DD
	cout << "Reading Sessions" << endl;
	cout << left << setw(10) << "Session"
		<< setw(12) << "Start Page"
		<< setw(10) << "End Page"
		<< right << setw(16) << "Minutes" << endl;
	for (int i = 0; i < sessionsLogged; i++)
	{
		cout << left << setw(10) << i + 1
			<< setw(12) << startPages[i]
			<< setw(10) << endPages[i]
			<< right << setw(16) << minutesRead[i] << endl;
	}
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
	int pagesRemaining, const int startPages[], const int endPages[],
	const double minutesRead[], int sessionsLogged, double percentageComplete,
	double avgTimePerPage, double timeRemaining)
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
	reportFile << left << setw(32) << "Book Length Category: "
		<< right << setw(16) << getBookLengthLabel(classifyBookLength(totalPages)) << endl;
	reportFile << left << setw(32) << "Current Page: "
		<< right << setw(16) << endPage << endl;
	reportFile << left << setw(32) << "Pages Remaining: "
		<< right << setw(16) << pagesRemaining << endl;
	reportFile << left << setw(32) << "Reading Sessions Logged: "
		<< right << setw(16) << sessionsLogged << endl;

	reportFile << setfill('-') << setw(totalWidth) << "" << endl;
	reportFile << setfill(' ');
	// changed to show number of reading sessions logged. -DD
	reportFile << "Reading Sessions" << endl;
	reportFile << left << setw(10) << "Session"
		<< setw(12) << "Start Page"
		<< setw(10) << "End Page"
		<< right << setw(16) << "Minutes" << endl;
	for (int i = 0; i < sessionsLogged; i++)
	{
		reportFile << left << setw(10) << i + 1
			<< setw(12) << startPages[i]
			<< setw(10) << endPages[i]
			<< right << setw(16) << minutesRead[i] << endl;
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
// added a function to log reading sessions, which collects the starting page, ending page, and total reading time for each session. 
// it also validates the input and ensures that the user cannot log more sessions than the array can hold or log sessions after finishing the book.
// passes arrays in the function parameters to store the session data and updates the number of sessions logged. -DD
void logReadingSessions(int startPages[], int endPages[], double minutesRead[], int& sessionsLogged, int capacity, int totalPages)
{
	// continue accepting sessions until the user stops, the book is done, or the array is full. -DD
	char logSession = 'y';
	while (logSession == 'y' || logSession == 'Y')
	{
		// Stop before writing past the end of the session array. -DD
		if (sessionsLogged >= capacity)
		{
			cout << "The maximum number of reading sessions has been reached." << endl;
			break;
		}

		// A completed book cannot have another reading session. -DD
		if (sessionsLogged > 0 && endPages[sessionsLogged - 1] >= totalPages)
		{
			cout << "Congratulations! You've finished your book!" << endl;
			break;
		}

		int startPage;
		if (sessionsLogged == 0)
		{
			// ask for the initial page only for the first session. -DD
			startPage = getValidInt("Enter the starting page: ", 0, totalPages - 1);
		}
		else
		{
			// continue from the ending page of the previous session. -DD
			startPage = endPages[sessionsLogged - 1];
			cout << "Starting page: " << startPage << endl;
		}

		// store this session's page range and reading time in the current array slot. -DD
		startPages[sessionsLogged] = startPage;
		endPages[sessionsLogged] = getValidInt("Enter the ending page: ", startPage + 1, totalPages);
		minutesRead[sessionsLogged] = getValidDouble("Enter the total reading time in minutes: ");
		// check the values at this index in the arrays and ask again if invalid. -DD
		while (endPages[sessionsLogged] <= startPages[sessionsLogged] ||
			endPages[sessionsLogged] > totalPages ||
			!isfinite(minutesRead[sessionsLogged]) || minutesRead[sessionsLogged] <= 0)
		{
			cout << "Invalid reading session. Please enter the session again." << endl;
			endPages[sessionsLogged] = getValidInt("Enter the ending page: ", startPage + 1, totalPages);
			minutesRead[sessionsLogged] = getValidDouble("Enter the total reading time in minutes: ");
		}

		// count the entry only after its values pass validation. -DD
		sessionsLogged++;

		// stop prompting when this session reaches the last page. -DD
		if (endPages[sessionsLogged - 1] >= totalPages)
		{
			cout << "Congratulations! You've finished your book!" << endl;
			break;
		}

		// ask whether another session should be added to the array. -DD
		cout << "Would you like to log another session? Enter 'Y' to continue." << endl;
		cin >> logSession;
	}
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

BookLength classifyBookLength(int totalPages)
{
	if (totalPages <= 200)
	{
		return Short;
	}
	if (totalPages <= 500)
	{
		return Medium;
	}
	return Long;
}

string getBookLengthLabel(BookLength bookLength)
{
	switch (bookLength)
	{
	case Short:
		return "Short";
	case Medium:
		return "Medium";
	case Long:
		return "Long";
	default:
		return "Unknown";
	}
}
