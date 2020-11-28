#ifndef HARVESTER_H
#define HARVESTER_H

#include "ant.h"

class Harvester: public Ant{
	public:
		Harvester();
		virtual string get_name();
};

#endif
