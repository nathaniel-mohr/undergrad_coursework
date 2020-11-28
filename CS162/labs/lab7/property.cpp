#include "property.h"

//accessors
int Property::get_property_value() const{return property_value;}
string Property::get_location() const{return location;}
int Property::get_mortgage() const{return mortgage;}
int Property::get_mortgage_payments() const{return mortgage_payments;}
float Property::get_property_tax() const{return property_tax;}

//mutators
void Property::set_property_value(int p){property_value = p;}
void Property::set_location(string l){location = l;}
void Property::set_mortgage(int m){mortgage = m;}
void Property::set_mortgage_payments(int m){mortgage_payments = m;}
void Property::set_property_tax(float p){property_tax = p;}


string Property::random_location(){
	int ans = rand() % 5;
	switch (ans){
		case 0:
			return "SE";
		case 1:
			return "NE";
		case 2:
			return "Midwest";
		case 3:
			return "SW";
		case 4:
			return "NW";
	}
}

Property::Property(){
	location = random_location();
	mortgage = rand() % 5000 + 1;
	mortgage_payments = 0;
}

bool Property::operator<(const Property &x){
	if(property_value < x.property_value){
		return true;
	}
	return false;
}

bool Property::operator>(const Property &x){
	if(property_value > x.property_value){
		return true;
	}
	return false;
}
