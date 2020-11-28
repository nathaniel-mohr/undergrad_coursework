#include "pizza.h"

//accessors
string Pizza::get_name() const{return name;}
int Pizza::get_small_cost() const{return small_cost;}
int Pizza::get_medium_cost() const{return medium_cost;}
int Pizza::get_large_cost() const{return large_cost;}
int Pizza::get_num_ingredients() const{return num_ingredients;}
string* Pizza::get_ingredients() const{return ingredients;}

//mutators
void Pizza::set_name(string new_name){
	name = new_name;}
void Pizza::set_small_cost(int new_cost){
	small_cost = new_cost;}
void Pizza::set_medium_cost(int new_cost){
	medium_cost = new_cost;}
void Pizza::set_large_cost(int new_cost){
	large_cost = new_cost;}
void Pizza::set_num_ingredients(int new_num){
	num_ingredients = new_num;}
void Pizza::set_ingredients(string* new_ingredients){
	ingredients = new_ingredients;}

//default constructor
Pizza::Pizza(){
	name = "";
	small_cost = 0;
	medium_cost = 0;
	large_cost = 0;
	num_ingredients = 0;
	ingredients = NULL;
}

//non-default constructor
Pizza::Pizza(string name, int sc, int mc, int lc, int ni, string* i){
	this->name = name;
	small_cost = sc;
	medium_cost = mc;
	large_cost = lc;
	num_ingredients = ni;
	ingredients = i;
}

//copy constructor
Pizza::Pizza(const Pizza& orig){
	name = orig.name;
	small_cost = orig.small_cost;
	medium_cost = orig.medium_cost;
	large_cost = orig.large_cost;
	num_ingredients = orig.num_ingredients;
	if(num_ingredients == 0){
		ingredients = NULL;
	}else{
		ingredients = new string[num_ingredients];
		for(int i = 0; i < num_ingredients; i++){
			ingredients[i] = orig.ingredients[i];
		}
	}
}

//assignment operator overload
const Pizza& Pizza::operator=(const Pizza& orig){
	name = orig.name;
	small_cost = orig.small_cost;
	medium_cost = orig.medium_cost;
	large_cost = orig.large_cost;
	num_ingredients = orig.num_ingredients;
	if(ingredients != NULL){
		delete[] ingredients;
	}
	if(num_ingredients == 0){
		ingredients = NULL;
	}else{
		ingredients = new string[num_ingredients];
		for(int i = 0; i < num_ingredients; i++){
			ingredients[i] = orig.ingredients[i];
		}
	}
	return *this;
}

//destructor
Pizza::~Pizza(){
	delete[] ingredients;
}

