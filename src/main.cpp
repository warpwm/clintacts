#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"
#include "inc/crypt.hpp"
// #include <cppurses/cppurses.hpp>


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
	WINDOW *two;
	initscr();
	start_color();
	scrollok(stdscr, TRUE);
	refresh();

	int y, x;
    getmaxyx(stdscr, y, x);
	init_pair(1, COLOR_BLACK, COLOR_BLUE);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	int centerx = x/2, centery = y/2;
	int width = x-(x/8), heigh = y-(y/8);

	two = newwin(heigh, width, centery-heigh/2,centerx-width/2);
	mvwaddstr(two, 0,0,"AWINDOW\n");
	// box(two, 0,0);
	bkgd(COLOR_PAIR(2));
	refresh();
	wbkgd(two, COLOR_PAIR(1));
	wrefresh(two);

	//USUAL END STAFF
	// refresh();
	getch();
    endwin();
	noecho();
    return 0;
}
