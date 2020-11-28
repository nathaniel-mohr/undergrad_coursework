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

using namespace std;

void mergesort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);

int main(){
  ifstream rf;
  ofstream wf;
  int num_vars, temp;
  vector< vector<int> > data_vec;
  vector<int> temp_vec;

  // Read in the numbers from data.txt, adding each line into a new vector of ints
  rf.open("data.txt");
  while(rf >> num_vars){
    temp_vec.clear();
    for(int i = 0; i < num_vars; i++){
      rf >> temp;
      temp_vec.push_back(temp);
    }
    data_vec.push_back(temp_vec);
  }
  rf.close();

  // Sort the array using merge sort
  for(int i = 0; i < data_vec.size(); i++){
    mergesort(data_vec.at(i), 0, data_vec.at(i).size() - 1);
  }

  // Output sorted data to merge.out
  wf.open("merge.out");
  for(int i = 0; i < data_vec.size(); i++){
    for(int j = 0; j < data_vec.at(i).size(); j++){
      wf << data_vec.at(i).at(j) << " ";
    }
    wf << endl;
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
