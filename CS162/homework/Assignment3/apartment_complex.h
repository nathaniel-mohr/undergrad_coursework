#ifndef APARTMENT_COMPLEX_H
#define APARTMENT_COMPLEX_H

#include "property.h"
#include "citizen.h"

class Apartment_Complex: public Property{
	private:
		int apartment_num;
		static int num_apartments;
		int rooms;
		int rent;
		Citizen* renters;

	public:
		int get_rooms() const;
		int get_rent() const;
		Citizen* get_renters() const;

		void set_rooms(int);
		void set_rent(int);
		void set_renters(Citizen*);

		void print_apartment();

		Apartment_Complex();
		Apartment_Complex(const Apartment_Complex &);
		const Apartment_Complex & operator=(const Apartment_Complex &);
		~Apartment_Complex();
};

#endif
