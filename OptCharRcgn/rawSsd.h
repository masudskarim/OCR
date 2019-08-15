#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct RawSsd {
    string line1, line2, line3;     // three lines of input data for complete digits
};

class DigitsList {
public:
    static vector<string> Digits;       // result (i.e. all decoded account numbers)
    DigitsList();                       // default constructor
    DigitsList(RawSsd lines, int maxDigits, int digitWidth);    // read text and update result
};