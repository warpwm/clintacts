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

void contact::newContact(){
    cout << "\x1B[2J\x1B[H";
    cout << "Enter details for the new contact:" << endl;
    name = userInput("Name: ", "Invalid format. You can only use characters.\n", "[a-zA-Z ]+");
    address = userInput("Address: ", "Invalid format. You can only use characters and digits.\n", ".+");
    email_personal = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-u0-9]+@[a-z.]+");
    email_work = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-z0-9]+@[a-z.]+");
    phone = userInput("Phone: ", "Invalid format. The format should be: 'xxxyyxxyyy'\n", "[0-9]{7,16}");
    website = userInput("Website: ", "Invalid format. Use <https://www.website.com> format\n", "https?://[-._a-z0-9]+.[a-z]+");
    social = userInput("Address: ", "Invalid format. You can only use characters and digits.\n", ".+");
    cout << "Contact has been created!" << endl;
    cout << "\x1B[2J\x1B[H";
}

string contact::getName(){ return name; }
void contact::setName(string value){ name=value; }
string contact::getAddress(){ return address; }
void contact::setAddress(string value){ address=value; }
string contact::getEmailPersonal(){ return email_personal; }
void contact::setEmailPersonal(string value){ email_personal=value; }
string contact::getEmailWork(){ return email_work; }
void contact::setEmailWork(string value){ email_work=value; }
string contact::getPhone(){ return phone; }
void contact::setPhone(string value){ phone=value; }
string contact::getWebsite(){return website; }
void contact::setWebsite(string value){ website=value; }
string contact::getSocial(){return social;}
void contact::setSocial(string value){ social=value; }



void contact::printContact() {
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Name: \t\t" << red << name << reset <<std::endl;
    std::cout << "Address: \t" << red << address << reset << std::endl;
    std::cout << "Email: \t\t" << red << email_personal << reset << std::endl;
    std::cout << "Email: \t\t" << red << email_work << reset << std::endl;
    std::cout << "Phone: \t\t" << red << phone << reset << std::endl;
    std::cout << "Website: \t" << red << website << reset << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

void contacts::addContact(contact c){
    contactList.push_back(c);
}

void contacts::removeContact(contact c){}
contact contacts::searchContact(string phrse){}
void contacts::listContacts(){}
void contacts::contactInfo(contact c){}
void contacts::printContacts(){
    for (auto i : contactList) {
        i.printContact();
    }
}
vector<contact> contacts::loadContacts(string filePath){
    auto config = YAML::LoadAllFromFile(filePath);
    for (auto config : config) {
        contact contact;
        contact.setName(config["Name"].as<string>());
        contact.setAddress(config["Address"].as<string>());
        contact.setEmailPersonal(config["EmailPersonal"].as<string>());
        contact.setEmailWork(config["EmailWork"].as<string>());
        contact.setPhone(config["Phone"].as<string>());
        contact.setWebsite(config["Website"].as<string>());
        contactList.push_back(contact);
    }
    return contactList;
}
void contacts::saveContacts(string filePath){
    YAML::Emitter out;
    for (auto i : contactList) {
        out << YAML::BeginMap;
        out << YAML::Key << "Name" << YAML::Value << i.getName();
        out << YAML::Key << "Address" << YAML::Value << i.getAddress();
        out << YAML::Key << "EmailPersonal" << YAML::Value << i.getEmailPersonal();
        out << YAML::Key << "EmailWork" << YAML::Value << i.getEmailWork();
        out << YAML::Key << "Phone" << YAML::Value << i.getPhone();
        out << YAML::Key << "Website" << YAML::Value << i.getWebsite();
        out << YAML::EndMap;
        ofstream fout(filePath);
        fout << out.c_str();
    }
}
contact contacts::getContact(int index){
    return contactList[index];
}
