#include "contacts.h"

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
            cout << errorMsg;
        }
    }
}

contact::contact(){
    // cout << "\x1B[2J\x1B[H";
    cout << "Enter details for the new contact:" << endl;
    name = userInput("Name: ", "Invalid format. You can only use characters.\n", "[a-zA-Z ]+");
    address = userInput("Address: ", "Invalid format. You can only use characters and digits.\n", ".+");
    email_personal = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-u0-9]+@[a-z.]+");
    email_work = userInput("Email: ", "Invalid format. Email adresses must contain '@' and can only contain characters, periods and underscores.\n", "[._a-z0-9]+@[a-z.]+");
    mobile = userInput("Phone: ", "Invalid format. The format should be: 'xxxyyxxyyy'\n", "[0-9]{7,10}");
    birthday = userInput("Birthday: ", "Invalid format. The format should be: 'yyyymmdd'\n", "[0-9]{8}");
    website = userInput("Website: ", "Invalid format. Can't use newline.\n", "https?://[-._a-z0-9]+.[a-z]+");
    misc = userInput("Miscellaneous: ", "Invalid format. Can't use newline.\n", ".+");
    cout << "Contact has been created!" << endl;
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
