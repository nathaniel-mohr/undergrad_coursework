#include <iostream>
#include <cstring>

using namespace std;

char* dynam(int length);
void getString(char *str, int length);
void setReplaceString(char *str, char *cop);
int getSearchReplace(char choice, char *str, char *cop);

int main(){
	char *orig, *cop;
	char choice;
	int length = 0;
	cout << "How many characters is your string?" << endl;
	cin >> length;
	orig = dynam(length);
	cop = dynam(length);
	while(cin.get() != '\n');
	getString(orig, length);
	strcpy(cop, orig);	
	setReplaceString(orig, cop);
	cout << "Choose a letter: ";
	choice = cin.get();
	cout << "Number of " << choice << " in string: " << getSearchReplace(choice, orig, cop) << endl;
	delete[] orig;
	delete[] cop;
}

char* dynam(int length){
	return new char[length + 1];
}

void getString(char *str, int length){
	
	cout << "Enter a string: ";
	cin.getline(str,length, '\n');
}

void setReplaceString(char *str, char *cop){
	for(int i = 0; i < strlen(str); i++){
		if(str[i] != ' '){
			cop[i] = '-';
		}
	}
	cout << "Dashed string: " << cop << endl;

}
int getSearchReplace(char choice, char *str, char *cop){
	int counter = 0;
	for(int i = 0; i < strlen(str); i++){
		if(str[i] == choice){
			cop[i] = choice;
			counter++;
		}
	}
	cout << "Jeopardy string: " << cop << endl;
	return counter;
}

