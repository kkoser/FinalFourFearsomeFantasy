//
//  MainCharacter.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 3/20/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include <string>
#include <vector>
#include "Move.h"

using namespace std;

class MainCharacter : public BaseCharacter {
private: 
	//these can be upgraded using level points
	int maxHealth;
	int standardPower;
	int maxPP; //mana for moves
	int standardPPRegen;
	int standardArmor;

	int currentHealth; //current health in battle

	//these are augmented in battle and reset afterwords
	int currentPower;
	int currentPP;
	int currentPPRegen;
	int currentArmor;

	//these are not increased by level points
	int level;
	int exp;
	int expToNext;
	int accuracy;

	string name;
    string file;
	vector<Move> moves;
	Move activeMoves[4];

	string spriteName;

public:
	MainCharacter(string fileName);
    ~MainCharacter();

	void actOnCharacter(MainCharacter &ch, Move m);
    void levelUp(int healthAdded, int powerAdded, int ppRegenAdded, int armorAdded);
    
    void writeToFile(string fileName);
};