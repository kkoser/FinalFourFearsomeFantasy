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
#include "BaseCharacter.h"

using namespace std;

class MainCharacter : public BaseCharacter {
private:

	//these are not increased by level points
	int level;
	int exp;
	int expToNext;
    
    string dialogueSpriteName;
    
public:
	MainCharacter(string fileName);
    
    void levelUp(int healthAdded, int powerAdded, int ppRegenAdded, int armorAdded);
};


#endif /* defined(__tester__MainCharacter__) */
