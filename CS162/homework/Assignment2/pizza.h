#ifndef PIZZA_H
#define PIZZA_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Pizza{
	private:
		string name;
		int small_cost;
		int medium_cost;
		int large_cost;
		int num_ingredients;
		string* ingredients;
	public:
		//accessors
		string get_name() const;
		int get_small_cost() const;
		int get_medium_cost() const;
		int get_large_cost() const;
		int get_num_ingredients() const;
		string* get_ingredients() const;

		//mutators
		void set_name(string);
		void set_small_cost(int);
		void set_medium_cost(int);
		void set_large_cost(int);
		void set_num_ingredients(int);
		void set_ingredients(string*);

		//constructor
		Pizza();
				
		//non-default constructor
		Pizza(string, int, int, int, int, string*);

		//copy constructor
		Pizza(const Pizza &);

		//assignment operator overload
		const Pizza & operator=(const Pizza &);

		//destructors
		~Pizza();
};
#endif
