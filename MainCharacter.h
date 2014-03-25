//
//  MainCharacter.h
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

	//these are not increased by level points
	int exp;
	int expToNext;
    
    string dialogueSpriteName;
    string movementSpriteName;
    
    
public:
	MainCharacter(string fileName);
    
    void levelUp(int healthAdded, int powerAdded, int ppRegenAdded, int armorAdded);
};


#endif /* defined(__tester__MainCharacter__) */
