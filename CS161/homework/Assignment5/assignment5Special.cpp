#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool isInt(string input);
int getInt();
int stringToInt(string input);
int* initArray(int num);
string* initStrArray(int num);
void fillArray(int arr[], int num, int val);
void printArray(int arr[], int num);
void printScores(int scoreboard[], int players);
void printScores(int scoreboard[], string playerNames[], int players);
int* cutArray(int arr[], int startIndex, int newLength);
int* sortArray(int arr[], int length);
bool checkScoreboard(int scoreboard[], int players);
void playerTurn(int scoreboard[], int player);
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


int main(){
	srand(time(NULL));
	cout << "\t\tWELCOME TO FARKLE" << endl;
	cout << "How many players are going to play?" << endl;
	int players = getInt();
	int* scoreboard = initArray(players);
	string* playerNames;
	fillArray(scoreboard, players, 0);
	cout << "Do you want to name your players?" << endl;
	bool names = getAnswer();
	if(names == true){
		playerNames = initStrArray(players);
		for(int i = 0; i < players; i++){
			cout << "Enter player " << i+1 << "'s name: ";
			getline(cin, playerNames[i]);
		}
	}
	while(checkScoreboard(scoreboard, players) == true){
		for(int i = 0; i < players; i++){
			cout << endl;
			if(names == true){
				cout << "\t*** " << playerNames[i] << " ***" << endl;
				playerTurn(scoreboard, i);
				cout << endl;
				printScores(scoreboard, playerNames, players);
			}else{
				cout << "\t*** Player " << i+1 << " ***" << endl;
				playerTurn(scoreboard, i);
				cout << endl;

			}
		}

	}
	delete[] playerNames;
	delete[] scoreboard;
}

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

int getInt(){
	string input = "";
	do{
		cout << "Enter integer: ";
		getline(cin, input);
	}while(isInt(input) == false);
	return stringToInt(input);

}

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

int* initArray(int num){
	return new int[num];
}

string* initStrArray(int num){
	return new string[num];
}

void fillArray(int arr[], int num, int val){
	for(int i = 0; i < num; i++){
		arr[i] = val;
	}
}

void printArray(int arr[], int num){
	for(int i = 0; i < num; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printScores(int scoreboard[], int players){
	cout << "\tScoreboard:" << endl;
	cout << "        ------------" << endl;
	for(int i = 0; i < players; i++)
		cout << "\tPlayer " << i+1 << ":  " << scoreboard[i] << endl;
}

void printScores(int scoreboard[], string playerNames[], int players){
	cout << "\tScoreboard:" << endl;
	cout << "        ------------" << endl;
	for(int i = 0; i < players; i++)
		cout << "\t" << playerNames[i] << ":  " << scoreboard[i] << endl;
}

int* cutArray(int arr[], int startIndex, int newLength){
	int* temp = initArray(newLength);
	for(int i = 0; i < newLength; i++){
		temp[i] = arr[i+startIndex];
	}
	return temp;
}

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

bool checkScoreboard(int scoreboard[], int players){
	for(int i = 0; i < players; i++){
		if(scoreboard[i] < 10000){
			return true;
		}
	}
	return false;
}

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
	scoreboard[player] = runningTotal;
	delete[] diceArray;
}

int* diceRoll(int length){
	int *arr = new int[length];
	for(int i = 0; i < length; i++){
		arr[i] = rand() % 6 + 1;
	}
	return arr;
}

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

int twoDice(int choiceArray[]){
	return oneDie(choiceArray[0]) + oneDie(choiceArray[1]);
}

int oneDie(int choiceArray){
	if(choiceArray == 1){
		return 100;
	}else if(choiceArray == 5){
		return 50;
	}else{
		return 0;
	}

}

