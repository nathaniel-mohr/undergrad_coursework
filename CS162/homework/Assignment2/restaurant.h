#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "menu.h"
#include "structs.h"

class Restaurant{
	private:
		Menu menu;
		int num_employees;
		employee* employees;
		int num_days;
		hours* week;
		string name;
		string phone;
		string address;
	public:
		//accessors
		Menu get_menu() const;
		int get_num_employees() const;
		employee* get_employees() const;
		int get_num_days() const;
		hours* get_week() const;
		string get_name() const;
		string get_phone() const;
		string get_address() const;

		//mutators
		void set_menu(Menu);
		void set_num_employees(int);
		void set_employees(employee*);
		void set_num_days(int);
		void set_week(hours*);
		void set_name(string);
		void set_phone(string);
		void set_address(string);
		
		//default constructor
		Restaurant();

		//non-default constructor
		Restaurant(Menu, int, employee*, int, hours*, string, string, string);
		
		//copy constructors
		Restaurant(const Restaurant&);

		//assignment operator overload
		const Restaurant& operator=(const Restaurant&);

		//destructor
		~Restaurant();
		
		void load_data(); //reads from files to correctly populate menu, employees, hours, etc
		bool login(string id, string password);
		void view_menu();
		void view_hours();
		void view_address();
		void view_phone();
		void search_menu_by_price();
		void search_by_ingredients();
		void include();
		void exclude();
		void get_ingredients(int* num, string** ingredients);
		void place_order(Pizza* selection);
		void change_hours();
		void add_to_menu();
		void remove_from_menu();
		void view_orders();
		void remove_orders();
		void update_restaurant_info();
};
#endif
