#include <iostream>
#include <string>

using namespace std;

int a_to_i(char character);
char i_to_a(int decimal);

int main(){
	char character;
	int decimal;

	cout << "Enter a character" << endl;
	cin >> character;
	cout << "The decimal equivalent: " << a_to_i(character) << endl;

	cout << "Enter an integer from 0 to 127" << endl;
	cin >> decimal;
	cout << "The character that corresponds to that integer: " << i_to_a(decimal) << endl;

}



/*
 * Function: a_to_i
 * Description: turns a character into a decimal value
 * Parameters: char character
 * Pre-Conditions: the input is a character
 * Post-Conditions: returned the decimal value of the character
 */
int a_to_i(char character){
	if(character >= 48 && character <= 57){
		return (int) character;	
	}else{
		return 0;
	}
}




/*
 * Function: i_to_a
 * Description: turns a decimal value into a character
 * Parameters: int decimal
 * Pre-Conditions: the input is an integer
 * Post-Conditions: returned the character which represents the decimal value
 */

char i_to_a(int decimal){
	return (char) decimal;
}
