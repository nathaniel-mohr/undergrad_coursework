#include "space.h"

int Space::get_rent() const{return rent;}
Business Space::get_renter() const{return renter;}

void Space::set_rent(int r){rent = r;}

string Space::random_size(){
	int ans = rand() % 3;
	switch (ans){
		case 0:
			return "small";
		case 1:
			return "medium";
		case 2:
			return "large";
	}
}

void Space::print_space(){
	cout << "Size: " << size << endl;
	cout << "Rent: " << rent << endl;
}

Space::Space(){
	rent = 0;
	size = random_size();
	Business renter;
}
