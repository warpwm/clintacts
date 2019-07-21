#include <string>
#include <vector>

using namespace std;

#ifndef COMMANDS_H
#define COMMANDS_H

struct contact { // Definition of the contact structure
	string name;
	string address;
	string email;
	string phonenr;
	string birthday;
	string misc;
};

bool execCmd(string cmd); // Checks validity of commands and executes the connected function if command exists
void printHelpScreen(); // Prints out a help screen of commands
void clear(); // Clears console and prints out welcome message
void addContact(); // Lets user add a new contact
void removeContact(); // Lets user remove a contact
void searchContacts(bool output); // Lets user search for contacts
void listContacts(); // Lists all contacts
vector<contact> regexSearch(string exp); // Performs regex search on contacts
void printWelcomeMessage(); // Prints out welcome message

#endif
