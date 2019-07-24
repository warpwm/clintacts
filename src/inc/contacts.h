#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <map>
#include <yaml-cpp/yaml.h>
#include "crypt.hpp"

using namespace std;

class contact {
    private:
        map<std::string, std::string> container;
        pair<string, int> index = make_pair("Index", 0);
        pair<string, string> name = make_pair("Name", "(none)");
        pair<string, string> group = make_pair("Group", "(none)");
        pair<string, string> company= make_pair("Company", "(none)");
        pair<string, string> email1 = make_pair("EmailPersonal", "(none)");
        pair<string, string> email2 = make_pair("EmailWork", "(none)");
        pair<string, string> phone = make_pair("Phone", "(none)");
        pair<string, string> website = make_pair("Website", "(none)");
        pair<string, string> social = make_pair("Social", "(none)");

    public:
        void setIndex(int value);
        int getIndex(){ return index.second; }
        string getIndexLabel(){ return index.first; }
        void setGroup(string value);
        string getGroup(){ return group.second; }
        string getGroupLabel(){ return group.first; }
        void setName(string value);
        string getName(){ return name.second; }
        string getNameLabel(){ return name.first; }
        void setCompany(string value);
        string getCompany(){ return company.second; }
        string getCompanyLabel(){ return company.first; }
        void setEmailPersonal(string value);
        string getEmailPersonal(){ return email1.second; }
        string getEmailPersonalLabel(){ return email1.first; }
        void setEmailWork(string value);
        string getEmailWork(){ return email2.second; }
        string getEmailWorkLabel(){ return email2.first; }
        void setPhone(string value);
        string getPhone(){ return phone.second; }
        string getPhoneLabel(){ return phone.first; }
        void setWebsite(string value);
        string getWebsite(){return website.second; }
        string getWebsiteLabel(){return website.first; }
        void setSocial(string value);
        string getSocial(){return social.second;}
        string getSocialLabel(){return social.first;}

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
        void editContact(contact c); // Lets user add a new contact
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
