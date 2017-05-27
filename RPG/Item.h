#ifndef Item_H
#define Item_H

class Item {
	public:
	primary_stats stats;
	
	Item(primary_stats);
};

class Weapon(Item) {
	public:
	offensive_stats offense;
	
	Weapon(primary_stats, offensive_stats);
}

class Armor(Item) {
	public:
	defensive_stats defense;
	
	Armor(primary_stats, defensive_stats);
}
#endif