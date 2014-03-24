//
//  BaseCharacter.h
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

/*
This is the base character class of which other characters will inherit.
 It is an abstract class, as there will be no base character filetype to parse.
 */
#ifndef __tester__BaseCharacter__
#define __tester__BaseCharacter__

#include <iostream>
#include <string>
#include <vector>
#include "Move.h"

using namespace std;

class BaseCharacter {
protected:
	int maxHealth;
	int standardPower;
	int maxPP; //mana for moves
	int standardPPRegen;
	int standardArmor;
    
	int currentHealth; //current health in/out battle
    
	//these are augmented in battle and reset afterwords
	int currentPower;
	int currentPP;
	int currentPPRegen;
	int currentArmor;
    
	//these are not increased by level points
	int accuracy;
    
	string name;
    string file;
	vector<Move> moves;
	Move activeMoves[4];
    
	string spriteName;
        
public:
	BaseCharacter(string fileName);
    
	void actOnCharacter(BaseCharacter *ch, Move m);
    
    //attribute setters for battle
    void setPower(int p);
};

#endif /* defined(__tester__BaseCharacter__) */
