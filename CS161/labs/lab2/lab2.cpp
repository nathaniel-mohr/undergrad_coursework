#include <iostream>
#include <climits>
#include <cmath>

#define MIN 0
using namespace std;

int main() {
	int userByte = 0;
	int bits;	

	cout << "Signed int max is: " << INT_MAX << endl;
	cout << "Signed int min is: " << INT_MIN << endl;
	cout << "Unsigned int max is: " << UINT_MAX << endl;
	cout << "Unsigned int min is: " << MIN << endl;

	cout << "\nSigned short max is: " << SHRT_MAX << endl;
        cout << "Signed short min is: " << SHRT_MIN << endl;
        cout << "Unsigned short max is: " << USHRT_MAX << endl;
	cout << "Unsigned short min is: " << MIN << endl;

	cout << "\nSigned long max is: " << LONG_MAX << endl;
        cout << "Signed long min is: " << LONG_MIN << endl;
        cout << "Unsigned long max is: " << ULONG_MAX << endl;
	cout << "Unsigned long min is: "<< MIN << endl;

	cout << "\nHow many bytes do you want to use?" << endl;
	cin >> userByte;
	bits = userByte * 8;
	cout << "The maximum signed number is: " << pow(2, bits-1) - 1 << endl;
	cout << "The minimum signed number is: " << -pow(2, bits-1) << endl;
	cout << "The maximum unsigned number is: " << pow(2,bits) - 1 << endl;
	cout << "The minimum signed number is: " << MIN << endl;
}
