#include "Arduino.h"
#include "Character.h"

character::character(int intelligence, int agility, int strength, int hp) {
	
	primary.intelligence = intelligence;
	primary.agility = agility;
	primary.strength = strength;
	
	_health = hp;
	_max_health = hp;
};

void character::attack() {
	int roll = random(100);
	if (roll > primary.agility) {
      Serial.print("Hit for ");
      Serial.print(primary.strength);
      Serial.println(" damage!");
    }
    else {
      Serial.println("Missed!");
    }
};