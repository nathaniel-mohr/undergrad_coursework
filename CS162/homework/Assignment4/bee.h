#ifndef BEE_H
#define BEE_H

#include "insect.h"

class Bee: public Insect{
	public:
		Bee();
		virtual string get_name();
};

#endif
