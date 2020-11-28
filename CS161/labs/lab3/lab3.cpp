#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
	srand(time(NULL));

	int passLength = 0;
	int letter = 0;
	int numCap = 0;
	int numLow = 0;
	int numNum = 0;
	string password = "";	
	
	cout << "Welcome to the Password Generator!" << endl;

	cout << "\nHow long do you want your password to be?" << endl;
	cin >> passLength;

	cout << "Do you want letters in your password? (1 yes, 0 no)" << endl;
	cin >> letter;

	if(letter == 1) {
		cout << "How many capital letters do you want?" << endl;
		cin >> numCap;

		cout << "How many lowercase letters do you want?" << endl;
		cin >> numLow;
	}

	cout << "How many numbers do you want?" << endl;
	cin >> numNum;

	while(numCap > 0){
		password += (rand() % 27 + 65);
		numCap--;
	}

	while(numLow > 0){
                password += (rand() % 27 + 97);
                numLow--;
        }

	while(numNum > 0){
		password += (rand() % 10 + 48);
		numNum--;
	}
	
	cout << password << endl;

}
