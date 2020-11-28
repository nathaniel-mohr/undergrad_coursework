#ifndef BUSINESS_COMPLEX_H
#define BUSINESS_COMPLEX_H

#include "property.h"
#include "space.h"

class Business_Complex: public Property{
	private:
		static int num_businesses;
		int business_num;
		int num_spaces;
		Space* spaces;
	public:
		int get_num_spaces() const;
		Space* get_spaces() const;

		void print_b_complex();

		Business_Complex();
		const Business_Complex & operator=(const Business_Complex &);
		Business_Complex(const Business_Complex &);
		~Business_Complex();
};

#endif
