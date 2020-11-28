#ifndef NINJA_H
#define NINJA_H

#include "ant.h"

class Ninja: public Ant{
	public:
		Ninja();
		virtual string get_name();
};

#endif
