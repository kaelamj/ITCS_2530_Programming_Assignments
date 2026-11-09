// HobbyProgram.cpp 
//Week 4 Assignment 

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {

	//---------------------------------------------
	//         Variable Declarations:
	// Because variables need to be called outside
	// of a loop, pre-initializing here.
	//---------------------------------------------

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

	const int totalWidth = 48;
	const int leftColumn = 32;
	const int rightColumn = 16;

	// Welcome message: 
	cout << "Welcome! Let's begin tracking your current read." << endl;
	cout << "This program will track your progress, find your reading speed, and estimate the time it'll take to finish your current book." << endl;

	// ---------------------------------------------
	//              Display Menu:
	// Do while loop will allow multiple entries
	// Switch statement will iterate based on case
	//----------------------------------------------

	int choice = 0;
	do
	{
		cout << "Select a menu option below by entering the corresponding number: " << endl;
		cout << "1. Add a book" << endl;
		cout << "2. Log a reading session" << endl;
		cout << "3. View reading summary" << endl;
		cout << "4. Save a copy of your summary to report.txt" << endl;
		cout << "5. Exit" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Let's start by gathering some information about your current book." << endl;
			cout << "Enter the title of the book: " << endl;
			getline(cin >> ws, bookTitle);

			// While loop is used for ALL input validations
			// ws discards any leading whitespace from input stream
			// !reminder: implement a function for input validation later to avoid repetition
			while (bookTitle.empty()) {
				cout << "Invalid input. Enter the title of the book: " << endl;
				getline(cin >> ws, bookTitle);
			}

			cout << "Enter the total page length of the book: " << endl;
			cin >> totalPages;

			while (cin.fail() || totalPages <= 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Enter the total page length of the book: " << endl;
				cin >> totalPages;
			}

			// Adding a new book would overwrite previous logged sessions for right now. 
			// !reminder: implement a way to save multiple books and their assigned statistics.
			// Reset all variables here if adding a new book.

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
			// Selection statement for input validation:
			// if statement will make sure a book has been
			// entered before someone can log a session
			// related to that title.
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
						cout << "Enter the starting page: " << endl;
						cin >> startPage;

						while (cin.fail() || startPage < 0 || startPage >= totalPages)
						{
							cin.clear();
							cin.ignore(1000, '\n');

							cout << "Invalid input. Enter the starting page: " << endl;
							cin >> startPage;
						}
					}
					else
					{
						startPage = endPage;
						cout << "Starting page: " << startPage << endl;
					}

					cout << "Enter the ending page: " << endl;
					cin >> endPage;

					while (cin.fail() || endPage <= startPage || endPage > totalPages)
					{
						cin.clear();
						cin.ignore(1000, '\n');

						cout << "Invalid input. Enter the ending page: " << endl;
						cin >> endPage;
					}

					cout << "Enter the total reading time in minutes: " << endl;
					cin >> minutesRead;

					while (cin.fail() || minutesRead <= 0)
					{
						cin.clear();
						cin.ignore(1000, '\n');

						cout << "Invalid input. Enter the total reading time in minutes: " << endl;
						cin >> minutesRead;
					}
					// update variables to accumulate multiple session entries
					totalPagesRead += endPage - startPage;
					totalMinutesRead += minutesRead;
					sessionsLogged++;

					// calculations
					pagesRemaining = totalPages - endPage;
					percentageComplete = (endPage * 100.0) / totalPages;

					// using an if statement to determine calculations to run based on previous entries
					if (totalPagesRead > 0 && totalMinutesRead > 0)
					{
						avgTimePerPage = totalMinutesRead / totalPagesRead;
						timeRemaining = (pagesRemaining * avgTimePerPage) / 60.0;
					}
					else
					{
						avgTimePerPage = 0.0;
						timeRemaining = 0.0;
					}

					cout << "Would you like to log another session? Enter 'Y' to continue." << endl;
					cin >> logSession;
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
				// Displaying the summary report to the console
				cout << "\n";
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
				// Create report.txt and save the original formatted summary to it
				ofstream reportFile("report.txt");
				if (!reportFile)
				{
					cout << "Error: Unable to create report.txt!" << endl;
					return 1;
				}

				reportFile << setfill('=') << setw(totalWidth) << "" << endl;
				reportFile << setfill(' ');
				reportFile << "Reading Progress Tracker" << endl;
				reportFile << setfill('=') << setw(totalWidth) << "" << endl;
				reportFile << setfill(' ');

				reportFile << left << setw(leftColumn) << "Book Information" << endl;
				reportFile << setfill('-') << setw(totalWidth) << "" << endl;
				reportFile << setfill(' ');

				reportFile << left << setw(leftColumn) << "Book Title: "
					<< right << setw(rightColumn) << bookTitle << endl;
				reportFile << left << setw(leftColumn) << "Total Page Length: "
					<< right << setw(rightColumn) << totalPages << endl;
				reportFile << left << setw(leftColumn) << "Current Page: "
					<< right << setw(rightColumn) << endPage << endl;
				reportFile << left << setw(leftColumn) << "Pages Remaining: "
					<< right << setw(rightColumn) << pagesRemaining << endl;

				reportFile << setfill('-') << setw(totalWidth) << "" << endl;
				reportFile << setfill(' ');

				reportFile << "Reading Progress" << endl;
				reportFile << left << fixed << setprecision(2) << percentageComplete << "%"
					<< right << setw(rightColumn - 6) << "completed" << endl;

				reportFile << "Reading Time Estimate" << endl;
				reportFile << left << setw(leftColumn) << "Average Time Per Page: "
					<< right << setw(rightColumn) << avgTimePerPage << " min" << endl;
				reportFile << left << setw(leftColumn) << "Estimated Time Remaining: "
					<< right << setw(rightColumn) << timeRemaining << " hours" << endl;

				reportFile.close();
				cout << "Your reading summary report has been saved to report.txt!" << endl;
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

