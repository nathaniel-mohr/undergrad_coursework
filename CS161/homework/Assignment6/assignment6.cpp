/*
** Program Filename: assignment6
** Author: Nathaniel Mohr
** Date: March 12, 2018
** Description: Game of Checkers
** Input: User input for movement of pieces
** Output: Game of checkers
*/

#include <iostream>
#include <string>

using namespace std;

bool isInt(string num);
bool isNum(char prompt);
bool isCapital(char prompt); 
int stringToInt(string prompt);
int getInt();
string** initArray(int rows);
void fillBoard(string** playerOne, string** playerTwo, int rows);
void printBoard(string** playerOne, string** playerTwo, int rows);
void printArray(string** arr, int rows);
void deleteArray(string**, int rows);
void playerTurn(string** playerOne, string** playerTwo, int player, int rows);
bool isPiece(string** playerOne, string** playerTwo, int player, int row, int col);
bool isSpace(string move);
int noPieces(string** playerOne, string** playerTwo, int rows);

/*
** Function: main
** Description: runs a game of checkers
** Parameters: command line arguments
** Pre-Conditions: none
** Post-Conditions: game of checkers
*/

int main(int argc, char** argv){
	int rows, player = 0;
	if(argc != 2 || isInt(argv[1]) == false){
		cout << "Size of board: " << endl;
		rows = getInt();
	}else
		rows = stringToInt(argv[1]);

	string **playerOne = initArray(rows);
	string **playerTwo = initArray(rows);
	fillBoard(playerOne,playerTwo,rows);

	printBoard(playerOne,playerTwo,rows);

	/*
	while(noPieces(playerOne,playerTwo,rows) == 0){
		playerTurn(playerOne,playerTwo,(i%2),rows);
		printBoard(playerOne,playerTwo,rows);i
		i++;	
	}
	*/

	deleteArray(playerOne,rows);
	deleteArray(playerTwo,rows);
}

/*
** Function: isInt
** Description: determines if a string is an integer
** Parameters: string
** Pre-Conditions: none
** Post-Conditions: string is an integer
*/

bool isInt(string num){
	int neg = 0;
	if(num[0] == '-'){
		neg = 1;
	}
	for(int i = neg; i < num.length(); i++){			
		if(num[i] < 48 || num[i] > 57){
			return false;
		}
	}
	return true;
}

/*
** Function: isNum
** Description: determines if a character is a number
** Parameters: char
** Pre-Conditions: none
** Post-Conditions: character is a number
*/

bool isNum(char prompt){
	if(prompt < '0' || prompt > '9'){
		return false;
	}
	return true;
}

/*
** Function: isCapital
** Description: determines if a character is a capital letter
** Parameters: char
** Pre-Conditions: none
** Post-Conditions: character is a capital letter
*/

bool isCapital(char prompt){
	if(prompt < 'A' || prompt > 'Z'){
		return false;
	}
	return true;
}

/*
** Function: stringToInt
** Description: converts a string to an integer
** Parameters: string
** Pre-Conditions: string is an integer
** Post-Conditions: integer equivalence is found
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
** Function: getInt
** Description: prompts the user for a string until it is an integer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: string is an integer
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
** Function: initArray
** Description: initializes a 2D array on the heap of size rows*rows
** Parameters: int
** Pre-Conditions: none
** Post-Conditions: memory for 2D array on heap
*/

string** initArray(int rows){
	string **arr = new string*[rows];
	for(int i = 0; i < rows; i++){
		arr[i] = new string[rows];
	}
	return arr;
}

/*
** Function: printBoard
** Description: prints a checker board with player pieces
** Parameters: pieces of both players and the size of board
** Pre-Conditions: arrays have valid memory and size given is accurate
** Post-Conditions: board is printed
*/

void printBoard(string** playerOne, string** playerTwo, int rows){
	cout << "    ";
	for(int i=0; i<rows; i++){
		cout << "| " << (char)(i+65) << " ";
	}
	cout << endl;
	for(int i=0; i<rows; i++){
		for(int j=0; j<rows; j++) {
			if(j == 0){
				cout << "| " << i+1 << " ";
			}
			if (i%2 == 0 && j%2 == 0){
				cout << "|\033[30;47m   ";
			}else if (i%2 == 1 && j%2 == 1){
				cout << "|\033[30;47m   ";
			}else{
				if(playerOne[i][j].length() != 0){
					cout << "|\033[31;40m " << playerOne[i][j] << " ";  
				}else if(playerTwo[i][j].length() != 0){
					cout << "|\033[0m " << playerTwo[i][j] << " "; 	
				}else{
					cout << "|\033[0m   ";
				}
			}
			cout << "\033[0m";
		}
		cout << endl;
	}

}

/*
** Function: fillBoard
** Description: gives pieces to the players corresponding to the size of the board
** Parameters: 2 arrays and size of them
** Pre-Conditions: arrays have valid memory and size is accurate
** Post-Conditions: arrays are filled with accurate number of pieces
*/

void fillBoard(string** playerOne, string** playerTwo, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < rows; j++){
			if((i%2!=0 || j&2!=0) && (i%2!=1 || j%2!=1)){
				if(i > rows / 2){
					playerTwo[i][j] = "0";
				}else if(i < rows / 2 - 1){
					playerOne[i][j] = "0";
				}
			}
		}
	}
}

/*
** Function: printArray
** Description: prints a 2D array
** Parameters: array and size
** Pre-Conditions: array has valid memory and size is accurate
** Post-Conditions: array printed
*/

void printArray(string** arr, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < rows; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

/*
** Function: deleteArray
** Description: deletes a 2D array
** Parameters: array and size
** Pre-Conditions: array has valid memory and size is accurate
** Post-Conditions: memory of array is deleted
*/

void deleteArray(string** arr, int rows){
	for(int i = 0; i < rows; i++){
		delete[] arr[i];
	}
	delete[] arr;
	arr = NULL;
}

/*
** Function: playerTurn
** Description: runs the turn of a single player
** Parameters: 2 arrays and 2 ints
** Pre-Conditions: arrays have valid memory
** Post-Conditions: turn is taken
*/

void playerTurn(string** playerOne, string** playerTwo, int player, int rows){
	//print whose turn
	//get piece to move
	//get move
	//print board
}

/*
** Function: isPiece
** Description: determines if a piece is at the given location 
		and that it belongs to the player trying to access it
** Parameters: 2 arrays and 3 ints
** Pre-Conditions: arrays have valid memory
** Post-Conditions: check is determined
*/

bool isPiece(string** playerOne, string** playerTwo, int player, int row, int col){
	//if there is not a piece at [row][col]
	//	return false	
}

/*
** Function: isSpace
** Description: determines if the string is in the proper "A3" format
** Parameters: string
** Pre-Conditions: none
** Post-Conditions: check is determined
*/

bool isSpace(string move){
	if(move.length() != 2){
		return false;
	}else if(isCapital(move[0]) == false){
		return false;
	}else if(isNum(move[1]) == false){
		return false;
	}else{
		return true;
	}
}

/*
** Function: noPieces
** Description: determines which player, if any has no pieces
** Parameters: 2 arrays and size
** Pre-Conditions: arrays have valid memory
** Post-Conditions: corresponding number is returned
*/

int noPieces(string** playerOne, string** playerTwo, int rows){
	//returns which player has no pieces, and 0 if both have pieces
	int piecesOne = 0, piecesTwo = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < rows; j++){
			if(playerOne[i][j].length() > 0)
				piecesOne++;
			if(playerTwo[i][j].length() > 0)
				piecesTwo++;	
		}
	}
	if(piecesOne == 0){
		return 1;
	}else if(piecesTwo == 0){
		return 2;
	}else{
		return 0;
	}
}
