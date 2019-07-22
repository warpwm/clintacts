#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <sqlite3.h>

using namespace std;

class contact {
    private:
        string name;
        string address;
        string email_personal;
        string email_work;
        string phone;
        string website;
        string social;
    public:
        string getName();
        void setName(string value);
        string getAddress();
        void setAddress(string value);
        string getEmailPersonal();
        void setEmailPersonal(string value);
        string getEmailWork();
        void setEmailWork(string value);
        string getPhone();
        void setPhone(string value);
        string getWebsite();
        void setWebsite(string value);
        string getSocial();
        void setSocial(string value);

        void newContact();
        void printContact();
};

class contacts{
    private:
        vector<contact> contactList;
        int number;
    public:
        void addContact(contact c); // Lets user add a new contact
        void removeContact(contact c); // Lets user remove a contact
        contact searchContact(string phrse); // Lets user search for contacts
        contact getContact(int index); // Lets user search for contacts
        void listContacts(); // Lists all contacts
        void contactInfo(contact c);
        void printContacts();
        vector<contact> loadContacts(string filePath);
        void saveContacts(string filePath);
};
