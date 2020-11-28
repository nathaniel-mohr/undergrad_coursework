#include "wall.h"

Wall::Wall(){
	food_cost = 4;
	armor = 4;
	damage = 0;
}

string Wall::get_name(){
	return "WALL";
}
