#include <clintacts/contact.h>
using namespace ftxui;

std::string checkString( std::string input, std::string exp, std::string msg ) {
    std::smatch match;
    std::regex reg( exp );
    while( true ) {
        if( regex_match( input, match, reg ) ) {
            return input;
        } else {
            return "(none)";
        }
    }
}

void contact::setIndex( int value ) { index.second = value; }
void contact::setGroup( std::string value ) { group.second = checkString( value, ".+", "Invalid format." ); }
void contact::setName( std::string value ) { name.second = checkString( value, "[a-zA-Z ]+", "Invalid format. You can only use characters." ); }
void contact::setCompany( std::string value ) { company.second = checkString( value, ".+", "Invalid format." ); }
void contact::setTitle( std::string value ) { title.second = checkString( value, "[a-zA-Z ]+", "Invalid format. You can only use characters." ); }
void contact::setEmail( std::string value ) { email.second = checkString( value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'" ); }
void contact::setEmail_2( std::string value ) { email2.second = checkString( value, "[._a-z0-9]+@[a-z.]+", "Invalid format. You can only use characters, periods, underscores and '@'" ); }
void contact::setPhone( std::string value ) { phone.second = checkString( value, "[0-9]{7,16}", "Invalid format. The format should be: 'xxxyyxxyyy'" ); }
void contact::setPhone_2( std::string value ) { phone2.second = checkString( value, "[0-9]{7,16}", "Invalid format. The format should be: 'xxxyyxxyyy'" ); }
void contact::setWebsite( std::string value ) { website.second = checkString( value, "https?://[-._a-z0-9]+.[a-z]+", "Invalid format. Use <https://www.website.com> format" ); }
void contact::setAddress( std::string value ) { address.second = checkString( value, ".+", "Invalid format." ); }
void contact::setSocial( std::string value ) { social.second = checkString( value, ".+", "Invalid format." ); }

void contact::newContact() {
    std::string value;
    index.second = 0;
    std::cout << name.first << ": ";
    getline( std::cin, value );
    setName( value );
    std::cout << group.first << ": ";
    getline( std::cin, value );
    setGroup( value );
    std::cout << company.first << ": ";
    getline( std::cin, value );
    setCompany( value );
    std::cout << title.first << ": ";
    getline( std::cin, value );
    setTitle( value );
    std::cout << email.first << ": ";
    getline( std::cin, value );
    setEmail( value );
    std::cout << email2.first << ": ";
    getline( std::cin, value );
    setEmail_2( value );
    std::cout << phone.first << ": ";
    getline( std::cin, value );
    setPhone( value );
    std::cout << phone2.first << ": ";
    getline( std::cin, value );
    setPhone_2( value );
    std::cout << address.first << ": ";
    getline( std::cin, value );
    setAddress( value );
    std::cout << website.first << ": ";
    getline( std::cin, value );
    setWebsite( value );
    std::cout << social.first << ": ";
    getline( std::cin, value );
    setSocial( value );
}

std::wstring contact::widen( const std::string& str ) {
    std::wostringstream wstm;
    const std::ctype< wchar_t >& ctfacet = std::use_facet< std::ctype< wchar_t > >( wstm.getloc() );
    for( size_t i = 0; i < str.size(); ++i )
        wstm << ctfacet.widen( str[i] );
    return wstm.str();
}

std::string contact::narrow( const std::wstring& str ) {
    std::ostringstream stm;
    const std::ctype< char >& ctfacet = std::use_facet< std::ctype< char > >( stm.getloc() );
    for( size_t i = 0; i < str.size(); ++i )
        stm << ctfacet.narrow( str[i], 0 );
    return stm.str();
}

void contact::newContact2() {
    auto screen = ScreenInteractive::TerminalOutput();
    contact contact;
    contact.showcontact();
    contact.on_enter = screen.ExitLoopClosure();
    screen.Loop( &contact );
}

void contact::printContact() {
    std::cout << index.first << ": \t\t" << index.second << std::endl;
    std::cout << name.first << ": \t\t" << name.second << std::endl;
    std::cout << group.first << ": \t\t" << group.second << std::endl;
    std::cout << company.first << ": \t" << company.second << std::endl;
    std::cout << title.first << ": \t\t" << title.second << std::endl;
    std::cout << email.first << ": \t\t" << email.second << std::endl;
    std::cout << email2.first << ": \t" << email2.second << std::endl;
    std::cout << phone.first << ": \t\t" << phone.second << std::endl;
    std::cout << phone2.first << ": \t" << phone2.second << std::endl;
    std::cout << address.first << ": \t" << address.second << std::endl;
    std::cout << website.first << ": \t" << website.second << std::endl;
    std::cout << social.first << ": \t" << social.second << std::endl;
}

void contact::vCard( std::string dirpath ) {
    std::ofstream fileAddress;
    fileAddress.open( dirpath );
    fileAddress << "BEGIN:VCARD" << std::endl;
    fileAddress << "VERSION:3.0" << std::endl;
    std::istringstream ss( name.second );
    std::string name_, surname_;
    ss >> name_ >> surname_;
    fileAddress << "N:" << name_ << ";" << surname_ << ";;" << std::endl;
    fileAddress << "FN:" << name.second << std::endl;
    fileAddress << "ORG:" << company.second << std::endl;
    fileAddress << "TITLE:" << title.second << std::endl;
    fileAddress << "TEL;TYPE=home,voice;VALUE=uri:tel:" << phone.second << std::endl;
    // auto addr = utl::split(address.second, ",");
    // fileAddress << "ADR;TYPE=HOME;LABEL=\"" << address.second <<"\""<< ":;;" << addr[0] << ";" << addr[1] << ";" << addr[2] << ";" << addr[3] << ";" << addr[4] << std::endl;
    fileAddress << "EMAIL:" << email.second << std::endl;
    fileAddress << "END:VCARD" << std::endl;
    fileAddress.close();
}

