/*
* H2.2.functions.cpp
* Homework 2 Problem 2
* Dr. Sean Murthy; CS170@WCSU
* (c) Sean Murthy. Not for distribution in any form: not even to classmates
*
* Define function to convert a string containing a number in base 2-36 to 
* decimal. Also define related helper functions
*/


#include <string>
#include <cctype>

#include "H2.2.functions.h"

using std::string;

//provate utility functions
unsigned short detectBase(const string&);
short getDigitValue(char);

//all possible digits in any base 2-36: use a substring to permit/test digits
static const string ALL_DIGITS = "0123456789abcdefghijklmnopqrstuvwxyz";

/*
* Function: string getPermittedChars
*
* Returns a string containing digits valid in the given base
*
* Parameters:
*  unsigned short base: base of a number 0-36, except 1
*
* Treats Base 0 as Base 36. Returns empty string if base exceeds 36
*/

string getPermittedChars(unsigned short base)
{
	if (base == 0 || base == 36)
		return ALL_DIGITS; //as if Base 36
	else if (base < 36)
		return ALL_DIGITS.substr(0, base); //return appropriate subset
	else
		return "";
}


/*
* Function: string getErrorMessage
*
* Returns a string corresponding to the error code specified
*
* Parameters:
*  toDecimalError errorCode: a pre-defined error code
*
* Returns the string "Unknown error" if the error code is not recognized
*/

string getErrorMessage(toDecimalError errorCode)
{
	switch (errorCode)
	{
		case NoError: return "No error";
		case EmptyInput: return "Empty input";
		case NothingToConvert: return "Nothing to convert";
		case InvalidBase: return "Invalid base";
		case InvalidDigit: return "Invalid digit";
		case Overflow: return "Overflow";
		default: return "Unknown error";
	}
}


/*
* Function: unsigned long long toDecimal
*
* Returns the decimal equivalent of the string purportedly containing a
* number in base 2-36. Auto-detects base if base specified is 0.
*
* Parameters:
*  const string& number: string to convert
*  unsigned short* base: pointer to memory with base. updated if pointed 
*   value is 0
*  toDecimalError* errorCode: pointer to memory where error code is to be 
*   set if any occurs during conversion. Caler should use the retur value
*   and the ouput parameters only if the memory is set to NoError
*  string::size_type* pos: pointer to memory containing the number of 
*   characters processed successfully before any error. Set to a value 
*   equal to length of number if conversion succeeds
*
* When base is 0, auto-detects base embedded in number using the same
* rules C++ uses to indicate base in integral literals.
*/

unsigned long long toDecimal(const string& number, unsigned short* base, 
	toDecimalError* errorCode, string::size_type* pos)
{
	*pos = 0;

	//perform basic checks" empty input, invalid base
	if (number.empty())
	{
		*errorCode = EmptyInput;
		return 0;
	}

	if (*base == 1 || *base > 36)
	{
		*errorCode = InvalidBase;
		return 0;
	}
	
	//auto-detect base and determine the starting point of the actual 
	//number to convert 
	string::size_type length{number.length()};
	string::size_type firstDigitPosition{0};
	if (*base == 0)
	{
		*base = detectBase(number);
		if (*base == 2 || *base == 16)
			firstDigitPosition = 2;
		else if (*base == 8)
			firstDigitPosition = 1;

		if (firstDigitPosition >= length)
		{
			//let *pos stay 0 because technically no digits are yet processed
			//if *pos is set to length, caller might mistake conversion succeeded
			*errorCode = NothingToConvert;
			return 0;
		}
	}

	//prepare to convert
	*errorCode = NoError;
	unsigned long long decimal{0};
	unsigned long long placeValue{1};
	string::size_type index{length - 1};

	//proceed with conversion: scan and convert each digit, detect if an
	//invalid digit is seen
	while (index >= firstDigitPosition && index != string::npos)
	{
		short digitValue = getDigitValue(number[index]);
		if (digitValue < 0 || digitValue >= *base)
		{
			*errorCode = InvalidDigit;
			break;
		}
		else
			decimal += digitValue * placeValue;

		placeValue *= *base;
		index--;
	}

	//update position to length of number only if conversion succeeded
	//otherwise leave it pointing to error location
	*pos = (*errorCode == NoError ? length : index);
	return decimal;
}


/*
* Function: unsigned short detectBase
*
* Returns the base of the number as indicated by the number. Uses C++
* rules to specify base in integral literals
*
* Parameters:
*  const string& number: string to convert
*
* Does not test if string is valid in the base detected: not the purpose
*/

unsigned short detectBase(const string& number)
{
	if (number.front() == '0')
	{
		if (number.length() == 1)
			return 10;

		char secondChar = number[1];
		if (secondChar == 'b' || secondChar == 'B')
			return 2;
		else if (secondChar == 'x' || secondChar == 'X')
			return 16;
		else
			return 8;
	}
	else
		return 10;
}


/*
* Function: short getDigitValue
*
* Returns the decimal value of a digit, independent of any base
*
* Parameters:
*  char c: the "digit" whose value is to be determined
*
* Assumes base is some value 2-36. Returns -1 if the specified character is not 
( possible in base 2-36.
*/

short getDigitValue(char c)
{
	//slower but safer implementation
	string::size_type pos = ALL_DIGITS.find(static_cast<char>(std::tolower(c)));
	if (pos == string::npos)
		return -1;
	else
		return static_cast<short>(pos);

	//not as safe, but faster
	/*
	if (c < '0')
		return -1;
	else if (c <= '9')
		return c - '0';
	else if (c < 'a')
		return -1;
	else if (c <= 'z')
		return c - 'a' + 10;
	else
		return -1;
	*/
}