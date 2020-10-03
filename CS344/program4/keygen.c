// Program: keygen.c
// Author: Nathaniel Mohr
// Arguments: keylength
// Description: Generate a random key of length specified by user
//              using A-Z and SPACE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
  srand(time(NULL));
  int characterNum, i = 0;
  char newCharacter;

  // Add a random character as many times as the user specified
  for(i = 0; i < atoi(argv[1]); i++){
    characterNum = rand() % 27;
    // If the random number is 26, then new character is a space
    if(characterNum == 26){
      newCharacter = ' ';
    // Else it is the corresponding ASCII value
    }else{
      newCharacter = (char) (characterNum + 65);
    }
    // Add the new character to the output
    printf("%c", newCharacter);
  }

  printf("\n");

  return 0;
}
