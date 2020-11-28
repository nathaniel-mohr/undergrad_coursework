/*
  Program: badSort.cpp
  Author: Nathaniel Mohr
  Description: This program will read in a series of numbers in the format:
                num_vars var1 var2 ... var_num_vars
                from a file called data.txt
                The numbers will then be sorted using bad sort
                and written into a file called bad.out
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

float alpha;

void badSort(vector<int>&, int, int);

int main(int argc, char** argv){
  ifstream rf;
  ofstream wf;
  int num_vars, temp;
  vector< vector<int> > data_vec;
  vector<int> temp_vec;
  srand(time(NULL));

  alpha = atof(argv[1]);

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

  // Sort the array using bad sort
  for(int i = 0; i < data_vec.size(); i++){
    badSort(data_vec.at(i), 0, data_vec.at(i).size() - 1);
  }

  // Output sorted data to bad.out
  wf.open("bad.out");
  for(int i = 0; i < data_vec.size(); i++){
    for(int j = 0; j < data_vec.at(i).size(); j++){
      wf << data_vec.at(i).at(j) << " ";
    }
    wf << endl;
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
