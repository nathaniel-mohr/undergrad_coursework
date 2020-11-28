#include "rectangle.h"

float Rectangle::get_base() const{return base;}
float Rectangle::get_height() const{return height;}

void Rectangle::set_base(float b){base = b;}
void Rectangle::set_height(float h){height = h;}

float Rectangle::calculate_area(){
	return base * height;
}

Rectangle::Rectangle(){
	name = "Rectangle";
}
