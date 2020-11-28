#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <math.h>

class Circle:public Shape{
	private:
		float radius;
	public:
		float get_radius() const;
		void set_radius(float);
		virtual float calculate_area();

		Circle();
};

#endif
