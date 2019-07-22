#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"

int main(int argc, char **argv) {
    using namespace std;

    //initialze the screen
    //setup memory and screen
    // initscr();

    //refresh screen
    // refresh();

    //wait for keypress
    // int c = getchar();

    contacts contacts;
    contact contact1;
    contacts.addContact(contact1);

    contact contact2;
    contacts.addContact(contact2);

    contact contact3;
    contacts.addContact(contact3);

    contacts.getContact(2).printContact();
    // contacts.loadContacts("/home/bresilla/contacts.yaml");
    // getchar();
    //close the window buffer
    // endwin();

    return 0;
}
