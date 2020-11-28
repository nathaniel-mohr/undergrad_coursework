#ifndef GAME_H
#define GAME_H

#include "bee.h"
#include "harvester.h"
#include "long_thrower.h"
#include "short_thrower.h"
#include "thrower.h"
#include "fire.h"
#include "wall.h"
#include "bodyguard.h"
#include "ninja.h"
#include <vector>

class Game{
	private:
		vector<Insect*> board[10];
		int food;
	public:
		int get_food() const;

		Game();

		void play_game();
		void turn();
		void print_board();
		void bee_generation();
		void ant_placement();
		Ant* get_ant();
		Ant* ant_switch(int);
		bool valid_ant(int);
		bool valid_index(Ant*, int);
		void ant_actions();
		void collect_food();
		void bee_actions();
		void bee_attack(int);
		bool contains_ants(vector<Insect*>);
		bool contains_ninja(vector<Insect*>);
		int first_def_ant(vector<Insect*>);	
		int first_off_ant(vector<Insect*>);	
		bool contains_bees(vector<Insect*>);
		int first_bee(vector<Insect*>);
		bool game_end();
};

#endif
