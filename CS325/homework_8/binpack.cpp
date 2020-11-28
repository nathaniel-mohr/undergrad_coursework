/*
  Program: binpack.cpp
  Author: Nathaniel Mohr
  Description:
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

void mergesort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);
int binFill(vector<int>);
int firstFit(vector<int>, int);
int firstFitDec(vector<int>, int);
int bestFit(vector<int>, int);

int main(){
  ifstream rf;
  int numTrials, numVars, temp;
  vector< vector<int> > data_vec;
  vector<int> temp_vec;
  vector<int> capacities;

  rf.open("bin.txt");
  while(rf >> numTrials){
    rf >> temp;
    capacities.push_back(temp);
    rf >> numVars;
    temp_vec.clear();
    for(int i = 0; i < numVars; i++){
      rf >> temp;
      temp_vec.push_back(temp);
    }
    data_vec.push_back(temp_vec);
  }
  rf.close();

  for(int i = 0; i < numTrials; i++){
    cout << "Test Case " << i+1;
    cout << " First Fit: " << firstFit(data_vec.at(i), capacities.at(i));
    cout << ", First Fit Decreasing: " << firstFitDec(data_vec.at(i), capacities.at(i));
    cout << ", Best Fit: " << bestFit(data_vec.at(i), capacities.at(i)) << endl;
  }

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

int binFill(vector<int> bin){
  int sum = 0;
  for(int i = 0; i < bin.size(); i++){
    sum += bin.at(i);
  }
  return sum;
}

int firstFit(vector<int> items, int capacity){
  vector< vector<int> > bins;
  bool inBin = false;
  vector<int> temp;

  for(int i = 0; i < items.size(); i++){
    for(int j = 0; j < bins.size(); j++){
      if(items.at(i) < capacity - binFill(bins.at(j))){
        bins.at(j).push_back(items.at(i));
        inBin = true;
      }
    }
    if(!inBin){
      temp.clear();
      temp.push_back(items.at(i));
      bins.push_back(temp);
    }
    inBin = false;
  }
  return bins.size();
}

int firstFitDec(vector<int> items, int capacity){
  mergesort(items, 0, items.size()-1);
  return firstFit(items, capacity);
}
int bestFit(vector<int> items, int capacity){
  vector< vector<int> > bins;
  bool inBin = false;
  int binNum = -1;
  int excess = 0;
  int min = 0;
  vector<int> temp;

  for(int i = 0; i < items.size(); i++){
    min = capacity - binFill(bins.at(0)) - items.at(i);
    for(int j = 0; j < bins.size(); j++){
      excess = capacity - binFill(bins.at(j)) - items.at(i);
      if(excess < min){
        min = excess;
        binNum = j;
      }
    }
    if(binNum != -1){
      bins.at(binNum).push_back(items.at(i));
      inBin = true;
    }
    if(!inBin){
      temp.clear();
      temp.push_back(items.at(i));
      bins.push_back(temp);
    }
    inBin = false;
    binNum = -1;
  }
  return bins.size();
}
