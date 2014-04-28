//
//  Character.h
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

/*
This is the base character class of which other characters will inherit.
 */
#ifndef __tester__Character__
#define __tester__Character__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Settings.h"

using namespace std;

typedef struct {
    int turnsUntilGone; //when zero, status is removed
    bool causesIncap; //when 1, status incapacitates character
    int healthPerTurn; //amount of damage to be dealt per turn CAN BE NEGATIVE TO HEAL
} Status;

class Character {
protected:
    
    //these are stored to be returned to after battle (except health)
    //these can be improved by leveling up
	int maxHealth;
	int standardPower;
	int maxPP; //mana for moves
	int standardPPRegen;
	//int standardArmor;
    
	int currentHealth; //current health in/out battle
    
	//these are augmented in battle and reset afterwords to the above values
	int currentPower;
	int currentPP;
	int currentPPRegen;
    int currentShield; //reset to 0

	//int currentArmor;
    
	//these are not increased by level points
	//int accuracy;
    
    int isIncap;
    
	string name;
	
    vector<string> moves;
    vector<Status> statuses;
    
    string spriteName;
	string spriteFullPath;
    
    string displayLog;
    
    int exp;
        
public:
	Character();
    Character(string fileName);
    
    void actMoveOnTarget(string moveName, vector<Character *> targets);
    
    int numTargetsForMove(string moveName); //returns 0 if all
    
    //setters and getters, these adjust for <0 or >max inputs
    int getCurrentHealth();
    void setCurrentHealth(int health);
    int getMaxHealth();
    int getCurrentPower();
    void setCurrentPower(int power);
    int getCurrentPP();
    void setCurrentPP(int PP);
    int getMaxPP();
    int getCurrentPPRegen();
    void setCurrentPPRegen(int PPRegen);
    int getCurrentShield();
    void setCurrentShield(int shield);
    vector<string> getMoves();
    int ppCostForMove(string move);
    int getIsIncap();
    string getDisplayLog();
    void clearDisplayLog();
    
    string getSpriteFile(); //returns full path
    
    string getName();
    
    void applyStatus(string line, int casterPower); //applies status to self
    
    void updateStatuses(); //updates each status (to be done at beginning of turn)
    
    void changeHealth(int newHealth); //changes health, taking shields into account. pass in desired newHealth before shields
    
    bool canCastMove(string moveName); //checks if enough PP for move
    
    
private:
    
    string displayStringForMove(string command, Character *target, int targetDamage, int actorDamage); //creates text to be displayed
    int getValueForCommand(string command, int baseVal, int power); //baseval typically a char's stat, this parses and multiplies by the actor's power
    

};

#endif /* defined(__tester__Character__) */
