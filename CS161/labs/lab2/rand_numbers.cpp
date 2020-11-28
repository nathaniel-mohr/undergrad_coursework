#include <iostream>
#include <ctime> 	//included to allow time() to be used 
#include <cstdlib>	//included to allow rand() and srand() to be used

using namespace std;

int main() {
	int x;			// variable to hold our random integer
	srand(time(NULL)); 	// seeds random number generator. DO THIS JUST ONCE
	
	x = rand();
	cout << "x = " << x << endl;

	x = rand();
	cout << "x = " << x << endl;

	x = rand() % 6;
	cout << "x between 0 and 5 = " << x << endl;

	if(x == 0) {
		cout << "Bummer, I'm zero!!" << endl;
	}else if(x % 2 == 1) {
		cout << "I'm an odd number" << endl;
	}else{
		cout << "I'm an even number" << endl;
	}
}
