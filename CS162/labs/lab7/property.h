#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <cstdlib>

using namespace std;

class Property{
	protected:
		int property_value;
		string location;
		int mortgage;
		int mortgage_payments;
		float property_tax;
	public:
		
		int get_property_value() const;
		string get_location() const;
		int get_mortgage() const;
		int get_mortgage_payments() const;
		float get_property_tax() const;

		void set_property_value(int);
		void set_location(string);
		void set_mortgage(int);
		void set_mortgage_payments(int);
		void set_property_tax(float);
		
		static string random_location();

		Property();

		bool operator<(const Property &);
		bool operator>(const Property &);
};

#endif
