//
//  MainCharacter.h
<<<<<<< HEAD
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __tester__MainCharacter__
#define __tester__MainCharacter__

#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

using namespace std;

class MainCharacter : public Character {
private:
=======
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
>>>>>>> FETCH_HEAD

	//these are not increased by level points
	int exp;
	int expToNext;
    
    string dialogueSpriteName;
    string movementSpriteName;
    
    
public:
	MainCharacter(string fileName);
<<<<<<< HEAD
    
    void levelUp(int healthAdded, int powerAdded, int ppRegenAdded, int armorAdded);
};


#endif /* defined(__tester__MainCharacter__) */
=======
    ~MainCharacter();

	void actOnCharacter(MainCharacter &ch, Move m);
    void levelUp(int healthAdded, int powerAdded, int ppRegenAdded, int armorAdded);
    
    void writeToFile(string fileName);
};
>>>>>>> FETCH_HEAD
