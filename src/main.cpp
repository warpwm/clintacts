#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"
#include "inc/crypt.hpp"


int main(int argc, char **argv) {
    // string filePath = "/home/bresilla/contacts";
	// Contacts contacts;
    // contacts.encryption = true;
    // contacts.loadContacts(filePath);
    // contacts.newContact();
    // contacts.listContacts();
    // contacts.printContacts();
    // contacts.printAlt();
    // contacts.removeContact(contacts.getContact(10));
    // contacts.listContacts();
    // contacts.saveContacts(filePath);
    initscr();
    refresh();
    endwin();
    return 0;
}
