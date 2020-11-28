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

using namespace std;

int main(){
  ifstream rf;
  ofstream wf;
  int num_vars, temp;
  vector< vector<int> > data_vec;
  vector< vector<int> > sort_vec;
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
    for(int j = 1; j < data_vec.at(i).size(); j++){
      int key = data_vec.at(i).at(j);
      int k = j - 1;
      while(k >= 0 && data_vec.at(i).at(k) > key){
        data_vec.at(i).at(k+1) = data_vec.at(i).at(k);
        k--;
      }
      data_vec.at(i).at(k+1) = key;
    }
  }

  // Output sorted data to merge.out
  wf.open("insert.out");
  for(int i = 0; i < data_vec.size(); i++){
    for(int j = 0; j < data_vec.at(i).size(); j++){
      wf << data_vec.at(i).at(j) << " ";
    }
    wf << endl;
  }
  wf.close();

  return 0;
}
