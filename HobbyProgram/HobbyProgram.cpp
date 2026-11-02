// HobbyProgram.cpp 
//Week 3 Assignment 

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
	// variables for book info
	string bookTitle;
	int totalPages = 0;
	int startPage = 0;
	int endPage = 0;
	double minutesRead = 0.0;

	// user reading variables, preinitialized to 0 for calculations later
	int pagesRemaining = 0;
	double percentageComplete = 0.0;
	double avgTimePerPage = 0.0;
	double timeRemaining = 0.0;

	// constants for the summary table
	int choice = 0;
	const int totalWidth = 48;
	const int leftColumn = 32;
	const int rightColumn = 16;

	// Printing a welcome message to the console that explains the program

	cout << "Welcome to the Reading Progress Tracker!" << endl;
	cout << "This program will track your progress, display your reading speed, and estimate the time it will take to finish your book." << endl;

	// Gathering book information from the user

	cout << "Let's gather some information about the book you're currently reading!" << endl;
	cout << "Enter the title of the book: " << endl;
	getline(cin, bookTitle);

	// Selection statement will make sure the user input is not empty & ask them to retry if it is.

	if (bookTitle.empty()) {
		cout << "Invalid input. Please enter the title of the book: " << endl;
		getline(cin, bookTitle);
	}

	cout << "Enter the total page length of the book: " << endl;
	cin >> totalPages;

	// Selection statement will verify user input and ask to retry.

	if (cin.fail() || totalPages <= 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Enter the total page length of the book: " << endl;
		cin >> totalPages;
	}

	// Gathering user data for their current reading session and verifying input - Starting/Ending Page and Time

	cout << "Ready to track your current reading session?" << endl;
	cout << "Enter your starting page: ";
	cin >> startPage;


	if (cin.fail() || startPage < 0 || startPage >= totalPages) {
		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Invalid input. Enter your starting page: ";
		cin >> startPage;
	}

	cout << "Enter your ending page: ";
	cin >> endPage;

	if (cin.fail() || endPage <= startPage || endPage > totalPages) {
		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Invalid input. Enter your ending page: ";
		cin >> endPage;
	}

	cout << "Enter your total reading time in minutes for your current session: " << endl;
	cin >> minutesRead;

	// An additional check for invaild user input 

	if (cin.fail() || minutesRead <= 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid entry. Enter your reading time in minutes: " << endl;
		cin >> minutesRead;
	}

	// Added if statement to check user entry validity. 

	if (!cin.fail() && startPage >= 0 && startPage < totalPages &&
		endPage > startPage && endPage <= totalPages && minutesRead > 0)
	{
		// Calculate reading progress and estimated reading time
		pagesRemaining = totalPages - endPage;
		percentageComplete = (endPage * 100.0) / totalPages;
		avgTimePerPage = minutesRead / (endPage - startPage);
		timeRemaining = (pagesRemaining * avgTimePerPage) / 60.0;
	}
	else
	{
		cout << "Invalid reading session information. Ending program." << endl;
		return 1;
	}

	// Display menu options 
	cout << "Choose an option from the menu below by entering its corresponding number: " << endl;
	cout << "1. Log current reading session" << endl;
	cout << "2. View reading summary report" << endl;
	cout << "3. Save reading report to report.txt" << endl;
	cin >> choice;

	if (cin.fail())
	{
		cout << "Invalid menu entry. Ending program." << endl;
		return 1;
	}

	switch (choice) {

	case 1:
	{
		// Logging session data 
		cout << "\nReading session recorded!" << endl;
		cout << "Book: " << bookTitle << endl;
		cout << "Pages read this session: " << endPage - startPage << endl;
		cout << "Time spent reading: " << fixed << setprecision(2)
			<< minutesRead << " minutes" << endl;
		cout << "Book completion: " << fixed << setprecision(2)
			<< percentageComplete << "%" << endl;

		// added if statement to check for book completion
		if (pagesRemaining == 0 && percentageComplete >= 100.0)
		{
			cout << "You have finished your book!" << endl;
		}
		else
		{
			cout << "You have " << pagesRemaining
				<< " pages remaining. Keep reading!" << endl;
		}
		break;
	}

	case 2:
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
		cout << left << fixed << setprecision(2) << percentageComplete << "%"
			<< right << setw(rightColumn - 6) << "completed" << endl;

		cout << "Reading Time Estimate" << endl;
		cout << left << setw(leftColumn) << "Average Time Per Page: "
			<< right << setw(rightColumn) << avgTimePerPage << " min" << endl;
		cout << left << setw(leftColumn) << "Estimated Time Remaining: "
			<< right << setw(rightColumn) << timeRemaining << " hours" << endl;
		break;
	}

	case 3:
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
		break;
	}

	default:
	{
		cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
		break;
	}
	}

	return 0;
}

