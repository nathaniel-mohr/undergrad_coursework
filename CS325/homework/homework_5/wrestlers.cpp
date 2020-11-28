/*
  Program: wrestlers.cpp
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

int wrestlerNum(string wrestler, string* wrestlers, int size);

int main(int argc, char** argv){
  ifstream rf;
  int num_rivalries, num_wrestlers;
  string temp;

  rf.open(argv[1]);

  rf >> num_wrestlers;
  string* wrestlers = new string[num_wrestlers*2];
  for(int i = 0; i < num_wrestlers*2; i+=2){
    rf >> temp;
    wrestlers[i] = temp;
  }

  rf >> num_rivalries;
  string* rivalries = new string[num_rivalries*2];
  for(int i = 0; i < num_rivalries*2; i++){
    rf >> temp;
    rivalries[i] = temp;
  }

  rf.close();

  wrestlers[1] = "Babyfaces";

  for(int i = 0; i < num_rivalries*2 - 1; i+=2){
    int wrestlerOne = wrestlerNum(rivalries[i], wrestlers, num_wrestlers*2);
    int wrestlerTwo = wrestlerNum(rivalries[i+1], wrestlers, num_wrestlers*2);

    if(wrestlers[wrestlerOne+1] == wrestlers[wrestlerTwo+1] && wrestlers[wrestlerOne+1] != ""){
      cout << "Impossible" << endl;
      return 0;
    }else if(wrestlers[wrestlerOne+1] == "" && wrestlers[wrestlerTwo+1] == ""){
      wrestlers[wrestlerOne+1] = "Babyfaces";
      wrestlers[wrestlerTwo+1] = "Heels";
    }else if(wrestlers[wrestlerOne+1] == ""){
      if(wrestlers[wrestlerTwo+1] == "Babyfaces"){
        wrestlers[wrestlerOne+1] = "Heels";
      }else{
        wrestlers[wrestlerOne+1] = "Babyfaces";
      }
    }else if(wrestlers[wrestlerTwo+1] == ""){
      if(wrestlers[wrestlerOne+1] == "Babyfaces"){
        wrestlers[wrestlerTwo+1] = "Heels";
      }else{
        wrestlers[wrestlerTwo+1] = "Babyfaces";
      }
    }
  }

  for(int i = 0; i < num_wrestlers*2 - 1; i+=2){
    if(wrestlers[i+1] == ""){
      wrestlers[i+1] = "Babyfaces";
    }
  }
  cout << "Yes Possible" << endl;
  cout << "Babyfaces:";
  for(int i = 0; i < num_wrestlers*2-1; i+=2){
    if(wrestlers[i+1] == "Babyfaces") cout << " " << wrestlers[i];
  }
  cout << endl;
  cout << "Heels:";
  for(int i = 0; i < num_wrestlers*2-1; i+=2){
    if(wrestlers[i+1] == "Heels") cout << " " << wrestlers[i];
  }
  cout << endl;

  return 0;
}

int wrestlerNum(string wrestler, string* wrestlers, int size){
  for(int j = 0; j < size; j++){
    if(wrestlers[j] == wrestler){
      return j;
    }
  }
}
