/*
  Adventure Program
  Author: Nathaniel Mohr

  This program will provide an interface for playing the game using the most recently generated rooms.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pthread.h>

// Declaration of room struct
struct Room{
  char name[9];           // Each name can be a max of 8 characters
  char roomType[11];      // "START_ROOM" is the longest room type at 10 characters
  int numConnections;
  char connections[6][9]; // Each room can have at max 6 connections
                          // and the name of each connection is at max 8 characters
};

struct Room activeRooms[7];
int numSteps;
char pathArray[100][9];
pthread_mutex_t lock;
pthread_t timeThread;

// Function prototypes
void determineDirectory(char*);
int nameStartsRight(char*);
void populateActiveRooms(char*);
struct Room* determineStart();
void playTurn(struct Room*);
void getChoice(struct Room*);
void* timeFunction(void*);
int validConnection(struct Room, char*);
void updateCurr(struct Room*, char*);
int isGameOver(struct Room);
void gameWon();
void displayRooms();

int main(){
  struct Room curr;
  char roomsDirectory[32];

  determineDirectory(roomsDirectory);

  if(pthread_mutex_init(&lock, NULL) != 0){
    fprintf(stderr, "mutex init has failed\n");
    return 1;
  }

  if(pthread_mutex_lock(&lock) != 0){
    fprintf(stderr, "mutex locking has failed\n");
    return 1;
  }

  if(pthread_create(&timeThread, NULL, &timeFunction, NULL) != 0){
    fprintf(stderr, "Thread creation has failed\n");
    return 1;
  }

  populateActiveRooms(roomsDirectory);
  updateCurr(&curr, determineStart()->name);

  while(isGameOver(curr) == 0){
      playTurn(&curr);
  }
  gameWon();

  pthread_mutex_unlock(&lock);
  pthread_mutex_destroy(&lock);

  return 0;

}

// Determines which mohrna.rooms.* directory is the oldest
void determineDirectory(char* roomsDirectory){
  struct stat statstruct;
  time_t newest = 0;
  struct dirent* de;
  DIR *dr = opendir(".");

  while((de = readdir(dr)) != NULL){
    if(nameStartsRight(de->d_name) == 1){
      stat(de->d_name, &statstruct);
      // If the current rooms directory is newer then
      // newest and roomsDirectory are updated
      if(statstruct.st_mtime > newest){
        newest = statstruct.st_mtime;
        strcpy(roomsDirectory, de->d_name);
      }
    }
  }

  closedir(dr);
}

// Determines if the file/directory name starts with "mohrna.rooms."
int nameStartsRight(char* name){
  int i;
  char* properStart = "mohrna.rooms.";
  if(strlen(name) < 12){
    return 0;
  }
  for(i = 0; i < 13; i++){
    if(name[i] != properStart[i]) return 0;
  }
  return 1;
}

// Parses through the files in the roomsDirectory to fill the activeRooms array
void populateActiveRooms(char* roomsDirectory){
  struct dirent* de;
  FILE* fp;
  char line[256], dirPath[32], filePath[50];
  int i, fileCount = 0, endOfBeginning = 0;

  sprintf(dirPath, "%s%s", "./", roomsDirectory);
  DIR *dr = opendir(dirPath);

  // Read through all files inside the rooms directory
  // besides . and ..
  while((de = readdir(dr)) != NULL){
    if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
      sprintf(filePath, "%s%s%s", dirPath, "/", de->d_name);
      fp = fopen(filePath, "r");
      while(fgets(line, sizeof(line), fp)){
        i = 0;

        // Determines where the variables being (could be hardcoded)
        endOfBeginning = 0;
        while(line[endOfBeginning] != ':'){
          endOfBeginning++;
        }
        endOfBeginning+=2;
        // Copies the room name
        if(line[5] == 'N'){
          while(line[endOfBeginning+i] != '\n'){
            activeRooms[fileCount].name[i] = line[endOfBeginning+i];
            i++;
          }
          activeRooms[fileCount].name[i] = '\0';
          // Copies the connections
        }else if(line[0] == 'C'){
          while(line[endOfBeginning+i] != '\n'){
            activeRooms[fileCount].connections[activeRooms[fileCount].numConnections][i] = line[endOfBeginning+i];
            i++;
          }
          activeRooms[fileCount].connections[activeRooms[fileCount].numConnections][i] = '\0';
          activeRooms[fileCount].numConnections++;
          // Copies the room type
        }else if(line[5] == 'T'){
          while(line[endOfBeginning+i] != '\n'){
            activeRooms[fileCount].roomType[i] = line[endOfBeginning+i];
            i++;
          }
          activeRooms[fileCount].roomType[i] = '\0';
        }
      }
      fileCount++;
      fclose(fp);
    }
  }

  closedir(dr);
}


// Determines what room is the starting room i.e roomType == "START_ROOM"
// Returns the room
struct Room* determineStart(){
  int i;
  for(i = 0; i < 7; i++){
    if(strcmp(activeRooms[i].roomType, "START_ROOM") == 0){
      return &activeRooms[i];
    }
  }
}

// Plays a single turn
void playTurn(struct Room* curr){
  int i;

  printf("CURRENT LOCATION: %s\n", curr->name);

  printf("POSSIBLE CONNECTIONS: ");
  for(i = 0; i < curr->numConnections - 1; i++){
    printf("%s, ", curr->connections[i]);
  }
  printf("%s.\n", curr->connections[curr->numConnections-1]);

  printf("WHERE TO? >");

  getChoice(curr);
}

// Gets user input to determine what room to go to next
// The value of curr will change to what the user chose
// If the user inputs "time" then curr will remain the same
void getChoice(struct Room* curr){
  int i=0;
  char choice[32];
  char* choices = choice;
  size_t buff = 32;
  FILE* fp;
  char line[50];

  getline(&choices, &buff, stdin);
  //Replaces new line charcter with null terminating character
  while(choice[i] != '\n'){
    i++;
  }
  choice[i] = '\0';

  // User inputs valid connection so path is updated
  if(validConnection(*curr, choice) == 1){
    printf("\n");
    strcpy(pathArray[numSteps++], choice);
    updateCurr(curr, choice);
  // User requests time
  }else if(strcmp(choice, "time") == 0){
    pthread_mutex_unlock(&lock);
    sleep(1);
    fp = fopen("currentTime.txt", "r");
    fgets(line, sizeof(line), fp);
    fclose(fp);
    printf("\n%s\n\n", line);
  // Invalid input
  }else{
    printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
  }
}

// Time
void* timeFunction(void* arg){
  pthread_mutex_lock(&lock);
  int result;
  FILE* fp;
  char timeVar[50];
  struct tm* tmp;
  time_t t = time(NULL);

  tmp = localtime(&t);
  strftime(timeVar, sizeof(timeVar), "%l:%M%P, %A, %B %d, %Y", tmp);
  fp = fopen("currentTime.txt", "w");
  fprintf(fp, "%s", timeVar);
  fclose(fp);

  pthread_join(timeThread, NULL);
  pthread_mutex_lock(&lock);
  pthread_create(&timeThread, NULL, timeFunction, NULL);

  pthread_exit(0);
}

// Determines if the user choice is a valid connection
// i.e. choice is within connections and is not curr
int validConnection(struct Room curr, char* choice){
  int i;
  // Not valid if choice is equal to curr
  if(strcmp(choice, curr.name) == 0){
    return 0;
  // Valid if choice is in curr's connections
  }else{
    for(i = 0; i < curr.numConnections; i++){
      if(strcmp(curr.connections[i], choice) == 0){
        return 1;
      }
    }
    return 0;
  }
}

// Changes curr to be the newcurr
void updateCurr(struct Room* curr, char* newCurr){
  int i, index;
  // Finds newCurr in activeRooms array
  for(i = 0; i < 7; i++){
    if(strcmp(activeRooms[i].name, newCurr) == 0){
      index = i;
    }
  }

  // Copies over all information to curr
  strcpy(curr->name, activeRooms[index].name);
  curr->numConnections = activeRooms[index].numConnections;
  for(i = 0; i < activeRooms[index].numConnections; i++){
    strcpy(curr->connections[i], activeRooms[index].connections[i]);
  }
  strcpy(curr->roomType, activeRooms[index].roomType);
}

// Determines if a player has own i.e current room type is END_ROOM
int isGameOver(struct Room curr){
  return strcmp(curr.roomType, "END_ROOM") == 0 ? 1 : 0;
}

void gameWon(){
  int i;
  printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
  printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numSteps);
  for(i = 0; i < numSteps; i++){
    printf("%s\n", pathArray[i]);
  }
}

void displayRooms(){
  int i,j;
  for(i = 0; i < 7; i++){
    printf("ROOM NAME: %s\n", activeRooms[i].name);
    for(j = 0; j < activeRooms[i].numConnections; j++){
      printf("CONNECTION %d: %s\n", j+1, activeRooms[i].connections[j]);
    }
    printf("ROOM TYPE: %s\n\n", activeRooms[i].roomType);
  }
}
