#include <iostream>
#include <cstdlib>
#include <string>

struct multDivValues{
	int mult;
	float div;
};
void getDimensions(int* m, int* n);
bool isValidDimensions(char* m, char* n);
multDivValues** createTable(int m, int n);
void setMultValues(multDivValues** table, int m, int n);
void setDivValues(multDivValues** table, int m, int n);
void printMult(multDivValues** table, int m, int n);
void printDiv(multDivValues** table, int m, int n);
void deleteTable(multDivValues** table, int m);
bool getChoice();

