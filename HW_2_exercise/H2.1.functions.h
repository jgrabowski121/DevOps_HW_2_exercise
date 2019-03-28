/*
* H2.1.functions.h
* Homework 2 Problem 1
* Dr. Sean Murthy; CS170@WCSU
* (c) Sean Murthy. Not for distribution in any form: not even to classmates
*
* Declare functions to read numbers and lines of text from the console
*/

#ifndef H2_1_FUNCTIONS_H

#define H2_1_FUNCTIONS_H

#include <string>

using std::string;

//default buffer size to ignore: used for uniformity
const std::streamsize BUFFER_IGNORE_SIZE{10000U};

unsigned long long getNumber(const string&  prompt,
	unsigned long long minValue, unsigned long long maxValue,
	unsigned long long& attempts);

std::string getLine(const string& prompt, const string& permittedChars,
	bool ignoreCase,
	std::string::size_type minLength, std::string::size_type maxLength,
	unsigned long long& attempts);

#endif