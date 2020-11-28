#include "apartment_complex.h"

int Apartment_Complex::num_apartments = 0;

//accessors
int Apartment_Complex::get_rooms() const{return rooms;}
int Apartment_Complex::get_rent() const{return rent;}
Citizen* Apartment_Complex::get_renters() const{return renters;}

//mutators
void Apartment_Complex::set_rooms(int r){rooms = r;}
void Apartment_Complex::set_rent(int r){rent = r;}
void Apartment_Complex::set_renters(Citizen* r){renters = r;}

void Apartment_Complex::print_apartment(){
	cout << "Apartment #" << apartment_num << endl;
	cout << "Property Value: " << property_value << endl;
	cout << "Location: " << location << endl;
	cout << "Mortgage: " << mortgage << endl;
	cout << "Property Tax: " << property_tax << endl;
	cout << "Number of Rooms: " << rooms << endl;
	cout << "Rent: " << rent << endl;
	cout << endl;
}

Apartment_Complex::Apartment_Complex():Property(){
	num_apartments++;
	apartment_num = num_apartments;
	property_value = rand() % 300000 + 300000;
	rooms = rand() % 10 + 1;
	renters = new Citizen[rooms];
}

const Apartment_Complex & Apartment_Complex::operator=(const Apartment_Complex &orig){
	Property::operator=(orig);
	apartment_num = orig.apartment_num;
	rooms = orig.rooms;
	if(renters != NULL){
		delete[] renters;
	}
	renters = new Citizen[rooms];
	for(int i = 0; i < rooms; i++){
		renters[i] = orig.renters[i];
	}
}

Apartment_Complex::Apartment_Complex(const Apartment_Complex &orig):Property(orig){
	apartment_num = orig.apartment_num;
	rooms = orig.rooms;	
	renters = new Citizen[rooms];
	for(int i = 0; i < rooms; i++){
		renters[i] = orig.renters[i];
	}
}

Apartment_Complex::~Apartment_Complex(){
	delete[] renters;
}
