/*
  Program: insertsort.cpp
  Author: Nathaniel Mohr
  Description: This program will read in a series of numbers in the format:
                num_vars var1 var2 ... var_num_vars
                from a file called data.txt
                The numbers will then be sorted using insertion sort
                and written into a file called insert.out
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

#define MAX_N 50000
#define ITERATION 5000
#define NUM_ARRAYS 3

void insertion_sort(vector<int>&);

int main(){
  ofstream wf;
  int num_vars, temp;
  vector<int> temp_vec;
  float total, average;

  wf.open("insertTime.txt");

  for(int i = ITERATION; i <= MAX_N; i+=ITERATION){
    wf << i;
    cout << "Array Size: " << i;

    total = 0;
    average = 0;

    // Create NUM_ARRAYS arrays of each size
    for(int j = 0; j < NUM_ARRAYS; j++){
      // Populate array
      srand(time(NULL));
      temp_vec.clear();
      for(int k = 0; k < i; k++){
        temp = rand() % 10000;
        temp_vec.push_back(temp);
      }

      clock_t t1, t2;

      t1 = clock();

      // Sort the array using insertion sort
      insertion_sort(temp_vec);

      t2 = clock();
      float diff ((float)t2 - (float) t1);
      float seconds = diff / CLOCKS_PER_SEC;
      total += seconds;

      wf << " " << seconds;
      cout << " Time #" << j+1 << ": " << seconds;

    }
    average = total / NUM_ARRAYS;
    wf << " " << average << endl;
    cout << " Average: " << average << endl;
  }

  wf.close();

  return 0;
}

void insertion_sort(vector<int> &temp_vec){
  for(int j = 1; j < temp_vec.size(); j++){
    int key = temp_vec.at(j);
    int k = j - 1;
    while(k >= 0 && temp_vec.at(k) > key){
      temp_vec.at(k+1) = temp_vec.at(k);
      k--;
    }
    temp_vec.at(k+1) = key;
  }
}
