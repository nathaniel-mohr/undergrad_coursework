#ifndef SPACE_H
#define SPACE_H

#include <string>
#include <time.h>
#include <cstdlib>
#include "business.h" 

using namespace std;

class Space{
	private:
		string size;
		int rent;
		Business renter;

	public:
		int get_rent() const;
		Business get_renter() const;

		void set_rent(int);

		string random_size();
		void print_space();

		Space();	
};

#endif
