#include "business_complex.h"

int Business_Complex::num_businesses = 0;

int Business_Complex::get_num_spaces() const{return num_spaces;}
Space* Business_Complex::get_spaces() const{return spaces;}


void Business_Complex::print_b_complex(){
	cout << "Business #" << business_num << endl;
	cout << "Property Value: " << property_value << endl;
	cout << "Location: " << location << endl;
	cout << "Mortgage: " << mortgage << endl;
	cout << "Property Tax: " << property_tax << endl;
	cout << "Number of Spaces: " << num_spaces << endl;
	for(int i = 0; i < num_spaces; i++){
		cout << "Space #" << i+1 << endl;
		spaces[i].print_space();
	}
	cout << endl;
}

Business_Complex::Business_Complex(){
	num_businesses++;
	business_num = num_businesses;
	property_value = rand() % 200000 + 400000;
	property_tax = property_value * .015;
	num_spaces = rand() % 5 + 1;
	spaces = new Space[num_spaces];
}

const Business_Complex & Business_Complex::operator =(const Business_Complex &orig){
	Property::operator=(orig);
	business_num = orig.business_num;
	num_spaces = orig.num_spaces;
	if(spaces != NULL){
		delete[] spaces;
	}
	spaces = new Space[num_spaces];
	for(int i = 0; i < num_spaces; i++){
		spaces[i] = orig.spaces[i];
	}
}

Business_Complex::Business_Complex(const Business_Complex &orig):Property(orig){
	business_num = orig.business_num;
	num_spaces = orig.num_spaces;
	spaces = new Space[num_spaces];
	for(int i = 0; i < num_spaces; i++){
		spaces[i] = orig.spaces[i];
	}
}

Business_Complex::~Business_Complex(){
	delete[] spaces;
}
