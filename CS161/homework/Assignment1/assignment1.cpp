/*
 * Program Filename: assignment1.cpp
 * Author: Nathaniel Mohr
 * Date: 1/10/18
 * Description: Print the solutions to equations, labeling work along the way
 * Input: None
 * Output: Prints to the screen
 */

#include <math.h>
#include <iostream>
using namespace std;

int main() {
	int x = 0;
	float equationOne;
	float equationTwo;

	cout << "1. Find cos(2/3):" << endl;

	cout << "   cos(2/3) is " <<  cos(2.0/3) << endl;

	cout << "\n2. Find 2sin(2/3):" << endl;
	cout << "   2sin(2/3) is " << (2 * sin(2.0/3)) << endl;

	cout << "\n3. Find tan(-3/4):" << endl;
	cout << "   tan(-3/4) is " << tan(-3.0/4) << endl;

	cout << "\n4. Find log base 10 of 55:" << endl;
	cout << "   log base 10 of 55 is " << (log10(55)) << endl;

	cout << "\n5. Find ln(60):" << endl;
	cout << "   ln(60) is " << log(60) << endl;

	cout << "\n6. Find the log base 2 of 15:" << endl;
	cout << "   ln(x) = " << log(15) << endl;
	cout << "   ln(b) = " << log(2) << endl;
	cout << "   ln(x) / ln(b) = " << log(15) / log(2) << endl;

	cout << "\n\nComplete the following expressions with x=1, x=10, and x=100" << endl;
	cout << "     3 ^ sinx   and   log base 2 of ((x ^ 2) + 1)" << endl;

	cout << "\n  With x=1:" << endl;
	x = 1;
	equationOne = pow(3, sin(x));
	equationTwo = log((x * x)+1) / log(2);
	cout << "  3 ^ sinx = " << equationOne << endl;
	cout << "  log base 2 of ((x ^ 2) + 1) = " << equationTwo << endl;

	cout << "\n  With x=10:" << endl;
	x = 10;
	equationOne = pow(3, sin(x));
        equationTwo = log((x * x)+1) / log(2);
	cout << "  3 ^ sinx = " << equationOne << endl;
	cout << "  log base 2 of ((x ^ 2) + 1) = " << equationTwo << endl;

	cout << "\n  With x=100:" << endl;
        x = 100;
	equationOne = pow(3, sin(x));
        equationTwo = log((x * x)+1) / log(2);
        cout << "  3 ^ sinx = " << equationOne << endl;
        cout << "  log base 2 of ((x ^ 2) + 1) = " << equationTwo << endl;

	return 0;
}
	
