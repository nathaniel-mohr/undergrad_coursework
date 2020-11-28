#include <iostream>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

int fib_iter(int);
int fib_recur(int);

int fib_iter(int n){
	int total = 0, prev1 = 1, prev2 = 0;
	
	for(int i = 0; i < n - 1; i++){
		total = prev2 + prev1;
		prev2 = prev1;
		prev1 = total;
	}
	return total;
}

int fib_recur(int n){
	if(n == 0){
		return n;
	}
	if(n == 1){
		return n;
	}
	return fib_recur(n - 2) + fib_recur(n - 1);
}

int stairs(int n){
	if(n == 0){
		return 0;
	}
	if(n == 1){
		return 1;
	}
	if(n == 2){
		return 2;
	}
	return stairs(n-2) + stairs(n-1);
}

int main(){
	typedef struct timeval time;
	time stop, start;

	gettimeofday(&start, NULL);
	cout << "Fibonacci Iteration 1 : " << fib_iter(1) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;


	gettimeofday(&start, NULL);
	cout << "Fibonacci Recursion 1 : " << fib_recur(1) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;
	
	gettimeofday(&start, NULL);
	cout << "Fibonacci Iteration 5 : " << fib_iter(5) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;


	gettimeofday(&start, NULL);
	cout << "Fibonacci Recursion 5 : " << fib_recur(5) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;

	gettimeofday(&start, NULL);
	cout << "Fibonacci Iteration 15 : " << fib_iter(15) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;


	gettimeofday(&start, NULL);
	cout << "Fibonacci Recursion 15 : " << fib_recur(15) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;

	gettimeofday(&start, NULL);
	cout << "Fibonacci Iteration 25 : " << fib_iter(25) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;


	gettimeofday(&start, NULL);
	cout << "Fibonacci Recursion 25 : " << fib_recur(25) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;
	
	gettimeofday(&start, NULL);
	cout << "Fibonacci Iteration 45 : " << fib_iter(45) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;


	gettimeofday(&start, NULL);
	cout << "Fibonacci Recursion 45 : " << fib_recur(45) << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;

	cout << "Stairs(4): " << stairs(4) << endl;
	cout << "Stairs(5): " << stairs(5) << endl;

	return 0; 
}
