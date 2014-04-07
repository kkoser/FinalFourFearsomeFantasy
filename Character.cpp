//
//  Character.cpp
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "Character.h"

Character::Character(string fileName) {
    
    maxHealth = 100;
    standardPower = 10;
    maxPP = 10;
    standardPPRegen = 1;
    
    currentPPRegen = 1;
    currentPP = 10;
    currentPower = 10;
    currentHealth = 100;
    
    fileName = fileName;
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
        
        int hasRun = 0; //for once keyword
        
        //iterate through targets
        typename vector<Character>::iterator currentTarget;
        for (currentTarget = targets.begin(); currentTarget != targets.end(); ++currentTarget) {
        
            //get each word from line
            istringstream iss(line);
            string word;
            
            while (getline(iss, word, ' ')) {
                if (word=="Once") {
                    if (hasRun == 1) {
                        continue; //skips whole line if prefaced with "Once" and it has already been done to one target this move
                    }
                }
                else if (word=="Display") {
                    this->displayStringForMove(line, targets[0]);
                }
                else if (word=="Target") {
                    ch = *currentTarget;
                    
                }
                else if (word=="Actor") {
                    ch = *this;
                }
                else if (word=="Health") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch.getCurrentHealth(), ch.getCurrentPower());
                    ch.setCurrentHealth(val);
                }
                else if (word=="Power") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch.getCurrentPower(), ch.getCurrentPower());
                    ch.setCurrentPower(val);
                }
                else if (word=="PP") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch.getCurrentPP(), 1);
                    ch.setCurrentPP(val);
                }
                else if (word=="PPRegen") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch.getCurrentPPRegen(), ch.getCurrentPower());
                    ch.setCurrentPPRegen(val);
                }
                else if (word=="Status") {
                    getline(iss, word);
                    ch.applyStatus(word, getCurrentPower()); //pass in power of caster
                }
                
                else {
                    cout << "Error reading word " << word << endl;
                }
                hasRun = 1;
            }
        }
    }
}

void Character::applyStatus(string line, int casterPower) {
    
    istringstream issline(line);
    string word;
    
    Status thisStatus;
    
    while (getline(issline, word, ' ')) {
        if (word=="DPT") {
            getline(issline, word, ' ');
            thisStatus.damagePerTurn = casterPower*atof(word.c_str());
        }
        else if (word=="Incap") {
            getline(issline, word, ' ');
            if (word=="YES") {
                thisStatus.causesIncap = 1;
            }
            else {
                thisStatus.causesIncap = 0;
            }
        }
        else if (word=="Length") {
            getline(issline, word, ' ');
            thisStatus.turnsUntilGone = atof(word.c_str());
        }
        else thisStatus.turnsUntilGone = 1; //default to single turn status
    }
    statuses.push_back(thisStatus); //save status to array
    
}

void Character::updateStatuses() {
    
    int shouldBeIncap = 0; //statuses will update this if char should be incap
    
    typename vector<Status>::iterator currentStatus;
    for (currentStatus = statuses.begin(); currentStatus != statuses.end(); ++currentStatus) {
        
        //check if status expires
        if (currentStatus->turnsUntilGone==0) {
            
            currentStatus = statuses.erase(currentStatus); //erase any statuses that need to go
            if (currentStatus == statuses.end()) {
                break; //check to see if had removed last status
            }
        }
        
        //update status and character
        currentStatus->turnsUntilGone = currentStatus->turnsUntilGone - 1; //decrement turns left
        setCurrentHealth(getCurrentHealth() - currentStatus->damagePerTurn); //do damage
        if (currentStatus->causesIncap) {
            shouldBeIncap = 1;
        }
        
    }
    
    isIncap = shouldBeIncap;
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
    
    
int Character::getValueForCommand(string com, int baseVal, int power) {
    int val = 0;
    
    //first check what kind of change we're doing
    char c = com.at(0);
    com.erase(0,1); //get rid of sign
    float movePower = atof(com.c_str()); //get move power
    int totalPower = power*movePower; //int totalPower truncates decimals

    switch (c) {
        case '+':
            val = baseVal + totalPower;
            break;
        case '-':
            val = baseVal - totalPower;
            break;
        case '*':
            val = baseVal*totalPower;
            break;
        case '/':
            val = baseVal/totalPower;
            break;
        default:
            val = 0;
            break;
    }
    
    return val;
}

string Character::displayStringForMove(string com, Character target) {
    ostringstream output;
    
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
            output << word;
        }
        else {
            if (word == "$ACTOR_NAME") {
                output << this->getName();
            }
            else if (word == "$TARGET_NAME") {
                output << target.getName();
            }
            else if (word == "$ACTOR_HEALTH") {
                output << this->getCurrentHealth();
            }
            else if (word == "$TARGET_HEALTH") {
                output << target.getCurrentHealth();
            }
            
        }
        
    }
    
    
    return output.str();
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
    else {
        currentPower = power;
    }
}

int Character::getCurrentPP() {
    return currentPP;
}

void Character::setCurrentPP(int PP) {
    if (PP < 0) {
        PP = 0;
    }
    else if (PP > maxPP){
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
    else {
        currentPPRegen = PPRegen;
    }
}

string Character::getName() {
    return name;
}