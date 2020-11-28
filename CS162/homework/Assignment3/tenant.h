#ifndef TENANT_H
#define TENANT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

class Tenant{
	protected:
		string name;
		int max_budget;
		int agreeability;

	public:
		int get_max_budget() const;
		int get_agreeability() const;
		string get_name() const;

		void set_name(string);
		void set_max_budget(int);
		void set_agreeability(int);

		void print_tenant();
		void vacate();

		Tenant();
};

#endif
