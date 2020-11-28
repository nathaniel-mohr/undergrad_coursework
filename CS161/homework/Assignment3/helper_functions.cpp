/*
 * Program Filename: helper_functions.cpp
 * Author: Nathaniel Mohr
 * Date: 1/27/18
 * Description: Definitions of 16 helper functions
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

bool check_range(int lower_bound, int upper_bound, int test_value){
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

bool is_int(string num){
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

bool is_float(string num){
	bool decimalFlag = false;
	bool intFlag = false;
	int neg = 0;
	if(num[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < num.length(); i++){
		if(num[i] == 46){		// checks to see if there is a decimal present
			decimalFlag = true;
		}else if(num[i] >= 48 && num[i] <= 57){		// checks to see if there are ints present
			intFlag = true;
		}else{
			decimalFlag = false;
			intFlag = false;
			break;
		}
	}
	if(decimalFlag == true && intFlag == true){	// if there are ints and a decimal present then it is a float
		return true;
	}else{
		return false;
	}
}



/*
 * Function: is_capital
 * Description: Checks to see if a character is a capital letter
 * Parameters: char
 * Pre-Conditions: valid char
 * Post-Conditions: returns if the given char is a capital
 */

bool is_capital(char letter){
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

bool is_even(int num){
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

bool is_odd(int num){
	if((num % 2) == 1){
		return true;
	}else{
		return false;
	}
}



/*
 * Function: equality_test
 * Description: Checks to see the relation between two ints 
 * Parameters: 2 ints
 * Pre-Conditions: valid ints
 * Post-Conditions: returns an integer referring to how the ints are related
 */

int equality_test(int num1, int num2){
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

bool float_is_equal(float num1, float num2, float precision){
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

bool numbers_present(string sentence){
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

bool letters_present(string sentence){
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

bool contains_sub_string(string sentence, string sub_string){
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

int word_count(string sentence){
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

string to_upper(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 97 && sentence[i] <= 122){
			sentence[i] -= 32;
		}
	}
	return sentence;
}



/*
 * Function: to_lower
 * Description: Converts all the letters in a string to lowercase and then returns it
 * Parameters: string
 * Pre-Conditions: valid string
 * Post-Conditions: string with all letters being lowercase
 */

string to_lower(string sentence){
	for(int i = 0; i < sentence.length(); i++){
		if(sentence[i] >= 65 && sentence[i] <= 90){
			sentence[i] += 32;
		}
	}
	return sentence;
}



/*
 * Function: get_int
 * Description: Continues to prompt the user for a string literal until it is a valid int. Then it return the int
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: String provided by the user was a proper int, then was returned as an int
 */

int get_int(){
	int ans = 0;
	string prompt = "";
	int neg = 0;

	do{
		cout << "Enter an integer: ";
		getline(cin, prompt);

	} while(is_int(prompt) == false);
	
	if(prompt[0] = 45){
		neg = 1;
	}
	for(int i = neg; i < prompt.length(); i++){
		ans *= 10;
		ans += prompt[i] - 48;	
	}
	if(neg == 1){
		ans *= -1;
	}
	return ans;
}



/*
 * Function: get_float
 * Description: Continues to prompt the user for a string literal until it is a valid float. Then it returns the float
 * Parameters: None
 * Pre-Conditions: None
 * Post-Conditions: String provided by the user was a proper float, then was returned as a float
 */

float get_float(){
	string prompt = "";
	float ans = 0, dec = 0;
	int decPoint = 0, count = 0, neg = 0;

	do{
		cout << "Enter a float: ";
		getline(cin, prompt);

	} while(is_float(prompt) == false);
	
	if(prompt[0] == 45){	// sees if the float is negative
		neg = 1;
	}

	for(int i = 0; i < prompt.length(); i++){	
		if(prompt[i] == 46){	// finds where the decimal point is
			decPoint = i;
		}
	}
	for(int i = neg; i < decPoint; i++){ // calculates the value of the number before the decimal point
		ans *= 10;
		ans += prompt[i] - 48;
	}
	for(decPoint; decPoint < prompt.length() - 1; decPoint++){	// calculates the value of the number after the decimal point
		dec *= 10;
		dec += prompt[decPoint + 1] - 48;
		count++;
	}

	dec /= (pow(10, count));	// changes the dec number to a fraction
	ans += dec;	
	if(neg == 1){
		ans *= -1;
	}
	return ans;
}
