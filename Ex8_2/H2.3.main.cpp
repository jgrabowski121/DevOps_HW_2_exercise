/*
* H2.1.main.cpp
* Homework 2, Problem 2
* Dr. Sean Murthy; CS170@WCSU
*
* Justin John Grabowski
* CS-298-01
* Due March 28th 2019
*
* Driver to test function toDecimal
*/

#include <iostream>
#include <string>
#include <map>

#include "H2.1.functions.h"
#include "H2.2.functions.h"

using std::cout;
using std::cin;
using std::string;

//void convertToDecimalAndOutput(const string& number, unsigned short base);
typedef std::tuple<unsigned long long, short, toDecimalError, std::string::size_type> output_value;

//Define the input_key for a map to hold tests
typedef std::tuple<const string, unsigned short, toDecimalError> input_key;

void test_getPermittedChars();
void test_toDecimal();
void checkResultAndOutput(unsigned testNumber, std::string expectedP, std::string actualP);

static int testsFailed{ 0 };

int main()
{
	test_getPermittedChars();
	cout << "\n\nTesting toDecimal..\n\n";
	test_toDecimal();
	return testsFailed;
}

void test_getPermittedChars()
{
	unsigned testNumber{ 1 };//counter for tests

	std::map<unsigned, std::string> tests;

	//check valid inputs
	tests.insert(std::pair<int, std::string>(0, "0123456789abcdefghijklmnopqrstuvwxyz"));
	tests.insert(std::pair<int, std::string>(36, "0123456789abcdefghijklmnopqrstuvwxyz"));
	tests.insert(std::pair<int, std::string>(1, "0"));
	tests.insert(std::pair<int, std::string>(35, "0123456789abcdefghijklmnopqrstuvwxy"));
	tests.insert(std::pair<int, std::string>(2, "01"));
	tests.insert(std::pair<int, std::string>(8, "01234567"));
	tests.insert(std::pair<int, std::string>(10, "0123456789"));
	tests.insert(std::pair<int, std::string>(16, "0123456789abcdef"));
	tests.insert(std::pair<int, std::string>(3, "012"));
	tests.insert(std::pair<int, std::string>(9, "012345678"));
	tests.insert(std::pair<int, std::string>(11, "0123456789a"));
	tests.insert(std::pair<int, std::string>(15, "0123456789abcde"));

	//check invalid base: should return an empty string
	tests.insert(std::pair<int, std::string>(37, ""));

	for (auto[first, second] : tests)
	{
		checkResultAndOutput(testNumber++, second, getPermittedChars(first));
	}
}


void checkResultAndOutput(unsigned testNumber, std::string expectedP, std::string actualP)
{
	std::cout << "Test " << testNumber << ": ";
	if (actualP == expectedP)
		std::cout << "Pass\n";
	else
	{
		std::cout << "Fail\n";
		testsFailed++;
	}
}


// To Decimal Signiture: unsigned long long toDecimal(const string& number,
// unsigned short*, toDecimalError*, string::size_type*);
void test_toDecimal()
{
	unsigned testNumber{ 1 }; //counter for tests
	std::map<input_key, output_value> testsMap;
	//const string inputString = "101";
	//short basePtr = 2;
	string::size_type posPtr;
	//toDecimalError errPtr = NoError;

	//test 1 data
	auto test_input = std::make_tuple("101", 2, NoError);
	auto test_expectedOutput = std::make_tuple(5, 2, NoError, 3);
	testsMap[test_input] = test_expectedOutput;

	//test 2 data
	test_input = std::make_tuple("ff", 16, NoError);
	test_expectedOutput = std::make_tuple(255, 16, NoError, 2);
	testsMap[test_input] = test_expectedOutput;


	for (auto[key, value] : testsMap)
	{
		string input = std::get<0>(key);
		unsigned short base = std::get<1>(key);
		toDecimalError err = std::get<2>(key);;

		unsigned long long expectedOutput = std::get<0>(value);
		unsigned short expectedBase = std::get<1>(value);
		toDecimalError expectedErr = std::get<2>(value);
		string::size_type expectedPos = std::get<3>(value);

		unsigned long long output = toDecimal(input, &base, &err, &posPtr);

		std::cout << "Test # " << testNumber++ << "\n"
			<< (output == expectedOutput ? "Result: Pass\n" : "Result: Fail\n")
			<< "Actual result: " << output << " Expected result: " << expectedOutput << "\n\n"
			<< (base == expectedBase ? "Base: Pass\n" : "Base: Fail\n")
			<< "Actual base: " << base << " Expected base: " << expectedBase << "\n\n"
			<< (err == expectedErr ? "Error: Pass\n" : "Error: Fail\n")
			<< "Actual error: " << err << " Expected error: " << expectedErr << "\n\n"
			<< (posPtr == expectedPos ? "Pos: Pass\n" : "Pos: Fail\n")
			<< "Actual pos: " << posPtr << " Expected pos: " << expectedPos << "\n\n";

		if (output != expectedOutput || base != expectedBase ||
			err != expectedErr || posPtr != expectedPos)
			testsFailed++;
	}
}

/*
* Function: void convertToDecimalAndOutput
*
* Convenient function to convert a string containing number in base 2-36
* to decimal
*
* Parameters:
*  const string& number: number to convert
*  unsigned short base: base of a number to convert
*
* Uses toDecimal to covert and prints the decimal equivalent or an error
* message depending on the error code returned. Also verifies result using
* std::stoull
*/


void convertToDecimalAndOutput(const string& number, unsigned short base)
{
	string::size_type pos;
	toDecimalError errorCode;
	auto originalBase(base);
	unsigned long long decimal = toDecimal(number, &base, &errorCode, &pos);

	cout << "::toDecimal> Number: " << number << "; ";

	if (errorCode == NoError)
	{
		cout << "Decimal: " << decimal;
		if (originalBase == 0)
			cout << "; Base: " << base;
	}
	else
	{
		cout << "Error: " << getErrorMessage(errorCode);
		if (errorCode == InvalidDigit || errorCode == Overflow)
			cout << " '" << number[pos] << "' at position " << pos;
	}

	cout << '\n';

	//verify using std::stoull
	decimal = std::stoull(number, &pos, originalBase);
	cout << "std::stoull> Number: " << number;

	if (pos == number.length())
	{
		cout << "; Decimal: " << decimal;
		if (originalBase == 0)
			cout << "; Base: " << originalBase;
	}
	else
		cout << "; Error: '" << number[pos] << "' at position " << pos;

	cout << "\n\n";
}