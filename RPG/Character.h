#ifndef Character_H
#define Character_H

#include "Stats.h"

class character {
	public:
	
	character(int intelligence, int dexterity, int strength, int hp);
	
	void attack();
	
	
	private:
	primary_stats primary;
	offensive_stats offensive;
	defensive_stats defensive;
	
	int _health;
	int _max_health;
};

#endif