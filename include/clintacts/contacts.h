#pragma once
#include <crypt.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <rang.hpp>
#include <regex>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <clintacts/contact.h>

class Contacts {
private:
    std::vector< contact > contactList;
    static int number;

public:
    bool encryption = false;
    contact newContact();
    void addContact( contact c );
    void editContact( contact c );
    void removeContact( contact c );
    Contacts searchContact( std::string phrse );
    contact getContact( std::string phrse );
    contact getContact( int index );
    void listContacts();
    void printContacts();
    std::vector< contact > loadContacts( std::string filePath );
    void saveContacts( std::string filePath );
    int numerate();
    int size() { return contactList.size(); };
    bool isValidContact( contact c );

    void testNew();
};
