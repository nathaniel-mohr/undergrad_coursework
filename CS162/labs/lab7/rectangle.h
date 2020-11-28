#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle:public Shape{
	private:
		float base;
		float height;
	public:
		float get_base() const;
		float get_height() const;

		void set_base(float);
		void set_height(float);

		virtual float calculate_area();

		Rectangle();
};

#endif
