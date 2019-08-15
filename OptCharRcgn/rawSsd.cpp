#include <iterator>
#include "rawSsd.h"
#include <regex>

using namespace std;

/* Each digit read as single string from the first row,
left to right, down to the third row (9 chars total)*/
string readOneDigit(string unfurledDigit)
{
    if (unfurledDigit.compare(" _ | ||_|") == 0){
        return "0";
    }
    else if (unfurledDigit.compare("     |  |") == 0){
        return "1";
    }
    else if (unfurledDigit.compare(" _  _||_ ") == 0){
        return "2";
    }
    else if (unfurledDigit.compare(" _  _| _|") == 0){
        return "3";
    }
    else if (unfurledDigit.compare("   |_|  |") == 0){
        return "4";
    }
    else if (unfurledDigit.compare(" _ |_  _|") == 0){
        return "5";
    }
    else if (unfurledDigit.compare(" _ |_ |_|") == 0){
        return "6";
    }
    else if (unfurledDigit.compare(" _   |  |") == 0){
        return "7";
    }
    else if (unfurledDigit.compare(" _ |_||_|") == 0){
        return "8";
    }
    else if (unfurledDigit.compare(" _ |_| _|") == 0){
        return "9";
    }
    else{
        regex expr1("[^\\|_\\s]");      // any character that is not '|', '_', or ' '
        smatch m;
        regex expr2("( _ )|(\\|_\\|)|(  \\|)|(\\|  )|( _\\|)|(\\|_ )|(\\| \\|)|[^\\S\\t\\n\\r]{3}");
            // digit building block patterns, per assumptions in main.cpp
        if (regex_search(unfurledDigit, m, expr1))
        {
            cerr << "Invalid character (not ' ', '_', or '|') found.  Exiting...\n";
            exit(EXIT_FAILURE);
        }
        ptrdiff_t numMatches(distance(
            sregex_iterator(unfurledDigit.begin(), unfurledDigit.end(), expr2),
            sregex_iterator()));
        if (numMatches != 3) {
            cerr << "Digit building block(s) incorrect or missing.  Exiting...\n";
            exit(EXIT_FAILURE);
        }
        cerr << "Digit building block(s) do not resemble any digit.  Exiting...\n";
            // If the '|', '_', and ' ' patterns are correct, the combinations may not be.
        exit(EXIT_FAILURE);
    }
}

DigitsList::DigitsList(){
    // Do nothing.
}

/* Read "unfurled" digit and concatenate till length of maxDigits.
 Then push this account number to vector containing all decoded account numbers*/
DigitsList::DigitsList(RawSsd lines, int maxDigits, int digitWidth){
    string accountNum = "";
    for (int i = 0; i < maxDigits; i++) // Only extract first 9 digits; ignore what comes after.
    {
        accountNum += readOneDigit(lines.line1.substr(digitWidth*i, 3) +
            lines.line2.substr(digitWidth*i, 3) + lines.line3.substr(digitWidth*i, 3));
    }
    this->Digits.push_back(accountNum);
}