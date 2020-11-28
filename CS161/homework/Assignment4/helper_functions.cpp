/*
 * Program Filename: helper_functions.cpp
 * Author: Nathaniel Mohr
 * Date: 1/27/18
 * Description: Definitions of  helper functions
 * Input:  
 * Output: 
 */

#include <string>
#include <iostream>
#include <cmath>
#include "helper_functions.h"

using namespace std;



/*
 * Function: check_range
 * Description: Checks to see if a test value is within a given range
 * Parameters: 3 ints
 * Pre-Conditions: 3 valid ints
 * Post-Conditions: returns if the test value is within the range
 */

bool checkRange(int lower_bound, int upper_bound, int test_value){
	if(test_value >= lower_bound && test_value <= upper_bound){
		return true;
	}else{
		return false;
	}
}



/*
 * Function: is_int
 * Description: Checks to see if the given string is an int
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: returns if the given string is an int
 */

bool isInt(string num){
	bool flag = false;
	int neg = 0;
	if(num[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < num.length(); i++){		// for every character it will check if it is in the range of integers
		if(num[i] >= 48 && num[i] <= 57){
			flag = true;
		}else{
			flag = false;
			break;
		}
	}
	return flag;
}


/*
 * Function: is_float
 * Description: Checks to see if the given string is a float
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: returns if the given string is a float
 */

bool isFloat(string num){
	int neg = 0;
	if(num[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < num.length(); i++){
		if(!(num[i] >= 48 && num[i] <= 57) && (num[i] != '.')){
			return false;
		}
	}
	return true;
}

/*
 * Function: isBin
 * Description: Checks to see if a string is a binary
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: string is a binary number
 */

bool isBin(string bin){
	for(int i = 0; i < bin.length(); i++){
		if((bin[i] != '0') && (bin[i] != '1')){
			return false;
		}
	}
	return true;
}


/*i
 * Function: is_capital
 * Description: Checks to see if a character is a capital letter
 * Parameters: char
 * Pre-Conditions: valid char
 * Post-Conditions: returns if the given char is a capital
 */

bool isCapital(char letter){
	if(letter >= 65 && letter <= 90){	// checks if the character is within the range of capitals
		return true;
	}else{
		return false;
	}
}



/*
 * Function: is_even
 * Description: Checks to see if the given int is even
 * Parameters: int
 * Pre-Conditions: valid int
 * Post-Conditions: returns if the given int is even or not
 */

bool isEven(int num){
	if((num % 2) == 0){
		return true;
	}else{
		return false;
	}
}



/*
 * Function: is_odd
 * Description: Checks to see if the given int is odd
 * Parameters: int
 * Pre-Conditions: valid int
 * Post-Conditions: returns if the given int is odd or not
 */

bool isOdd(int num){
	if((num % 2) == 1){
		return true;
	}else{
		return false;
	}
}

/*
 * Function: getBin
 * Description: Continues to prompt the user until a valid binary is given
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: user entered a valid binary number 
 */

string getBin(){
	string bin = "";
	do{
		cout << "Provide binary number: ";
		getline(cin, bin);
	}while(isBin(bin) == false);
	return bin;
}

/*
 * Function: getInt
 * Description: Continues to prompt the user until a valid integer is give
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: user enterd a valid integer
 */

int getInt(){
	string num = "";
	do{
		cout << "Provide integer: ";
		getline(cin, num);
	}while(isInt(num) == false);
	return stringToInt(num);
}

/*
 * Function: stringToInt
 * Description: Converts a string to an integer
 * Parameters: string
 * Pre-Conditions: string is a valid integer
 * Post-Conditions: string was converted to an integer
 */

int stringToInt(string prompt){
	int neg = 0, ans = 0;
	if(prompt[0] == 45)
		neg = 1;
	for(int i = neg; i < prompt.length(); i++){
		ans *= 10;
		ans += prompt[i] - 48;
	}
	if(neg == 1)
		ans *= -1;
	return ans;
}

/*
 * Function: substringToFloat
 * Description: Converts a string from one index to another to a float
 * Parameters: string and two ints
 * Pre-Conditions: string is a valid float
 * Post-Conditions: string was converted to a float
 */

float substringToFloat(string substring, int start, int end){
	float ans = 0;
	if(start == findDecPoint(substring)){
		for(start; start < end - 1; start++){
			ans *= 10;
			ans += substring[start + 1] - 48;
		}
	}else{
		for(start; start < end; start++){
			ans *= 10;
			ans += substring[start] - 48;
		}
	}
	return ans;

}

/*
 * Function: findDecPoint
 * Description: finds where the decimal point is in a float
 * Parameters: string
 * Pre-Conditions: string that is a valid float
 * Post-Conditions: decimal point in float was found (if there is none, then will return length of string)
 */

int findDecPoint(string num){
	int decPoint = -1;
	for(int i = 0; i < num.length(); i++){
		if(num[i] == '.' && (i >= 0)){
			decPoint = i;
			break;
		}else{
			decPoint = num.length();
		}
	}
	return decPoint;
}

/*
 * Function: stringToFloat
 * Description: converts a string to a float
 * Parameters: string
 * Pre-Conditions: string that is a valid float
 * Post-Conditions: string was converted to a float
 */

float stringToFloat(string prompt){
	int neg = 0, decPoint = 0;
	float ans = 0, dec = 0;
	if(prompt[0] == 45){
		neg = 1;
	}
	decPoint = findDecPoint(prompt);
	ans = substringToFloat(prompt, neg, decPoint);
	dec = substringToFloat(prompt, decPoint, prompt.length());
	ans += (dec / pow(10, (prompt.length() - decPoint - 1)));
	if(neg == 1)
		ans *= -1;
	return ans;
}

/*
 * Function: binToDec
 * Description: Converts a binary number to a decimal
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: binary number was converted to decimal
 */

int binToDec(){
	string bin = "";
	int ans = 0;
	bin = getBin();
	for(int i = 0; i < bin.length(); i++){
		if(bin[i] == '1')
			ans += pow(2, (bin.length() - 1 - i));
	}
	return ans;
}

/*
 * Function: decToBin
 * Description: Converts a decimal number to a binary
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: Decimal number was converted to a binary
 */

string decToBin(){
	string ans = "";
	int num = 0;
	num = getInt();
	while(num != 0){
		if(num % 2 == 1){
			ans = "1" + ans;
		}else{
			ans = "0" + ans;
		}
		num /= 2;
	}
	return ans;
}

/*
 * Function: equality_test
 * Description: Checks to see the relation between two ints 
 * Parameters: 2 ints
 * Pre-Conditions: valid ints
 * Post-Conditions: returns an integer referring to how the ints are related
 */

int equalityTest(int num1, int num2){
	if(num1 < num2){
		return -1;
	}else if(num1 > num2){
		return 1;
	}else{
		return 0;
	}
}



/*
 * Function: float_is_equal
 * Description: Checks to see if two floats are equal, within a given precision
 * Parameters: 3 floats
 * Pre-Conditions: 3 vaild floats
 * Post-Conditions: returns if the given floats were equal
 */

bool floatIsEqual(float num1, float num2, float precision){
	if(num1 == num2){
		return true;
	}else if(abs(num1 - num2) <= precision){	
		return true;
	}else{
		return false;
	}
}



/*
 * Function: numbers_present
 * Description: Checks to see if there are letters present in a string
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: returns if the given string has numbers
 */

bool numbersPresent(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 48 && sentence[i] <= 57){
			return true;
		}
	}
	return false;
}



/*
 * Function: letters_present
 * Description: Checks to see if there are letters present in a string 
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: returns if the given string has letters
 */

bool lettersPresent(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 65 && sentence[i] <= 90){
			return true;
		}else if(sentence[i] >= 97 && sentence[i] <= 122){
			return true;
		}else{
			return false;
		}
	}
}



/*
 * Function: contains_sub_string
 * Description: Checks to see if a substring is present in a string
 * Parameters: two strings
 * Pre-Conditions: two valid strings
 * Post-Conditions: returns if the given substring was present in the given string
 */

bool containsSubstring(string sentence, string sub_string){
	int counter = 0;
	bool flag = false;
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] == sub_string[0]){	// finds the location where the substring begins to share characters with the substring
			for(counter; counter < sub_string.length(); counter++){	// checks to see that the rest of the substring matches
				if(sentence[i + counter] == sub_string[counter]){
					flag = true;
				}else{
					flag = false;
				}
			}
		}
		if(flag == true && counter == sub_string.length()){
			break;
		}
		counter = 0;
	}
	return flag;
}



/*
 * Function: word_count
 * Description: returns the number of words in a string
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: number of words in a string has been returned
 */

int wordCount(string sentence){
	int counter = 0;
	for(int i = 0; i < sentence.length(); i++){
		if(((sentence[i] >= 65 && sentence[i] <= 90) || (sentence[i] >= 97 && sentence[i] <= 122)) && (i + 1 == sentence.length())){
			counter++;
		}
		if(sentence[i] == 32 && ((i + 1) < sentence.length())){
			if((sentence[i+1] >= 65 && sentence[i+1] <= 90) || (sentence[i+1] >= 97 && sentence[i+1] <= 122)){
				counter++;
			}
		}
		
	}
	return counter;
}



/*
 * Function: to_upper
 * Description: Converts all the letters in a string to uppercase and then returns it
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: string with all letters being uppercase
 */

string toUpper(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 97 && sentence[i] <= 122){
			sentence[i] -= 32;
		}
	}
	return sentence;
}



/*
 * Function: toLower
 * Description: Converts all the letters in a string to lowercase and then returns it
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: string with all letters being lowercase
 */

string toLower(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 65 && sentence[i] <= 90){
			sentence[i] += 32;
		}
	}
	return sentence;
}



