//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 3/20/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//
#include "MainCharacter.h"

MainCharacter::MainCharacter(string fileName) {
    
    ifstream file;
    file.open(fileName.c_str());
    
    if (!file) {
        cout<<"File "<<fileName<<" failed to open"<<endl;
        return;
    }
    
    for (int i = 0; i < 10; i++) {
        int val;
        file >> val;
        
        //the only things in the save file are the 4 base values and the health, which persists
        //characters are read in line by line in this order
        //pp and statuses do NOT persist from battle to battle, so aren't written to file
        switch (i) {
            case 0:
                maxHealth = val;
                break;
            case 1:
                standardPower = val;
                break;
            case 2:
                maxPP = val;
                break;
            case 3:
                standardPPRegen = val;
                break;
            case 4:
                currentHealth = val;
                break;
                
            default:
                break;
        }
    }
    
    currentPower = standardPower;
    currentPPRegen = standardPPRegen;
    currentPP = maxPP;
    currentShield = 0;
    
    fileName = fileName;
}

MainCharacter::~MainCharacter() {
    //save the character to the file so that the levels will persist
    this->writeToFile(file);
}

void MainCharacter::writeToFile(string fileName) {
    ofstream file;
    file.open(fileName.c_str());
    
    
}