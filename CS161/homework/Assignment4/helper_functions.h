/*
 * Program Filename: helper_functions.h
 * Author: Nathaniel Mohr
 * Date: 1/27/18
 * Description: Declarations of helper functions
 * Input:  None
 * Output: None
 */

#include <string>

using namespace std;

bool checkRange(int lower_bound, int upper_bound, int test_value);

bool isInt(string num);

bool numCheck(string input);

bool isFloat(string num);

bool isBin(string bin);

bool isCapital(char letter);

bool isEven(int num);

bool isOdd(int num);

string getBin();

int getInt();

int stringToInt(string prompt);

float substringToFloat(string substring, int start, int end);

int findDecPoint(string num);

float stringToFloat(string prompt);

int binToDec();

string decToBin();

int equalityTest(int num1, int num2);

bool floatIsEqual(float num1, float num2, float precision);

bool numbersPresent(string sentence);

bool lettersPresent(string sentence);

bool containsSubstring(string sentence, string sub_string);

int wordCount(string sentence);

string toUpper(string sentence);

string toLower(string sentence);


