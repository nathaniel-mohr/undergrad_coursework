#ifndef BODYGUARD_H
#define BODYGUARD_H

#include "ant.h"

class Bodyguard: public Ant{
	public:
		Bodyguard();
		virtual string get_name();
};

#endif
