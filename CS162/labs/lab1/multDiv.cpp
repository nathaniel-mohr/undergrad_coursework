#include <iostream>
#include <cstdlib>
#include <string>
#include "./multDiv.h"

using namespace std;

void getDimensions(int* m, int* n){
	do{
		cout << "Enter number of rows: ";
		cin >> *m;
	}while(*m <= 0);
	do{
		cout << "Enter number of cols: ";
		cin >> *n;
	}while(*n <= 0);
}

bool isValidDimensions(char* m, char* n){
	int i = 0;
	while(m[i] != '\0'){
		if(m[i] < '0' || m[i] > '9'){
			return false;
		}
		i++;
	}
	i = 0;
	while(n[i] != '\0'){
		if(n[i] < '0' || n[i] > '9'){
			return false;
		}
		i++;
	}
	return true;
}

multDivValues** createTable(int m, int n){
	multDivValues** table = new multDivValues*[m];
	for(int i = 0; i < m; i++){
		table[i] = new multDivValues[n];
	}
	return table;
}

void setMultValues(multDivValues** table, int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			table[i][j].mult = (i+1)*(j+1);
		}
	}
}

void setDivValues(multDivValues** table, int m, int n){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			table[i][j].div = (i+1)/(float)(j+1);
		}
	}

}

void printMult(multDivValues** table, int m, int n){
	cout << "MULTIPLICATION TABLE" << endl;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout << table[i][j].mult << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printDiv(multDivValues** table, int m, int n){
	cout << "DIVISION TABLE" << endl;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout << table[i][j].div << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void deleteTable(multDivValues** table, int m){
	for(int i = 0; i < m; i++){
		delete[] table[i];
	}
	delete[] table;
	table = NULL;
}

bool getChoice(){
	int choice = -1;
	cout << "Would you like to see a different size matrix (1-yes, 0-no)? ";
	do{
		cin >> choice;
	}while(choice != 1 && choice != 0);
	if(choice == 1)
		return true;
	else
		return false;
}
