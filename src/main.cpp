#include <iostream>
#include <string>
#include <vector>

#include "inc/contacts.h"
#include "inc/args.hpp"

int main(int argc, char **argv) {
    // contacts.printAlt();
    // contacts.removeContact(contacts.getContact(10));
    // contacts.listContacts();
    // contacts.saveContacts(filePath);

    args::ArgumentParser parser("CONTACTS APP");

    //COMMANDS
    args::Group commands(parser, "COMMANDS (only one at time)", args::Group::Validators::AtMostOne, args::Options::None);
    args::Command add(commands, "new", "add a new contact");

    //LISTER
    args::Command list(commands, "list", "list contacts");
    args::Group lister(list, "ARGUMENTS (at most one)", args::Group::Validators::AtMostOne, args::Options::Required);
    args::Flag l_detail(lister, "detail", "show detailed all", {'d', "detailed"});
    args::ValueFlag<int> l_index(lister, "index", "show contact", {'i'});

    //SEARCHER
    args::Command search(commands, "search", "search for a contact");
    args::Group searcher(search, "ARGUMENTS", args::Group::Validators::AtLeastOne, args::Options::Required);
    args::Positional<std::string> s_name(searcher, "expression", "match expresion for contact");

    //PIPER
    args::Command out(commands, "out", "pipe to output");
    args::PositionalList<std::string> p_exp(out, "expression", "match expresion for contact");
    args::Group piper(out, "ARGUMENTS (at least one)", args::Group::Validators::AtLeastOne, args::Options::Required);
    args::Flag p_name(piper, "name", "pipe put contact name", {'n', "name"});
    args::Flag p_email(piper, "email", "pipe put contact email", {'e', "email"});
    args::Flag p_work(piper, "wormail", "pipe put contact workmail", {'w', "work"});

    //EDITOR
    args::Command edit(commands, "edit", "edit contacts");
    args::Group editor(edit, "ARGUMENTS (only one at time)", args::Group::Validators::Xor, args::Options::Required);
    args::ValueFlag<int> e_index(editor, "index", "edit contact by index", {'i',"index"});
    args::ValueFlag<std::string> e_name(editor, "name", "edit contact by name", {'n',"name"});

    //REMOVER
    args::Command remove(commands, "remove", "remove contacts");
    args::Group remover(remove, "ARGUMENTS", args::Group::Validators::Xor, args::Options::Required);
    args::ValueFlag<int> r_index(remover, "index", "delete contact by index", {'i'});
    args::ValueFlag<std::string> r_name(remover, "name", "delete contact by name", {"n"});

    //FLAGS
    args::Group flags(parser, "FLAGS (none, multi or all)", args::Group::Validators::DontCare, args::Options::Global);
    args::ValueFlag<std::string> getdir(flags, "path", "contacts file path", {"database"});
    args::Flag crypt(flags, "encrypt", "encrypt the database", {'e', "crypt"});

    //GLOBALHELP
    args::Group global(parser, "GLOBAL (only one at time)", args::Group::Validators::AtMostOne, args::Options::Global);
    args::HelpFlag help(global, "help", "show CLINTACTS help", {'h', "help"});
    args::Flag version(global, "version", "show CLINTACTS version", {'v', "version"});
    args::Flag about(global, "about", "show CLINTACTS about", {'a', 'i', "about", "info"});

    try {
        parser.ParseCLI(argc, argv);

        Contacts contacts;
        contacts.encryption = crypt;
        std::string filePath = getdir ? args::get(getdir) : "/home/bresilla/contacts";
        if (!std::ifstream(filePath)){
            std::cout << BOLDRED("\nNOT A VALID FILEPATH\n") << std::endl;
            return 1;
        }
        contacts.loadContacts(filePath);

        if (list) {
            if (l_detail){
                contacts.printContacts();
            } else if (l_index) {
                if (args::get(l_index) <= 0 || args::get(l_index)>contacts.size()) {
                    std::cout << BOLDRED("\nNOT A VALID INDEX\n") << std::endl;
                } else {
                    std::cout << std::endl;
                    contacts.getContact(args::get(l_index)).printContact();
                    std::cout << std::endl;
                }
            } else {
                contacts.listContacts();
            }
        } else if (search) {
            if (contacts.getContact(args::get(s_name)).getIndex() <= 0){
                    std::cout << BOLDRED("\nNO CONTACTS FOUND\n") << std::endl;
            } else {
                std::cout << std::endl;
                contacts.getContact(args::get(s_name)).printContact();
                std::cout << std::endl;
            }
        } else if (out) {
            for (const auto expression: args::get(p_exp)){
                auto tempCont  = contacts.getContact(expression);
                if (p_name) { std::cout << tempCont.getName() << "\t\t"; }
                if (p_email) { std::cout << tempCont.getEmail() << "\t\t"; }
                if (p_work) { std::cout << tempCont.getEmail_2() << "\t\t"; }
                std::cout << std::endl;
            }
        } else if (edit) {
            contacts.saveContacts(filePath);
        } else if (add) {
            auto tempCon = contacts.newContact();
            tempCon.printContact();
            contacts.saveContacts(filePath);
        } else if (remove) {
            if (r_index) {
                if (args::get(l_index) <= 0 || args::get(l_index)>contacts.size()) {
                    std::cout << BOLDRED("\nNOT A VALID INDEX\n") << std::endl;
                } else {
                    auto name = contacts.getContact(args::get(r_index)).getName();
                    std::cout << "Deleting: " << name << std::endl;
                    contacts.removeContact(contacts.getContact(args::get(r_index)));
                    contacts.saveContacts(filePath);
                }
            } else if (r_name) {
                if (contacts.getContact(args::get(r_name)).getIndex() <= 0){
                    std::cout << BOLDRED("\nNO CONTACTS FOUND\n") << std::endl;
                } else {
                    auto name = contacts.getContact(args::get(r_name)).getName();
                    std::cout << " \n Contact " << BOLDRED(name) << " deleted.\n"<<std::endl;
                    contacts.removeContact(contacts.getContact(args::get(r_name)));
                    contacts.saveContacts(filePath);
                }
            }
        } else {
            if (help){
                std::cout << parser;
            } else if (version) {
                std::cout << "Verion: 0.0.1" << std::endl;
            } else {
                std::cout << "PLEASE WRITE A COMMAND OR A FLAG/ARGUENT\nUSE --help or -h TO SHOW USAGE HELP" << std::endl;
            }
        }
    }
    catch (args::Help) {
        std::cout << parser;
    }
    catch (args::Error& e) {
        std::cerr << e.what() << std::endl << parser;
        return 1;
    }
    return 0;
}
