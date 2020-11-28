#include "game.h"

Game::Game(){
	num_turn = 1;
	num_houses = 3;
	num_apartments = 3;
	num_businesses = 3;
	houses = new House[num_houses];
	apartments = new Apartment_Complex[num_apartments];
	businesses = new Business_Complex[num_businesses];
	Player p;
}

bool Game::game_over(){
	if(p.get_bank_balance() <= 0){
		cout << "YOU LOST" << endl;
		return true;
	}else if(p.get_bank_balance() >= 1000000){
		cout << "YOU WON" << endl;
		return true;
	}else{
		return false;
	}
}

void Game::play_game(){
	cout << "    WELCOME TO THE REAL ESTATE TYCOON GAME" << endl;
	cout << "----------------------------------------------" << endl;
	while(game_over() == false){
		collect_mortgage();
		collect_rent();
		collect_tax();
		random_event();
		adjust_tax();
		buy_property();
		sell_property();
		adjust_property();
		p.print_player();
		cout << "END OF YEAR " << (num_turn / 12) << " MONTH " << num_turn << endl << endl;
		num_turn++;
	}
}

void Game::collect_mortgage(){
	for(int i = 0; i < p.get_num_houses(); i++){
		p.set_bank_balance(p.get_bank_balance() - p.get_houses()[i].get_mortgage());	
	}
	for(int i = 0; i < p.get_num_apartments(); i++){
		p.set_bank_balance(p.get_bank_balance() - p.get_apartments()[i].get_mortgage());	
	}
	for(int i = 0; i < p.get_num_businesses(); i++){
		p.set_bank_balance(p.get_bank_balance() - p.get_businesses()[i].get_mortgage());	
	}
}

void Game::collect_rent(){
	for(int i = 0; i < p.get_num_houses(); i++){
		if(p.get_houses()[i].get_owner().get_max_budget() < p.get_houses()[i].get_rent()){
			if(p.get_houses()[i].get_owner().get_agreeability() > 2){
				p.get_houses()[i].get_owner().vacate();
			}
		}else{
			p.set_bank_balance(p.get_bank_balance() + p.get_houses()[i].get_rent());	
		}
	}
	for(int i = 0; i < p.get_num_apartments(); i++){
		for(int j = 0; j < p.get_apartments()[i].get_rooms(); j++){
			if(p.get_apartments()[i].get_renters()[j].get_max_budget() < p.get_apartments()[i].get_rent()){
				if(p.get_apartments()[i].get_renters()[j].get_agreeability() > 2){
					p.get_apartments()[i].get_renters()[j].vacate();			
				}
			}else{
				p.set_bank_balance(p.get_bank_balance() + p.get_apartments()[i].get_rent());	
			}
		}
	}
	for(int i = 0; i < p.get_num_businesses(); i++){
		for(int j = 0; j < p.get_businesses()[i].get_num_spaces(); j++){
				if(p.get_businesses()[i].get_spaces()[j].get_renter().get_max_budget() < p.get_businesses()[i].get_spaces()[j].get_rent()){
					if(p.get_businesses()[i].get_spaces()[j].get_renter().get_agreeability() > 2){
						p.get_businesses()[i].get_spaces()[j].get_renter().vacate();
					}
				}else{
					p.set_bank_balance(p.get_bank_balance() + p.get_businesses()[i].get_spaces()[j].get_rent());	
				}
		}
	}
}

void Game::collect_tax(){
	if(num_turn % 12 == 0){
		for(int i = 0; i < p.get_num_houses(); i++){
			p.set_bank_balance(p.get_bank_balance() - p.get_houses()[i].get_property_tax());	
		}
		for(int i = 0; i < p.get_num_apartments(); i++){
			p.set_bank_balance(p.get_bank_balance() - p.get_apartments()[i].get_property_tax());	
		}
		for(int i = 0; i < p.get_num_businesses(); i++){
			p.set_bank_balance(p.get_bank_balance() - p.get_businesses()[i].get_property_tax());	
		}
	}
}

void Game::random_event(){
	int ans = rand() % 6;
	cout << "RANDOM EVENT: ";
	switch (ans){
		case 0:
			cout << "A hurricane has appeared\n" << endl;
			p.hurricane();
			break;
		case 1:
			cout << "A tornado has appeared\n" << endl;
			p.tornado();
			break;
		case 2:
			cout << "An earthquake has appeared\n" << endl;
			p.earthquake();
			break;
		case 3:
			cout << "A wildfire has appeared\n" << endl;
			p.wildfire();
			break;
		case 4:
			cout << "The stock market has crashed\n" << endl;
			p.stock_market();
			break;
		case 5: 
			cout << "Gentrification\n" << endl;
			p.gentrification();
			break;
	}
}

void Game::adjust_tax(){
	for(int i = 0; i < p.get_num_houses(); i++){
		p.get_houses()[i].set_property_tax(p.get_houses()[i].get_property_value()*.015);	
	}
	for(int i = 0; i < p.get_num_apartments(); i++){
		p.get_apartments()[i].set_property_tax(p.get_apartments()[i].get_property_value()*.015);	
	}
	for(int i = 0; i < p.get_num_businesses(); i++){
		p.get_businesses()[i].set_property_tax(p.get_businesses()[i].get_property_value()*.015);	
	}

}

void Game::buy_property(){
	string ans;
	cout << "Would you like to buy a property?" << endl;
	do{
		cin >> ans; 
	}while(ans != "yes" && ans != "no");
	if(ans == "yes"){
		get_random_properties();
	}
}

void Game::sell_property(){
	if(p.get_num_houses() > 0 || p.get_num_apartments() > 0 || p.get_num_businesses() > 0){
		string ans;
		cout << "Would you like to sell a property?" << endl;
		do{
			cin >> ans; 
		}while(ans != "yes" && ans != "no");
		if(ans == "yes"){
			cout << "A house (H), apartment complex (A), or business complex (B)?" << endl;
			do{
				cin >> ans;
			}while(ans != "H" && ans != "A" && ans != "B");
			if(ans == "H"){
				p.sell_house();
			}else if(ans == "A"){
				p.sell_apartment();
			}else{
				p.sell_business();
			}
		}
	}
}

void Game::adjust_property(){
	if(p.get_num_houses() > 0 || p.get_num_apartments() > 0 || p.get_num_businesses() > 0){
		string ans;
		cout << "Would you like to adjust a property's rent?" << endl;
		do{
			cin >> ans; 
		}while(ans != "yes" && ans != "no");
		if(ans == "yes"){
			cout << "A house (H), apartment complex (A), or business complex (B)?" << endl;
			do{
				cin >> ans;
			}while(ans != "H" && ans != "A" && ans != "B");
			if(ans == "H"){
				p.adjust_house();
			}else if(ans == "A"){
				p.adjust_apartment();
			}else{
				p.adjust_business();
			}

		}
	}
}

void Game::get_random_properties(){
	
}
