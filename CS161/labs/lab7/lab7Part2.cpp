#include <iostream>
#include <string>

using namespace std;

int* byValue();
void byReference(int*& x);
void byPointer(int** x);
void changeVal(int** x, int num);
void del(int*& x);

int main(){
	int* x;
	x = byValue();
	//byReference(x);
	//byPointer(&x);
	*x = 42; 
	cout << *x << endl;
	del(x);
}

int* byValue(){
	return new int;	
}

void byReference(int*& x){
	x = new int;
}

void byPointer(int** x){
	*x = new int;
}

void changeVal(int** x, int num){
	*x = &num;
}

void del(int*& x){
	delete x;
	x = NULL;
}

