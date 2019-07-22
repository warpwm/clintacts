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
    contacts.listContacts();
    contacts.saveContacts("/home/bresilla/contacts.yaml");

    // contacts.searchContact("lavi").printContacts();
    // contacts.getContact(2).printContact();
    contacts.getContact("fla").printContact();
    return 0;
}
