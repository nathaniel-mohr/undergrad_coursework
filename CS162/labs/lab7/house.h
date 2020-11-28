#ifndef HOUSE_H
#define HOUSE_H

#include "property.h"
#include "citizen.h"

class House: public Property{
	private:
		int house_num;
		int rent;
		Citizen owner;
		static int num_houses;

	public:
		int get_rent() const;
		Citizen get_owner() const;

		void set_rent(int);
		void set_owner(Citizen);

		void print_house();
		
		House();
};


#endif
