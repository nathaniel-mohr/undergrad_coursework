#ifndef ANT_H
#define ANT_H

#include "insect.h"

class Ant: public Insect{
	protected:
		int food_cost;
	public:
		int get_food_cost() const;

		void set_food_cost(int);

		virtual string get_name() = 0;
};

#endif
