#include "house.h"

int House::num_houses = 0;

int House::get_rent() const{return rent;}
Citizen House::get_owner() const{return owner;}

void House::set_rent(int r){rent = r;}
void House::set_owner(Citizen o){owner = o;}

void House::print_house(){
	cout << "House #" << house_num << endl;
	cout << "Property Value: " << property_value << endl;
	cout << "Location: " << location << endl;
	cout << "Mortgage: " << mortgage << endl;
	cout << "Property Tax: " << property_tax << endl;
	cout << "Rent: " << rent << endl;	
	cout << endl;
}

House::House(){
	num_houses++;
	house_num = num_houses;
	property_value = rand() % 500000 + 100000;
	property_tax = property_value * .015;	 
	rent = 10000;
}


