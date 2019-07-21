#include "contacts.h"

string getUserInput(string label, string errorMsg, string exp) {
    string input;
    smatch base_match;
    regex base_regex(exp);
    while(true) {
        cout << label;
        getline(cin, input);
        if (regex_match(input, base_match, base_regex )) {
            return input;
        } else {
            cout << errorMsg;
        }
    }
}

contact::contact(){
    cout << "\x1B[2J\x1B[H";
    cout << "Enter details for the new contact:" << endl;
    name = getUserInput("Name: ", "Invalid format. You can only use characters.\n", "[a-öA-Ö ]+");
    address = getUserInput("Address: ", "Invalid format. You can only use characters and digits.\n", "[a-öA-Ö0-9 ]+");
    email_personal = getUserInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-ö0-9]+@[a-ö.]+");
    email_work = getUserInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-ö0-9]+@[a-ö.]+");
    mobile = getUserInput("Phone: ", "Invalid format. The format should be: 'xxxyyxxyyy'\n", "[0-9]{10}");
    birthday = getUserInput("Birthday: ", "Invalid format. The format should be: 'yyyymmdd'\n", "[0-9]{8}");
    website = getUserInput("Miscellaneous: ", "Invalid format. Can't use newline.\n", ".+");
    misc = getUserInput("Miscellaneous: ", "Invalid format. Can't use newline.\n", ".+");
    cout << "Contact has been added!" << endl;
}

void contact::printContact() {
    std::cout << name << std::endl;
    std::cout << address << std::endl;
    std::cout << email_personal << std::endl;
    std::cout << email_work << std::endl;
    std::cout << mobile << std::endl;
    std::cout << birthday << std::endl;
    std::cout << website << std::endl;
    std::cout << misc << std::endl;
}
