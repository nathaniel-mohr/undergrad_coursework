#include <iostream>
#include <stdlib.h>

using namespace std;

void towers(int disks, int b[][3], int fromCol, int toCol, int spare); 	//static
void towers(int disks, int **b, int size, int fromCol, int toCol, int spare);	//dynamic
int** initArray(int rows);
void fillArray(int **arr, int n);
void deleteArray(int **arr, int rows);
void printArray(int b[][3], int rows);	//static
void printArray(int **b, int rows);	//dynamic

int main(){
	string input = "";
	int disks = 0;
	int board[3][3] = {{1,0,0},{2,0,0},{3,0,0}};
	printArray(board, 3);
	cout << endl;
	towers(3, board, 0, 2, 1);
	
	cout << "Number of disks: ";
	cin >> disks;
	int** boardTwo = initArray(disks);
	fillArray(boardTwo, disks);
	printArray(boardTwo, disks);
	cout << endl;
	towers(disks, boardTwo, disks, 0, 2, 1);
	deleteArray(boardTwo, disks);	
	return 0;
}

void towers(int disk, int b[][3], int fromCol, int toCol, int spare){
	//if number of disks >= 1
	//	call towers(disk-1, b, fromCol, spare, toCol)
	//	move the disk
	//	print the board
	//	call towers(disk-1, b, spare, toCol, fromCol)
	if(disk >= 1){
		int temp = 0;
		towers(disk - 1, b, fromCol, spare, toCol);		
		for(int i = 0; i < 3; i++){
			if(b[i][fromCol] != 0){
				temp = b[i][fromCol];
				b[i][fromCol] = 0;
				break;
			}
		}
		for(int i = 2; i >= 0; i--){
			if(b[i][toCol] == 0){
				b[i][toCol] = temp;
				break;
			}
		}
		printArray(b, 3);
		cout << endl;
		towers(disk - 1, b, spare, toCol, fromCol);
	}

}

void towers(int disk, int **b, int size, int fromCol, int toCol, int spare){
	int temp = 0;
	if(disk >= 1){
		towers(disk - 1, b, size, fromCol, spare, toCol);
		for(int i = 0; i < size; i++){
			if(b[i][fromCol] != 0){
				temp = b[i][fromCol];
				b[i][fromCol] = 0;
				break;
			}
		}
		for(int i = size - 1; i >= 0; i--){
			if(b[i][toCol] == 0){
				b[i][toCol] = temp;
				break;
			}
		}

		printArray(b, size);
		cout << endl;
		towers(disk - 1, b, size, spare, toCol, fromCol);
	}

}

int** initArray(int rows){
	int **arr = new int*[rows];
	for(int i = 0; i < rows;i++){
		arr[i] = new int[3];
	}
	return arr;
}

void fillArray(int **arr, int n){
	for(int i = 0; i < n; i++){
		arr[i][0] = i+1;
	}
}

void deleteArray(int **arr, int rows){
	for(int i = 0; i < rows; i++){
		delete [] arr[i];
	}
	delete [] arr;
	arr = NULL;
}

void printArray(int b[][3], int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < 3; j++){
			cout << b[i][j] << " ";

		}
		cout << endl;
	}
}

void printArray(int **b, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < 3; j++){
			cout << b[i][j] << " ";

		}
		cout << endl;
	}
}
