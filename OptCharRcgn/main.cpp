/*
Project:	Optical Character Recognition 
Author:		Masud Karim
Date:		14-Aug-2019
**********************PROBLEM STATEMENT**********************
You work for a bank, which has recently purchased an ingenious
machine to assist in reading letters and faxes sent in by 
branch offices. The machine scans the paper documents, and 
produces a file with a number of entries which each look like 
this:
  _  _     _  _  _  _  _ 
| _| _||_||_ |_   ||_||_|
||_  _|  | _||_|  ||_| _|

Each entry is 4 lines long, and each line has 27 characters. 
The first 3 lines of each entry contain an account number 
written using pipes and underscores, and the fourth line is 
blank. Each account number should have 9 digits, all of which 
should be in the range 0-9. A normal file contains around 500 
entries.

Your task is to write a C++ program that can take this file and
parse it into actual account numbers.

**************************ASSUMPTIONS*************************
1) Pipes can only be the first or third character in one row of
the digital display.  Underscores can only be the middle
character.  No pipes on top row.
2) 27 characters includes trailing spaces (i.e. input from text
file is not trimmed).  Only first 27 characters will be read
from each line.  File entries are delimited by carriage return
or newline.  One entry per line, and no headers.
3) "Unfurled" (3 rows of 3 chars, left to right, then top to
bottom) representation of 0 is " _ | ||_|".  Each number has
only one "unfurled" representation (i.e. 7 and 9 could have had 
different forms than what is presented in the problem statement).
4) No mention is made of how account numbers should be stored
or outputted. All account numbers to be stored in a vector of 
strings.

**************************************************************
*/

#include <iostream>
#include <fstream>
#include "rawSsd.h"
#include <string>
#include <vector>

using namespace std;

#define MAX_DIGITS 9            // All account numbers have 9 digits
#define DIGIT_WIDTH 3           // Each digit requires 3 chars per row

vector<string> DigitsList::Digits;  // ALL DECODED DATA STORED IN THIS OBJECT

int main() {
    //if (argc < 0)
    //{
    //    cerr << "Command line must have filename argument.  Exiting program..." << endl;
    //    exit(EXIT_FAILURE);
    //}
    string filepath = "Data\\dataset1.txt";
    //cout << "Please enter filepath: " << endl;
    //cin >> filepath;        // Otherwise set to argv[0] if running executable.
    RawSsd rawVals;           // three lines of raw data read from input file
    DigitsList result;        // result stored in "Digits" vector
    ifstream fin;
    fin.open(filepath);
    if (fin.fail())
    {
        cerr << "Error opening input file.\n";
        exit(1);    // Terminate program if file cannot be opened.
    }
    else
    {
        cout << "The following account numbers have been decoded: " << endl;
        int i = 0;
        while (!fin.eof())
        {
            // Read three lines together.
            getline(fin, rawVals.line1);
            getline(fin, rawVals.line2);
            getline(fin, rawVals.line3);
            // Enumerate on console for debugging and traceability.
            cout << i + 1 << ": ";
            // Process seven-segment like display into string of numbers & load to vector.
            DigitsList(rawVals, MAX_DIGITS, DIGIT_WIDTH);
            // Output account numbers from vector<string> object.
            cout << result.Digits.at(i) << endl;
            i++;
            // Account numbers are separated from one another by a blank line.
            fin.ignore(256, '\n');
        }
    }
    fin.close();
}