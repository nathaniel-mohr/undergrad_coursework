#ifndef MENU_H
#define MENU_H

#include "pizza.h"

class Menu{
	private:
		int num_pizzas;
		Pizza* pizzas;
	public: 
		//accessors
		int get_num_pizzas() const;
		Pizza* get_pizzas() const;

		//mutators
		void set_num_pizzas(int);
		void set_pizzas(Pizza*);

		//default constructor
		Menu();

		//non-default constructor
		Menu(int, Pizza*);

		//copy constructors
		Menu(const Menu &);

		//assignment operator overload
		const Menu& operator=(const Menu &);

		//destructors
		~Menu();
		
		Menu search_pizza_by_cost(int, string);
		Menu search_small(int);
		Menu search_medium(int);
		Menu search_large(int);
		Menu search_pizza_by_ingredients_to_include(string*, int);
		Menu search_pizza_by_ingredients_to_exclude(string*, int);
		void add_to_menu(Pizza);
		void remove_from_menu(int);
		void load_menu();
		void print_pizzas();
};

#endif
