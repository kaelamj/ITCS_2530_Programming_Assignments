// HobbyProgram.cpp 
//Week 5 Assignment 

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std;

//------Function Prototypes------

void bannerMessage();
void changeConsoleColor();
void displayMenu();
void saveReport(string bookTitle, int totalPages, int endPage, int pagesRemaining, double percentageComplete, double avgTimePerPage, double timeRemaining);
void displaySummary(string bookTitle, int totalPages, int endPage, int pagesRemaining, double percentageComplete, double avgTimePerPage, double timeRemaining);

int getValidInt(string prompt, int minValue, int maxValue);
string getValidString(string prompt);
double getValidDouble(string prompt);

double calculatePercentage(int currentPage, int totalPages);
double calculateAvgTimePerPage(double totalMinutes, int pagesRead);
double calculateTimeRemaining(int remainingPages, double minutesPerPage);

int main() {

	// Variable declarations

	string bookTitle;
	int totalPages = 0;
	int startPage = 0;
	int endPage = 0;
	int sessionsLogged = 0;
	double minutesRead = 0.0;

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

			startPage = 0;
			endPage = 0;
			minutesRead = 0.0;
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

				// using a while loop to allow for multiple entries 
				char logSession = 'y';
				while (logSession == 'y' || logSession == 'Y')
				{
					// this if statement checks for previous logged entries, that way it doesn't require the user to re-enter starting page for each session. 
					
					if (sessionsLogged == 0)
					{
						startPage = getValidInt("Enter the starting page: ", 0, totalPages - 1);
					}
					else
					{
						startPage = endPage;
						cout << "Starting page: " << startPage << endl;
					}

					endPage = getValidInt("Enter the ending page: ", startPage + 1, totalPages);
					minutesRead = getValidDouble("Enter the total reading time in minutes: ");

					totalPagesRead += endPage - startPage;
					totalMinutesRead += minutesRead;
					sessionsLogged++;

					// calculations
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
					// if statement to prevent the user from continuing if book is complete
					if (endPage >= totalPages)
					{
						cout << "Congratulations! You've finished your book!" << endl;
						logSession = 'n';
					}
					else
					{
						cout << "Would you like to log another session? Enter 'Y' to continue." << endl;
						cin >> logSession;
					}
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
				displaySummary(bookTitle, totalPages, endPage, pagesRemaining, percentageComplete, avgTimePerPage, timeRemaining);
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
				saveReport(bookTitle, totalPages, endPage, pagesRemaining, percentageComplete, avgTimePerPage, timeRemaining);
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
	reportFile << left << setw(32) << "Current Page: "
		<< right << setw(16) << endPage << endl;
	reportFile << left << setw(32) << "Pages Remaining: "
		<< right << setw(16) << pagesRemaining << endl;

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