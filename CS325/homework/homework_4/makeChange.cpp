/*
  Program: makeChange.cpp
  Author: Nathaniel Mohr
  Description:
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

void createChange(int, int, int, vector<int>&);

int main(){
  ifstream rf;
  ofstream wf;
  int temp, num_tests;
  vector<int> data_vec;
  vector<int> temp_vec;
  vector< vector<int> > results;

  // Read in from data.txt
  // Indexes of variables in data_vec
  // c of i - data_vec[3i]
  // k of i - data_vec[3i+1]
  // n of i - data_vec[3i+2]
  rf.open("data.txt");
  while(rf >> temp){
    data_vec.push_back(temp);
  }
  rf.close();

  num_tests = data_vec.size() / 3;

  for(int i = 0; i < num_tests; i++){
    temp_vec.clear();
    createChange(data_vec.at(3*i), data_vec.at(3*i+1), data_vec.at(3*i+2), temp_vec);
    results.push_back(temp_vec);
  }

  // Output data to change.txt
  wf.open("change.txt");
    for(int i = 0; i < num_tests; i++){
      temp = 1;
      for(int j = 0; j < results.at(i).size(); j++){
        if(j+1 < results.at(i).size() && results.at(i).at(j) == results.at(i).at(j+1)){
          temp++;
        }else{
          wf << results.at(i).at(j) << " " << temp << endl;
        }
      }
      wf << "~~~" << endl;
    }
  wf.close();

  return 0;
}

void createChange(int c, int k, int n, vector<int> &A){
  if(n == pow(c, k)){
    A.push_back(pow(c,k));
  }else if(n > pow(c, k)){
    A.push_back(pow(c,k));
    createChange(c,k,n-pow(c, k),A);
  }else if(n < pow(c, k)){
    createChange(c,k-1,n,A);
  }
}
