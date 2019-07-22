#include "contacts.h"

const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");

string userInput(string label, string errorMsg, string exp) {
    string input;
    smatch match;
    regex reg(exp);
    while(true) {
        cout << label;
        getline(cin, input);
        if (regex_match(input, match, reg)) {
            return input;
        } else {
            if(input.empty()){
                return "(none)";
            }
            cout << errorMsg;
        }
    }
}

contact::contact(){
    cout << "\x1B[2J\x1B[H";
    cout << "Enter details for the new contact:" << endl;
    name = userInput("Name: ", "Invalid format. You can only use characters.\n", "[a-zA-Z ]+");
    address = userInput("Address: ", "Invalid format. You can only use characters and digits.\n", ".+");
    email_personal = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-u0-9]+@[a-z.]+");
    email_work = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-z0-9]+@[a-z.]+");
    mobile = userInput("Phone: ", "Invalid format. The format should be: 'xxxyyxxyyy'\n", "[0-9]{7,16}");
    website = userInput("Website: ", "Invalid format. Use <https://www.website.com> format\n", "https?://[-._a-z0-9]+.[a-z]+");
    cout << "Contact has been created!" << endl;
    getchar();
}


void contact::printContact() {
    cout << "\x1B[2J\x1B[H";
    std::cout << "\n-----------------------------" << std::endl;
    std::cout << "Name: \t\t" << red << name << reset <<std::endl;
    std::cout << "Address: \t" << address << std::endl;
    std::cout << "Email: \t\t" << email_personal << std::endl;
    std::cout << "Email: \t\t" << email_work << std::endl;
    std::cout << "Phone: \t\t" << mobile << std::endl;
    std::cout << "Website: \t" << website << std::endl;
    std::cout << "-----------------------------\n" << std::endl;
}


void contactList::addContact(contact c){
    contacts.push_back(c);
}
void contactList::removeContact(contact c){}
contact contactList::searchContact(string phrse){}
void contactList::listContacts(){}
void contactList::contactInfo(contact c){}
void contactList::printContacts(vector<contact>){}
vector<contact> contactList::loadContacts(string filePath){
    YAML::Node config = YAML::LoadFile(filePath);
    return contacts;
}
void contactList::saveContacts(vector<contact>, string filePath){}
contact contactList::getContact(int index){
    return contacts[index];
}
