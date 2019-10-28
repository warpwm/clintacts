#pragma once
#include "../sgl/crypt.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>
#include "../../thrd/yaml-cpp/include/yaml-cpp/yaml.h"

class contact {
private:
    std::pair< std::string, int > index = std::make_pair( "Index", 0 );
    std::pair< std::string, std::string > name = std::make_pair( "Name", "(none)" );
    std::pair< std::string, std::string > group = std::make_pair( "Group", "(none)" );
    std::pair< std::string, std::string > company = std::make_pair( "Company", "(none)" );
    std::pair< std::string, std::string > title = std::make_pair( "Title", "(none)" );
    std::pair< std::string, std::string > email = std::make_pair( "Email", "(none)" );
    std::pair< std::string, std::string > email2 = std::make_pair( "Email_2", "(none)" );
    std::pair< std::string, std::string > phone = std::make_pair( "Phone", "(none)" );
    std::pair< std::string, std::string > phone2 = std::make_pair( "Phone_2", "(none)" );
    std::pair< std::string, std::string > address = std::make_pair( "Address", "(none)" );
    std::pair< std::string, std::string > website = std::make_pair( "Website", "(none)" );
    std::pair< std::string, std::string > social = std::make_pair( "Social", "(none)" );

public:
    void setIndex( int value );
    int getIndex() { return index.second; }
    std::string getIndexLabel() { return index.first; }
    void setGroup( std::string value );
    std::string getGroup() { return group.second; }
    std::string getGroupLabel() { return group.first; }
    void setName( std::string value );
    std::string getName() { return name.second; }
    std::string getNameLabel() { return name.first; }
    void setTitle( std::string value );
    std::string getTitle() { return title.second; }
    std::string getTitleLabel() { return title.first; }
    void setCompany( std::string value );
    std::string getCompany() { return company.second; }
    std::string getCompanyLabel() { return company.first; }
    void setEmail( std::string value );
    std::string getEmail() { return email.second; }
    std::string getEmailLabel() { return email.first; }
    void setEmail_2( std::string value );
    std::string getEmail_2() { return email2.second; }
    std::string getEmail_2Label() { return email2.first; }
    void setPhone( std::string value );
    std::string getPhone() { return phone.second; }
    std::string getPhoneLabel() { return phone.first; }
    void setPhone_2( std::string value );
    std::string getPhone_2() { return phone2.second; }
    std::string getPhone_2Label() { return phone2.first; }
    void setAddress( std::string value );
    std::string getAddress() { return address.second; }
    std::string getAddressLabel() { return address.first; }
    void setWebsite( std::string value );
    std::string getWebsite() { return website.second; }
    std::string getWebsiteLabel() { return website.first; }
    void setSocial( std::string value );
    std::string getSocial() { return social.second; }
    std::string getSocialLabel() { return social.first; }

    void printContact();
    void vCard( std::string dirpath );
    void newContact();
};

class Contacts {
private:
    std::vector< contact > contactList;
    static int number;

public:
    bool encryption = false;
    contact newContact();
    void addContact( contact c );
    void editContact( contact c );
    void removeContact( contact c );
    Contacts searchContact( std::string phrse );
    contact getContact( std::string phrse );
    contact getContact( int index );
    void listContacts();
    void printContacts();
    std::vector< contact > loadContacts( std::string filePath );
    void saveContacts( std::string filePath );
    int numerate();
    int size() { return contactList.size(); };
    bool isValidContact( contact c );
};
