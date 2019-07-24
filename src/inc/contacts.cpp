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
            return "(none)";
        }
    }
}

void contact::setIndex(int value) { index=value; }
void contact::setGroup(string value){ group=checkString(value, ".+", "Invalid format."); }
void contact::setName(string value){ name=checkString(value, "[a-zA-Z ]+", "Invalid format. You can only use characters."); }
void contact::setCompany(string value){ company=checkString(value, ".+", "Invalid format."); }
void contact::setEmailPersonal(string value){ email_personal=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'");}
void contact::setEmailWork(string value){ email_work=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'"); }
void contact::setPhone(string value){ phone=checkString(value, "[0-9]{7,16}", "Invalid format. The format should be: 'xxxyyxxyyy'"); }
void contact::setWebsite(string value){ website=checkString(value, "https?://[-._a-z0-9]+.[a-z]+", "Invalid format. Use <https://www.website.com> format"); }
void contact::setSocial(string value){ social=checkString(value, ".+", "Invalid format."); }

int contact::getIndex(){ return index; }
string contact::getGroup(){ return group; }
string contact::getName(){ return name; }
string contact::getCompany(){ return company; }
string contact::getEmailPersonal(){ return email_personal; }
string contact::getEmailWork(){ return email_work; }
string contact::getPhone(){ return phone; }
string contact::getWebsite(){return website; }
string contact::getSocial(){return social;}

// void contact::setGroup(string value){ group=value; }
// void contact::setName(string value){ name=value; }
// void contact::setCompany(string value){ company=value; }
// void contact::setEmailPersonal(string value){ email_personal=value; }
// void contact::setEmailWork(string value){ email_work=value; }
// void contact::setPhone(string value){ phone=value; }
// void contact::setWebsite(string value){ website=value; }
// void contact::setSocial(string value){ social=value; }


void contact::newContact(){
    cout << "\x1B[2J\x1B[H";
    string value;
    cout << "Enter details for the new contact:" << endl;
    index=0;
    cout << namex.first << ": "; getline(cin, value);
    name=checkString(value, "[a-zA-Z ]+", "Invalid format. You can only use characters.");
    cout << groupx.first << ": "; getline(cin, value);
    group=checkString(value, ".+", "Invalid format.");
    cout << companyx.first << ": "; getline(cin, value);
    company=checkString(value, ".+", "Invalid format.");
    cout << email1.first  << ": "; getline(cin, value);
    email_personal=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'");
    cout << email2.first << ": "; getline(cin, value);
    email_work=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'");
    cout << phonex.first << ": "; getline(cin, value);
    phone=checkString(value, "[0-9]{7,16}", "Invalid format. The format should be: 'xxxyyxxyyy'");
    cout << websitex.first << ": "; getline(cin, value);
    website=checkString(value, "https?://[-._a-z0-9]+.[a-z]+", "Invalid format. Use <https://www.website.com> format");
    cout << socialx.first << ": "; getline(cin, value);
    social=checkString(value, ".+", "Invalid format.");
    cout << "Contact has been created!" << endl;
    cout << "\x1B[2J\x1B[H";
}



void contact::printContact() {
    std::cout << "-----------------------------" << std::endl;
    std::cout << indexx.first << ": \t\t" << red << index << reset <<std::endl;
    std::cout << namex.first << ": \t\t" << red << name << reset <<std::endl;
    std::cout << groupx.first << ": \t\t" << red << group << reset <<std::endl;
    std::cout << companyx.first << ": \t" << red << company << reset << std::endl;
    std::cout << email1.first << ": \t\t" << red << email_personal << reset << std::endl;
    std::cout << email2.first << ": \t\t" << red << email_work << reset << std::endl;
    std::cout << phonex.first << ": \t\t" << red << phone << reset << std::endl;
    std::cout << websitex.first << ": \t" << red << website << reset << std::endl;
    std::cout << socialx.first << ": \t" << red << social << reset << std::endl;
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

void Contacts::editContact(contact c){
    contact contact;
    contact.newContact();
    for (int i = 0; i < contactList.size(); ++i) {
        if (contactList[i].getIndex() == c.getIndex() && contactList[i].getName() == c.getName()) {
            contactList[i]=contact;
        }
    }
    numerate();
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
        contact.setName(config[contact.name_label].as<string>());
        contact.setGroup(config[contact.group_label].as<string>());
        contact.setCompany(config[contact.company_label].as<string>());
        contact.setEmailPersonal(config[contact.email1_label].as<string>());
        contact.setEmailWork(config[contact.email2_label].as<string>());
        contact.setPhone(config[contact.phone_label].as<string>());
        contact.setWebsite(config[contact.website_label].as<string>());
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
        out << YAML::Key << i.index_label << YAML::Value << index;
        out << YAML::Key << i.name_label << YAML::Value << i.getName();
        out << YAML::Key << i.group_label << YAML::Value << i.getGroup();
        out << YAML::Key << i.company_label << YAML::Value << i.getCompany();
        out << YAML::Key << i.email1_label << YAML::Value << i.getEmailPersonal();
        out << YAML::Key << i.email2_label << YAML::Value << i.getEmailWork();
        out << YAML::Key << i.phone_label << YAML::Value << i.getPhone();
        out << YAML::Key << i.website_label << YAML::Value << i.getWebsite();
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
