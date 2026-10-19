// HobbyProgram.cpp 
//Week 1 Assignment 

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string favoriteGenre;
	int booksPerMonth;
	double hoursPerBook;
	double hoursPerWeek;

	//Prompting the user for their favorite book genre, number of books read per month, and hours spent reading each week

    cout << "What is your favorite book genre?";
	cin >> favoriteGenre;

	cout << "How many books did you read this month?";
	cin >> booksPerMonth;

	cout << "How many hours do you read each week?";
	cin >> hoursPerWeek; 

	// calculate average hours spent reading each book


	hoursPerBook = (hoursPerWeek * 4) / booksPerMonth;

	//output the results 

	cout << "Your favorite book genre is " << favoriteGenre << "!" << endl;

	cout << "You've read " << booksPerMonth << " book(s) this month and spent approximately " << hoursPerWeek << " hours reading each week." << endl;
	
	cout << "You've spent an average of " << hoursPerBook << " hours reading each book." << endl;
	return 0;


}

