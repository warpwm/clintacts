#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

using namespace std;

class contact {
    private:
        int index;
        string name;
        string address;
        string email_personal;
        string email_work;
        string phone;
        string website;
        string social;
    public:
        int getIndex();
        void setIndex(int value);
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
        void printContact();
        void newContact();
};

class Contacts{
    private:
        vector<contact> contactList;
        static int number;
    public:
        void newContact();
        void addContact(contact c); // Lets user add a new contact
        void removeContact(contact c); // Lets user remove a contact
        Contacts searchContact(string phrse); // Lets user search for contacts
        contact getContact(int index); // Lets user search for contacts
        void listContacts(); // Lists all contacts
        void printContacts();
        vector<contact> loadContacts(string filePath);
        void saveContacts(string filePath);
};
