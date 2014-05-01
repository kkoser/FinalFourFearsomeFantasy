//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 3/20/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//
#include "MainCharacter.h"

MainCharacter::MainCharacter(string file) : Character(file) {
    
    fileName = fileName;
}

MainCharacter::~MainCharacter() {
    //save the character to the file so that the levels will persist
    this->writeToFile(fileName);
}

//used to save stats changes (i.e. leveling)
//mirrors the Constructor of Character
void MainCharacter::writeToFile(string fileName) {
    ofstream file;
    file.open(fileName.c_str());
    
    file << name << endl;
    file << maxHealth << endl;
    file << standardPower << endl;
    file << maxPP <<endl;
    file << standardPPRegen << endl;
    file << currentHealth << endl;
    file << exp << endl;
    file << spriteName << endl;
    
    string fullmoves = "";
    typename vector<string>::iterator move;
    for (move = moves.begin(); move != moves.end(); ++move) {
        if (fullmoves.compare("") != 0) {
            fullmoves = fullmoves + ","; //append a comma at the end of the previous move, but only if there is a previous move
        }
        fullmoves = fullmoves + *move;
    }
    
    file.close();
    
}

//convenience method for leveling up
void MainCharacter::levelUp(int healthAdded, int powerAdded, int ppRegenAdded) {
    maxHealth += healthAdded;
    standardPower += powerAdded;
    standardPPRegen += ppRegenAdded;
}

void MainCharacter::addExperience(int added) {
    exp += added;
    if (exp > EXP_TO_LEVEL) {
        exp = 0;
        levelUp(5, 1, 1);
    }
}