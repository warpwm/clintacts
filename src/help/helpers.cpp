#include <string>
#include <regex>
#include <iostream>

using namespace std;

bool isNumber(string& s); // Checks if string is number
string strToLower(string s); // Returns string in lowercase
string getUserInput(string label, string errorMsg, string exp); // Helps get user input, takes a label for cout, errormsg for invalid input, and exp for validation

// Checks if a string is a number
bool isNumber(string& s) {
	string::const_iterator it = s.begin(); // Create iterator for string

	while (it != s.end() && isdigit(*it)) ++it; // Iterate through string

	return !s.empty() && it == s.end();
}
// Turns a string into lowercase
string strToLower(string s) {
	for (int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);

	return s;
}
// Gets user input
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
