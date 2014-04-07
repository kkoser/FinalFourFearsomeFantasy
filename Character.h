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

typedef enum {NOSTATUS, DPT, SHIELD, INCAP} Statuses; //these can be applied by the move
//typedef enum {NOATTRIBUTE, POWER, CURRENTPP, PPREGEN, ARMOR} Attributes; //certain moves multiply these

using namespace std;

typedef struct {
    int turnsUntilGone; //when zero, status is removed
    bool causesIncap; //when 1, status incapacitates character
    int damagePerTurn; //amount of damage to be dealt per turn
    
    
} Status;

class Character {
protected:
    
	int maxHealth;
	int standardPower;
	int maxPP; //mana for moves
	int standardPPRegen;
	//int standardArmor;
    
	int currentHealth; //current health in/out battle
    
	//these are augmented in battle and reset afterwords
	int currentPower;
	int currentPP;
	int currentPPRegen;
	//int currentArmor;
    
	//these are not increased by level points
	int accuracy;
    
    int isIncap;
    
	string name;
    string file;
	
    vector<string> moves;
    vector<Status> statuses;
    
	string spriteName;
        
public:
	Character(string fileName);
    
    void actMoveOnTarget(string moveName, vector<Character> targets);
    
    int numTargetsForMove(string moveName); //returns 0 if all
    
    //setters and getters, these adjust for <0 or >max inputs
    int getCurrentHealth();
    void setCurrentHealth(int health);
    int getCurrentPower();
    void setCurrentPower(int power);
    int getCurrentPP();
    void setCurrentPP(int PP);
    int getCurrentPPRegen();
    void setCurrentPPRegen(int PPRegen);
    
    string getName();
    
    void applyStatus(string line, int casterPower); //applies status to self
    
    void updateStatuses(); //updates each status (to be done at beginning of turn)
    
    
private:
    
    string displayStringForMove(string command, Character target); //creates text to be displayed
    int getValueForCommand(string command, int baseVal, int power); //baseval typically a char's stat
    

};

#endif /* defined(__tester__Character__) */
