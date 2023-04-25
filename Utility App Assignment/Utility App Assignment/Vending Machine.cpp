#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

void output(string msg);
int numCheck(int min, int max);
bool nameCheck(string name);
bool letterCheck(char letter);
double moneyCheck(double money);

int main() {

	//sets the decimal point by 2
	cout << setprecision(2) << fixed;
	char cont;
	char transaction;
	int categoryChoice;
	int itemChoice;
	string basket;
	double total = 0;
	double money = 0;

	//multi dimensional array to store all of the products
	string products[4][7] = {
		{ "Snickers", "Crunchie", "Twirl",
		"Mars", "Galaxy", "KitKat", "Maltesers" },

		{ "Skittles", "Jelly Babies", "Wine Gums",
		"Haribos", "Starburst", "Love Hearts", "Fruit Pastilles" },

		{ "Hula Hoops", "Quavers","Wotsis",
		"Walkers Ready Salted", "Walkers Cheese & Onion",
		"Walkers Salt & Vinegar", "Doritos Cool Original" },

		{ "Coca-Cola", "Diet Coke", "Mineral Water",
		"Pepsi Max", "Fanta", "Sprite", "Ribena" }
	};

	//multi dimensional array to store all the prices for each product
	double prices[4][7] = {
		{0.60, 0.60, 0.60, 0.60, 1.00, 1.00, 1.00},
		{0.85, 0.85, 0.65, 0.65, 0.65, 0.65, 0.85},
		{0.60, 1.48, 1.48, 1.25, 0.60, 0.35, 0.60},
		{1.48, 1.33, 0.75, 1.10, 1.33, 1.33, 1.30}

	};
	//welcoming the user to the program and asking them their name
	output("Welcome to Marcus' Vending Machine");
	output("What is your name?");

	//stores the user name and ensure we get full name
	string name;
	getline(cin, name);
	//checking if name is NOT a string
	while (!nameCheck(name)) {
		output("Only letters can be accepted.");
		getline(cin, name);
	}

	//formatting the string - first index capitalised
	name[0] = toupper(name[0]);
	//for loop, checking for a space and capitalising first letter
	for (int i = 0; i < name.length(); i++) {
		if (name[i] == ' ') {
			name[i + 1] = toupper(name[i + 1]);
			break;
		}
	}

	//message saying hello to the user and informing them of the next stages
	cout << "Hello, " << name << ". Please input your money then"
		" you can choose which products you'd like to purchase." << endl;

	//when the user enters 'N', they come back here and restart with money input
	do {
		//variables are empty so if the user made a mistake with their basket, they can start again.
		total = 0;
		basket.clear();

		//no endl so the input can be on the same line
		cout << "How much money do you have? " << char(156);
		cin >> money;
		//moneyCheck function checks 
		money = moneyCheck(money);

		//when the user enters 'Y', they can re-purchase an and come back to this point in the program 
		do {
			cout << "You have " << char(156) << money - total << ". What would you like to buy?"
				"\nChocolate (1), Sweets (2), Crisps (3) or Cold Drinks (4)?" << endl;

			//their input goes through the function checking for any errors 
			categoryChoice = numCheck(1, 4);

			//printing out all of the items for the category selected
			for (int i = 0; i < 7; i++) {
				cout << "(" << i + 1 << ") " << products[categoryChoice - 1][i]
					<< " " << char(156) << prices[categoryChoice - 1][i];
				//if statement is used for UX. Printing a comma after the items and question mark for the last item
				if (i < 6) {
					cout << ", ";
				}
				else if (i == 6) {
					cout << "?";
				}
			}
			cout << endl;

			//users item choice goes through the same function as category choice
			itemChoice = numCheck(1, 7);
			//message to tell the user, item selected and the cost of the item
			cout << "You have selected the following item: " <<
				products[categoryChoice - 1][itemChoice - 1] <<
				". It costs: " << char(156) << prices[categoryChoice - 1][itemChoice - 1] << endl;

			//.append allow the user to add more than one item to the basket
			basket.append(" " + products[categoryChoice - 1][itemChoice - 1]);
			//total being added together by adding up the cost of all the items selected
			total += prices[categoryChoice - 1][itemChoice - 1];
			cout << "Your basket currently costs: " << char(156) << total << endl;

			//asking the user if they would like another item
			do {
				output("Would you like to buy another item? (Y/N)");
				cin >> cont;
				//toupper is used to ensure users input is uppercase
				cont = toupper(cont);
				//user input goes through the function and checks for any errors		
			} while (letterCheck(cont));

		} while (cont == 'Y');

		//informs the user what is in their basket
		cout << "You have the following items in your basket:" << basket << endl;

		//as long as the amount of the basket is more than, money entered. Print message asking for more money
		while (total > money) {
			cout << "Please, Enter more money! " << char(156) << total - money << endl;
			double tempMoney;
			cin >> tempMoney;
			money += moneyCheck(tempMoney);
		}

		//letting the user know they have entered enough money
		cout << "You have entered enough money: " << char(156) << money << endl;

		//checking if user has inputted 'Y' or 'N'
		do {
			output("Is this correct? (Y/N) (Selecting 'N' will ask you to input money again)");
			cin >> transaction;
			//user input to uppercase
			transaction = toupper(transaction);
		} while (letterCheck(transaction));

		//user goes back to money input
	} while (transaction == 'N');

	//if 'Y' entered, output message informing them of the process
	output("Your transaction is processing...");
	//this is used to simulate a transaction being processed
	Sleep(3000);

	//telling the user transaction is complete, their change and goodbye message
	cout << "Transaction complete\n\nHere is your change: " << char(156) << money - total
		<< ".\nHope you come back soon!\nGoodbye!" << endl;

	return 0;
}

//simple output function writes messages to the user
void output(string msg) {
	cout << msg << endl;
}

//ensuring the user has put an integer
int numCheck(int min, int max) {
	int num;
	cin >> num;
	//cin.peek has a look what is entered first and not extracting the input. Enter key does NOT pass through the stream  
	while (cin.fail() || num < min || num > max || cin.peek() != '\n') {
		cout << "Invalid, must be between " << min << "-" << max << "." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> num;
	}
	//ignores leftover enter key
	cin.ignore(); 
	return num;
}

//checks every character in the string for letters
bool nameCheck(string name) {
	//loop through all characters in string
	for (int i = 0; i < name.length(); i++) {
		//check if character is not a letter or a space
		if (!isalpha(name[i]) && name[i] != ' ') {
			return false;
		}
	}
	return true;
}

//checks if user has inputted a char
bool letterCheck(char letter) {
	if (!isalpha(letter) ){
		output("A number or symbol is invalid.");
		cin.ignore(256, '\n');
		return true;
	}
	//only allowing one character to be inputted
	else if (cin.peek() != '\n') {
		output("Too many characters have been entered. Please enter 'Y' or 'N'.");
		cin.ignore(256, '\n');
		return true;
	}
	//allows 'Y' and 'N' to been entered
	else if (letter == 'Y' || letter == 'N') {
		return false;
	}
	output("Other letters are invalid.");
	return true;
}

//to ensure the user can only input a double
double moneyCheck(double money) {
	//this will keep happening until users input is a double 
	while (cin.fail() || cin.peek() != '\n') {
		cout << "Please, enter at least " << char(156) << "0.01." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> money;
	}
	return money;
}