#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>

using namespace std;

class Shape{
	protected:
		string name;
		string color;
	public:
		string get_name() const;
		string get_color() const;

		void set_name(string);
		void set_color(string);

		virtual float calculate_area() = 0;
};

#endif
