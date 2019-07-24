#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"
#include "inc/crypt.hpp"


int main(int argc, char **argv) {
    using namespace std;
    string filePath = "/home/bresilla/contacts";
    Contacts contacts;
    contacts.encryption = true;

    contacts.loadContacts(filePath);
    // contacts.newContact();
    // contacts.listContacts();

    // contacts.searchContact("lavi").printContacts();
    // contacts.editContact(contacts.getContact("franc"));
    contacts.listContacts();
    // contacts.getContact("fla").printContact();
    // contacts.saveContacts(filePath);
    return 0;
}
