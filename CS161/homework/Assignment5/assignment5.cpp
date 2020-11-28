/*
* Program Filename: assignment5.cpp
* Author: Nathaniel Mohr
* Date: 2/28/18
* Description: This program simulates a game of Farkle
* Input: Number of players as well as dice selection and turn based decisions
* Output: Game of Farkle
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool isInt(string input);
int getInt();
int stringToInt(string input);
int* initArray(int num);
void fillArray(int arr[], int num, int val);
void printArray(int arr[], int num);
void printScores(int scoreboard[], int players);
int* cutArray(int arr[], int startIndex, int newLength);
int* sortArray(int arr[], int length);
bool checkScoreboard(int scoreboard[], int players);
int findFlag(int scoreboard[], int players);
void playerTurn(int scoreboard[], int player);
void play(int scoreboard[], int players, int start, int finish);
void findWinner(int scoreboard[], int players);
int* diceRoll(int length);
void getChoices(int diceArray[], int choiceArray[], int choice);
bool getAnswer();
int pointConversion(int choiceArray[], int choice);
bool equalityTest(int arr[], int length);
int sixDice(int choiceArray[]);
int fiveDice(int choiceArray[]);
int fourDice(int choiceArray[]);
int threeDice(int choiceArray[]);
int twoDice(int choiceArray[]);
int oneDie(int choiceArray);

/*
** Function: Main
** Description: Runs the game of Farkle
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Game of Farkle
*/
int main(){
	int flag = 0;
	srand(time(NULL));
	cout << "\t\tWELCOME TO FARKLE" << endl;
	cout << "How many players are going to play?" << endl;
	int players = getInt();
	int* scoreboard = initArray(players);
	fillArray(scoreboard, players, 0);
	while(checkScoreboard(scoreboard, players) == false){
		play(scoreboard, players, 0, players);
		if(checkScoreboard(scoreboard, players) == true){
			flag = findFlag(scoreboard, players);
			play(scoreboard, players, 0, flag);
			findWinner(scoreboard, players);
			delete[] scoreboard;
			return 0;
		}

	}
}

/*
** Function: isInt
** Description: determines if a string is an int
** Parameters: string
** Pre-Conditions: none
** Post-Conditions: string was an int
*/

bool isInt(string input){
	if(input.length() == 0){
		return false;
	}
	int neg = 0;
	if(input[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < input.length(); i++){
		if(!(input[i] >= '0' && input[i] <= '9')){
			return false;
		}
	}
	return true;
}

/*
** Function: getInt
** Description: gets a string from the user that is a valid int
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: string entered was a valid int
*/

int getInt(){
	string input = "";
	do{
		cout << "Enter integer: ";
		getline(cin, input);
	}while(isInt(input) == false);
	return stringToInt(input);

}

/*
** Function: stringToInt
** Description: converts a string to an int
** Parameters: string
** Pre-Conditions: string is a valid int
** Post-Conditions: return the int equivalent of the string
*/

int stringToInt(string input){
	int neg = 0, ans = 0;
	if(input[0] == '-'){
		neg = 1;
	}
	for(int i = 0 ; i < input.length(); i++){
		ans *= 10;
		ans += input[i] - 48;	
	}
	if(neg == 1){
		ans *= -1;
	}
	return ans;
}

/*
** Function: initArray
** Description: creates int memory on the heap of size num
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: int memory on the heap of size num
*/

int* initArray(int num){
	return new int[num];
}

/*
** Function: fillArray
** Description: fills an array with a value
** Parameters: int[], int, int
** Pre-Conditions: array with valid memory
** Post-Conditions: array is filled with inputted value
*/

void fillArray(int arr[], int num, int val){
	for(int i = 0; i < num; i++){
		arr[i] = val;
	}
}

/*
** Function: printArray
** Description: prints the contents of an array
** Parameters: int[], int
** Pre-Conditions: array has valid memory
** Post-Conditions: prints array to screen
*/

void printArray(int arr[], int num){
	for(int i = 0; i < num; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

/*
** Function: printScores
** Description: prints the scoreboard
** Parameters: int[], int
** Pre-Conditions: scoreboard has valid memory
** Post-Conditions: scoreboard was printed
*/

void printScores(int scoreboard[], int players){
	cout << "\tScoreboard:" << endl;
	cout << "        ------------" << endl;
	for(int i = 0; i < players; i++)
		cout << "\tPlayer " << i+1 << ":  " << scoreboard[i] << endl;
}

/*
** Function: cutArray
** Description: returns a portion of an array
** Parameters: int[], int, int
** Pre-Conditions: array has valid memory
** Post-Conditions: array of length given starting at start point returned
*/

int* cutArray(int arr[], int startIndex, int newLength){
	int* temp = initArray(newLength);
	for(int i = 0; i < newLength; i++){
		temp[i] = arr[i+startIndex];
	}
	return temp;
}

/*
** Function: sortArray
** Description: sorts an array in ascending order
** Parameters: int[], int
** Pre-Conditions: array has valid memory
** Post-Conditions: array is sorted
*/

int* sortArray(int arr[], int length){
	int temp;
	for(int i = 0; i < length; i++){
		for(int j = i+1; j < length; j++){
			if(arr[i] > arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return arr;
}

/*
** Function: checkScoreboard
** Description: checks to see if any player is over 10000
** Parameters: int[], int
** Pre-Conditions: scoreboard has valid memory
** Post-Conditions: result is determined
*/

bool checkScoreboard(int scoreboard[], int players){
	for(int i = 0; i < players; i++){
		if(scoreboard[i] >= 10000){
			return true;
		}
	}
	return false;
}

/*
** Function: findFlag
** Description: finds the player over 10000
** Parameters: int[], int
** Pre-Conditions: scoreboard has valid memory
** Post-Conditions: result is determined
*/

int findFlag(int scoreboard[], int players){
	for(int i = 0; i < players; i++){
		if(scoreboard[i] >= 10000){
			return i;
		}
	}
}

/*
** Function: playerTurn
** Description: runs a single player's turn
** Parameters: int[], int
** Pre-Conditions: scoreboard has valid memory and player is within the array
** Post-Conditions: the player's score for the turn was added to scoreboard
*/

void playerTurn(int scoreboard[], int player){
	int choice = 0, totalDice = 0, runningTotal = 0, *choiceArray, *diceArray;
	bool turnChoice = true;
	do{
		diceArray = sortArray(diceRoll(6-totalDice), (6-totalDice));
		cout << "\nYou rolled a: ";
		printArray(diceArray, (6-totalDice));
		if(pointConversion(diceArray, (6-totalDice)) <= 0){
			cout << "*** FARKLE ***" << endl;
			runningTotal = 0;
			break;
		}
		cout << "How many dice would you like to take out?" << endl;
		choice = getInt();
		totalDice += choice;
		choiceArray = initArray(choice);
		cout << endl;
		getChoices(diceArray, choiceArray, choice);
		runningTotal += pointConversion(choiceArray, choice);
		cout << "\t*** Score this turn: " << runningTotal << " ***" << endl;
		if(scoreboard[player] >= 500 || runningTotal >= 500){
			cout << "Would you like to keep rolling?" << endl;
			turnChoice = getAnswer();
		}
		delete[] choiceArray;
		if(totalDice >= 6){
			totalDice = 0;
		}
	}while(turnChoice == true);
	scoreboard[player] += runningTotal;
	delete[] diceArray;
}

/*
** Function: play
** Description: runs the turns of player start to finish
** Parameters: int[], int, int, int
** Pre-Conditions: scoreboard has valid memory
** Post-Conditions: play is simulted
*/

void play(int scoreboard[], int players, int start, int finish){
	for(int i = start; i < finish; i++){
		cout << endl;
		cout << "\t*** Player " << i+1 << " ***" << endl;
		playerTurn(scoreboard, i);
		cout << endl;
		printScores(scoreboard, players);		
	}
}

/*
** Function: findWinner
** Description: determines who has the highest score
** Parameters: int[], int
** Pre-Conditions: scoreboard has valid memory
** Post-Conditions: result is determined
*/

void findWinner(int scoreboard[], int players){
	int max = scoreboard[0], index;;
	for(int i = 0; i < players; i++){
		if(scoreboard[players] > max){
			max = scoreboard[players];
			index = i;
		}
	}
	cout << "The winner is Player " << index + 1 << endl;
}

/*
** Function: diceRoll
** Description: fills an array with dice rolls
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: an array has length random numbers from 1-6
*/

int* diceRoll(int length){
	int *arr = new int[length];
	for(int i = 0; i < length; i++){
		arr[i] = rand() % 6 + 1;
	}
	return arr;
}

/*
** Function: getChoices
** Description: gets the dice the user wants to remove and ads them to an array
** Parameters: int[], int[], int
** Pre-Conditions: arrays have valid memory
** Post-Conditions: array was filled with dice choices
*/

void getChoices(int diceArray[], int choiceArray[], int choice){
	int select = 0;
	do{
		cout << "Getting dice choices" << endl;
		for(int i = 0; i < choice; i++){
			cout << "Dice #" << i+1 << endl;
			select = getInt();
			choiceArray[i] = diceArray[select - 1];	
		}
	}while(pointConversion(choiceArray, choice) <= 0);
}

/*
** Function: getAnswer
** Description: gets answer for a yes or no question
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns choice
*/

bool getAnswer(){
	int answer = 0;
	do{
		answer = getInt();

	}while(answer != 1 && answer != 0);
	if(answer == 1){
		return true;
	}else{
		return false;
	}
}

/*
** Function: pointConversion
** Description: returns the point value associated with the dice selected
** Parameters: int[], int
** Pre-Conditions: array has valid memory
** Post-Conditions: points were returned
*/

int pointConversion(int choiceArray[], int choice){
	switch(choice){
		case 6:
			return sixDice(choiceArray);
			break;
		case 5:
			return fiveDice(choiceArray);
			break;
		case 4:
			return fourDice(choiceArray);
			break;
		case 3:
			return threeDice(choiceArray);
			break;
		case 2:
			return twoDice(choiceArray);
			break;
		case 1:
			return oneDie(choiceArray[0]);
			break;
		default:
			break;	
		
	} 
}

/*
** Function: equalityTest
** Description: determines if all contents of an array are equal
** Parameters: int[], int
** Pre-Conditions: array has valid memory
** Post-Conditions: equality was determined
*/

bool equalityTest(int arr[], int length){
	int num = arr[0];
	bool flag = true;
	for(int i = 0; i < length; i++){
		if(arr[i] != num){
			flag = false;
		}
	}
	return flag;
}

/*
** Function: sixDice
** Description: determines the point value for six dice
** Parameters: int[]
** Pre-Conditions: array has valid memory
** Post-Conditions: returns point value
*/

int sixDice(int choiceArray[]){
	bool flag = equalityTest(choiceArray, 6);
	if(flag == true){
		return 3000;
	}else if(choiceArray[0] == 1 && choiceArray[1] == 2 && choiceArray[2] == 3 && choiceArray[3] == 4 && choiceArray[4] == 5 && choiceArray[5] == 6){
		//1-6 straight
		return 1500;
	}else if(choiceArray[0] == choiceArray[1] && choiceArray[2] == choiceArray[3] && choiceArray[4] == choiceArray[5]){
		//three pairs
		return 1500;
	}else if(choiceArray[0] == choiceArray[1] && choiceArray[0] == choiceArray[2] && choiceArray[3] == choiceArray[4] && choiceArray[3] == choiceArray[5]){
		//two triplets
		return 2500;
	}else if(choiceArray[0] == choiceArray[1] && choiceArray[1] == choiceArray[2] && choiceArray[2] == choiceArray[3] && choiceArray[4] == choiceArray[5]){
		//four of any number with a pair
		return 1500;
	}else if(choiceArray[0] == choiceArray[1] && choiceArray[2] == choiceArray[3] && choiceArray[3] == choiceArray[4] && choiceArray[4] == choiceArray[5]){
		//a pair with four of any number
		return 1500;
	}else{
		return fiveDice(cutArray(choiceArray,0, 5)) + oneDie(choiceArray[5]);
	}
}
/*
** Function: fiveDice
** Description: determines the point value for five dice
** Parameters: int[]
** Pre-Conditions: array has valid memory
** Post-Conditions: returns point value
*/

int fiveDice(int choiceArray[]){
	bool flag = equalityTest(choiceArray, 5);
	if(flag == true){
		return 2000;
	}else if(choiceArray[0] == choiceArray[1] && choiceArray[0] == choiceArray[2] && choiceArray[0] == choiceArray[3]){
		return fourDice(cutArray(choiceArray, 0, 4)) + oneDie(choiceArray[4]);
	}else if(choiceArray[4] == choiceArray[3] && choiceArray[4] == choiceArray[2] && choiceArray[4] == choiceArray[1]){
		return fourDice(cutArray(choiceArray, 1, 4)) + oneDie(choiceArray[0]);
	}else if(choiceArray[4] == choiceArray[3] && choiceArray[4] == choiceArray[2]){
		return threeDice(cutArray(choiceArray, 2, 3)) + twoDice(cutArray(choiceArray,0,2));
	}else{		
		return threeDice(cutArray(choiceArray, 0, 3)) + twoDice(cutArray(choiceArray,3, 2));
	}
}
/*
** Function: fourDice
** Description: determines the point value for four dice
** Parameters: int[]
** Pre-Conditions: array has valid memory
** Post-Conditions: returns point value
*/

int fourDice(int choiceArray[]){
	bool flag = equalityTest(choiceArray, 4);
	if(flag == true){
		return 1000;
	}else if(choiceArray[0] == choiceArray[1] && choiceArray[0] == choiceArray[2]){
		return threeDice(cutArray(choiceArray,0, 3)) + oneDie(choiceArray[3]);
	}else if(choiceArray[3] == choiceArray[2] && choiceArray[3] == choiceArray[1]){
		return threeDice(cutArray(choiceArray,1,3)) + oneDie(choiceArray[0]);
	}else{
		return twoDice(cutArray(choiceArray,0,2)) + twoDice(cutArray(choiceArray,2,2));
	}
}
/*
** Function: threeDice
** Description: determines the point value for three dice
** Parameters: int[]
** Pre-Conditions: array has valid memory
** Post-Conditions: returns point value
*/

int threeDice(int choiceArray[]){
	int flag = equalityTest(choiceArray, 3);
	if(flag == true){
		switch(choiceArray[0]){
			case 1:
				return 300;
				break;
			default:
				return choiceArray[0] * 100;
				break;
		}
	}else{ 
		return twoDice(cutArray(choiceArray,0, 2)) + oneDie(choiceArray[2]);
	}
	
}
/*
** Function: twoDice
** Description: determines the point value for two dice
** Parameters: int[]
** Pre-Conditions: array has valid memory
** Post-Conditions: returns point value
*/

int twoDice(int choiceArray[]){
	return oneDie(choiceArray[0]) + oneDie(choiceArray[1]);
}

/*
** Function: oneDie
** Description: determines the point value for one die
** Parameters: int[]
** Pre-Conditions: array has valid memory
** Post-Conditions: returns point value
*/

int oneDie(int choiceArray){
	if(choiceArray == 1){
		return 100;
	}else if(choiceArray == 5){
		return 50;
	}else{
		return 0;
	}

}

