#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"

void newContact(contacts& contacts){
    contact newContact;
    newContact.newContact();
    contacts.addContact(newContact);
}

int main(int argc, char **argv) {
    using namespace std;

    contacts contacts;
    // newContact(contacts);
    // newContact(contacts);
    // newContact(contacts);
    contacts.loadContacts("/home/bresilla/contacts.yaml");
    contacts.printContacts();

    contacts.saveContacts("/home/bresilla/contacts.yaml");
    return 0;
}
