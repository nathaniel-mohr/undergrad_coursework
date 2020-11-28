/*
  Program: badSortTime.cpp
  Author: Nathaniel Mohr
  Description:
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

float alpha = .6;

#define MAX_N 50000
#define ITERATION 5000
#define NUM_ARRAYS 3

void badSort(vector<int>&, int, int);

int main(){
  ofstream wf;
  int num_vars, temp;
  vector<int> temp_vec;
  float total, average;


  wf.open("badSortTime.txt");

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

      // Sort the array using merge sort
      badSort(temp_vec, 0, temp_vec.size() - 1);

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

void badSort(vector<int> &vec, int l, int r){
  if(l < r){
    //int id = rand() % 1000;
    //cout << "badSort " << id << " -- l: " << l << ", r: " << r << endl;
    int x, m;
    int n = r-l+1;
    //cout << id << " - n: " << n << endl;
    if(n == 2 && vec.at(l) > vec.at(r)){
      x = vec.at(l);
      vec.at(l) = vec.at(r);
      vec.at(r) = x;
    }else if(n > 2){
      m = ceil(alpha*n);
      //cout << id << " - m: " << m << endl;
      if(m == r) m -= 1;
      badSort(vec, l, l+m);
      badSort(vec, l+m+1, r-1);
      badSort(vec, l, l+m);
    }
  }
}
