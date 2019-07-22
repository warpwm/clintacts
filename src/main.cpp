#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"

int main(int argc, char **argv) {
    using namespace std;

    Contacts contacts;
    contacts.loadContacts("/home/bresilla/contacts.yaml");
    // contacts.newContact();
    // contacts.printContacts();
    contacts.listContacts();

    // contacts.searchContact("lavi").printContacts();

    // contacts.saveContacts("/home/bresilla/contacts.yaml");
    contacts.getContact(2).printContact();
    return 0;
}
