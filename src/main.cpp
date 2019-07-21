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

    contact contact;
    contact.printContact();
    // getchar();
    //close the window buffer
    // endwin();

    return 0;
}
