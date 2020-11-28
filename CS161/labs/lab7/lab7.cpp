#include <iostream>
#include <string>

using namespace std;

void getString(string *str);
void setReplaceString(string str, string *cop);
int getSearchReplace(char choice, string str, string & cop);

int main(){
	string orig = "", cop = "";
	char choice;
	getString(&orig);
	cop = orig;
	setReplaceString(orig, &cop);
	cout << "Choose a letter: ";
	cin >> choice;
	cout << "Number of " << choice << " in string: " << getSearchReplace(choice, orig, cop) << endl;
}

void getString(string *str){
	cout << "Enter a string: ";
	getline(cin, (*str));
	
}
void setReplaceString(string str, string *cop){
	for(int i = 0; i < str.length(); i++){
		if(str[i] != ' '){
			(*cop)[i] = '-';
		}
	}
	cout << "Dashed string: " << *cop << endl;

}
int getSearchReplace(char choice, string str, string & cop){
	int counter = 0;
	for(int i = 0; i < str.length(); i++){
		if(str[i] == choice){
			cop[i] = choice;
			counter++;
		}
	}
	cout << "Jeopardy string: " << cop << endl;
	return counter;
}
