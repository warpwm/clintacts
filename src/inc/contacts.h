#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "crypt.hpp"

using namespace std;

class contact {
    private:
        int index;
        string name;
        string group;
        string company;
        string email_personal;
        string email_work;
        string phone;
        string website;
        string social;
    public:
        int getIndex();
        void setIndex(int value);
        string getGroup();
        void setGroup(string value);
        string getName();
        void setName(string value);
        string getCompany();
        void setCompany(string value);
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
        bool encryption = false;
        void newContact();
        void addContact(contact c); // Lets user add a new contact
        void editContact(contact& c); // Lets user add a new contact
        void removeContact(contact c); // Lets user remove a contact
        Contacts searchContact(string phrse); // Lets user search for contacts
        contact getContact(string phrse); // Lets user search for contacts
        contact getContact(int index); // Lets user search for contacts
        void listContacts(); // Lists all contacts
        void printContacts();
        vector<contact> loadContacts(string filePath);
        void saveContacts(string filePath);
        int numerate();
        bool isValidContact(contact c);
};
