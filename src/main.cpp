#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#include "inc/contacts.h"
#include "inc/crypt.hpp"

void encryption(string filePath){
    std::ifstream ifs(filePath);
    auto fileStr =  string((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    std::cout << fileStr << std::endl;
    auto enc = cryptor::encrypt(fileStr);
    ofstream fout(filePath);
    fout << enc;
}

void decryption (string filePath){
    std::ifstream ifs(filePath);
    auto fileStr =  string((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    std::cout << fileStr << std::endl;
    auto dec = cryptor::decrypt(fileStr);
    ofstream fout(filePath);
    fout << dec;
}

int main(int argc, char **argv) {
    using namespace std;
    string filePath = "/home/bresilla/contacts";
    Contacts contacts;

    // encryption(filePath);
    // decryption(filePath);

    contacts.loadContacts(filePath);
    // contacts.newContact();
    contacts.listContacts();
    // contacts.saveContacts(filePath);

    contacts.searchContact("lavi").printContacts();
    // contacts.getContact(2).printContact();
    // contacts.getContact("fla").printContact();
    return 0;
}
