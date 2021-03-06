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
	int expToNextLevel;
    
    string dialogueSpriteName;
    string movementSpriteName;
    
    
public:
	MainCharacter(string fileName);
    ~MainCharacter();
    
    void levelUp(int healthAdded, int powerAdded, int ppRegenAdded, int armorAdded);


	void actOnCharacter(Character &ch, string moveName);
    
    void writeToFile(string fileName);
};


#endif /* defined(__tester__MainCharacter__) */
