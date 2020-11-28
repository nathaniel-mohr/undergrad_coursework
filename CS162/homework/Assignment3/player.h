#ifndef PLAYER_H
#define PLAYER_H

#include "house.h"
#include "apartment_complex.h"
#include "business_complex.h"
#include <string>
#include <iostream>

using namespace std;

class Player{
	private:
		int bank_balance;
		int num_houses;
		House* houses;
		int num_apartments;
		Apartment_Complex* apartments;
		int num_businesses;
		Business_Complex* businesses;

	public:
		int get_bank_balance() const;
		int get_num_houses() const;
		int get_num_apartments() const;
		int get_num_businesses() const;
		House* get_houses() const;
		Apartment_Complex* get_apartments() const;
		Business_Complex* get_businesses() const;

		void set_bank_balance(int);
		
		void print_player();
		void hurricane();
		void tornado();
		void earthquake();
		void wildfire();
		void stock_market();
		void gentrification();
		void sell_house();
		void sell_apartment();
		void sell_business();
		void sold_house(House);
		void sold_apartment(Apartment_Complex);
		void sold_business(Business_Complex);
		void adjust_house();
		void adjust_apartment();
		void adjust_business();

		Player();
};


#endif
