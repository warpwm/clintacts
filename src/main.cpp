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

    auto enc = cryptor::encryptFile(filePath);
    // std::cout << "\n\n\n---------------\n\n\n" << enc << std::endl;
    auto dec = cryptor::decryptFile(filePath);
    // std::cout << "\n\n\n---------------\n\n\n" << dec << std::endl;

    // contacts.loadContacts(filePath);
    // contacts.newContact();
    // contacts.listContacts();
    // contacts.saveContacts(filePath);

    // contacts.searchContact("lavi").printContacts();
    // contacts.getContact(2).printContact();
    // contacts.getContact("fla").printContact();
    return 0;
}
