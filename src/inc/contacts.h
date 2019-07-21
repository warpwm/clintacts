#include <iostream>
#include <string>
#include <vector>

using namespace std;

class contact {
    private:
        string name;
        string address;
        string email;
        string phonenr;
        string birthday;
        string misc;
    public:
        contact();
        contact newContact();
        void addContact(contact c); // Lets user add a new contact
        void removeContact(contact c); // Lets user remove a contact
        contact searchContacts(string phrse); // Lets user search for contacts
        void listContacts(); // Lists all contacts
        void contactInfo(contact c);
        void printContacts(vector<contact>);
};
