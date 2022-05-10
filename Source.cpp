#include <iostream>
#include <cmath>
#include <cstring>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>	
using namespace std;

#define constant 48 //convert char type data into 1 digit number
#define CASE_NUM 8 // number of selection, must be lesser than 9 due to the constrain of char type
#define BOOK_NUM 50 //maximum number of book.
typedef struct { string Bookname, ISBNnumber, Author, Edition, Year, Quantity, Tempbook,TempISBN,
						Tempauth, Tempedit, Tempyear, Tempquan; } LIST;

void home(void);
int get_option(); //display screen ONLY
void home_1_normal(); //first screen
void home_1_request();//ask for option
void home_1_invalid();//invalid input for option
void home_invalid_1(); // invalid input for repeat
void home_1_repeat(); //ask for repeat
void home_1_thank(); //end screen

//function
char repeat();				//function to repeat 
void display_header(LIST list[], int value);	//display the header for the table of the list
void file(LIST list[], int number, int& booknumber);			//obtain information from our text file and check for the total book in the store
void listout(LIST list[], int number);		//function to list out the information

void search_by_num(LIST list[], int value);		//function to search by ISBN number
/*void search_by_keyword(LIST list[], int value);	//function to search by keyword
void transform(string& word);*/
void lowquan(LIST list[], int value);

void update_list(LIST list[], int value);		//function to update the list
void add(LIST list[], int value);				//function to add information into the list
void delete_records(LIST list[], int value);	//function to delete information from the list
void exit(LIST list[], int value);				//function to exit and save the function

int main()
{
	int option, invalid, totalbook;
	char proceed;
	LIST list[BOOK_NUM+1];	//Book number need to +1 since the 0 is the header in the text file

	file(list, BOOK_NUM+1,totalbook);	//open file
	int check_booknumber(LIST list[], int number);
	home();					//Welcome screen

	do
	{
		home_1_request();
		option = get_option();	//Obtain option
		system("CLS");

		switch (option)
		{
		case 1:	//list out the information
		{
			listout(list, BOOK_NUM + 1);
			cout << "The total number of book is: " << totalbook << endl;
			system("PAUSE");
			system("CLS");
			proceed = 'n'; //So that the program can return to main menu.
			break;
		}
		case 2:	//search by ISBN number
		{
			do
			{
				search_by_num(list, totalbook +1);
				proceed = repeat();
				system("CLS");
			} while (proceed == 'y' || proceed == 'Y');
			break;
		}
		/*case 3:	//Search by keyword
		{
			do
			{	search_by_keyword(list, totalbook + 1);
				cout << endl;
				proceed = repeat();
				system("CLS");
			} while (proceed == 'y' || proceed == 'Y');
			break;
		}*/
		case 4:	//Show books with low inventory
		{
			do
			{
				lowquan(list, totalbook + 1);
				cout << endl;
				proceed = repeat();
				system("CLS");
			} while (proceed == 'y' || proceed == 'Y');
			break;
		}
		case 5:	//Update the list
		{
			do
			{
				update_list(list, totalbook + 1);
				cout << endl;
				proceed = repeat();
				system("CLS");
			} while (proceed == 'y' || proceed == 'Y');
			break;
		}
		case 6:	//Add new book information
		{
			do
			{
				if (totalbook < BOOK_NUM)
				{
					add(list, totalbook + 1);
					cout << endl;
					totalbook++;
					proceed = repeat();
					system("CLS");
				}
				else
				{
					cout << "Existing number of book exceeded the system capacity." << endl
						<< "Please update the source code or delete some files to continue." << endl;
					proceed = 'n';
				}
			} while (proceed == 'y' || proceed == 'Y');
			break;
			
		}
		case (7)://Remove existing book information
		{
			do
			{
				delete_records(list, totalbook + 1);
				proceed = repeat();
			} while (proceed == 'y' || proceed == 'Y');
			break;
		}
		case (8)://Exit and Save changes
		{
			exit(list, totalbook + 1);
			home_1_thank();
			system("PAUSE");
			exit(0);

		}
		}
	} while (proceed == 'N' || proceed == 'n'); 
	return 0;
}								

//FUNCTION PROTOTYPE DECLARATION

//HEADER
void home()
{
	home_1_normal();
	system("PAUSE");
	system("CLS");
	return;
}

void home_1_normal()
{
	cout << "Hi";
	return;
}

void home_1_request()
{
	cout << "1) List                        |\n"
		<< " 2) Search by ISBN number       |\n"
		<< " 3) Search by keyword           |\n"
		<< " 4) Show Low Inventories        |\n"
		<< " 5) Update                      |\n"
		<< " 6) Add                         |\n"
		<< " 7) Delete                      |\n"
		<< " 8) Exit and Save Changes       |\n";
	return;
}

void home_1_invalid()
{
	cout << "Opps, there is some error for   |\n"
		<< " your input... Can you please    |\n"
		<< " reenter your option?            |\n"
		<< " 1) List                        |\n"
		<< " 2) Search by ISBN number       |\n"
		<< " 3) Search by keyword           |\n"
		<< " 4) Show Low Inventories        |\n"
		<< " 5) Update                      |\n"
		<< " 6) Add                         |\n"
		<< " 7) Delete                      |\n"
		<< " 8) Exit       					|\n";
	return;
}

void home_1_repeat()
{
	cout<< " Do you want to repeat?  |\n"
		<< " (Y/N)                 |\n";
	return;
}

void home_invalid_1 ()
{
	{
		cout << "  Invalid input.          |\n"
			<< "  Please reenter.	    |\n"
			<< "  Do you want to repeat?  |\n"
			<< "  (Y/N)                  |\n";
		return;
	}
}

void home_1_thank()
{
	cout 
		<< "  Thank you very much.    |\n"
		<< "  Good bye and have a     |\n"
		<< "  nice day.              |\n";
	return;
}

void display_header(LIST list[], int value)
{
	cout << endl
		<< left << setw(56) << list[0].Bookname << "\t"
		<< left << setw(13) << list[0].ISBNnumber << "\t"
		<< left << setw(25) << list[0].Author << "\t"
		<< left << setw(5) << list[0].Edition << "\t"
		<< left << setw(4) << list[0].Year << "\t"
		<< left << setw(4) << list[0].Quantity << endl;

	cout << setfill('-') << setw(140) << "\n";
	cout << setfill(' ') << endl;
}

//FUNCTIONS
char repeat()
{
	char option;
		
	home_1_repeat();
	cout << "Your option (Y/N): \n";
	cin >> option;
	if (option != 'Y' && option != 'y' && option != 'N' && option != 'n')
	{
		do
		{
			system("CLS"); 
			cin.ignore();			
			home_invalid_1();
			cout << "Your option: \n";
			cin >> option;
		} while (option != 'Y' && option != 'y' && option != 'N' && option != 'n');
	}
	else system("CLS");
	return option;
}

int get_option()
{
	char option;
	cout << "Your option: \n";
	cin >> option;

	//ensure the option is always constant 1 to constant 7
	while (option <= constant || option > CASE_NUM + constant)
	{
		system("CLS");
		home_1_invalid();
		cout << "Your option: " << endl;
		cin >> option;
	};
	return ((int)option - constant);
}

void file(LIST list[], int number, int& booknumber)
{
	ifstream inFile;
	string reference = "";
	inFile.open("Text.txt");	//open text file
	booknumber = -1;				//initiate, negative one since there is a header row in the text file
	if (!inFile)
	{
		cerr << "Error opening input file\n";
		exit(100);
		system("PAUSE");
	};

	int i;
	for (i = 0; i < BOOK_NUM+1; i++)		//get data from text file
	{
		getline(inFile, list[i].Bookname, '\t');
		getline(inFile, list[i].ISBNnumber, '\t');
		getline(inFile, list[i].Author, '\t');
		getline(inFile, list[i].Edition, '\t');
		getline(inFile, list[i].Year, '\t');
		getline(inFile, list[i].Quantity, '\n');
		if (list[i].ISBNnumber.compare(reference) != 0) booknumber++;

	}
	inFile.close();		//close text file
	return;
}

void listout(LIST list[], int number)
{
	int i;

	for (i = 0; i < 50; i++)
	{
		if (list[i].ISBNnumber != "")		//to not creating empty lines after the last data
		{
			cout << left	<< setw(56) << list[i].Bookname << "\t" 
							<< setw(13) << list[i].ISBNnumber << "\t"
							<< setw(25) << list[i].Author << "\t" 
							<< setw(5) << list[i].Edition << "\t"
							<< setw(4) << list[i].Year << "\t" 
							<< setw(4) << list[i].Quantity << endl;
		}
	}
}

void search_by_num(LIST list[], int value)
{
	string num;
	int i;
	bool empty = true;
		cin.ignore();
		cout << "You have selected Search by ISBN number" << endl;
		cout << "Please key in search by" << endl;
		getline(cin, num);
		display_header(list, value);
		
		for (i = 1; i <= value; i++)
		{
			if (list[i].ISBNnumber.compare(num) == 0)
			{
				cout<< left << setw(56) << list[i].Bookname << "\t" 
					<< left << setw(13) << list[i].ISBNnumber << "\t"
					<< left << setw(25) << list[i].Author << "\t" 
					<< left << setw(5) << list[i].Edition<< "\t"
					<< left << setw(4) << list[i].Year << "\t" 
					<< left << setw(4) << list[i].Quantity << endl;
				empty = false;
			}
		};
		
		if (empty)
		{
			cout <<"\n" << "NO RECORD!!" << endl;
		};
	}

/*void search_by_keyword(LIST list[], int value)
{
	string keyword;
	int i;
	bool check = true;
	cin.ignore();
	cout << "------Search by Keyword------"<<endl;
	cout << "Please key in the keyword :";
	getline(cin, keyword);
	display_header(list, value);
	transform(keyword);

	for (i = 1; i <= value; i++)
	{
		list[i].Tempbook = list[i].Bookname;
		list[i].TempISBN = list[i].ISBNnumber;
		list[i].Tempauth = list[i].Author;
		list[i].Tempedit = list[i].Edition;
		list[i].Tempyear = list[i].Year;
		list[i].Tempquan = list[i].Quantity;

		transform(list[i].Tempbook);
		transform(list[i].TempISBN);
		transform(list[i].Tempauth);
		transform(list[i].Tempedit);
		transform(list[i].Tempyear);
		transform(list[i].Tempquan);

		if ((strstr(list[i].Tempbook.c_str(), keyword.c_str()) ||
			strstr(list[i].TempISBN.c_str(), keyword.c_str()) ||
			strstr(list[i].Tempauth.c_str(), keyword.c_str()) ||
			strstr(list[i].Tempedit.c_str(), keyword.c_str()) ||
			strstr(list[i].Tempyear.c_str(), keyword.c_str()) ||
			strstr(list[i].Tempquan.c_str(), keyword.c_str())))
		{
			cout << left << setw(58) << list[i].Bookname << "\t"
				<< left << setw(13) << list[i].ISBNnumber << "\t"
				<< left << setw(25) << list[i].Author << "\t"
				<< left << setw(5) << list[i].Edition << "\t"
				<< left << setw(4) << list[i].Year << "\t"
				<< left << setw(4) << list[i].Quantity << "\n";
			check = false;
		}

	}
		if (check)
			cout << "\n" << "NO RECORD!!" << endl;

	
}

void transform(string& word)
{
	string wuka;
	wuka.resize(word.length());
	transform(word.begin(), word.end(), word.begin(), tolower);
}*/

void lowquan(LIST list[], int value)
{
	int i;
	bool check = true;
	display_header(list, value);


	for (i = 1; i <= value; i++)
	{
		stringstream geek(list[i].Quantity);
		int x = 0;
		geek >> x;
			if (x < 10)
			{
				cout << left << setw(58) << list[i].Bookname << "\t"
					<< left << setw(13) << list[i].ISBNnumber << "\t"
					<< left << setw(25) << list[i].Author << "\t"
					<< left << setw(5) << list[i].Edition << "\t"
					<< left << setw(4) << list[i].Year << "\t"
					<< left << setw(4) << list[i].Quantity << "\n";
				check = false;
			}
		
	}
			if (check)
			cout << "\n" << "NO RECORD!!" << endl;

}
void update_list(LIST list[], int value)
{
	string num;
	int i, j;
	j = 0;


	cout << "Please enter ISBN number you wish to update: ";
	cin >> num;

	for (i = 0; i < value; i++)
	{
		if (list[i].ISBNnumber.compare(num) == 0)
		{
			cin.ignore();
			system("CLS");
			cout << "Record found!!\n";
			cout << "Please update book information\n";

			cout << "Book Name:";
			getline(cin, list[i].Bookname,'\n');

			cout << "ISBN Number: ";
			getline(cin, list[i].ISBNnumber, '\n');

			cout << "Author:";
			getline(cin, list[i].Author, '\n');

			cout << "Edition: ";
			getline(cin, list[i].Edition, '\n');

			cout << "Year: ";
			getline(cin, list[i].Year, '\n');

			cout << "Quantity: ";
			getline(cin, list[i].Quantity, '\n');

			cout << "Information updated.";

		}		else	j++;
	};

		if (j == value)
		{
			system("CLS");
			cout << "No item number matches\n";
		}
		else;
	return;
}

void add(LIST list[], int value)
{
	int i;
	
		i = 0;
		while ( list[i].ISBNnumber != "")
			i++;
		cin.ignore();
		cout << "Please enter new information.\n";
		cout <<left << "Book Name:";
		getline(cin, list[i].Bookname);

		cout << left << "ISBN Number: ";
		getline(cin, list[i].ISBNnumber);

		cout << left << "Author:";
		getline(cin, list[i].Author);

		cout << left << "Edition: ";
		getline(cin, list[i].Edition);

		cout << left << "Year: ";
		getline(cin, list[i].Year);

		cout << left << "Quantity: ";
		getline(cin, list[i].Quantity);

	return;
}

void delete_records(LIST list[], int value)
{
	string num;
	int i, j;
	j = 0;

	cout << "Please enter ISBN number you wish to delete: ";
	cin >> num;

	for (i = 0; i < value; i++)

	{
		if (list[i].ISBNnumber.compare(num)==0)
		{
			cout << "Record found!!\n";
			display_header(list,value);
			cout<< left << setw(56) << list[i].Bookname << "\t"
				<< left << setw(13) << list[i].ISBNnumber << "\t"
				<< left << setw(25) << list[i].Author << "\t"
				<< left << setw(5) << list[i].Edition << "\t"
				<< left << setw(4) << list[i].Year << "\t"
				<< left << setw(4) << list[i].Quantity << "\t";

			list[i].ISBNnumber = "";
			list[i].Bookname = "";
			list[i].Author = "";
			list[i].Quantity = "";
			list[i].Edition = "";
			list[i].Year = "";

			cout << "\nThe above data has been deleted\n";
			system("PAUSE");
		}
		else j++;
	}

		if (j == value +1)
		{
			system("CLS");
			cout << "No information found\n";
		}

}

void exit(LIST list[], int value)
{
	ofstream outFile("Text.txt");
	if (!outFile)
	{
		cout << "Error opening output file."<<endl;
		exit(100);
	}
	else
	{
		for (int i = 0; i < 50; i++)
		{
			if (list[i].ISBNnumber != "")
			{
				outFile << left << setw(58) << list[i].Bookname << "\t"
					<< left << setw(13) << list[i].ISBNnumber << "\t"
					<< left << setw(25) << list[i].Author << "\t"
					<< left << setw(5) << list[i].Edition << "\t"
					<< left << setw(4) << list[i].Year << "\t"
					<< left << setw(4) << list[i].Quantity << "\n";
			}
		}
	}
	return;
}

