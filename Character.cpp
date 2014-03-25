//
//  Character.cpp
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "Character.h"

Character::Character(string fileName) {
    
}

void Character::actMoveOnTarget(string moveName, vector<Character> targets) {
    
    //open file
    ifstream file(moveName.c_str());
    //check for open
    if (!file) {
        cout<<"File "<<moveName<<" failed to open"<<endl;
        return;
    }
    
    //get each line from file
    string line;
    while (getline(file, line)) {
        
        Character &ch = *this;
        
        int hasRun = 0;
        
        //get each word from line
        istringstream iss(line);
        string word;
        while (getline(iss, word, ' ')) {
            if (word=="Once") {
                if (hasRun == 1) {
                    continue;
                }
            }
            else if (word=="Display") {
                this->displayStringForMove(line, targets[0]);
            }
            else if (word=="Target") {
                ch = targets[0];
                
            }
            else if (word=="Actor") {
                ch = *this;
            }
            else if (word=="Health") {
                getline(iss, word);
                
                int val = getValueForCommand(word, ch.getCurrentHealth());
                ch.setCurrentHealth(val);
            }
            else if (word=="Power") {
                getline(iss, word);
                
                int val = getValueForCommand(word, ch.getCurrentPower());
                ch.setCurrentPower(val);
            }
            else if (word=="PP") {
                getline(iss, word);
                
                int val = getValueForCommand(word, ch.getCurrentPP());
                ch.setCurrentPP(val);
            }
            else if (word=="PPRegen") {
                getline(iss, word);
                
                int val = getValueForCommand(word, ch.getCurrentPPRegen());
                ch.setCurrentPPRegen(val);
            }
            
            
            else {
                cout << "Error reading word " << word << endl;
            }
        }
        
        hasRun = 1;
    }
    
}

int Character::numTargetsForMove(string moveName) {
    ifstream file(moveName.c_str());
    
    if (!file) {
        cout<<"File "<<moveName<<" failed to open"<<endl;
    }
    
    string line;
    
    while (file.good()) {
        getline(file, line); //split file into lines
        
        istringstream iss(line); //convert to stream for tokenization
        string word; //individual word of line
        while (getline(iss, word, ' ')) { //store next word from line
            
            //look for TARGETS keyword, otherwise move on
            if (word=="Targets") {
                getline(iss, word, ' ');
                if (word=="ALL") {
                    return 0;
                }
                else {
                    return atoi(word.c_str()); //convert to int
                }
            }
        }
    }
    
    return 1;   //defaults to 1 if can't find target

}

int Character::getValueForCommand(string com, int baseVal) {
    int val = 0;
    
    //first check what kind of change we're doing
    char c = com.at(0);
    com.erase(0,1);
    switch (c) {
        case '+':
            val = baseVal + atoi(com.c_str());
            break;
        case '-':
            val = baseVal - atoi(com.c_str());
            break;
        case '*':
            val = (float)baseVal*atof(com.c_str());
            break;
        case '/':
            val = (float)baseVal/atof(com.c_str());
            break;
        default:
            val = 0;
            break;
    }
    
    return val;
}

string Character::displayStringForMove(string com, Character target) {
    string output;
    
    istringstream iss(com);
    string word;
    
    int isFirst = 1;
    while (getline(iss, word, ' ')) {
        //skip the first line, becuase it is the keyword Display
        if (isFirst == 1) {
            isFirst = 0;
            continue;
        }
        
        //$ is the keyword indicating a word needs to be parsed
        char c = word.at(0);
        if (c != '$') {
            output.append(word);
        }
        else {
            if (word == "$ACTOR_NAME") {
                output.append(this->getName());
            }
            else if (word == "$TARGET_NAME") {
                output.append(target.getName());
            }
        }
        
    }
    
    
    return NULL;
}

//setters and getters
int Character::getCurrentHealth() {
    return currentHealth;
}

void Character::setCurrentHealth(int health) {
    if (health < 0) {
        health = 0;
    }
    else if (health > maxHealth) {
        health = maxHealth;
    }
    currentHealth = health;
}

int Character::getCurrentPower() {
    return currentPower;
}

void Character::setCurrentPower(int power) {
    if (power < 0) {
        power = 0;
    }
    else if (power > standardPower) {
        power = standardPower;
    }
    currentPower = power;
}

int Character::getCurrentPP() {
    return currentPP;
}

void Character::setCurrentPP(int PP) {
    if (PP < 0) {
        PP = 0;
    }
    else if (PP > maxPP) {
        PP = maxPP;
    }
    currentPP = PP;
}

int Character::getCurrentPPRegen() {
    return currentPPRegen;
}

void Character::setCurrentPPRegen(int PPRegen) {
    if (PPRegen < 0) {
        PPRegen = 0;
    }
    else if (PPRegen > standardPPRegen) {
        PPRegen = standardPPRegen;
    }
    currentPPRegen = PPRegen;
}

string Character::getName() {
    return name;
}