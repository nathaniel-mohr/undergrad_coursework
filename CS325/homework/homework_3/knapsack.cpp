/*
  Program: knapsack.cpp
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

int main(int argc, char** argv){
  vector<int> data_vec;
  int** B;
  ifstream rf;
  int temp;
  int capacity = atoi(argv[1]) + 1; // add one to create zeroth row of table
  int n;
  int count;

  // Read in weights and values from data.txt
  // data_vec has weight_i in data_vec[2i] and value_i at data_vec[2i+1]
  data_vec.clear();
  rf.open("data.txt");
  while(rf >> temp){
    data_vec.push_back(temp);
  }
  rf.close();

  // Get number of items and increase by 1 to have zeroth column of table
  n = data_vec.size() / 2;
  n++;

  // Initialize table
  B = new int*[n];
  for(int i = 0; i < n; i++){
    B[i] = new int[capacity];
  }

  for(int w = 0; w < capacity; w++){
    B[0][w] = 0;
  }

  // Knapsack algorithm
  for(int i = 0; i < n; i++){
    B[i][0] = 0;
    if(i > 0){
      for(int w = 0; w < capacity; w++){
        int b_i = data_vec.at(2 * (i-1)+1);
        int w_i = data_vec.at(2 * (i-1));
        if(w_i <= w){
          if(b_i + B[i-1][w - w_i] > B[i-1][w]){
            B[i][w] = b_i + B[i-1][w - w_i];
          }else{
            B[i][w] = B[i-1][w];
          }
        }else{
          B[i][w] = B[i-1][w];
        }
      }
    }
  }

  cout << "Greatest value: " << B[n-1][capacity-1] << endl;

  // Cleaning up memory
  for(int i = 0; i <= n; i++){
    delete[] B[i];
  }
  delete[] B;

  return 0;
}
