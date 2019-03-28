/*
* H2.1.main.cpp
* Homework 2, Problem 2
* Dr. Sean Murthy; CS170@WCSU
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
typedef std::tuple<const string, unsigned short, toDecimalError, std::string::size_type> input_key;

void test_getPermittedChars();
void test_toDecimal();
void checkResultAndOutput(unsigned testNumber, std::string expectedP, std::string actualP);


int main()
{
    test_getPermittedChars();
    cout << "\n\nTesting toDecimal..\n";
    test_toDecimal();
	return 0;
}

void test_getPermittedChars()
{
    unsigned testNumber{1};//counter for tests
    //std::string actualResult;
    //std::string expectedResult;
    
    std::map<unsigned, std::string> tests;
    
    tests.insert(std::pair<int, std::string>(0,  "0123456789abcdefghijklmnopqrstuvwxyz"));
    tests.insert(std::pair<int, std::string>(36, "0123456789abcdefghijklmnopqrstuvwxyz"));
    tests.insert(std::pair<int, std::string>(1,  "0"));
    tests.insert(std::pair<int, std::string>(35, "0123456789abcdefghijklmnopqrstuvwxy"));
    tests.insert(std::pair<int, std::string>(2,  "01"));
    tests.insert(std::pair<int, std::string>(8,  "01234567"));
    tests.insert(std::pair<int, std::string>(10, "0123456789"));
    tests.insert(std::pair<int, std::string>(16, "0123456789abcdef"));
    tests.insert(std::pair<int, std::string>(3,  "012"));
    tests.insert(std::pair<int, std::string>(9,  "012345678"));
    tests.insert(std::pair<int, std::string>(11, "0123456789a"));
    tests.insert(std::pair<int, std::string>(15, "0123456789abcde"));
    
    for (auto&& [first, second] : tests)
    {
        checkResultAndOutput(testNumber++, second, getPermittedChars(first));
    }
}


void checkResultAndOutput(unsigned testNumber, std::string expectedP, std::string actualP)
{
    std::cout << "Test " << testNumber << ": ";
    if(actualP == expectedP)
        std::cout << "Pass\n";
    else
        std::cout << "Fail\n";
}


// To Decimal Signiture: unsigned long long toDecimal(const string& number,
// unsigned short*, toDecimalError*, string::size_type*);
void test_toDecimal()
{
    unsigned testNumber{1}; //counter for tests
    std::map<input_key, output_value> testsMap;
    const string inputString = "101";
    short basePtr = 2;
    string::size_type posPtr = 2;
    toDecimalError errPtr = NoError;
    
    auto test_input = std::make_tuple(inputString, basePtr, errPtr, posPtr);
    auto test_expectedOutput = std::make_tuple(5, 2, NoError, 3);
    
    testsMap[test_input] = test_expectedOutput;

	test_input = std::make_tuple("0xff", 16, NoError, 0);
	test_expectedOutput = std::make_tuple(255, 16, NoError, 4);

	testsMap[test_input] = test_expectedOutput;


    for(auto[key, value]: testsMap)
    {
       //auto[a,b,c,d] = key;
		string input = std::get<0>(key);
		unsigned short base = std::get<1>(key); 
		toDecimalError err = std::get<2>(key);;
		string::size_type pos = std::get<3>(key);

		unsigned long long expectedOutput = std::get<0>(value);
		unsigned short expectedBase = std::get<1>(value);
		toDecimalError expectedErr = std::get<2>(value);
		string::size_type expectedPos = std::get<3>(value);
       
		unsigned long long output = toDecimal(input, &base, &err, &pos);

		std::cout << (output == expectedOutput ? "Pass\n" : "Fail\n")
			<< (base == expectedBase ? "Base okay\n" : "Base incorrect\n")
			<< "Actual base: " << base << " Expected base: " << expectedBase << std::endl
			<< (err == expectedErr ? "Error okay\n" : "Error incorrect\n")
			<< (pos == expectedPos ? "Pos Okay\n" : "Pos Incorrect\n");
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

/*
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
 */

/*
void testGetPermittedChars()
{
    unsigned testNumber{1};//counter for tests
    std::string actualResult;
    std::string expectedResult;
 
    
    
    
    
    actualResult = getPermittedChars(0);
    expectedResult = "0123456789abcdefghijklmnopqrstuvwxyz";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(36);
    expectedResult = "0123456789abcdefghijklmnopqrstuvwxyz";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(1);
    expectedResult = "0";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(35);
    expectedResult = "0123456789abcdefghijklmnopqrstuvwxy";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(2);
    expectedResult = "01";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(8);
    expectedResult = "01234567";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(10);
    expectedResult = "01233456789";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(16);
    expectedResult = "0123456789abcdef";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(3);
    expectedResult = "012";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(9);
    expectedResult = "012345678";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(11);
    expectedResult = "0123456789a";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
    actualResult = getPermittedChars(15);
    expectedResult = "012345678abcd";
    checkResultAndOutput(testNumber++, expectedResult, actualResult);
    
}
*/


