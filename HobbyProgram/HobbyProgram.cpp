// HobbyProgram.cpp 
//Week 1 Assignment 

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
	string bookTitle;
	int totalPages;
	int startPage;
	int endPage;
	double minutesRead;

	// Printing a welcome message to the console that explains the program

	cout << "Welcome to the Reading Progress Tracker!" << endl;
	cout << "Track your progress, discover your reading speed, and estimate how long it will take to finish your book!" << endl;
	
	// Gathering the user data for their book information _ Title and Length (string and int)
	
	cout << "Lets gather some information about the book you're currently reading!" << endl;
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
		cin.ignore(1000, '/n');
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
		cin.ignore(1000, '/n');
		cout << "Invalid entry. Enter your reading time in minutes: " << endl;
		cin >> minutesRead;
	}

	// Calculating the users book progress: pages remaining & percent read.

	int pagesRemaining = totalPages - endPage;
	double percentageComplete = (endPage * 100.0) / totalPages;

	// Calculate the users average reading time per page and the estimated time until completion

	double avgTimePerPage = minutesRead / (endPage - startPage);
	double timeRemaining = (pagesRemaining * avgTimePerPage) / 60;

	// Creating the summary table that will present users results. 
	// Declaring const variables to define the column widths
	// using setfill to create a separator

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
	cout << left << fixed << setprecision(2) << percentageComplete << "%"
		<< right << setw(rightColumn - 6) << "completed" << endl;

	cout << "Reading Time Estimate" << endl;
	cout << left << setw(leftColumn) << "Average Time Per Page: "
		<< right << setw(rightColumn) << avgTimePerPage << " min" << endl;
	cout << left << setw(leftColumn) << "Estimated Time Remaining: "
		<< right << setw(rightColumn) << timeRemaining << " hours" << endl;

	// Creating the report file and checking if it opened correctly

	ofstream reportFile("report.txt");
	if (!reportFile)
	{
		cout << "Error: Unable to create report.txt!" << endl;
		return 1;
	}

	// Summary table for the report file

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

	// Closing the File
	reportFile.close();
	cout << "Your reading summary report has been saved!" << endl;

	return 0;
}

