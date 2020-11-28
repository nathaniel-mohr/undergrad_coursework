/*
 * Program: assignment2.cpp
 * Author: Nathaniel Mohr
 * Date: January 18, 2018
 * Input: Number choices from the user, prompted by the terminal
 * Output: A text adventure story based on the user input and some chance
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
	int input = 0;
	srand(time(NULL));
	int randNum = 0;
	
	cout << "WELCOME TO THIS TEXT ADVENTURE!" << endl;
	cout << "\n\nYou are a noble knight leaving the kingdom of Camelot in an attempt to find a new place in the world." << endl;

	cout << "\nAfter leaving the kingdom, you venture into a dark forest." << endl;
	cout << "You see a pack of wolves in the distance." << endl;
	cout << "Do you: " << endl;
	cout << "       1. Attempt to befriend the wolves?" << endl;
	cout << "       2. Try and fight the pack?" << endl;
	cout << "       3. Sneak around the pack to avoid detection?" << endl;

	cin >> input;

	randNum = rand() % 2;
	
	if(input == 1 && randNum == 1){ //Choose to attempt to befriend the wolves but you fail
		cout << "\nThe wolves did not take care for you very much and did not choose to become your allies." << endl;

		cout << "\nYou exit the forest a little heartbroken by the wolves' decision." << endl;
		cout << "You come upon a group of travlers." << endl;
		cout << "Do you (1) join their caravan or (2) continue on alone?" << endl;

		cin >> input;

		if(input == 1){ //Choose to join caravan
			cout << "\nYou are happy to know that at least one being likes you and you decide to become a part of this caravan" << endl;
		}else if(input == 2) { //Choose to not join caravn
			cout << "\nYou pass by the caravan and continue on your adventure" << endl;
			cout << "\nYou come across the kingdom of Azeroth." << endl;
			cout << "Do you (1) end your journey here or (2) attempt to continue along looking for a greater purpose?" << endl;

			cin >> input;

			if(input == 1){ //Choose to stay in Azeroth
                        	cout << "\nAzeroth becomes your new home." << endl;
                	}else if(input == 2){ //Choose to try and find greater purpose
                        	cout << "\nYou make the decision that you search for a greater purpose." << endl;
				cout << "\nTurns out that you had no greater purpose." << endl;
			}else {
				cout << "ERROR" << endl;
			}		                  
		}else {
			cout << "ERROR" << endl;
		}
	}else if(input == 1 && randNum == 0){ //Choose to attempt to befriend the wolves and it works
		cout << "\nThe wolves have decided to join you in your adventure." << endl;

		cout << "\nYou exit the forest with the wolves at your side." << endl;
		cout << "You see a group of travelers who look away and hurry off, frightened by your newly acquired army." << endl;
		cout << "After seeing how society reacts to your new lifestyle, you decide to run off to live in the woods with the wolves." << endl;
	}else if(input == 2 && randNum == 1){ //Choose to fight the wolves and they kill you
		cout << "\nThe pack overcame you and you did not leave this fight alive." << endl;
	}else if(input == 2 && randNum == 0){ //Choose to fight the wolves and you become victorious
		cout << "\nVictory! The wolves have fallen to your blade and you continue on your journey." << endl;

		cout << "\nYou exit the forest with a wolf head helmet as a trophy." << endl;
		cout << "You see a group of travlers and they are greatly impressed by you trophy and hope you would accompany them on their journey." << endl;
		cout << "Do you (1) accept or (2) reject their offer?" << endl;

		cin >> input;

		if(input == 1){ //Choose to accept offer
			cout << "\nThe caravan is grateful that you have accepted their offer and you become their protector for the end of your days." << endl;
		}else if(input == 2){ //Choose to decline offer
			cout << "The caravan understands your decision and you part ways with them, continuing on your adventure." << endl;
			cout << "\nAs you near the kingdom of Orgrimarr, you notice it seems to be in disarray." << endl;
			cout << "Peasants run out claiming that the King has fallen, and seeing your trophy, insist you fill the power void." << endl;
			cout << "Do you (1) become the new king of Orgrimarr or (2) refuse the offer?" << endl;

			cin >> input;

			if(input == 1){ //Choose to become new king of Orgrimarr
				cout << "\nYou have claimed the throne of Orgrimarr!" << endl;
			}else if(input == 2){ //Choose to refuse offer
				cout << "\nAfter moving on from Orgrimarr, you see the kingdom crumble from behind you." << endl;
				cout << "You feel responsible for the fall of a once great kingdom and slip into the life of a hermit." << endl;
			}else {
				cout << "ERROR" << endl;
			}
		}else {
			cout << "ERROR" << endl;
		}
	}else if(input == 3){ //Choose to sneak around the wolves
		cout << "\nThe wolves paid no attention to you and you successfully moved around them." << endl;
		
		cout << "\nYou exit the forest and see a group of travlers on the path." << endl;
		cout << "Do you (1) join their caravan or (2) continue on alone?" << endl;

		cin >> input;

		if(input == 1){ //Choose to join caravan
			cout << "\nYou decide that these travlers could be your new home and you end your adventure." << endl;
		}else if(input == 2) { //Choose to continue alone
			cout << "\nYou yet again decide that no contact is best contact and continue down the road." << endl;
			cout << "You come to the realization that maybe the adventuring life is not for you and you go back to Camelot." << endl;
		}else{
			cout << "ERROR" << endl;
		}
	}else{
		cout << "ERROR" << endl;
	}
	
	cout << "This is the end of your journey!" << endl;
	return 0;
}
