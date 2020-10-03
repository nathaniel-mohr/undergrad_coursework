/*
  Build Rooms Program
  Author: Nathaniel Mohr

  This program will create a series of files
  that hold descriptions of the in-game rooms and how the rooms are connected

  Each file will contain:
    ROOM NAME: <room name>
    CONNECTION 1: <room name>
    …
    ROOM TYPE: <room type>
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Declaration of room struct
struct Room{
  char name[9];           // Each name can be a max of 8 characters
  char roomType[11];      // "START_ROOM" is the longest room type at 10 characters
  int numConnections;
  char connections[6][9]; // Each room can have at max 6 connections
                          // and the name of each connection is at max 8 characters
};

// Possible room choices
char* possibleRooms[10] = {"Kitchen", "Ballroom", "Bedroom", "Cellar", "Attic", "Bedroom", "Dungeon", "Library", "Pantry", "Dining"};
struct Room activeRooms[7];
char roomsDirectory[32];

// Function prototypes
void generateRoomsDirectory();
void populateActiveRooms();
int notNewRoom(char* name);
void createLayout();
int isGraphFull();
void addRandomConnection();
struct Room* getRandomRoom();
int canAddConnectionFrom(struct Room* a);
int isSameRoom(struct Room* a, struct Room* b);
int connectionAlreadyExists(struct Room* a, struct Room* b);
void connectRooms(struct Room* a, struct Room* b);
void appointRoomTypes();
void displayRooms();

int main(){
  int i;
  srand(time(NULL));

  generateRoomsDirectory();
  populateActiveRooms();
  createLayout();
  displayRooms();

  return 0;
}

// Create a directory based on the process ID
void generateRoomsDirectory(){
  char directoryPrefix[] = "mohrna.rooms.";
  int processID = getpid();
  sprintf(roomsDirectory, "%s%d", directoryPrefix, processID);
  mkdir(roomsDirectory, 0755);
}

// Choose the 7 random rooms and assign their room types
void populateActiveRooms(){
  int i;
  int roomSelection;

  for(i=0; i < 7; i++){
    do{
      roomSelection = rand()%10;
    }while(notNewRoom(possibleRooms[roomSelection]) == 1);
    strcpy(activeRooms[i].name, possibleRooms[roomSelection]);
    activeRooms[i].numConnections = 0;
  }
  appointRoomTypes();
}

// Assigns the room types to each room
void appointRoomTypes(){
  int i, start=rand()%7, end;
  do {
    end = rand()%7;
  } while(start == end);
  for(i = 0; i < 7; i++){
    if(i != start && i != end){
      strcpy(activeRooms[i].roomType, "MID_ROOM");
    }
  }
  strcpy(activeRooms[start].roomType, "START_ROOM");
  strcpy(activeRooms[end].roomType, "END_ROOM");
}

// Check that a given room has not already been chosen
int notNewRoom(char* name){
  int i;
  for(i = 0; i < 7; i++){
    if(strcmp(name,activeRooms[i].name) == 0){
      return 1;
    }
  }
  return 0;
}

// Add the connections to the rooms
void createLayout(){
  while(isGraphFull() == 0){
    addRandomConnection();
  }
}

// Determines if all rooms have at least 3 connections
int isGraphFull(){
  int i;
  for(i = 0; i < 7; i++){
    if(activeRooms[i].numConnections < 3){
      return 0;
    }
  }
  return 1;
}

// Adds a random, valid outbound connection from a Room to another Room
void addRandomConnection(){
  struct Room* A;
  struct Room* B;
  while(1){
    A = getRandomRoom();
    if(canAddConnectionFrom(A) == 1){
      break;
    }
  }
  do{
    B = getRandomRoom();
  }while(canAddConnectionFrom(B) == 0 || isSameRoom(A,B) == 1 || connectionAlreadyExists(A,B) == 1);
  connectRooms(A,B);
  connectRooms(B,A);
}

// Returns a random Room
struct Room* getRandomRoom(){
  return &activeRooms[rand()%7];
}

// Returns true if a connection be added from Room a
int canAddConnectionFrom(struct Room* a){
  return a->numConnections < 6 ? 1 : 0;
}

// Returns true if a connection from Room a to Room b already exists
int connectionAlreadyExists(struct Room* a, struct Room* b){
  int i;
  for(i = 0; i < a->numConnections; i++){
    if(strcmp(a->connections[i], b->name) == 0){
      return 1;
    }
  }
  return 0;
}

// Returns true if Rooms a and b are the same Room
int isSameRoom(struct Room* a, struct Room* b){
  return strcmp(a->name, b->name) == 0 ? 1 : 0;
}

// Connects Rooms a and b together
void connectRooms(struct Room* a, struct Room* b){
  strcpy(a->connections[a->numConnections], b->name);
  a->numConnections++;
}

// Prints out the room information to a file in the rooms directory
void displayRooms(){
  int i,j;
  FILE* fp;
  char file[32];
  for(i = 0; i < 7; i++){
    sprintf(file, "%s%s%s%s", roomsDirectory, "/", activeRooms[i].name, "_file");
    fp = fopen(file, "w");
    fprintf(fp, "ROOM NAME: %s\n", activeRooms[i].name);
    for(j = 0; j < activeRooms[i].numConnections; j++){
      fprintf(fp,"CONNECTION %d: %s\n", j+1, activeRooms[i].connections[j]);
    }
    fprintf(fp,"ROOM TYPE: %s\n\n", activeRooms[i].roomType);
    fclose(fp);
  }
}
