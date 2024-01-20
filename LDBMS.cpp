// Group-F
// BY: Muhammad Haseeb Zaheer (Group Leader) (21L-5171)
// Zohaib Hasan Malik (21L-7530)
// Muhammad Bilal Arshad (21L-7714)
// Section 1N
// Bs(CS)
// Project-3: Library Database Management System(LDBMS)

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

const int SIZE = 1100;		// Size of both arrays
const int FINE = 50;		// Fine is 50 Rupees per day

struct Date
{
	int day;
	int month;
	int year;
};
struct Book
{
	char author[30];
	char coauthor[30];
	char title[45];
	char publisher[30];
	char subject[30];
	char ID[6];

	int accessionNumber;
	int yearOfPub;

	bool issuable;
	bool issuedOrNot;

	Date issuanceOfBook;
	Date returnDate;
};
struct User
{
	char name[30];
	char fathersName[30];
	char rank[10];
	char department[30];
	char address[100];
	char ID[70];
	char cellNumber[15];

	Date dob;
};

int Input();
void Menu();
void ReadFileBook(ifstream& finBook, Book books[], int& numberOfRecords);
void ReadFileUser(ifstream& finUser, User users[], int& numofUserrecords);

void BookIssue(ofstream& foutBook, Book books[], int numberOfRecords, char bookFileName[]);
void BookReturn(ofstream& foutBook, Book books[], int numberOfRecords, char bookFileName[]);
void BookSearch(const Book books[], int numberOfRecords);
void BookSort(Book books[], int numberOfRecords);

void BookInsert(ifstream& finBook, ofstream& foutBook, Book books[], int& numofrecords, char bookFileName[]);
void BookDelete(ifstream& finBook, ofstream& foutBook, Book books[], int& numofrecords, char bookFileName[]);
void BookDisplay(Book books[], int& numofrecords);

void UserEdit(ofstream& foutUser, User users[], int& numofUserrecords, char userFileName[10]);
void UserSearch(User users[], Book books[]);

void OutputRecord(const Book books[], int index);
void CopyArray(Book books[], Book sortedBooks[], int numberOfRecords);
void Swap(Book book1[], int number);
void OutputToFileBook(ofstream& foutBook, Book books[], int index);
void OutputToFileUser(ofstream& fout, User users[], int index);
void DateAdd(Date& date, int days, Date& newDate);
void GetDate(Date& date);
Date Age(Date dob, Date currentDate);

int main()
{
	char input;                           // Initializing variables
	ifstream finBook, finUser;          // File input and output variables
	ofstream foutBook, foutUser;
	char bookFileName[10], userFileName[10];        // Stores the names of files with .dat extension
	Book books[SIZE];                               // Struct type arrays holding the database
	User users[SIZE];
	int numberOfRecords = 0;
	int numofUserrecords = 0;

	cout << "Please enter the file name with the BOOK database. Please DO include file extension\n=> ";     //Taking input for both book and user database file names
	cin >> bookFileName;
	cout << "Please enter the file name with the USER database. Please DO include file extension\n=> ";
	cin >> userFileName;

	cout << endl;

	finBook.open(bookFileName);                       // Opening both the book and user databases for program
	finUser.open(userFileName);

	foutBook.open(bookFileName, ios::app);

	ReadFileBook(finBook, books, numberOfRecords);
	ReadFileUser(finUser, users, numofUserrecords);
	input = Input();                               // Calling input function 

	do                         // Makes it menu driven so the program only stops on Exit 
	{
		switch (input)          // Conditional to corresspond to user input
		{
		case 1:
			BookInsert(finBook, foutBook, books, numberOfRecords, bookFileName);
			input = Input();
			break;
		case 2:
			BookDelete(finBook, foutBook, books, numberOfRecords, bookFileName);
			input = Input();
			break;
		case 3:
			BookIssue(foutBook, books, numberOfRecords, bookFileName);
			input = Input();
			break;
		case 4:
			BookReturn(foutBook, books, numberOfRecords, bookFileName);
			input = Input();
			break;
		case 5:
			BookSearch(books, numberOfRecords);
			input = Input();
			break;
		case 6:
			BookSort(books, numberOfRecords);
			input = Input();
			break;
		case 7:
			BookDisplay(books, numberOfRecords);
			input = Input();
			break;
		case 8:
			UserEdit(foutUser, users, numofUserrecords, userFileName);
			input = Input();
			break;
		case 9:
			UserSearch(users, books);
			input = Input();
			break;
		case 10:
			break;
		default:
			break;
		}
	} while (input != 10);

	finBook.close();                       // Closing both the book and user databases
	finUser.close();
	foutBook.close();
}

int Input()                 // Takes the input from the user for menu selection
{
	int input;              // Declaring variables
	Menu();                 // Calling Menu function
	cin >> input;           // Taking input from user
	while (input < 1 || input > 10)          // validation check to make sure input is not out of bounds
	{
		cout << "INVALID SELECTION! TRY AGAIN!" << endl;
		cout << "=> ";
		cin >> input;
	}
	cout << endl;
	return input;              // returning input to calling function i.e. main
}
void Menu()          // Displays Menu
{
	cout << "Please make your selection from 1-10" << endl;
	cout << "1. Insert a Book " << endl;
	cout << "2. Delete a Book" << endl;
	cout << "3. Issue a Book " << endl;
	cout << "4. Return a Book " << endl;
	cout << "5. Search for a Book " << endl;
	cout << "6. Sort the Book database in Ascending order " << endl;
	cout << "7. Display Books " << endl;
	cout << "8. Edit an existing user " << endl;
	cout << "9. Search for a user" << endl;
	cout << "10. Exit" << endl;
	cout << "=> ";
}
void ReadFileBook(ifstream& finBook, Book books[], int& numberOfRecords)
{
	char ch;

	for (int i = 0; finBook.eof() == false; i++) {
		finBook.get(books[i].author, 30, ',');
		finBook >> ch;
		finBook.get();
		finBook.get(books[i].coauthor, 30, ',');
		finBook >> ch;
		finBook.get();
		finBook.get(books[i].title, 45, ',');
		finBook >> ch;
		finBook.get();
		finBook.get(books[i].publisher, 30, ',');
		finBook >> ch;
		finBook.get();
		finBook.get(books[i].subject, 30, ',');
		finBook >> ch;
		finBook.get();
		finBook.get(books[i].ID, 6, ',');
		finBook >> ch;
		finBook >> books[i].accessionNumber;
		finBook >> ch;
		finBook >> books[i].yearOfPub;
		finBook >> ch;
		finBook >> books[i].issuable;
		finBook >> ch;
		finBook >> books[i].issuedOrNot;
		finBook >> ch;
		finBook >> books[i].issuanceOfBook.day;
		finBook >> ch;
		finBook >> books[i].issuanceOfBook.month;
		finBook >> ch;
		finBook >> books[i].issuanceOfBook.year;
		finBook >> ch;
		finBook >> books[i].returnDate.day;
		finBook >> ch;
		finBook >> books[i].returnDate.month;
		finBook >> ch;
		finBook >> books[i].returnDate.year;
		finBook.get();
		numberOfRecords += 1;
	}
}
void ReadFileUser(ifstream& finUser, User users[], int& numofUserrecords)
{
	char ch;
	for (int j = 0; finUser.eof() == false; j++) {
		finUser.get(users[j].name, 30, ',');
		finUser >> ch;
		finUser.get();
		finUser.get(users[j].fathersName, 30, ',');
		finUser >> ch;
		finUser.get();
		finUser.get(users[j].rank, 10, ',');
		finUser >> ch;
		finUser.get();
		finUser.get(users[j].department, 30, ',');
		finUser >> ch;
		finUser.get();
		finUser.get(users[j].ID, 70, ',');
		finUser >> ch;
		finUser >> users[j].dob.day;
		finUser >> ch;
		finUser >> users[j].dob.month;
		finUser >> ch;
		finUser >> users[j].dob.year;
		finUser >> ch;
		finUser.get();
		finUser.get(users[j].address, 100, '0');
		finUser.get(users[j].cellNumber, 15, ' ');
		finUser.get();
		finUser.get();
		numofUserrecords++;
	}
}

void BookSearch(const Book books[], int numberOfRecords)
{
	char choice;			// Declaring variables needed
	char search[35] = {'\0'};
	int index, number = 0;
	bool Found = false;			// Boolean which stores status of book being found

	cout << "a. Search through Author's name. " << endl;		// Inputting choice of user
	cout << "b. Search through co-author's name. " << endl;
	cout << "c. Search through Accession number. " << endl;
	cout << "=> ";
	cin >> choice;


	while (tolower(choice) < 'a' || tolower(choice) > 'c')		// Input Validation
	{
		cout << "Invalid Input. Try again!" << endl;
		cout << "=> ";
		cin >> choice;
	}

	cout << "Input search value:\n=> ";			// Inputting search value
	if (tolower(choice) != 'c')
	{
		cin.ignore();
		cin.get(search, 35);
	}
	else			// Accession number is an integer
		cin >> number;

	for (int i = 0;(i < numberOfRecords && !Found);i++)
	{
		if (tolower(choice) == 'a' && strcmp(books[i].author, search) == 0)		// Search according to author
		{
			index = i;
			Found = true;
		}
		else if (tolower(choice) == 'b' && strcmp(books[i].coauthor, search) == 0)		// Search according to Co-Author
		{
			index = i;
			Found = true;
		}
		else if (tolower(choice) == 'c' && books[i].accessionNumber == number)		// Search according to Accession Number
		{
			index = i;
			Found = true;
		}
	}

	if (Found)		// Book was found
	{
		cout << endl;
		cout << "Book has been found!" << endl;
		OutputRecord(books, index);			// Calling function to output the record on index
	}
	else
		cout << "Book was not found!" << endl;		// Book not found
	cout << endl;
}
void BookSort(Book books[], int numberOfRecords)
{
	Book sortedBooks[SIZE];		// Declaring Variables
	ofstream fout;
	char choice;
	char fileName[30];
	bool swapping = false;

	CopyArray(books, sortedBooks, numberOfRecords);			// Copying the array into sortedBooks

	cout << "a. Sort based on Author's name. " << endl;			// Inputting the users choice
	cout << "b. Sort based on book title. " << endl;
	cout << "=> ";
	cin >> choice;

	while (tolower(choice) < 'a' || tolower(choice) > 'b')		// Input Validation
	{
		cout << "Invalid Input. Try again!" << endl;
		cout << "=> ";
		cin >> choice;
	}

	cout << "Enter the name of the new file (with extension)\n=> ";	// File Name to store the sorted records
	cin >> fileName;

	if (tolower(choice) == 'a')			// Sorting according to author
	{
		for (int i = 0; i < numberOfRecords;i++)
		{
			swapping = false;
			for (int j = 0;j < numberOfRecords - i;j++)
			{
				if (strcmp(sortedBooks[j].author, sortedBooks[j + 1].author) > 0)			// If first index value > second index value
				{
					Swap(sortedBooks, j);			// Swapping both the index values
					swapping = true;		// Swapping has been done
				}
			}
			if (!swapping)			// If no swapping, array is fully sorted already, Break loop
				break;
		}
	}
	else				// Sorting according to book title
	{
		for (int i = 0; i < numberOfRecords;i++)
		{
			swapping = false;
			for (int j = 0;j < numberOfRecords - i;j++)
			{
				if (strcmp(sortedBooks[j].title, sortedBooks[j + 1].title) > 0)
				{
					Swap(sortedBooks, j);
					swapping = true;
				}
			}
			if (!swapping)
				break;
		}
	}

	fout.open(fileName);		// Opening the new file
	for (int i = 0;i < numberOfRecords;i++)			// Outputting to the new file
	{
		OutputToFileBook(fout, sortedBooks, i);
		if (i < numberOfRecords - 1)
			fout << endl;
	}
	cout << "Sorting Complete!" << endl;		// Notification that sorting is complete
	cout << endl;
	fout.close();		// Closing the new file
}
void BookIssue(ofstream& foutBook, Book books[], int numberOfRecords, char bookFileName[])
{
	Book newBook;		// Declaring variables
	Date currentDate;
	Date currentReturnDate = {'\0'};
	bool bookFound = false;

	cout << "Input the name of the Author\n=> ";		// Getting the author of the book
	cin.ignore();
	cin.get(newBook.author, 30);

	cout << "Input Title of the Book\n=> ";		// Getting title of the book
	cin.ignore();
	cin.get(newBook.title, 45);

	newBook.issuedOrNot = false;
	for (int i = 0; (i < numberOfRecords && !bookFound); i++)
	{
		if ((strcmp(books[i].title, newBook.title) == 0) && (strcmp(books[i].author, newBook.author) == 0))
		{
			bookFound = true;
			if (books[i].issuable)		// Checking if book is issuable
			{
				if (books[i].issuedOrNot)		// Checking if the book has already been issued
					cout << "The Book has already been issued." << endl;
				else
				{
					GetDate(currentDate);
					cout << "Enter the student or employee ID\n=> ";
					cin.ignore();
					cin.get(newBook.ID, 6);

					while (tolower(newBook.ID[0]) != 's' && tolower(newBook.ID[0]) != 'e')
					{
						cout << "Invalid ID. Please Try Again\n=> ";
						cin.ignore();
						cin.get(newBook.ID, 6);
					}

					if (tolower(newBook.ID[0]) == 's')
						DateAdd(currentDate, 15, currentReturnDate);		// Getting the return date (15 days more in this case)
					else if (tolower(newBook.ID[0]) == 'e')
						DateAdd(currentDate, 120, currentReturnDate);		// Getting the return date (120 days / 4 months more in this case)

					strcpy_s(books[i].ID, newBook.ID);						// Copying ID
					books[i].issuanceOfBook.day = currentDate.day;			// Assigning date values for book issuance
					books[i].issuanceOfBook.month = currentDate.month;
					books[i].issuanceOfBook.year = currentDate.year;

					books[i].returnDate.day = currentReturnDate.day;		// Assigning date values for return date
					books[i].returnDate.month = currentReturnDate.month;
					books[i].returnDate.year = currentReturnDate.year;

					books[i].issuedOrNot = true;			// Assigning that the book has been issued
					newBook.issuedOrNot = true;
				}
			}
			else			// If book is not issuable
				cout << "The Book is not issuable!" << endl;
		}
	}
	if (!bookFound)		// Book was not found
		cout << "The book was not found." << endl;
	else		// Book was found
	{
		if (newBook.issuedOrNot)
		{
			foutBook.close();			// Closing File
			foutBook.open(bookFileName);		// Reopening file without append
			for (int i = 0;i < numberOfRecords;i++)			// Writing new records to the file
			{
				OutputToFileBook(foutBook, books, i);
				if (i < numberOfRecords - 1)
					foutBook << endl;
			}
			foutBook.close();		// Closing File
			foutBook.open(bookFileName, ios::app);		// Reopening in append mode so other functions work properly
			cout << "The book has been issued!" << endl;		// Notification that the book has been issued
		}
	}
	cout << endl;
}
void BookReturn(ofstream& foutBook, Book books[], int numberOfRecords, char bookFileName[])
{
	Date difference;		// Declaring Variables
	Date returnDate;
	Date currentDate;
	Book returnBook;

	int totalDays = 0;
	int totalFine = 0;
	char empty[6] = { "0" };
	bool bookFound = false;

	currentDate.day = 0;		// Initialising the currentDate variable
	currentDate.month = 0;
	currentDate.year = 0;

	cout << "Input the name of the Author\n=> ";		// Getting the author of the book
	cin.ignore();
	cin.get(returnBook.author, 30);

	cout << "Input Title of the Book\n=> ";		// Getting title of the book
	cin.ignore();
	cin.get(returnBook.title, 45);

	returnBook.issuedOrNot = true;
	for (int i = 0; (i < numberOfRecords && !bookFound); i++)
	{
		if ((strcmp(books[i].title, returnBook.title) == 0) && (strcmp(books[i].author, returnBook.author) == 0))
		{
			bookFound = true;

			books[i].issuanceOfBook.day = 0;			// Assigning date values for book issuance
			books[i].issuanceOfBook.month = 0;
			books[i].issuanceOfBook.year = 0;

			returnDate.day = books[i].returnDate.day;		// Storing the return date 
			returnDate.month = books[i].returnDate.month;
			returnDate.year = books[i].returnDate.year;

			books[i].returnDate.day = 0;			// Assigning date values for return date
			books[i].returnDate.month = 0;
			books[i].returnDate.year = 0;

			strcpy_s(books[i].ID, empty);		// Empting the Student/Employee ID

			books[i].issuedOrNot = false;			// Book is not issued anymore
			returnBook.issuedOrNot = false;
		}
	}

	if (!returnBook.issuedOrNot && bookFound == true)		// Book is not issued and book was found (Changes were made)
	{
		foutBook.close();			// Closing File
		foutBook.open(bookFileName);		// Reopening file without append
		for (int i = 0;i < numberOfRecords;i++)			// Writing new records to the file
		{
			OutputToFileBook(foutBook, books, i);
			if (i < numberOfRecords - 1)
				foutBook << endl;
		}
		foutBook.close();		// Closing File
		foutBook.open(bookFileName, ios::app);		// Reopening in append mode so other functions work properly
		cout << "The book has been returned!" << endl;		// Notification that the book has been issued

		difference = Age(returnDate, currentDate);			// Using the age function to calculate the difference between returnDate and currentDate
		totalDays = difference.day + (difference.month * 31) + (difference.year * 365);		// Calculating total days of difference
		if (totalDays <= 0)			// If the totalDays were negative or zero (Book was returned before returnDate), no fine
			cout << "Fine = " << totalFine << "Rs" << endl;
		else		// If the totalDays were positive (Book was not returned before returnDate), fine is calculated
		{
			totalFine = FINE * totalDays;		// 50 Rupees fine per day
			cout << "Fine = " << totalFine << "Rs" << endl;
		}
	}
	else
		cout << "Book was not found!" << endl;
	cout << endl;
}

void BookInsert(ifstream& finBook, ofstream& foutBook, Book books[], int& numofrecords, char bookFileName[])
{
	foutBook.close();
	foutBook.open(bookFileName);					// Overwriting existing data so to rewrite in order of accession number

	int temp = -1, anum, yearp;
	char uauthor[60];
	char ucoauthor[60];
	char utitle[45], upublisher[30], usubject[30], uID[70];
	char date[50];
	char issuable, issued;
	bool found = false, written = false, last = false;
	bool sameNum = false;

	cout << "Enter the Accession Number of the book you're wishing to store\n=> ";
	cin >> anum;
	for (int i = 0;i < numofrecords && !sameNum;i++)
	{
		if (books[i].accessionNumber == anum)
			sameNum = true;
	}

	while (sameNum)
	{
		cout << "Invalid Accession Number! Please add a unique number\n=> ";
		cin >> anum;
		sameNum = false;
		for (int i = 0;i < numofrecords && !sameNum;i++)
		{
			if (books[i].accessionNumber == anum)
				sameNum = true;
		}
	}

	cout << "Enter the author's name\n=> ";
	cin.ignore();
	cin.get(uauthor, 60);

	cout << "Enter the co-author's name\n=> ";
	cin.ignore();
	cin.get(ucoauthor, 60);

	cout << "Enter publisher's name\n=> ";
	cin >> upublisher;

	cout << "Enter subject\n=> ";
	cin >> usubject;

	cout << "Enter your ID (If not issued, enter 0)\n=> ";
	cin >> uID;

	cout << "Enter year of publication\n=> ";
	cin >> yearp;

	cout << "Is book issuable? Enter Y or N\n=> ";
	cin >> issuable;

	for (int i = 0; i < numofrecords; i++)
	{
		if (anum > books[numofrecords - 1].accessionNumber)
		{
			last = true;						//Print at the end of the file if accession number from user greater than that of last record
			break;
		}
		if (books[i].accessionNumber > anum)
		{
			temp = i;
			found = true;
			break;
		}
		if (found == false)
			temp = numofrecords - 1;
	}

	for (int i = 0; i < numofrecords; i++)
	{
		if ((i == temp) && (written == false) && (last == false))
		{
			foutBook << uauthor << ", " << ucoauthor << ", ";

			cout << "Enter the book title\n=> ";
			cin.ignore();
			cin.get(utitle, 45);
			foutBook << utitle;

			foutBook << ',' << ' ';
			foutBook << upublisher << ", " << usubject << ", " << uID << ", ";
			foutBook << anum << ", " << yearp << ", ";
			if (toupper(issuable) == 'N')
				foutBook << "0, 0, 00/00/0000, 00/00/0000" << endl;
			else if (toupper(issuable) == 'Y')
			{
				cout << "Has book been issued or not? Enter Y or N" << endl;
				cin >> issued;
				foutBook << "1, ";
				if (toupper(issued) == 'N')
					foutBook << "0, 00/00/0000, 00/00/0000" << endl;
				else if (toupper(issued) == 'Y')
				{
					foutBook << "1, ";
					cout << "Enter the issuance date in (DD/MM/YYYY) format\n=> ";
					cin.ignore();
					cin.get(date, 50);
					foutBook << date << ", ";
					cout << "Enter date of return in the same manner (DD/MM/YYYY)\n=> ";
					cin.ignore();
					cin.get(date, 50);
					foutBook << date << endl;
				}
			}
			OutputToFileBook(foutBook, books, i);
			written = true;
			if (i < numofrecords - 1)
				foutBook << endl;
		}
		else if (last == false)
		{
			OutputToFileBook(foutBook, books, i);
			if (i < numofrecords - 1)
				foutBook << endl;
		}
	}

	if (last == true)
	{
		for (int i = 0; i < numofrecords; i++)
		{
			OutputToFileBook(foutBook, books, i);
			foutBook << endl;
		}
		foutBook << uauthor << ", " << ucoauthor << ", ";

		cout << "Enter the book title\n=> ";
		cin.ignore();
		cin.get(utitle, 45);
		foutBook << utitle;

		foutBook << ',' << ' ';
		foutBook << upublisher << ", " << usubject << ", " << uID << ", ";
		foutBook << anum << ", " << yearp << ", ";
		if (issuable == 'N')
		{
			foutBook << "0, 0, 00/00/0000, 00/00/0000";
		}
		else if (issuable == 'Y')
		{
			cout << "Has book been issued or not? Enter Y or N\n=> ";
			cin >> issued;
			foutBook << "1, ";
			if (issued == 'N')
			{
				foutBook << "0, 00/00/0000, 00/00/0000";
			}
			else if (issued == 'Y')
			{
				foutBook << "1, ";
				cout << "Enter the issuance date in (DD/MM/YYYY) format\n=> ";
				cin.ignore();
				cin.get(date, 50);
				foutBook << date << ", ";
				cout << "Enter date of return in the same manner\n=> ";
				cin.ignore();
				cin.get(date, 50);
				foutBook << date;
			}
		}
	}
	numofrecords++;
	foutBook.close();
	foutBook.open(bookFileName, ios::app);
	ReadFileBook(finBook, books, numofrecords);
	cout << endl;
}
void BookDelete(ifstream& finBook, ofstream& foutBook, Book books[], int& numofrecords, char bookFileName[])
{
	foutBook.close();
	foutBook.open(bookFileName);
	int n, temp1 = 0, temp2 = 0;
	bool found = false;

	cout << "Enter the accession number of the book you wish to remove from the data file\n=> ";
	cin >> n;

	for (int i = 0; i < numofrecords; i++)
	{
		if (books[i].accessionNumber == n)
		{
			temp1 = n;
			temp2 = i;
			cout << "Book found" << endl;
			found = true;
		}
	}

	if ((temp1 == n) && (found == true))
	{
		for (int j = 0; j < numofrecords; j++)
		{
			if (j != temp2)
			{
				OutputToFileBook(foutBook, books, j);
				if (j < numofrecords - 1)
					foutBook << endl;
			}
		}
		cout << "Book removed" << endl;
		foutBook.close();
		numofrecords--;
	}
	else
	{
		cout << "Book not found" << endl;
		for (int j = 0; j < numofrecords; j++)
		{
			{
				OutputToFileBook(foutBook, books, j);
				if (j < numofrecords - 1)
					foutBook << endl;
			}
		}
	}

	foutBook.close();
	foutBook.open(bookFileName, ios::app);
	ReadFileBook(finBook, books, numofrecords);
	cout << endl;
}
void BookDisplay(Book books[], int& numofrecords)
{
	char userauthor[30], usersubject[30];
	int option = 0;
	int ref = 0;
	bool found = false;

	cout << "For the books you want to be displayed, select one of following: " << endl;
	cout << "1. Display using a specified author " << endl;
	cout << "2. Display using a specified subject \n=> ";

	cin >> option;
	while ((option != 1) && (option != 2))						// Validating user input
	{
		cout << "Error, please enter a valid option\n=> ";
		cin >> option;
	}

	if (option == 1)											// Executes if option is 1 
	{
		cout << "Enter the name of the author\n=> ";
		cin.ignore();
		cin.get(userauthor, 30);
		for (int i = 0; i <= numofrecords - 1; i++)
		{
			if (strcmp(userauthor, books[i].author) == 0)
			{
				ref = i;
				cout << "Book title: " << books[ref].title << endl;				// Display title of book found
				found = true;
			}
		}
		if (found == false)										// Display message if book not found
			cout << "Book not found" << endl;
	}
	else if (option == 2)										// Executes if option is 2
	{
		cout << "Enter subject" << endl;
		cin.ignore();
		cin.get(usersubject, 30);
		for (int i = 0; i <= numofrecords - 1; i++)
		{
			if (strcmp(usersubject, books[i].subject) == 0)
			{
				ref = i;
				cout << "Book title: " << books[ref].title << endl;				// Display title of book found
				found = true;
			}
		}
		if (found == false)										// Display message if book not found
			cout << "Book not found";
	}
	cout << endl;
}

void UserSearch(User users[], Book books[])
{
	char choice, search[35];                     // declaring variables
	int index;
	bool Found = false;                                // declaring and initializing flag
	Date date = { '/0' }, age;                        // declaring and initializing variables of data type Date which is a structure
	cout << "Please enter option 'a' to search through name" << endl << "Please enter option 'b' to search through ID" << endl << "Please enter option 'c' to search through cell number\n=> "; // asking user for input
	cin >> choice;
	while (tolower(choice) != 'a' && tolower(choice) != 'b' && tolower(choice) != 'c')             // input validation check
	{
		cout << "INVALID ENTRY. Please enter an option form a to c\n=> ";
		cin >> choice;
	}
	cout << "Input search value:\n=> ";
	if (tolower(choice) == 'a')
	{
		cin.ignore();
		cin.get(search, 35);
	}
	else
		cin >> search;                                 // input ID or cell number
	for (int i = 0; (i < SIZE && !Found); i++)              // loop runs until user is found
	{
		if ((tolower(choice) == 'a') && (strcmp(users[i].name, search) == 0))             // checking input against array
		{
			index = i;                                                                         // flag switches when found and the index is saved
			Found = true;
		}
		else if ((tolower(choice) == 'b') && (strcmp(users[i].ID, search) == 0))            // checking input against array
		{
			index = i;                                                                         // flag switches when found and the index is saved
			Found = true;
		}
		else if ((tolower(choice) == 'c') && (strcmp(users[i].cellNumber, search) == 0))       // checking input against array
		{
			index = i;                                                                         // flag switches when found and the index is saved
			Found = true;
		}
	}
	if (Found)                                          // only runs if flag is true
	{
		cout << endl;
		age = Age(users[index].dob, date);	               // calls Age function and saves the returning value in variable
		cout << "User has been found!" << endl;
		cout << "User Name: " << users[index].name << endl;        // outputting user record
		cout << "Father's Name: " << users[index].fathersName << endl;
		cout << "Rank: " << users[index].rank << endl;
		cout << "Department: " << users[index].department << endl;
		cout << "Address: " << users[index].address << endl;
		cout << "ID: " << users[index].ID << endl;
		cout << "Cell Number: " << users[index].cellNumber << endl;
		cout << "Date of Birth: " << users[index].dob.day << "/" << users[index].dob.month << "/" << users[index].dob.year << endl;
		cout << "Age: " << age.year << " years" << endl;
		cout << "Book Titles issued: " << endl;
		for (int i = 0; i < SIZE; i++)
			if (strcmp(users[index].ID, books[i].ID) == 0)            // finds books issues to user by comparing their ID in user array against the ID in book array
				cout << books[i].title << endl;
	}
	else
		cout << "SORRY, USER NOT FOUND" << endl;
	cout << endl;
}
void UserEdit(ofstream& foutUser, User users[], int& numofUserrecords, char userFileName[10])
{
	char choice, search[35], replaceData[70];                     // declaring variables
	char replaceID[70];
	int index;
	bool Found = false;                                // declaring and initializing flag
	Date date = { '/0' };                        // declaring and initializing variables of data type Date which is a structure

	cout << "Please enter option 'a' to search through name the record you wish to edit" << endl << "Please enter option 'b' to search through ID the record you wish to edit\n=> "; // asking user for input
	cin >> choice;
	while (tolower(choice) != 'a' && tolower(choice) != 'b')             // input validation check
	{
		cout << "INVALID ENTRY. Please enter an option form a to b\n=> ";
		cin >> choice;
	}
	cout << "Input search value:\n=> ";
	if (tolower(choice) == 'a')                                         // Input name, as it has a space between so it has to be input seperately and then merged (user will input as normal)
	{
		cin.ignore();
		cin.get(search, 35);
	}
	else
		cin >> search;                                 // input ID or cell number
	for (int i = 0; (i < numofUserrecords && !Found); i++)              // loop runs until user is found
	{
		if ((tolower(choice) == 'a') && (strcmp(users[i].name, search) == 0))             // checking input against array
		{
			index = i;                                                                         // flag switches when found and the index is saved
			Found = true;
		}
		else if ((tolower(choice) == 'b') && (strcmp(users[i].ID, search) == 0))            // checking input against array
		{
			index = i;                                                                         // flag switches when found and the index is saved
			Found = true;
		}
	}
	if (Found)                                          // only runs if flag is true
	{
		cout << "User has been found!" << endl<< endl;
		cout << "User Name: " << users[index].name << endl;        // outputting user record
		cout << "Father's Name: " << users[index].fathersName << endl;
		cout << "Rank: " << users[index].rank << endl;
		cout << "Department: " << users[index].department << endl;
		cout << "Address: " << users[index].address << endl;
		cout << "ID: " << users[index].ID << endl;
		cout << "Cell Number: " << users[index].cellNumber << endl;
		cout << "Date of Birth: " << users[index].dob.day << "/" << users[index].dob.month << "/" << users[index].dob.year << endl << endl;
		cout << "Please enter the letter corresponding to the field you wish to edit" << endl << "a) Name" << endl << "b) Father's Name" << endl << "c) Rank" << endl << "d) Department" << endl << "e) Address" << endl << "f) ID" << endl << "g) Cell Number" << endl << "h) Date of Birth\n=> ";
		cin >> choice;
		while (tolower(choice) < 'a' || tolower(choice) > 'h')             // input validation check
		{
			cout << "INVALID ENTRY. Please enter an option form a to h\n=> ";
			cin >> choice;
		}
		if (tolower(choice) == 'f')
		{
			cout << "Enter the student or employee ID\n=> ";
			cin.ignore();
			cin.get(replaceID, 70);
			while (tolower(replaceID[0]) != 's' && tolower(replaceID[0]) != 'e')
			{
				cout << "Invalid ID. Please Try Again\n=> ";
				cin.ignore();
				cin.get(replaceID, 70);
			}
		}
		else if (tolower(choice) != 'h')
		{
			cout << "Enter data to replace the existing field with. IN CASE OF ADDRESS TERMINATE WITH ',' AND THEN A SPACE ' '\n=> ";
			cin.ignore();
			cin.get(replaceData, 70);
		}
		else
			GetDate(date);
		switch (tolower(choice))
		{
		case 'a': strcpy_s(users[index].name, replaceData);                 // Copying over user input into the users array
			break;
		case 'b': strcpy_s(users[index].fathersName, replaceData);
			break;
		case 'c': strcpy_s(users[index].rank, replaceData);
			break;
		case 'd': strcpy_s(users[index].department, replaceData);
			break;
		case 'e': strcpy_s(users[index].address, replaceData);
			break;
		case 'f': strcpy_s(users[index].ID, replaceID);
			break;
		case 'g': strcpy_s(users[index].cellNumber, replaceData);
			break;
		case 'h': users[index].dob.day = date.day;
			users[index].dob.month = date.month;
			users[index].dob.year = date.year;
			break;
		default:
			break;
		}
		foutUser.open(userFileName);           // opening users.dat
		int i = 0;
		for (i = 0; i < numofUserrecords - 1; i++)            // loop runs for all records except the last one
		{
			OutputToFileUser(foutUser, users, i);		// writing to users.dat
			foutUser << endl;
		}
		if (i == (numofUserrecords - 1))        // for last record
		{
			OutputToFileUser(foutUser, users, i);		// writing to users.dat
		}
		foutUser.close();                   // closing users.dat
		cout << "EDIT SUCCESSFUL!" << endl;
	}
	else
		cout << "SORRY, USER NOT FOUND" << endl;
	cout << endl;
}

void GetDate(Date& date)
{
	int day, month, year;               // declaring variables
	bool leap = false;                  // declaring flag and setting the default to false
	cout << "Please enter the current year\n=> ";
	cin >> year;                                      // user inputs year
	while (year < 0)                             // validation check for year
	{
		cout << "INVALID ENTRY" << endl << "Please enter the year\n=> ";
		cin >> year;
	}
	if (year % 4 == 0)                                    // leap year check
		if (year % 100 == 0)
			if (year % 400 == 0)
				leap = true;
			else
				leap = true;
	cout << "Please enter the current month in digit from 1-12 inclusive\n=> ";
	cin >> month;                      // user inputs month
	while (month < 1 || month > 12)                          // validation check for month
	{
		cout << "INVALID ENTRY" << endl << "Please enter the month in digit from 1-12 inclusive\n=> ";
		cin >> month;
	}
	cout << "Please enter the current day in digits\n=> ";
	cin >> day;                              // user inputs day
	while ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31 || day < 1))         //  validation check for day
	{
		cout << "INVALID ENTRY" << endl << "Please enter the day in digits\n=> ";
		cin >> day;
	}
	while ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1))                         //  validation check for day
	{
		cout << "INVALID ENTRY" << endl << "Please enter the day in digits\n=> ";
		cin >> day;
	}
	while (((month == 2) && (day > 29 || day < 1) && (leap == true)) || ((month == 2) && (day > 28 || day < 1) && (leap == false)))       //  validation check for day in feb or 2nd month in case of leap year
	{
		cout << "INVALID ENTRY" << endl << "Please enter the day in digits\n=> ";
		cin >> day;
	}
	date.year = year;                         // assigning the input and validated date
	date.month = month;
	date.day = day;
}
void DateAdd(Date& date, int days, Date& newDate)  // Function
{
	newDate.day = date.day + days;    // adding days to old date to create a new date
	newDate.month = date.month;
	newDate.year = date.year;
	if (newDate.day > 30)           // exception handling the newDate
	{
		newDate.month++;
		newDate.day -= 30;
	}
	if (newDate.month > 12)           // exception handling the newDate
	{
		newDate.year++;
		newDate.month -= 12;
	}
}
void OutputToFileBook(ofstream& fout, Book books[], int index)
{
	fout << books[index].author << ", " << books[index].coauthor << ", " << books[index].title << ", " << books[index].publisher << ", " << books[index].subject << ", ";
	fout << books[index].ID << ", " << books[index].accessionNumber << ", " << books[index].yearOfPub << ", ";
	fout << books[index].issuable << ", " << books[index].issuedOrNot << ", ";
	fout << books[index].issuanceOfBook.day << "/" << books[index].issuanceOfBook.month << "/" << books[index].issuanceOfBook.year << ", ";
	fout << books[index].returnDate.day << "/" << books[index].returnDate.month << "/" << books[index].returnDate.year;
}
void OutputToFileUser(ofstream& fout, User users[], int index)
{
	fout << users[index].name << ',' << ' ';              // writing to users.dat 
	fout << users[index].fathersName << ',' << ' ';
	fout << users[index].rank << ',' << ' ';
	fout << users[index].department << ',' << ' ';
	fout << users[index].ID << ',' << ' ';
	fout << users[index].dob.day << '/' << users[index].dob.month << '/' << users[index].dob.year << ',' << ' ';
	fout << users[index].address;
	fout << users[index].cellNumber << ' ';
}
void Swap(Book book1[], int number)
{
	Book tempArray;

	// temp = num1		
	strcpy_s(tempArray.author, book1[number].author);
	strcpy_s(tempArray.coauthor, book1[number].coauthor);
	strcpy_s(tempArray.title, book1[number].title);
	strcpy_s(tempArray.publisher, book1[number].publisher);
	strcpy_s(tempArray.subject, book1[number].subject);
	strcpy_s(tempArray.ID, book1[number].ID);
	tempArray.accessionNumber = book1[number].accessionNumber;
	tempArray.yearOfPub = book1[number].yearOfPub;
	tempArray.issuable = book1[number].issuable;
	tempArray.issuedOrNot = book1[number].issuedOrNot;
	tempArray.issuanceOfBook.day = book1[number].issuanceOfBook.day;
	tempArray.issuanceOfBook.month = book1[number].issuanceOfBook.month;
	tempArray.issuanceOfBook.year = book1[number].issuanceOfBook.year;
	tempArray.returnDate.day = book1[number].returnDate.day;
	tempArray.returnDate.month = book1[number].returnDate.month;
	tempArray.returnDate.year = book1[number].returnDate.year;

	// num1 = num2
	strcpy_s(book1[number].author, book1[number + 1].author);
	strcpy_s(book1[number].coauthor, book1[number + 1].coauthor);
	strcpy_s(book1[number].title, book1[number + 1].title);
	strcpy_s(book1[number].publisher, book1[number + 1].publisher);
	strcpy_s(book1[number].subject, book1[number + 1].subject);
	strcpy_s(book1[number].ID, book1[number + 1].ID);
	book1[number].accessionNumber = book1[number + 1].accessionNumber;
	book1[number].yearOfPub = book1[number + 1].yearOfPub;
	book1[number].issuable = book1[number + 1].issuable;
	book1[number].issuedOrNot = book1[number + 1].issuedOrNot;
	book1[number].issuanceOfBook.day = book1[number + 1].issuanceOfBook.day;
	book1[number].issuanceOfBook.month = book1[number + 1].issuanceOfBook.month;
	book1[number].issuanceOfBook.year = book1[number + 1].issuanceOfBook.year;
	book1[number].returnDate.day = book1[number + 1].returnDate.day;
	book1[number].returnDate.month = book1[number + 1].returnDate.month;
	book1[number].returnDate.year = book1[number + 1].returnDate.year;

	// num2 = temp
	strcpy_s(book1[number + 1].author, tempArray.author);
	strcpy_s(book1[number + 1].coauthor, tempArray.coauthor);
	strcpy_s(book1[number + 1].title, tempArray.title);
	strcpy_s(book1[number + 1].publisher, tempArray.publisher);
	strcpy_s(book1[number + 1].subject, tempArray.subject);
	strcpy_s(book1[number + 1].ID, tempArray.ID);
	book1[number + 1].accessionNumber = tempArray.accessionNumber;
	book1[number + 1].yearOfPub = tempArray.yearOfPub;
	book1[number + 1].issuable = tempArray.issuable;
	book1[number + 1].issuedOrNot = tempArray.issuedOrNot;
	book1[number + 1].issuanceOfBook.day = tempArray.issuanceOfBook.day;
	book1[number + 1].issuanceOfBook.month = tempArray.issuanceOfBook.month;
	book1[number + 1].issuanceOfBook.year = tempArray.issuanceOfBook.year;
	book1[number + 1].returnDate.day = tempArray.returnDate.day;
	book1[number + 1].returnDate.month = tempArray.returnDate.month;
	book1[number + 1].returnDate.year = tempArray.returnDate.year;
}
void CopyArray(Book books[], Book sortedBooks[], int numberOfRecords)
{
	for (int i = 0;i < numberOfRecords;i++)					// For all records
	{
		strcpy_s(sortedBooks[i].author, books[i].author);
		strcpy_s(sortedBooks[i].coauthor, books[i].coauthor);
		strcpy_s(sortedBooks[i].title, books[i].title);
		strcpy_s(sortedBooks[i].publisher, books[i].publisher);
		strcpy_s(sortedBooks[i].subject, books[i].subject);
		strcpy_s(sortedBooks[i].ID, books[i].ID);
		sortedBooks[i].accessionNumber = books[i].accessionNumber;
		sortedBooks[i].yearOfPub = books[i].yearOfPub;
		sortedBooks[i].issuable = books[i].issuable;
		sortedBooks[i].issuedOrNot = books[i].issuedOrNot;
		sortedBooks[i].issuanceOfBook.day = books[i].issuanceOfBook.day;
		sortedBooks[i].issuanceOfBook.month = books[i].issuanceOfBook.month;
		sortedBooks[i].issuanceOfBook.year = books[i].issuanceOfBook.year;
		sortedBooks[i].returnDate.day = books[i].returnDate.day;
		sortedBooks[i].returnDate.month = books[i].returnDate.month;
		sortedBooks[i].returnDate.year = books[i].returnDate.year;
	}
}
void OutputRecord(const Book books[], int index)
{
	cout << endl;
	cout << "Author Name: " << books[index].author << endl;
	cout << "Co-Author's Name: " << books[index].coauthor << endl;
	cout << "Title: " << books[index].title << endl;
	cout << "Publisher: " << books[index].publisher << endl;
	cout << "Subject: " << books[index].subject << endl;
	cout << "ID: " << books[index].ID << endl;
	cout << "Accession Number: " << books[index].accessionNumber << endl;
	cout << "Year Of Publication: " << books[index].yearOfPub << endl;
	cout << "Issuable: " << books[index].issuable << endl;
	cout << "Issued or Not: " << books[index].issuedOrNot << endl;
	cout << "Date of Issuance: " << books[index].issuanceOfBook.day << "/" << books[index].issuanceOfBook.month << "/" << books[index].issuanceOfBook.year << endl;
	cout << "Book Return Date: " << books[index].returnDate.day << "/" << books[index].returnDate.month << "/" << books[index].returnDate.year << endl << endl;
}
Date Age(Date dob, Date currentDate)            // Function
{
	Date age;                       // declaring variables
	GetDate(currentDate);           // calling GetDate function to get latest date from user
	age.year = currentDate.year - dob.year;           // Calculating age
	age.month = currentDate.month - dob.month;
	age.day = currentDate.day - dob.day;
	if (age.day < 0)                      // Exception handling age 
	{
		age.day += 30;
		age.month--;
	}
	if (age.month < 0)                   // Exception handling age 
	{
		age.month += 12;
		age.year--;
	}
	return age;                // returning to calling function
}