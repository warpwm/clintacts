#include <string>

using namespace std;

#ifndef HELPERS_H
#define HELPERS_H

bool isNumber(string& s); // Checks if string is number
string strToLower(string s); // Returns string in lowercase
string getUserInput(string label, string errorMsg, string exp); // Helps get user input, takes a label for cout, errormsg for invalid input, and exp for validation

#endif
