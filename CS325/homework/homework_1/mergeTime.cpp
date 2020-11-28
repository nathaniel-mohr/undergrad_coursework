/*
  Program: mergesort.cpp
  Author: Nathaniel Mohr
  Description: This program will read in a series of numbers in the format:
                num_vars var1 var2 ... var_num_vars
                from a file called data.txt
                The numbers will then be sorted using merge sort
                and written into a file called merge.out
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

void mergesort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);

int main(){
  ofstream wf;
  int num_vars, temp;
  vector<int> temp_vec;
  float total, average;


  wf.open("mergeTime.txt");

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
      mergesort(temp_vec, 0, temp_vec.size() - 1);

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

void mergesort(vector<int> &vec, int l, int r){
  if(l < r){
    // find midpoint
    int m = l + (r-l) / 2;
    // mergesort left half
    mergesort(vec, l, m);
    // mergesort right half
    mergesort(vec, m+1, r);
    // merge both halves
    merge(vec, l, m, r);
  }
}

void merge(vector<int> &vec, int l, int m, int r){
  int i, j, k;
  int n1 = m - l + 1; // size of subarray from l to m
  int n2 = r - m;     // size of subarray from m+1 to r

  // Create subvectors
  vector<int> left;
  vector<int> right;

  for(i = 0; i < n1; i++){
    left.push_back(vec.at(l+i));
  }
  for(j = 0; j < n2; j++){
    right.push_back(vec.at(m+1+j));
  }

  i = 0; // index of left subarray
  j = 0; // index of right subarray
  k = l; // index of sorted array

  // Merge two arrays together as long as both indices are not beyond their bounds
  while(i < n1 && j < n2){
    // If current element in left array is smaller, add to sorted array
    if(left.at(i) <= right.at(j)){
      vec.at(k) = left.at(i);
      i++;
    }else{
      vec.at(k) = right.at(j);
      j++;
    }
    k++;
  }

  // Copy over any remaining elements
  while(i < n1){
    vec.at(k) = left.at(i);
    i++;
    k++;
  }
  while(j < n2){
    vec.at(k) = right.at(j);
    j++;
    k++;
  }
}
