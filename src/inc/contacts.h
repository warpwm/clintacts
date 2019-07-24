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
        pair<string, int> indexx = make_pair("Index", 0);
        pair<string, string> namex = make_pair("Name", "(none)");
        pair<string, string> groupx = make_pair("Group", "(none)");
        pair<string, string> companyx= make_pair("Company", "(none)");
        pair<string, string> email1 = make_pair("EmailPersonal", "(none)");
        pair<string, string> email2 = make_pair("EmailWork", "(none)");
        pair<string, string> phonex = make_pair("Phone", "(none)");
        pair<string, string> websitex = make_pair("Website", "(none)");
        pair<string, string> socialx = make_pair("Social", "(none)");

        string index_label = "Index";
        string name_label = "Name";
        string group_label = "Group";
        string company_label = "Company";
        string email1_label = "EmailPersonal";
        string email2_label = "EmailWork";
        string phone_label = "Phone";
        string website_label = "Website";
        string social_label = "Social";

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
