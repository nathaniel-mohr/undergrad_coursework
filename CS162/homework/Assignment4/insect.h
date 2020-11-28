#ifndef INSECT_H
#define INSECT_H

#include <iostream>
#include <string>

using namespace std;

class Insect{
	protected:
		int armor;
		int damage;
	public:
		int get_armor() const;
		int get_damage() const;

		void set_armor(int);
		void set_damage(int);

		virtual string get_name() = 0;
};

#endif
