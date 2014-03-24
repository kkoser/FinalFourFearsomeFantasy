//
//  Move.h
//  FFFF
//
//  Created by Zach Waterson on 3/21/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __FFFF__Move__
#define __FFFF__Move__

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef enum {NOSTATUS, DPT, SHIELD, INCAP} Statuses; //these can be applied by the move
typedef enum {NOATTRIBUTE, POWER, CURRENTPP, PPREGEN, ARMOR} Attributes; //certain moves multiply these

class Move {
private:
    
	string name;
	string flavorText; //associated flavor text for move
    
	int power; //amount of damage or healing done (negative for damage)
	int isSingleTarget; //if false, will target entire eligible group
	int targetsEnemy; //if false, can target friendly party members
    
	Statuses statusToApply;
	int statusPower; //strength of status
    
	Attributes attributeToAugment;
	double attributeMultiplier; //amount attribute is to be changed (ie 1.2 or 0.8)
    

    
    
    
public:
    Move(string filename); //constructor
    bool needsTarget(); //returns isSingleTarget
    
};


#endif /* defined(__FFFF__Move__) */
