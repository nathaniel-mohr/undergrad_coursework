#include "player.h"

int Player::get_bank_balance() const{return bank_balance;}
int Player::get_num_houses() const{return num_houses;}
int Player::get_num_apartments() const{return num_apartments;}
int Player::get_num_businesses() const{return num_businesses;}
House* Player::get_houses() const{return houses;}
Apartment_Complex* Player::get_apartments() const{return apartments;}
Business_Complex* Player::get_businesses() const{return businesses;}

void Player::set_bank_balance(int b){bank_balance = b;}

void Player::print_player(){
	cout << "\nPLAYER DETAILS" << endl;
	cout << "------------------\n" << endl;
	cout << "Bank balance: " << bank_balance << endl;
	cout << "\nNumber of Houses: " << num_houses << endl << endl;
	for(int i = 0; i < num_houses; i++){
		houses[i].print_house();
	}
	cout << "Number of Apartments: " << num_apartments << endl << endl;
	for(int i = 0; i < num_apartments; i++){
		apartments[i].print_apartment();
	}
	cout << "Number of Businesses: " << num_businesses << endl << endl;
	for(int i = 0; i < num_businesses; i++){
		businesses[i].print_b_complex();
	}
}

Player::Player(){
	bank_balance = 500000;
	num_houses = 0;
	houses = new House[num_houses];
	num_apartments = 0;
	apartments = new Apartment_Complex[num_apartments];
	num_businesses = 0;
	businesses = new Business_Complex[num_businesses];
}

void Player::hurricane(){
	if(num_houses > 0){
		for(int i = 0; i < num_houses; i++){
			if(houses[i].get_location() == "SE"){
				houses[i].set_property_value(houses[i].get_property_value()*.5);
			}
		}
	}
	if(num_apartments > 0){
		for(int i = 0; i < num_apartments; i++){
			if(apartments[i].get_location() == "SE"){
				apartments[i].set_property_value(apartments[i].get_property_value()*.5);
			}
		}
	}
	if(num_businesses > 0){
		for(int i = 0; i < num_businesses; i++){
			if(businesses[i].get_location() == "SE"){
				businesses[i].set_property_value(businesses[i].get_property_value()*.5);
			}
		}
	}
}

void Player::tornado(){
	if(num_houses > 0){
		for(int i = 0; i < num_houses; i++){
			if(houses[i].get_location() == "Midwest"){
				houses[i].set_property_value(houses[i].get_property_value()*.7);
			}
		}
	}
	if(num_apartments > 0){
		for(int i = 0; i < num_apartments; i++){
			if(apartments[i].get_location() == "Midwest"){
				apartments[i].set_property_value(apartments[i].get_property_value()*.7);
			}
		}
	}
	if(num_businesses > 0){
		for(int i = 0; i < num_businesses; i++){
			if(businesses[i].get_location() == "Midwest"){
				businesses[i].set_property_value(businesses[i].get_property_value()*.7);
			}
		}
	}
}

void Player::earthquake(){
	if(num_houses > 0){
		for(int i = 0; i < num_houses; i++){
			if(houses[i].get_location() == "NW"){
				houses[i].set_property_value(houses[i].get_property_value()*.1);
			}
		}
	}
	if(num_apartments > 0){
		for(int i = 0; i < num_apartments; i++){
			if(apartments[i].get_location() == "NW"){
				apartments[i].set_property_value(apartments[i].get_property_value()*.1);
			}
		}
	}
	if(num_businesses > 0){
		for(int i = 0; i < num_businesses; i++){
			if(businesses[i].get_location() == "NW"){
				businesses[i].set_property_value(businesses[i].get_property_value()*.1);
			}
		}
	}
}

void Player::wildfire(){
	if(num_houses > 0){
		for(int i = 0; i < num_houses; i++){
			if(houses[i].get_location() == "SW"){
				houses[i].set_property_value(houses[i].get_property_value()*.75);
			}
		}
	}
	if(num_apartments > 0){
		for(int i = 0; i < num_apartments; i++){
			if(apartments[i].get_location() == "SW"){
				apartments[i].set_property_value(apartments[i].get_property_value()*.75);
			}
		}
	}
	if(num_businesses > 0){
		for(int i = 0; i < num_businesses; i++){
			if(businesses[i].get_location() == "SW"){
				businesses[i].set_property_value(businesses[i].get_property_value()*.75);
			}
		}
	}
}

void Player::stock_market(){
	if(num_houses > 0){
		for(int i = 0; i < num_houses; i++){
			houses[i].set_property_value(houses[i].get_property_value()*.7);
		}
	}
	if(num_apartments > 0){
		for(int i = 0; i < num_apartments; i++){
			apartments[i].set_property_value(apartments[i].get_property_value()*.7);
		}
	}
	if(num_businesses > 0){
		for(int i = 0; i < num_businesses; i++){
			businesses[i].set_property_value(businesses[i].get_property_value()*.7);
		}
	}
}

void Player::gentrification(){
	string location = Property::random_location();
	if(num_houses > 0){
		for(int i = 0; i < num_houses; i++){
			if(houses[i].get_location() == location){
				houses[i].set_property_value(houses[i].get_property_value()*1.2);
			}
		}
	}
	if(num_apartments > 0){
		for(int i = 0; i < num_apartments; i++){
			if(apartments[i].get_location() == location){
				apartments[i].set_property_value(apartments[i].get_property_value()*1.2);
			}
		}
	}
	if(num_businesses > 0){
		for(int i = 0; i < num_businesses; i++){
			if(businesses[i].get_location() == location){
				businesses[i].set_property_value(businesses[i].get_property_value()*1.2);
			}
		}
	}
}

void Player::sell_house(){
	int ans;
	cout << "What house would you like to sell? (index of house)" << endl;
	do{
		cin >> ans;
	}while(ans < 0 || ans > num_houses - 1);
	House* temp = new House[num_houses - 1];
	for(int i = 0; i < ans; i++){
		temp[i] = houses[i];
	}
	for(int i = ans; i < num_houses - 1; i++){
		temp[i] = houses[i+1];
	}
	num_houses--;
	delete[] houses;
	houses = temp;
}

void Player::sell_apartment(){
	int ans;
	cout << "What apartment would you like to sell? (index of apartment)" << endl;
	do{
		cin >> ans;
	}while(ans < 0 || ans > num_apartments - 1);
	Apartment_Complex* temp = new Apartment_Complex[num_apartments - 1];
	for(int i = 0; i < ans; i++){
		temp[i] = apartments[i];
	}
	for(int i = ans; i < num_apartments - 1; i++){
		temp[i] = apartments[i+1];
	}
	num_apartments--;
	delete[] apartments;
	apartments = temp;
}

void Player::sell_business(){
	int ans;
	cout << "What business complex would you like to sell? (index of business complex)" << endl;
	do{
		cin >> ans;
	}while(ans < 0 || ans > num_businesses - 1);
	sold_business(businesses[ans]);
	Business_Complex* temp = new Business_Complex[num_businesses - 1];
	for(int i = 0; i < ans; i++){
		temp[i] = businesses[i];
	}
	for(int i = ans; i < num_businesses - 1; i++){
		temp[i] = businesses[i+1];
	}
	num_businesses--;
	delete[] businesses;
	businesses = temp;
}

void Player::sold_house(House h){
	int result = rand() % 3 + 1;
	int ans;
	cout << "How much would you like to sell it for?" << endl;
	cin >> ans;
	switch (result){
		case 1:
			cout << "It was sold for: " << h.get_property_value() * .9 << endl;
			bank_balance = bank_balance + (h.get_property_value() * .9);
			break;
		case 2:
			cout << "It was sold for: " << h.get_property_value() << endl;
			bank_balance += h.get_property_value();
			break;
		case 3:
			cout << "It was sold for: " << ans << endl;
			bank_balance += ans;
			break;
	}

}

void Player::sold_apartment(Apartment_Complex a){
	int result = rand() % 3 + 1;
	int ans;
	cout << "How much would you like to sell it for?" << endl;
	cin >> ans;
	switch (result){
		case 1:
			cout << "It was sold for: " << a.get_property_value() * .9 << endl;
			bank_balance = bank_balance + (a.get_property_value() * .9);
			break;
		case 2:
			cout << "It was sold for: " << a.get_property_value() << endl;
			bank_balance += a.get_property_value();
			break;
		case 3:
			cout << "It was sold for: " << ans << endl;
			bank_balance += ans;
			break;
	}

}

void Player::sold_business(Business_Complex b){
	int result = rand() % 3 + 1;
	int ans;
	cout << "How much would you like to sell it for?" << endl;
	cin >> ans;
	switch (result){
		case 1:
			cout << "It was sold for: " << b.get_property_value() * .9 << endl;
			bank_balance = bank_balance + (b.get_property_value() * .9);
			break;
		case 2:
			cout << "It was sold for: " << b.get_property_value() << endl;
			bank_balance += b.get_property_value();
			break;
		case 3:
			cout << "It was sold for: " << ans << endl;
			bank_balance += ans;
			break;
	}
}

void Player::adjust_house(){
	int ans, new_rent;
	cout << "What house would you like to adjust? (index of house)" << endl;
	do{
		cin >> ans;
	}while(ans < 0 || ans > num_houses - 1);
	cout << "What would you like the new rent to be?" << endl;
	cin >> new_rent;
	houses[ans].set_rent(new_rent);
}

void Player::adjust_apartment(){
	int ans, new_rent;
	cout << "What apartment would you like to adjust? (index of apartment)" << endl;
	do{
		cin >> ans;
	}while(ans < 0 || ans > num_apartments - 1);
	cout << "What would you like the new rent to be?" << endl;
	cin >> new_rent;
	apartments[ans].set_rent(new_rent);

}

void Player::adjust_business(){
	int complex_num, space_num, new_rent;
	cout << "What business would you like to adjust? (index of business complex)" << endl;
	do{
		cin >> complex_num;
	}while(complex_num < 0 || complex_num > num_businesses - 1);
	cout << "What space would you like to adjust?" << endl;
	do{
		cin >> space_num;
	}while(space_num < 0 || space_num > businesses[complex_num].get_num_spaces() - 1);
	cout << "What would you like the new rent to be?" << endl;
	cin >> new_rent;
	businesses[complex_num].get_spaces()[space_num].set_rent(new_rent);
}
