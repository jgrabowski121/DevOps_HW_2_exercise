/*
* H2.2.functions.h
* Homework 2 Problem 2
* Dr. Sean Murthy; CS170@WCSU
* (c) Sean Murthy. Not for distribution in any form: not even to classmates
*
* Declare functions to read numbers and lines of text from the console
*/

#include <string>

using std::string;

enum toDecimalError
{
	NoError, EmptyInput, NothingToConvert, InvalidBase, InvalidDigit, Overflow
};


//function declarations
string getPermittedChars(unsigned short base);
string getErrorMessage(toDecimalError);
unsigned long long toDecimal(const string& number, unsigned short*, toDecimalError*, string::size_type*);