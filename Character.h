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
    
	string name;
    string file;
	
    vector<string> moves;
    
	string spriteName;
    
    string displayLog;
        
public:
	Character(string fileName);
    
    //attribute setters for battle
    void setPower(int p);
    
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
    
    
private:
    
    string displayStringForMove(string command, Character target, int targetDamage, int actorDamage); //creates text to be displayed
    int getValueForCommand(string command, int baseVal, int power); //baseval typically a char's stat
    

};

#endif /* defined(__tester__Character__) */
