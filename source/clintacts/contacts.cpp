#include <clintacts/contacts.h>
using namespace ftxui;

void Contacts::testNew() {
    contact newContact;
    newContact.newContact2();
}

int Contacts::numerate() {
    int index = 1;
    for( auto& i : contactList ) {
        i.setIndex( index );
        index++;
    }
    return index;
}

contact Contacts::newContact() {
    contact newContact;
    newContact.newContact();
    contactList.push_back( newContact );
    numerate();
    return newContact;
}

void Contacts::addContact( contact c ) {
    contactList.push_back( c );
}

void Contacts::removeContact( contact c ) {
    for( int i = 0; i < contactList.size(); ++i ) {
        if( contactList[i].getIndex() == c.getIndex() && contactList[i].getName() == c.getName() ) {
            contactList.erase( contactList.begin() + i );
        }
    }
    numerate();
}

void Contacts::editContact( contact c ) {
    contact contact;
    contact.newContact();
    for( int i = 0; i < contactList.size(); ++i ) {
        if( contactList[i].getIndex() == c.getIndex() && contactList[i].getName() == c.getName() ) {
            contactList[i] = contact;
        }
    }
    numerate();
}

void Contacts::listContacts() {
    // std::cout << "\x1B[2J\x1B[H";
    for( auto c : contactList ) {
        std::cout << c.getIndex() << ".  ";
        std::cout << FOLDRED( c.getName() ) << std::endl;
    }
}

void Contacts::printContacts() {
    if( contactList.size() < 1 ) { return; }
    for( auto i : contactList ) {
        std::cout << "\n----------------------------------------------------------\n"
                  << std::endl;
        i.printContact();
    }
    std::cout << "\n----------------------------------------------------------\n"
              << std::endl;
}

std::vector< contact > Contacts::loadContacts( std::string filePath ) {
    cryptor::decryptFile( filePath );
    auto config = YAML::LoadAllFromFile( filePath );
    int index = 1;
    for( auto config : config ) {
        contact contact;
        contact.setIndex( index );
        if( config[contact.getNameLabel()] ) { contact.setName( config[contact.getNameLabel()].as< std::string >() ); }
        if( config[contact.getGroupLabel()] ) { contact.setGroup( config[contact.getGroupLabel()].as< std::string >() ); }
        if( config[contact.getCompanyLabel()] ) { contact.setCompany( config[contact.getCompanyLabel()].as< std::string >() ); }
        if( config[contact.getTitleLabel()] ) { contact.setTitle( config[contact.getTitleLabel()].as< std::string >() ); }
        if( config[contact.getEmailLabel()] ) { contact.setEmail( config[contact.getEmailLabel()].as< std::string >() ); }
        if( config[contact.getEmail_2Label()] ) { contact.setEmail_2( config[contact.getEmail_2Label()].as< std::string >() ); }
        if( config[contact.getPhoneLabel()] ) { contact.setPhone( config[contact.getPhoneLabel()].as< std::string >() ); }
        if( config[contact.getPhone_2Label()] ) { contact.setPhone_2( config[contact.getPhone_2Label()].as< std::string >() ); }
        if( config[contact.getAddressLabel()] ) { contact.setAddress( config[contact.getAddressLabel()].as< std::string >() ); }
        if( config[contact.getWebsiteLabel()] ) { contact.setWebsite( config[contact.getWebsiteLabel()].as< std::string >() ); }
        contactList.push_back( contact );
        index++;
    }
    if( encryption ) {
        cryptor::encryptFile( filePath );
    }
    return contactList;
}

void Contacts::saveContacts( std::string filePath ) {
    YAML::Emitter out;
    int index = 1;
    for( auto i : contactList ) {
        out << YAML::BeginMap;
        out << YAML::Key << i.getIndexLabel() << YAML::Value << index;
        out << YAML::Key << i.getNameLabel() << YAML::Value << i.getName();
        out << YAML::Key << i.getGroupLabel() << YAML::Value << i.getGroup();
        out << YAML::Key << i.getCompanyLabel() << YAML::Value << i.getCompany();
        out << YAML::Key << i.getTitleLabel() << YAML::Value << i.getTitle();
        out << YAML::Key << i.getEmailLabel() << YAML::Value << i.getEmail();
        out << YAML::Key << i.getEmail_2Label() << YAML::Value << i.getEmail_2();
        out << YAML::Key << i.getPhoneLabel() << YAML::Value << i.getPhone();
        out << YAML::Key << i.getPhone_2Label() << YAML::Value << i.getPhone_2();
        out << YAML::Key << i.getAddressLabel() << YAML::Value << i.getAddress();
        out << YAML::Key << i.getWebsiteLabel() << YAML::Value << i.getWebsite();
        out << YAML::EndMap;
        std::ofstream fout( filePath );
        fout << out.c_str();
        index++;
    }
    if( encryption ) {
        cryptor::encryptFile( filePath );
    }
}

Contacts Contacts::searchContact( std::string phrse ) {
    Contacts matches;
    std::smatch match;
    std::string tmp;
    for( auto i : contactList ) {
        tmp = i.getName();
        transform( tmp.begin(), tmp.end(), tmp.begin(), ::tolower );
        transform( phrse.begin(), phrse.end(), phrse.begin(), ::tolower );
        if( regex_search( tmp, match, std::regex( phrse ) ) ) {
            matches.addContact( i );
        }
    }
    return matches;
}

contact Contacts::getContact( std::string phrse ) {
    contact contact;
    std::smatch match;
    std::string tmp;
    for( auto i : contactList ) {
        tmp = i.getName();
        transform( tmp.begin(), tmp.end(), tmp.begin(), ::tolower );
        transform( phrse.begin(), phrse.end(), phrse.begin(), ::tolower );
        if( regex_search( tmp, match, std::regex( phrse ) ) ) {
            return i;
        }
    }
    return contact;
}

contact Contacts::getContact( int index ) {
    contact contact;
    if( index <= contactList.size() || index > 0 ) {
        return contactList[index - 1];
    }
    return contact;
}

bool Contacts::isValidContact( contact c ) {
    if( c.getName().empty() || c.getIndex() == 0 ) {
        return false;
    }
    return true;
}
