#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game{
	private:
		int num_turn;
		int num_houses;
		int num_apartments;
		int num_businesses;
		House* houses;
		Apartment_Complex* apartments;
		Business_Complex* businesses;
		Player p;
	public:
		Game();
		bool game_over();
		void play_game();
		void collect_mortgage();
		void collect_rent();
		void collect_tax();
		void random_event();
		void adjust_tax();
		void buy_property();
		void sell_property();
		void adjust_property();
		void get_random_properties();
};

#endif
