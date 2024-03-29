#pragma once
#include <crypt.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <rang.hpp>
#include <regex>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "ftxui/component/container.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/string.hpp"

#define BOLDRED( x )                                              \
    rang::bg::red << rang::style::bold << x << rang::style::reset \
                  << rang::bg::reset
#define FOLDRED( x )                                              \
    rang::fg::red << rang::style::bold << x << rang::style::reset \
                  << rang::fg::reset

using namespace ftxui;

class contact : public Component {
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
    void newContact2();

    void showcontact() {
        Add( &container );
        container.Add( &input_1 );
        container.Add( &input_2 );
        container.Add( &input_3 );
    }

    Container container = Container::Vertical();
    std::function< void() > on_enter = []() {};

    Input input_1;
    Input input_2;
    Input input_3;
    std::wstring widen( const std::string& str );
    std::string narrow( const std::wstring& str );

    Element Render() override {
        return border(
            vbox(
                hbox( text( widen( name.first + "     " ) ), input_1.Render() ),
                hbox( text( widen( email.first + "    " ) ), input_2.Render() ),
                hbox( text( widen( company.first + "  " ) ), input_3.Render() ) ) );
    }
};
