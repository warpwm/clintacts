#include "contacts.h"

std::string checkString(std::string input, std::string exp, std::string msg) {
    std::smatch match;
    std::regex reg(exp);
    while(true) {
        if (regex_match(input, match, reg)) {
            return input;
        } else {
            if (input.empty()) {
                return "(none)";
            } else {
                return "(error)";
            }
        }
    }
}

void contact::setIndex(int value) { index.second=value; }
void contact::setGroup(std::string value){ group.second=checkString(value, ".+", "Invalid format."); }
void contact::setName(std::string value){ name.second=checkString(value, "[a-zA-Z ]+", "Invalid format. You can only use characters."); }
void contact::setCompany(std::string value){ company.second=checkString(value, ".+", "Invalid format."); }
void contact::setEmail(std::string value){ email.second=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'");}
void contact::setEmail_2(std::string value){ email2.second=checkString(value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'"); }
void contact::setPhone(std::string value){ phone.second=checkString(value, "[0-9]{7,16}", "Invalid format. The format should be: 'xxxyyxxyyy'"); }
void contact::setWebsite(std::string value){ website.second=checkString(value, "https?://[-._a-z0-9]+.[a-z]+", "Invalid format. Use <https://www.website.com> format"); }
void contact::setSocial(std::string value){ social.second=checkString(value, ".+", "Invalid format."); }

void contact::newContact(){
    std::cout << "\x1B[2J\x1B[H";
    std::string value;
    std::cout << "Enter details for the new contact:" << std::endl;
    index.second=0;
    std::cout << name.first << ": "; getline(std::cin, value); setName(value);
    std::cout << group.first << ": "; getline(std::cin, value); setGroup(value);
    std::cout << company.first << ": "; getline(std::cin, value); setCompany(value);
    std::cout << email.first  << ": "; getline(std::cin, value); setEmail(value);
    std::cout << email2.first << ": "; getline(std::cin, value); setEmail_2(value);
    std::cout << phone.first << ": "; getline(std::cin, value); setPhone(value);
    std::cout << website.first << ": "; getline(std::cin, value); setWebsite(value);
    std::cout << social.first << ": "; getline(std::cin, value); setSocial(value);
    std::cout << "Contact has been created!" << std::endl;
}

void contact::printContact() {
    std::cout << index.first << ": \t\t" << index.second << std::endl;
    std::cout << name.first << ": \t\t" << name.second << std::endl;
    std::cout << group.first << ": \t\t" << group.second << std::endl;
    std::cout << company.first << ": \t" << company.second << std::endl;
    std::cout << email.first << ": \t\t" << email.second << std::endl;
    std::cout << email2.first << ": \t" << email2.second << std::endl;
    std::cout << phone.first << ": \t\t" << phone.second << std::endl;
    std::cout << website.first << ": \t" << website.second << std::endl;
    std::cout << social.first << ": \t" << social.second << std::endl;
}

int Contacts::numerate(){
    int index = 1;
    for (auto& i : contactList) {
        i.setIndex(index);
        index++;
    }
    return index;
}

contact Contacts::newContact(){
    contact newContact;
    newContact.newContact();
    contactList.push_back(newContact);
    numerate();
    return newContact;
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
    // std::cout << "\x1B[2J\x1B[H";
    for (auto c : contactList) {
        std::cout << c.getIndex() << ".  ";
        std::cout << FOLDRED(c.getName()) << std::endl;
    }
}

void Contacts::printContacts(){
    if (contactList.size() < 1) { return; }
    for (auto i : contactList) {
        std::cout << "\n----------------------------------------------------------\n" << std::endl;
        i.printContact();
    }
    std::cout << "\n----------------------------------------------------------\n" << std::endl;
}

std::vector<contact> Contacts::loadContacts(std::string filePath){
    cryptor::decryptFile(filePath);
    auto config = YAML::LoadAllFromFile(filePath);
    int index = 1;
    for (auto config : config) {
        contact contact;
        contact.setIndex(index);
        contact.setName(config[contact.getNameLabel()].as<std::string>());
        contact.setGroup(config[contact.getGroupLabel()].as<std::string>());
        contact.setCompany(config[contact.getCompanyLabel()].as<std::string>());
        contact.setEmail(config[contact.getEmailLabel()].as<std::string>());
        contact.setEmail_2(config[contact.getEmail_2Label()].as<std::string>());
        contact.setPhone(config[contact.getPhoneLabel()].as<std::string>());
        contact.setWebsite(config[contact.getWebsiteLabel()].as<std::string>());
        contactList.push_back(contact);
        index++;
    }
    if (encryption){
        cryptor::encryptFile(filePath);
    }
    return contactList;
}

void Contacts::saveContacts(std::string filePath){
    YAML::Emitter out;
    int index = 1;
    for (auto i : contactList) {
        out << YAML::BeginMap;
        out << YAML::Key << i.getIndexLabel() << YAML::Value << index;
        out << YAML::Key << i.getNameLabel() << YAML::Value << i.getName();
        out << YAML::Key << i.getGroupLabel() << YAML::Value << i.getGroup();
        out << YAML::Key << i.getCompanyLabel() << YAML::Value << i.getCompany();
        out << YAML::Key << i.getEmailLabel() << YAML::Value << i.getEmail();
        out << YAML::Key << i.getEmail_2Label() << YAML::Value << i.getEmail_2();
        out << YAML::Key << i.getPhoneLabel() << YAML::Value << i.getPhone();
        out << YAML::Key << i.getWebsiteLabel() << YAML::Value << i.getWebsite();
        out << YAML::EndMap;
        std::ofstream fout(filePath);
        fout << out.c_str();
        index++;
    }
    if (encryption){
        cryptor::encryptFile(filePath);
    }
}

Contacts Contacts::searchContact(std::string phrse){
    Contacts matches;
    std::smatch match;
    std::string tmp;
    for (auto i : contactList) {
        tmp = i.getName();
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        transform(phrse.begin(), phrse.end(), phrse.begin(), ::tolower);
        if(regex_search(tmp, match, std::regex(phrse))) {
            matches.addContact(i);
        }
    }
    return matches;
}

contact Contacts::getContact(std::string phrse){
    contact contact;
    std::smatch match;
    std::string tmp;
    for (auto i : contactList) {
        tmp = i.getName();
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        transform(phrse.begin(), phrse.end(), phrse.begin(), ::tolower);
        if(regex_search(tmp, match, std::regex(phrse))) {
            return i;
        }
    }
    return contact;
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
