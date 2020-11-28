//#include "house.h"
#include "shape.h"
#include "circle.h"
#include "rectangle.h"

void print_shape_info(Shape &s){
	cout << "Name: " << s.get_name() << endl;
	cout << "Color: " << s.get_color() << endl;
	cout << "Area: " << s.calculate_area() << endl;
	cout << endl;
}

int main(){
	/*House one;
	House two;

	one.print_house();
	two.print_house();

	cout << "First house < Second House" << endl;
	cout << (one < two) << endl;
	cout << "First house > Second House" << endl;
	cout << (one > two) << endl;
	*/
	
	Circle c;
	Rectangle r;
	print_shape_info(c);
	print_shape_info(r);

	c.set_radius(25);
	r.set_base(10);
	r.set_height(5);

	print_shape_info(c);
	print_shape_info(r);
}
