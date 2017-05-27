#ifndef Stats_H
#define Stats_H

typedef struct primary_stats {
	int agility;
	int strength;
	int intelligence;
}primary_stats;

typedef struct offensive_stats {
	int physical_damage;
	int magical_damage;
}offensive_stats;

typedef struct defensive_stats {
	// Physical defense
	int physical_defense;
	int physical_block_percent;
	int physical_block_absolute;
	
	// Magical defense
	int magical_defense;
	int magical_block_percent;
	int magical_block_absolute;
	
	// Other
	int health;
	int mana;
	
}defensive_stats;

#endif