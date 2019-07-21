#include <iostream>
#include <string>
#include <vector>
#include "helpers.h"
#include "commands.h"

using namespace std;

bool execCmd(string cmd); // Checks validity of commands and executes the connected function if command exists
void printHelpScreen(); // Prints out a help screen of commands
void clear(); // Clears console and prints out welcome message
void addContact(); // Lets user add a new contact
void removeContact(); // Lets user remove a contact
void searchContacts(bool output); // Lets user search for contacts
void listContacts(); // Lists all contacts
vector<contact> regexSearch(string exp); // Performs regex search on contacts
void printWelcomeMessage(); // Prints out welcome message

// Handles the clear command
void clear() {
	cout << "\x1B[2J\x1B[H";

	printWelcomeMessage();
}
// Handles the add command
void addContact() {
	contact c; // Make a new contact

	// Clear screen
	clear();

	cin.ignore();

	cout << "Enter details for the new contact:" << endl;

	// Let user enter details
	c.name = getUserInput("Name: ", "Invalid format. You can only use characters.\n", "[a-öA-Ö ]+");
	c.address = getUserInput("Address: ", "Invalid format. You can only use characters and digits.\n", "[a-öA-Ö0-9 ]+");
	c.email = getUserInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-ö0-9]+@[a-ö.]+");
	c.phonenr = getUserInput("Phone: ", "Invalid format. The format should be: 'xxxyyxxyyy'\n", "[0-9]{10}");
	c.birthday = getUserInput("Birthday: ", "Invalid format. The format should be: 'yyyymmdd'\n", "[0-9]{8}");
	c.misc = getUserInput("Miscellaneous: ", "Invalid format. Can't use newline.\n", ".+");

	// Add new contact to contacts and save to file
	contacts.push_back(c);
	exportContacts();

	// Notify user
	cout << "Contact has been added!" << endl;
}
// Handles the remove command
void removeContact() {
	string choice, searchPhrase;
	bool cancel = false;
	int listChoice;

	// Clear screen
	clear();

	// Receive search input from user
	cout << "Search for a contact to remove: ";
	cin >> searchPhrase;

	// Use regexSearch to get a vector of search results
	vector<contact> matches = regexSearch(searchPhrase);

	// Check if matches are found
	if( !matches.empty() ) { // Matches found
		// Print out matches
		printContacts(matches, true);

		// Let user select from menu by id
		cout << "Type in the number of the contact you would like to remove, or 'cancel' to cancel this process: ";

		while(cin >> choice) {
			if(choice == "cancel") {
				cancel = true;
				break;
			} else if ( isNumber(choice) ) {
				listChoice = stoi(choice);

				// Check if number is withing listing range
				if(listChoice >= 1 && listChoice <= matches.size()) {
					break;
				} else {
					cout << "The number specified is not within the lists range, please select another one: ";
				}
			} else {
				cout << "Invalid choice. Can only be a number in the list, or 'cancel': ";
			}
		}

		// Don't do if we cancelled
		if(!cancel) {
			// Print out details of that particular contact, Ask for confirmation y/n
			printContact(matches.at(listChoice - 1)); // - 1 since list starts at 1 instead of 0

			cout << "\nAre you sure you want to delete the contact above? (y/n) ";
			while(cin >> choice) {
				if(choice == "y") {
					// Remove the contact with this number
					for (int i = 0; i < contacts.size(); i++) {
						if(isContactMatch(matches.at(listChoice - 1), contacts.at(i) )) {
							contacts.erase(contacts.begin()+i); // Remove that contact
							exportContacts(); // Save changes to file
							break;
						}
					}

					cout << "Contact removed!" << endl;
					break;
				} else if (choice == "n") {
					break; // Break out so user can enter new commands
				} else {
					cout << "Invalid choice, please answer with 'y' or 'n': ";
				}
			}
		}

	} else { // No match found
		cout << "No matches found. Can't delete user if we can't find them!" << endl;
	}
}
// Handles the search command
void searchContacts(bool output) {
	// Clear screen
	clear();

	string searchPhrase;

	// Receive search input from user
	cout << "Enter search phrase: ";
	cin >> searchPhrase;

	// Store matches in matches vector
	vector<contact> matches = regexSearch(searchPhrase); // Use regexSearch to perform search and receive a list of contacts

	// Check if matches are found, if so, print them out
	if( !matches.empty() ) {
		cout << "Search yielded results:\n" << endl;
		printContacts(matches, false);
	} else {
		cout << "No matches have been found!" << endl;
	}
}
// Handles the list command, to list all contacts
void listContacts() {
	// Print out a list of all contacts in the contacts map
	if( !contacts.empty() ) { // If not empty
		printContacts(contacts, false);
	} else { // If empty
		cout << "You have no contacts silly! Add a new one by typing 'add'" << endl;
	}
}
// Takes a command, if valid executes it
bool execCmd(string cmd) {
	// Check if valid command and execute it if so, if not return false
	if(cmd == "q" || cmd == "quit") running = false; // User wants to terminate program
	else if(cmd == "help") printHelpScreen(); //
	else if(cmd == "add") addContact(); //
	else if(cmd == "remove") removeContact(); //
	else if(cmd == "search") searchContacts(true); //
	else if(cmd == "list") listContacts(); //
	else if(cmd == "clear") clear(); //
	else return false; // If no match found

	return true;
}
// Prints a list of commands
void printHelpScreen() {
	// Clear screen
	clear();

	cout << "Available commands and their usage:\n" << endl;

	// Print out commands and descriptions
	cout << "'clear': Clears the console. Useful for keeping things tidy." << endl;
	cout << "'add': Allows you to add a new contact." << endl;
	cout << "'remove': Removes a specific contact." << endl;
	cout << "'search': Searches based on search criteria." << endl;
	cout << "'list': Lists all of your current contacts." << endl;
	cout << "'q' or 'quit': Terminates the program.\n" << endl;
}
// Performs a regex search and returns matches based on given string
vector<contact> regexSearch(string exp) {
	// Declare matches vector
	vector<contact> matches;
	smatch m;
	string tmp;

	// Iterate through contacts
	for (int i = 0; i < contacts.size(); i++) {
		// Concatenate all of the fields in the contact
		tmp = contacts.at(i).name + contacts.at(i).address + contacts.at(i).email + contacts.at(i).phonenr + contacts.at(i).birthday + contacts.at(i).misc;
		tmp = strToLower(tmp);

		// Search the concatenated string for results
		if( regex_search( tmp, m, regex( strToLower(exp) ) ) ) {
			matches.push_back( contacts.at(i) ); // Add the contact to matches
		}
	}

	// Return matches vector
	return matches;
}
// Prints a welcome message
void printWelcomeMessage() {
	// Prints welcome message
	cout << "Welcome to Contacts. The console below allows you to perform various actions." << endl << "To see all available commands, type: 'help'\n" << endl;
}
