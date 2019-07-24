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

string checkString(std::string input, std::string exp, std::string msg) {
    smatch match;
    regex reg(exp);
    while(true) {
        if (regex_match(input, match, reg)) {
            return input;
        } else {
            if(input.empty()){
                return "(none)";
            }
            cout << msg;
        }
    }
}

// void contact::setGroup(string value){ group=checkString(value, ".+", "Invalid format."); }
// void contact::setName(string value){ name=checkString(value, "[a-zA-Z ]+", "Invalid format. You can only use characters."); }
// void contact::setCompany(string value){ company=checkString(value, ".+", "Invalid format."); }
// void contact::setEmailPersonal(string value){ email_personal=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'"); }
// void contact::setEmailWork(string value){ email_work=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'"); }
// void contact::setPhone(string value){ phone=checkString(value, "[0-9]{7,16}", "Invalid format. The format should be: 'xxxyyxxyyy'"); }
// void contact::setWebsite(string value){ website=checkString(value, "https?://[-._a-z0-9]+.[a-z]+", "Invalid format. Use <https://www.website.com> format"); }
// void contact::setSocial(string value){ social=checkString(value, ".+", "Invalid format."); }

int contact::getIndex(){ return index; }
void contact::setIndex(int value) { index=value; }
string contact::getGroup(){ return group; }
void contact::setGroup(string value){ group=value; }
string contact::getName(){ return name; }
void contact::setName(string value){ name=value; }
string contact::getCompany(){ return company; }
void contact::setCompany(string value){ company=value; }
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


void contact::newContact(){
    cout << "\x1B[2J\x1B[H";
    cout << "Enter details for the new contact:" << endl;
    name = userInput("Name: ", "Invalid format. You can only use characters.\n", "[a-zA-Z ]+");
    group = userInput("Group: ", "Invalid format. You can only use characters and digits.\n", ".+");
    company = userInput("Company: ", "Invalid format. You can only use characters and digits.\n", ".+");
    email_personal = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-z0-9]+@[a-z.]+");
    email_work = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-z0-9]+@[a-z.]+");
    phone = userInput("Phone: ", "Invalid format. The format should be: 'xxxyyxxyyy'\n", "[0-9]{7,16}");
    website = userInput("Website: ", "Invalid format. Use <https://www.website.com> format\n", "https?://[-._a-z0-9]+.[a-z]+");
    social = userInput("Social: ", "Invalid format. You can only use characters and digits.\n", ".+");
    index = 0;
    cout << "Contact has been created!" << endl;
    cout << "\x1B[2J\x1B[H";
}



void contact::printContact() {
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Index: \t\t" << red << index << reset <<std::endl;
    std::cout << "Name: \t\t" << red << name << reset <<std::endl;
    std::cout << "Group: \t\t" << red << group << reset <<std::endl;
    std::cout << "Company: \t" << red << company << reset << std::endl;
    std::cout << "Email: \t\t" << red << email_personal << reset << std::endl;
    std::cout << "Email: \t\t" << red << email_work << reset << std::endl;
    std::cout << "Phone: \t\t" << red << phone << reset << std::endl;
    std::cout << "Website: \t" << red << website << reset << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

int Contacts::numerate(){
    int index = 1;
    for (auto& i : contactList) {
        i.setIndex(index);
        index++;
    }
    return index;
}

void Contacts::newContact(){
    // int indx = 1;
    // for (auto i : contactList) {
        // indx++;
    // }
    contact newContact;
    newContact.newContact();
    contactList.push_back(newContact);
    numerate();
}

void Contacts::addContact(contact c){
    contactList.push_back(c);
}

void Contacts::removeContact(contact c){
    for (int i = 0; i < contactList.size(); ++i) {
        if (contactList[i].getIndex() == c.getIndex() && contactList[i].getName() == c.getName()) {
            contactList.erase(contactList.begin() + i);
        }
    }
    numerate();
}

void Contacts::editContact(contact& c){
    contact contact;
    contact.newContact();
    contact.setIndex(c.getIndex());
    c = contact;
}

void Contacts::listContacts(){
    cout << "\x1B[2J\x1B[H";
    for (auto c : contactList) {
        std::cout << red << c.getIndex() << ".  " <<reset;
        std::cout << c.getName() << "\t";
        std::cout << c.getEmailPersonal() << std::endl;
    }
}

void Contacts::printContacts(){
    for (auto i : contactList) {
        i.printContact();
    }
}

vector<contact> Contacts::loadContacts(string filePath){
    cryptor::decryptFile(filePath);
    auto config = YAML::LoadAllFromFile(filePath);
    int index = 1;
    for (auto config : config) {
        contact contact;
        contact.setIndex(index);
        contact.setName(config["Name"].as<string>());
        contact.setGroup(config["Group"].as<string>());
        contact.setCompany(config["Company"].as<string>());
        contact.setEmailPersonal(config["EmailPersonal"].as<string>());
        contact.setEmailWork(config["EmailWork"].as<string>());
        contact.setPhone(config["Phone"].as<string>());
        contact.setWebsite(config["Website"].as<string>());
        contactList.push_back(contact);
        index++;
    }
    if (encryption){
        cryptor::encryptFile(filePath);
    }
    return contactList;
}

void Contacts::saveContacts(string filePath){
    YAML::Emitter out;
    int index = 1;
    for (auto i : contactList) {
        out << YAML::BeginMap;
        out << YAML::Key << "Index" << YAML::Value << index;
        out << YAML::Key << "Name" << YAML::Value << i.getName();
        out << YAML::Key << "Group" << YAML::Value << i.getGroup();
        out << YAML::Key << "Company" << YAML::Value << i.getCompany();
        out << YAML::Key << "EmailPersonal" << YAML::Value << i.getEmailPersonal();
        out << YAML::Key << "EmailWork" << YAML::Value << i.getEmailWork();
        out << YAML::Key << "Phone" << YAML::Value << i.getPhone();
        out << YAML::Key << "Website" << YAML::Value << i.getWebsite();
        out << YAML::EndMap;
        ofstream fout(filePath);
        fout << out.c_str();
        index++;
    }
    if (encryption){
        cryptor::encryptFile(filePath);
    }
}

contact Contacts::getContact(string phrse){
    contact contact;
    smatch match;
    string tmp;
    for (auto i : contactList) {
        tmp = i.getName();
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        transform(phrse.begin(), phrse.end(), phrse.begin(), ::tolower);
        if(regex_search(tmp, match, regex(phrse))) {
            return i;
        }
    }
    return contact;
}

Contacts Contacts::searchContact(string phrse){
    Contacts matches;
    smatch match;
    string tmp;
    for (auto i : contactList) {
        tmp = i.getName();
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        transform(phrse.begin(), phrse.end(), phrse.begin(), ::tolower);
        if(regex_search(tmp, match, regex(phrse))) {
            matches.addContact(i);
        }
    }
    return matches;
}

contact Contacts::getContact(int index){
    contact contact;
    if (index <= contactList.size() || index > 0) {
        return contactList[index-1];
    }
    return contact;
}

bool Contacts::isValidContact(contact c){
    if (c.getName().empty() || c.getIndex()==0) {
        return false;
    }
    return true;
}
