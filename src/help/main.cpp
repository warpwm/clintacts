// Include libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include "inc/helpers.h"
#include "inc/commands.h"

using namespace std;

// Function declarations
void printContacts(vector<contact> cts, bool numbered);
void printContact(contact c); // Prints a contact
void importContacts(); // Imports contacts from file
void exportContacts(); // Exports contacts to file
bool isContactMatch(contact c1, contact c2); // Compares two contacts

// Global data structures
vector<contact> contacts; // Stores all contacts
bool running; // Handles program termination

// Main program
int main() {
	string cmd = ""; // Stores user command input

	// Clear the console and print out welcome message
	clear();

	// Import contacts from file
	importContacts();

	// Set running to true
	running = true;

	while(running) {
		// Receive commands
		cout << "$ ";
		cin >> cmd;

		// Execute entered command - If function returns false, invalid format/commands
		if(!execCmd(cmd)) {
			cout << "Command not recognized. Type 'help' for a list of commands." << endl;
		}
	}

	return 0;
}

// Prints out vector of given contacts, prints as list if numbered is true
void printContacts(vector<contact> cts, bool numbered) {
	for (int i = 0; i < cts.size(); i++) { // Iterate through all contacts
		if(numbered) cout << i+1 << "." << endl; // Print out list number

		printContact( cts.at(i) );

		cout << endl;
	}
}
// Prints a single contact
void printContact(contact c) {
	// Print out contact information
	cout << "Name: " << c.name << endl;
	cout << "Address: " << c.address << endl;
	cout << "Email: " << c.email << endl;
	cout << "Phone: " << c.phonenr << endl;
	cout << "Birthday: " << c.birthday << endl;
	cout << "Miscellaneous: " << c.misc << endl;
}
// Imports contacts from file
void importContacts() {
	fstream input("contacts.txt", fstream::in);
	string line, buff;
	bool errors = false;

	// Iterate through file and add to contacts
	while( getline(input, line) && errors == false ) {
		vector<string> fields;
		string field;
		stringstream ss(line);

		// Split line by space and process into fields vector
		while ( getline(ss, field, '|') ) {
			fields.push_back(field);
		}

		if(fields.size() == 6) { // Size will be one less than actual items
			// Create contact
			contact c;
			c.name = fields.at(0);
			c.address = fields.at(1);
			c.email = fields.at(2);
			c.phonenr = fields.at(3);
			c.birthday = fields.at(4);
			c.misc = fields.at(5);

			// Add contact to contacts vector
			contacts.push_back(c);
		} else {
			cout << "The file that stores the contacts is corrupt. Any changes you make will overwrite the file. You can exit by typing 'q' or 'quit' and manually go through the file yourself." << endl;

			errors = true; // Exit fstream loop
		}
	}
}
// Exports contacts to file
void exportContacts() {
	fstream output("contacts.txt", fstream::out);

	// Iterate through contacts and write to file
	for (int i = 0; i < contacts.size(); i++) { // Iterate through all contacts
		output << contacts.at(i).name << "|";
		output << contacts.at(i).address << "|";
		output << contacts.at(i).email << "|";
		output << contacts.at(i).phonenr << "|";
		output << contacts.at(i).birthday << "|";
		output << contacts.at(i).misc << endl;
	}
}
// Compares two contacts and returns true or false
bool isContactMatch(contact c1, contact c2) {
	// Returns an AND comparison between all the fields in c1 and c2
	return c1.name == c2.name && c1.address == c2.address && c1.email == c2.email && c1.phonenr == c2.phonenr && c1.birthday == c2.birthday && c1.misc == c2.misc;
}
