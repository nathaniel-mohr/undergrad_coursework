/*
 * Program Filename: assignment4.cpp
 * Author: Nathaniel Mohr
 * Date: 2/14/18
 * Description: Calculator function that can do 
 * 		a normal calculator, binary and decimal converter, and average grade calculator
 * Input: strings from user (numbers and choices) 
 * Output: Answers to calculations
 */

#include <iostream>
#include <string>
#include <cmath>
#include "helper_functions.h"

using namespace std;

bool isEquation(string prompt);
string getEquation();
string getComponent(int* i, string equation);
bool operatorCheck(char input);
int operatorSwitch(string input);
float calculation(float num1, float num2, int operation);
float getGrade();
float getWeight();
float unweightedAvg();
float weightedAvg();
void calculator();
void binDecConverter();
void avgGradeCalc();
void menuSelect(int choice);


/*
 * Function: main 
 * Description: Menu system
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: user had inputed a choice
 */

int main(){
	int choice = 0;
	string input = "";
	do{
		cout << "\n\n-------------------------------------------" << endl;
		cout << "|    (1)  Calculator                      |" << endl;
		cout << "|    (2)  Binary and Decimal Converter    |" << endl;
		cout << "|    (3)  Average Grade Calculator        |" << endl;
		cout << "|    (4)  Exit                            |" << endl;
		cout << "-------------------------------------------" << endl;
		getline(cin, input);
		choice = stringToInt(input);
	}while(!(choice >= 1 && choice <= 4));
	menuSelect(choice);
	return 0;
}

/*
 * Function: calculator 
 * Description: Runs a standard calculator
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: Equation had been solved and returned back to main
 */

void calculator(){
	int i = 0, operation = 0;
	float num1 = 0;
	string equation = "", temp = "";
	equation = getEquation();
	num1 = stringToFloat(getComponent(&i, equation));
	i++;
	for(i; i < equation.length(); i++){
		temp = getComponent(&i, equation);
		if(isFloat(temp)){
			num1 = calculation(num1, stringToFloat(temp), operation);
		}else{
			operation = operatorSwitch(temp);
		}
	}
	cout << "Answer: " <<  num1 << endl;
	main();
}

/*
 * Function: binDecConverter 
 * Description: Runs a binary and decimal converter
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: Returns answer and returned back to main
 */

void binDecConverter(){
	int choice = 0;
	string input = "";
	do{
		cout << "\n-------------------------------" << endl;
		cout << "|    (1) Binary to Decimal    |" << endl;
		cout << "|    (2) Decimal to Binary    |" << endl;
		cout << "-------------------------------" << endl;
		getline(cin, input);
		choice = stringToInt(input);
	}while(choice != 1 && choice != 2);
	if(choice == 1){
		cout << "Decimal equivalent: " << binToDec() << endl;
	}else{
		cout << "Binary equivalent: " << decToBin() << endl;
	}
	main();
}

/*
 * Function: avgGradeCalc 
 * Description: Runs an average grade calculator
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: Returns average and returned back to main
 */

void avgGradeCalc(){
	int choice = 0;
	string input = "";
	do{
		cout << "\n--------------------------------" << endl;
		cout << "|    (1) Unweighted Average    |" << endl;
		cout << "|    (2) Weighted Average      |" << endl;
		cout << "--------------------------------" << endl;
		getline(cin, input);
		choice = stringToInt(input);
	}while(choice != 1 && choice != 2);
	if(choice == 1){
		cout << "Average: " << unweightedAvg() << endl;
	}else{
		cout << "Average: " << weightedAvg() << endl;
	}
	main();
}

/*
 * Function: menuSelect
 * Description: switches integer choice to the equivalence in the main menu
 * Parameters: int
 * Pre-Conditions: valid choice 
 * Post-Conditions: selection of main menu was returned
 */

void menuSelect(int choice){
	switch(choice){
		case 1: 
			calculator();
			break;
		case 2:
			binDecConverter();
			break;
		case 3: 
			avgGradeCalc();
			break;
		default:
			break;
	}
}
/*
 * Function: isEquation
 * Description: Checks if a string is a valid equation
 * Parameters: prompt
 * Pre-Conditions: none
 * Post-Conditions: string is a valid equation (spacing between elements)
 */

bool isEquation(string prompt){
	for(int i = 0; i < prompt.length(); i++){
		if(!(prompt[i] >= 48 && prompt[i] <= 57) && (prompt[i] != '.') && (operatorCheck(prompt[i]) == false) && (prompt[i] != ' ')){
				return false;
		}
		if(operatorCheck(prompt[i]) == true){
			if((prompt[i - 1] != ' ') || (prompt[i + 1] != ' ') || ((i+1) >= prompt.length())){
				return false;
			}
		}

	}
	return true;
	
}

/*
 * Function: getEquation
 * Description: Gets an equation from the user
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: The string entered by the user is a valid equation 
 */

string getEquation(){
	string prompt = "";
	do{
		cout << "Enter equation: ";
		getline(cin, prompt);
	}while(isEquation(prompt) == false);
	return prompt;
}

/*
 * Function: getComponent 
 * Description: Returns an element of an equation ("12" from "12 + 3")
 * Parameters: int* and string
 * Pre-Conditions: valid equation
 * Post-Conditions: returned part of an equation
 */

string getComponent(int* i, string equation){
	string temp = "";
	while(equation[*i] != 32 && (*i < equation.length())){
		temp += equation[*i];
		*i = *i + 1;
	}
	return temp;
}


/*
 * Function: operatorCheck
 * Description: Checks if the character is an operation
 * Parameters: char
 * Pre-Conditions: none
 * Post-Conditions: char is a valid operation
 */

bool operatorCheck(char input){
	if(input != 42 && input != 43 && input != 45 && input != 47)
		return false;
	return true;
}

/*
 * Function: operationSwitch
 * Description: Converts the string to an integer standing for an operation
 * Parameters: string
 * Pre-Conditions: valid operation
 * Post-Conditions: returns an integer representing an operation
 */

int operatorSwitch(string input){
	if(input[0] == '+')
		return 1;
	if(input[0] == '-')
		return 2;
	if(input[0] == '*')
		return 3;
	if(input[0] == '/')
		return 4;
}

/*
 * Function: calculation
 * Description: Performs the operation signified by the operator
 * Parameters: 2 floats and an int
 * Pre-Conditions: valid floats and valid operator
 * Post-Conditions: Operation had been fulfilled 
 */

float calculation(float num1, float num2, int operation){
	if(operation == 1){
		return num1 + num2;
	}else if(operation == 2){
		return num1 - num2;
	}else if(operation == 3){
		return num1 * num2;
	}else{
		return num1 / num2;
	}
}

/*
 * Function: getGrade 
 * Description: Gets a grade from the user
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: Grade was a valid float
 */

float getGrade(){
	string input = "";
	do{
		cout << "Enter grade: ";
		getline(cin, input);
	}while(isFloat(input) == false);
	return stringToFloat(input);
}

/*
 * Function: getWeight
 * Description: Gets a weight from the user
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: Weight was a valid float
 */

float getWeight(){
	string input = "";
	do{
		cout << "Enter weight: ";
		getline(cin, input);
	}while(isFloat(input) == false);
	return stringToFloat(input);
}

/*
 * Function: unweightedAvg
 * Description: Calculates an unweighed average
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: unweighted average was returned
 */

float unweightedAvg(){
	int num = 0;
	string input = "";
	float ans = 0, total = 0, grade = 0;
	cout << "How many grades will you input? ";
	getline(cin, input);
	num = stringToInt(input);
	for(int i = 0; i < num; i++){
		cout << "Grade #" << i+1 << endl;
		grade = getGrade();
		total += grade;
	}
	ans = total / num;
	return ans;
}

/*
 * Function: weightedAvg
 * Description: Calculates a weighted average
 * Parameters: none
 * Pre-Conditions: none
 * Post-Conditions: weighted average was returned
 */

float weightedAvg(){
	float ans = 0, total = 0, weight = 0, grade = 0;
	int num = 0, amount = 0;
	string input = "";
	cout << "How many grades will you input? ";
	getline(cin, input);
	num = stringToInt(input);
	for(int i = 0; i < num; i++){
		cout << "Grade #" << i+1 << endl;
		grade = getGrade();
		cout << "Weight #" << i+1 << endl;
		weight = getWeight();
		total += grade * weight;
		amount += weight;
	}
	return total / amount;
}


