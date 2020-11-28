#include <iostream>
#include <string>
using namespace std;

int main() {
	string my_str;
	cout << "Please give a string without spaces: ";
	cin >> my_str;
	int length = my_str.length();
	bool flag = false;
	for(int i=0; i<(length/2); i++) {
		if (my_str[i] == my_str[length-1-i]) {
			flag = true;	
		}else{
			flag = false;
		}
	}
	if (flag) {
		cout << "It's a palindrome" << endl;	
	}
	else {
		cout << "It's not a palindrome" << endl;	
	}

	return 0;	
}
