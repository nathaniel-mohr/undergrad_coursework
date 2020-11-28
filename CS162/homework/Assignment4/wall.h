#ifndef WALL_H
#define WALL_H

#include "ant.h"

class Wall: public Ant{
	public:
		Wall();
		virtual string get_name();
};

#endif
