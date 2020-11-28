#include "menu.h"

//accessors
int Menu::get_num_pizzas() const{return num_pizzas;}
Pizza* Menu::get_pizzas() const{return pizzas;}

//mutators
void Menu::set_num_pizzas(int num){
	num_pizzas = num;}
void Menu::set_pizzas(Pizza* p){
	pizzas = p;}

//default constructor
Menu::Menu(){
	num_pizzas = 0;
	pizzas = NULL;
}

//non-default constructor
Menu::Menu(int num, Pizza* p){
	num_pizzas = num;
	pizzas = p;
}

//copy constructor
Menu::Menu(const Menu& orig){
	num_pizzas = orig.num_pizzas;
	if(num_pizzas == 0){
		pizzas = NULL;
	}else{
		pizzas = new Pizza[num_pizzas];
		for(int i = 0; i < num_pizzas; i++){
			pizzas[i] = orig.pizzas[i];
		}
	}
}

//assignment operator overload
const Menu& Menu::operator=(const Menu& orig){
	num_pizzas = orig.num_pizzas;
	if(pizzas != NULL){
		delete[] pizzas;
	}
	if(num_pizzas == 0){
		pizzas = NULL;
	}else{
		pizzas = new Pizza[num_pizzas];
		for(int i = 0; i < num_pizzas; i++){
			pizzas[i] = orig.pizzas[i];
		}
	}
	return *this;
}

//destructor
Menu::~Menu(){
	delete[] pizzas;
}

/*
 * Function: search_pizza_by_cost
 * Description: searchs pizzas below a cost
 * Parameters: int, string
 * Pre-Conditions: size is valid
 * Post-Conditions:
 */
Menu Menu::search_pizza_by_cost(int upper_bound, string size){
	if(size == "small"){
		return search_small(upper_bound);		
	}else if(size == "medium"){
		return search_medium(upper_bound);
	}else{
		return search_large(upper_bound);
	}
}

/*
 * Function: search_small
 * Description: searchs small pizzas below a cost
 * Parameters: int
 * Pre-Conditions: 
 * Post-Conditions:
 */
Menu Menu::search_small(int upper_bound){
	Pizza *temp_one = pizzas, *temp_two;
	int num;
	for(int i = 0; i < num_pizzas; i++){
		if(pizzas[i].get_small_cost() < upper_bound){
			num++;
			temp_two = new Pizza[num];
			for(int j = 0; j < num-1; i++){
				temp_two[j] = temp_one[j];
			}
			delete[] temp_one;
			temp_two[num] = pizzas[i];
			temp_one = temp_two;
			delete[] temp_two;

		}
	}
	Menu temp(num, temp_one);
	return temp;
}


/*
 * Function: search_medium
 * Description: searchs medium pizzas below a cost
 * Parameters: int
 * Pre-Conditions: 
 * Post-Conditions:
 */
Menu Menu::search_medium(int upper_bound){
	Pizza *temp_one = new Pizza[0], *temp_two;
	int num;
	for(int i = 0; i < num_pizzas; i++){
		if(pizzas[i].get_medium_cost() < upper_bound){
			num++;
			temp_two = new Pizza[num];
			for(int j = 0; j < num-1; j++){
				temp_two[j] = temp_one[j];
			}
			delete[] temp_one;
			temp_two[num] = pizzas[i];
			temp_one = temp_two;
			delete[] temp_two;

		}
	}
	Menu temp(num, temp_one);
	return temp;
}

/*
 * Function: search_large
 * Description: searchs large pizzas below a cost
 * Parameters: int
 * Pre-Conditions: 
 * Post-Conditions:
 */
Menu Menu::search_large(int upper_bound){
	Pizza *temp_one = new Pizza[0], *temp_two;
	int num;
	for(int i = 0; i < num_pizzas; i++){
		if(pizzas[i].get_large_cost() < upper_bound){
			num++;
			temp_two = new Pizza[num];
			for(int j = 0; j < num-1; j++){
				temp_two[j] = temp_one[j];
			}
			delete[] temp_one;
			temp_two[num] = pizzas[i];
			temp_one = temp_two;
			delete[] temp_two;
		}
	}
	Menu temp(num, temp_one);
	return temp;

}

/*
 * Function: search_pizza_by_ingredients_to_include
 * Description: searchs pizzas that contain one of select ingredients
 * Parameters: string*, int
 * Pre-Conditions: int and length of array are equal
 * Post-Conditions:
 */
Menu Menu::search_pizza_by_ingredients_to_include(string* ingredients, int num_ingredients){
	Pizza *temp_one = pizzas, *temp_two;
	int num;
	for(int i = 0; i < num_pizzas; i++){
		for(int j = 0; j < pizzas[i].get_num_ingredients(); j++){
			for(int k = 0; k < num_ingredients; k++){
				if(pizzas[i].get_ingredients()[j] == ingredients[k]){
					num++;
					temp_two = new Pizza[num];
					for(int l = 0; l < i; l++){
						temp_two[l] = temp_one[l];
					}
					delete[] temp_one;
					temp_two[num] = pizzas[i];
					temp_one = temp_two;
					delete[] temp_two;
					break;
				}
			}
		}
	}
	Menu temp(num, temp_one);
	return temp;
}

/*
 * Function: search_pizza_by_ingredients_to_exclude
 * Description: searchs pizzas that do not contain one of select ingredients
 * Parameters: string*, int
 * Pre-Conditions: int and length of array are equal
 * Post-Conditions:
 */
Menu Menu::search_pizza_by_ingredients_to_exclude(string* ingredients, int num_ingredients){
	Pizza *temp_one, *temp_two;
	int num = num_pizzas;
	for(int i = 0; i < num_pizzas; i++){
		for(int j = 0; j < pizzas[i].get_num_ingredients(); j++){
			for(int k = 0; k < num_ingredients; k++){
				if(pizzas[i].get_ingredients()[j] == ingredients[k]){
					num--;
					temp_two = new Pizza[num];
					for(int l = 0; l < i; l++){
						temp_two[l] = temp_one[l];	
					}
					for(int l = i; l < num - 1; l++){
						temp_two[l] = temp_one[l];
					}
					delete[] temp_one;
					temp_one = temp_two;
					delete[] temp_two;
					break;
				}
			}
		}
	}
	Menu temp(num, temp_one);
	return temp;
}

void Menu::load_menu(){
	string str; int num = 0;
	ifstream rf;
	rf.open("menu.txt");
	while(getline(rf, str))
		++num;
	rf.close();
	rf.open("menu.txt");
	num_pizzas = num - 1;
	pizzas = new Pizza[num_pizzas];
	for(int i = 0; i < num_pizzas; i++){
		rf >> str;
		pizzas[i].set_name(str);
		rf >> num;
		pizzas[i].set_small_cost(num);
		rf >> num;
		pizzas[i].set_medium_cost(num);
		rf >> num;
		pizzas[i].set_large_cost(num);
		rf >> num;
		pizzas[i].set_num_ingredients(num);
		string *temp = new string[pizzas[i].get_num_ingredients()];
		for(int j = 0; j < pizzas[i].get_num_ingredients(); j++){
			rf >> temp[j];
		}
		pizzas[i].set_ingredients(temp);
	}
	rf.close();
}

void Menu::print_pizzas(){
	for(int i = 0; i < num_pizzas; i++){
		cout << "Name: " << pizzas[i].get_name() << endl;
		cout << "Small: " << pizzas[i].get_small_cost() << endl;
		cout << "Medium: " << pizzas[i].get_medium_cost() << endl;
		cout << "Large: " << pizzas[i].get_large_cost() << endl;
		cout << "Ingredients: ";
		for(int j = 0; j < pizzas[i].get_num_ingredients(); j++){
			cout << pizzas[i].get_ingredients()[j] << " ";
		}
		cout << endl << endl;
	}
	cout << endl;
}


