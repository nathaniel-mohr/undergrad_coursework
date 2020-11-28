#include "game.h"

Game::Game(){
	food = 50;
	for(int i = 0; i < 10; i++){
		board[i] = vector<Insect*>();
	}
}

int Game::get_food() const{return food;}

void Game::play_game(){
	cout << "WELCOME TO ANTS VS. SOME BEES\n" << endl;
	do{
		turn();
	}while(game_end() == false);
}

void Game::turn(){
	bee_generation();
	ant_placement();
	ant_actions();
	bee_actions();
	collect_food();
	cout << "END OF TURN" << endl;
	cout << "-----------------------------------------------------------------\n\n" << endl;
}

void Game::print_board(){
	for(int i = 0; i < 10; i++){
		cout << "Space #" << i+1;
		if(i < 9) cout << " ";
		cout << ": ";
		for(int j = 0; j < board[i].size(); j++){
			cout << board[i].at(j)->get_name() << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Game::bee_generation(){
	cout << "\tBEE GENERATION" << endl;
	board[9].push_back(new Bee());
	print_board();
}

void Game::ant_placement(){
	int index;
	Ant* temp;
	cout << "\tANT PLACEMENT" << endl;
	cout << "\tFOOD BANK: " << food << endl;
	do{
		temp = get_ant();
	}while(food - temp->get_food_cost() < 0);
	food -= temp->get_food_cost();
	cout << temp->get_name() << endl;
	do{
		cout << "What space?" << endl;
		cin >> index;
	}while(valid_index(temp, index-1) == false);
	cout << endl;
	board[index-1].push_back(temp);
	print_board();
}

Ant* Game::get_ant(){
	int choice;
	cout << "  CHOICE         NAME          FOOD COST" << endl;
	cout << "------------------------------------------" << endl;
	cout << "    0    |   Harvester       |     2" << endl;
	cout << "    1    |   Long Thrower    |     3" << endl;
	cout << "    2    |   Short Thrower   |     3" << endl;
	cout << "    3    |   Thrower         |     4" << endl;
	cout << "    4    |   Fire            |     4" << endl;
	cout << "    5    |   Wall            |     4" << endl;
	cout << "    6    |   Bodyguard       |     4" << endl;
	cout << "    7    |   Ninja           |     6" << endl;
	do{
		cout << "What ant?" << endl;
		cin >> choice;	
	}while(valid_ant(choice) == false);
	return ant_switch(choice);
}

Ant* Game::ant_switch(int choice){
	switch (choice){
		case 0:
			return new Harvester();
		case 1:
			return new Long_Thrower();
		case 2: 
			return new Short_Thrower();
		case 3:
			return new Thrower();
		case 4:
			return new Fire();
		case 5:
			return new Wall();
		case 6:
			return new Bodyguard();
		case 7:
			return new Ninja();
	}
}

bool Game::valid_ant(int choice){
	int count = 0;
	if(choice > 7 || choice < 0){
		return false;	
	}
	Ant* temp = ant_switch(choice);
	//chose bodyguard
	if(temp->get_name() == "BODYGUARD"){
		//check to see there is a space that is not occupied by a bodyguard
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < board[i].size(); j++){
				if(board[i].at(j)->get_name() == "BODYGUARD" && board[i].at(j)->get_name() != "BEE"){
					count++;
					break;
				}
			}
		}
	//chose another ant
	}else{
		//check to see there is a space that either has no ant or a bodyguard
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < board[i].size(); j++){
				if(board[i].at(j)->get_name() != "BODYGUARD" && board[i].at(j)->get_name() != "BEE"){
					count++;
					break;
				}
			}
		}
	}		
	if(count == 10){
		return false;
	}
	return true;
}

bool Game::valid_index(Ant* selection, int index){
	if(board[index].size() > 0){
		for(int i = 0; i < board[index].size(); i++){
			//current insect is an ant
			if(board[index].at(i)->get_name() != "BEE"){
				//one of the ants is a bodyguard and the other is not
				if(board[index].at(i)->get_name() == "BODYGUARD" && selection->get_name() != "BODYGUARD"){
					return true;
				}else if(selection->get_name() == "BODYGUARD" && board[index].at(i)->get_name() != "BODYGUARD"){
					return true;
				//neither ant is a bodyguard or both are
				}else{
					return false;
				}
			}
		}
	}
	//no ants on space
	return true;
}

void Game::ant_actions(){
}

void Game::collect_food(){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < board[i].size(); j++){
			if(board[i].at(j)->get_name() == "HARVESTER"){
				food++;
			}
		}
	}
}

/*void Game::attack(Ant* attacker, int index){
	for(int i = 0; i < board[index].size(); i++){
		if(board[index].at(i)->get_name() == "BEE"){
			board[index].at(i)->set_armor(board[index].at(i)->get_armor() - attacker->get_attack());
			break;
		}
	}
}*/

void Game::bee_actions(){
	cout << "\tBEE ACTIONS" << endl;
	for(int i = 0; i < 10; i++){
		if(contains_bees(board[i]) == true){
			//there is an ant
			if(contains_ants(board[i]) == true && contains_ninja(board[i]) == false){
				bee_attack(i);
			//no ants. all bees move
			}else{
				for(int j = 0; j < board[i].size(); j++){
					board[i-1].push_back(board[i].at(j));
					board[i].erase(board[i].begin() + j);
				}
			}
		}
	}
	print_board();
}

void Game::bee_attack(int space){
	//first bee attacks
	board[space].at(first_def_ant(board[space]))->set_armor(board[space].at(first_def_ant(board[space]))->get_armor() - 1);
	if(board[space].at(first_def_ant(board[space]))->get_armor() <= 0){
		board[space].erase(board[space].begin() + first_def_ant(board[space]));
	}
	//other bees move
	for(int j = 0; j < first_bee(board[space]); j++){
		if(board[space].at(j)->get_name() == "BEE"){
			board[space-1].push_back(board[space].at(j));
			board[space].erase(board[space].begin() + j);
		}
	}
	for(int j = first_bee(board[space]); j < board[space].size(); j++){
		if(board[space].at(j)->get_name() == "BEE"){
			board[space-1].push_back(board[space].at(j));
			board[space].erase(board[space].begin() + j);
		}
	}
}

bool Game::contains_bees(vector<Insect*> space){
	for(int i = 0; i < space.size(); i++){
		if(space.at(i)->get_name() == "BEE"){
			return true;
		}
	}
	return false;
}

int Game::first_bee(vector<Insect*> space){
	for(int i = 0; i < space.size(); i++){
		if(space.at(i)->get_name() == "BEE"){
			return i;
		}
	}
}

bool Game::contains_ants(vector<Insect*> space){
	for(int i = 0; i < space.size(); i++){
		if(space.at(i)->get_name() != "BEE"){
			return true;
		}
	}
	return false;
}

bool Game::contains_ninja(vector<Insect*> space){
	for(int i = 0; i < space.size(); i++){
		if(space.at(i)->get_name() != "NINJA"){
			return true;
		}
	}
	return false;
}

int Game::first_def_ant(vector<Insect*> space){
	for(int i = 0; i < space.size(); i++){
		if(space.at(i)->get_name() != "BEE" && space.at(i)->get_name() != "NINJA"){
			return i;
		}
	}
}

int Game::first_off_ant(vector<Insect*> space){

}

bool Game::game_end(){
	//tests to see if first insect is a bee (bees win)
	if(board[0].size() > 0 && board[0].at(0)->get_name() == "BEE"){
		cout << "BEES WIN" << endl;
		return true;
	}
	//tests to see if there are bees present in other spaces
	//not including first space
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < board[i].size(); j++){
			if(board[i].at(j)->get_name() == "BEE"){
				return false;
			}
		}
	}
	//no bees are present
	cout << "PLAYER WINS" << endl;
	return true;
}
