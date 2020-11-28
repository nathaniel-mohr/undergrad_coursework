#include "circle.h"

float Circle::get_radius() const{return radius;}

void Circle::set_radius(float r){radius = r;}

float Circle::calculate_area(){
	return M_PI * radius * radius;	
}

Circle::Circle(){
	name = "Circle";
}
