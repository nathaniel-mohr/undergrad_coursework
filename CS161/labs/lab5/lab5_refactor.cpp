#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string getFloat();
float stringToFloat(string);
string getInt();
int stringToInt(string);

int main() {
	float current_offer = 0, future_offer = 0, interest = 0, m = 1, time = 0;
	string input;

	cout << "It looks like you have two offers. Let's calculate which one is worth more." << endl;
	
	cout << "\nCurrent Offer" << endl;
	input = getFloat();
	current_offer = stringToFloat(input);

	cout << "\nFuture Offer" << endl;
	input = getFloat();
	future_offer = stringToFloat(input);

	cout << "\nInterest Rate" << endl;
	input = getFloat();
	interest = stringToFloat(input);
	
	cout << "\nPlease provide the amount of time in years between the current offer and future offer: ";
	input = getInt();
	time = stringToInt(input);

	float val_current_offer = current_offer*(pow((1+(interest/m)),(time*m)));	
	float val_future_offer = future_offer/(pow((1+(interest/m)), (time*m))); 
	
	if (val_current_offer > val_future_offer) {
		cout << "\nTake the current offer" << endl;	
	}
	else if (val_current_offer < val_future_offer) {
		cout << "\nTake the future offer" << endl;	
	}	
	else {
		cout << "\nChoose which ever" << endl;	
	}
	

	return 0;	
}

string getFloat(){
	string input = "";
	bool flag = false;
	do{
		cout << "Enter the value: " << endl;
		getline(cin, input);
		flag = false;
		int count = 0;
		for(int i=0; i<input.length(); i++){
			if (input[i] < '0' || input[i] > '9') {
				if (input[i] == '.') {
					count++;
					if (count > 1) {
						flag = true;	
					}	
				}
				else {
					flag = true;
				}	
			} 	
		}
	} while (flag);
	return input;
}

float stringToFloat(string input){
	int count = 1, i = 0;
	float res = 0, val = 0, decimal = 0, ans = 0;

	for(i; i < input.length(); i++) {
		if (input[i] == '.')
			break;	
	}
	for(int j = i-1; j >= 0; j--) {
		val = ((int) input[j]) -48;
		res += val * pow(10, (i - 1 - j));
	}
	decimal = 0;
	count = 1;
	for(int k = i+1; k < input.length(); k++) {
		val = ((int) input[k]) - 48;
		decimal += val * pow(10, (-count));
		count++;
	}
	
	ans = res + decimal;
	return ans;
}

string getInt(){
	string input;
	bool flag = false;
	do{	
		cout << "Enter value: " << endl;
		getline(cin, input);
		flag = false;
		int count = 0;
		for(int i=0; i<input.length(); i++){
			if (input[i] < '0' || input[i] > '9') {
				flag = true;	
			}
		}
	} while (flag);
	return input;
}

int stringToInt(string input){
	int val = 0, res = 0;
	for(int i = (input.length()-1); i >= 0; i--) {
		val = ((int) input[i]) - 48;
		res +=  val * pow(10,(input.length() - i -1));
	}
	return res;
}
