/*
* H2.1.functions.cpp
* Homework 2 Problem 1
* Dr. Sean Murthy; CS170@WCSU
* (c) Sean Murthy. Not for distribution in any form: not even to classmates
*
* Define functions to read numbers and lines of text from the console
*/

#include <iostream>
#include <string>
#include <cctype>

#include "H2.1.functions.h"

using std::cin;
using std::string;


/*
* Function: unsigned long long getNumber
*
* Reads a number from console and ensures its value is in the specified 
* range. Wraps the std stream-extraction operator.
*
* Parameters:
*  const string& prompt: prompt to the user to enter data
*  unsigned long long minValue: smallest acceptable input number
*  unsigned long long maxValue: largest acceptable input number
*  unsigned long long& attempts: #attempts before correct data is input
*
* Displays prompt, extracts a number, and checks if number is in range.
* If number is not in range, or if extraction causes a recoverable error,
* displays prompt again, extracts, and tests. Stops if user provides 
* acceptable input, user signals EOF, or stream develops an irrecoverable
* error. Updates param attempts each time extraction is attempted.
* 
* Upon return, leaves the stream state unchanged for caller to test. Caller
* should use return value only if stream state is good. STream is guaranteed
* not have a "recoverable error" state upon return.
*/

unsigned long long getNumber(const string& prompt, 
	unsigned long long minValue, unsigned long long maxValue,
	unsigned long long& attempts)
{
	unsigned long long number;

	//read until a good number is supplied
	bool invalidInput{false};
	attempts = 0;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(BUFFER_IGNORE_SIZE, '\n');
		}

		//try reading (again)
		std::cout << prompt;
		cin >> number;
		attempts++;

		if (cin.good())
			invalidInput = number < minValue || number > maxValue;

	} while ((cin.fail() && !(cin.bad() || cin.eof())) || invalidInput);

	return number;
}


/*
* Function: string getLine
*
* Reads a line of text from console and ensures it has only the acceptable
* characters and its length is in the specified range. Wraps the function
* std::getline.
*
* Parameters:
*  const string& prompt: prompt to the user to enter data
*  const string&  permittedChars: acceptable input chars; all chars accepted
*   if this string is empty
*  bool ignoreCase: flag to denote if input in any character case is OK
*  unsigned long long minLength: smallest acceptable length of input string
*  unsigned long long maxLength: largest acceptable length of input string
*  unsigned long long& attempts: #attempts before correct data is input
*
* Displays prompt, reads a line, and checks if input is "in range".
* If input is not in range, or if reading causes a recoverable error,
* displays prompt again, reads, and tests. Stops if user provides
* acceptable input, user signals EOF, or stream develops an irrecoverable
* error. Updates param attempts each time read is attempted.
*
* Upon return, leaves the stream state unchanged for caller to test. Caller
* should use return value only if stream state is good. STream is guaranteed
* not have a "recoverable error" state upon return.
*/

string getLine(const string&  prompt, const string&  permittedChars,
	bool ignoreCase, 
	std::string::size_type minLength, std::string::size_type maxLength,
	unsigned long long& attempts)
{
	//copy permittedChars as-is or the upper-case version of it to a temporary
	//string depending on ignoreCase: later just use the temporary string
	string adjustedPermittedChars;
	if (ignoreCase)
		for (char c : permittedChars)
			adjustedPermittedChars += static_cast<char>(std::toupper(c));
	else
		adjustedPermittedChars = permittedChars;

	//read until a good string is supplied
	string line;
	bool invalidInput{false};
	attempts = 0;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(BUFFER_IGNORE_SIZE, '\n');
		}

		//try reading (again)
		std::cout << prompt;
		std::getline(cin, line);
		attempts++;

		//if there are no I/O issues, test if the line contains valid data
		//must have only permitted characters and satisfy length constraints;
		//any character is permitted if permittedChars is empty
		if (cin.good())
		{
			invalidInput = false;
			if (!permittedChars.empty())
				for (char c : line)
				{
					if (ignoreCase)
						c = static_cast<char>(toupper(c));
					
					if (adjustedPermittedChars.find(c) == std::string::npos)
					{
						invalidInput = true;
						break;
					}
				}

			if (!invalidInput)
			{
				std::string::size_type length{ line.length() };
				invalidInput = length < minLength || length > maxLength;
			}
		}

	} while ((cin.fail() && !(cin.bad() || cin.eof())) || invalidInput);

	return line;
}