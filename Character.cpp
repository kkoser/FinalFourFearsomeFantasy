//
//  Character.cpp
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "Character.h"

Character::Character() {
    
    

    maxHealth = 100;
    standardPower = 10;
    maxPP = 10;
    standardPPRegen = 1;
    
    currentPPRegen = 1;
    currentPP = 10;
    currentPower = 10;
    currentHealth = 100;
    currentShield = 0;
    
}

Character::Character(string fileName) {
    
    ifstream file;
    file.open(fileName.c_str());
    
    if (!file) {
        cout<<"File "<<fileName<<" failed to open"<<endl;
        return;
    }
    
    /*
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
            case 5:
                spriteName = val;
                
            default:
                break;
        }
    }*/
    
    file >> name;
    file >> maxHealth;
    file >> standardPower;
    file >> maxPP;
    file >> standardPPRegen;
    file >> currentHealth; //CHANGE?
    file >> exp;
    //get full path of sprite
    file >> spriteName;
    stringstream fullPath;
    fullPath << "Images/" << spriteName;
    spriteFullPath = pathForFile(fullPath.str());

    
    
    string moveList;
    file >> moveList;
    istringstream stream(moveList);
    string move;
    
    while (getline(stream, move, ',')) {
        moves.push_back(move);
    }
    
    
    currentPower = standardPower;
    currentPPRegen = standardPPRegen;
    currentPP = maxPP;
    currentShield = 0;
}

void Character::actMoveOnTarget(string moveName, vector<Character *> targets) {
    
    string fileName = pathForFile("Moves/" + moveName + ".move");
    //open file
    ifstream file(fileName.c_str());
    //check for open
    if (!file) {
        cout<<"File "<<fileName<<" failed to open"<<endl;
        return;
    }
    
    //keep track of the most recent damage dealt
    //used for display
    int actorDamage = 0;
    int targetDamage = 0;
    
    //get each line from file
    string line;
    while (getline(file, line)) {
        
        Character *ch = this;
        
        int hasRun = 0; //for once keyword
        

        
        //iterate through targets
        typename vector<Character *>::iterator currentTarget;
        for (currentTarget = targets.begin(); currentTarget != targets.end(); ++currentTarget) {
            
            //get each word from line
            istringstream iss(line);
            string word;
            
            
            
            while (getline(iss, word, ' ')) {
                if (word=="Once") {
                    if (hasRun == 1) {
                        break; //skips whole line if prefaced with "Once" and it has already been done to one target this move
                    }
                }
                else if (word=="Display") {
                    displayLog =  displayLog + this->displayStringForMove(line, targets[0], targetDamage, actorDamage);
                }
                else if (word=="Target") {
                    ch = *currentTarget;
                }
                else if (word=="Actor") {
                    ch = this;
                }
                else if (word=="Health") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentHealth(), ch->getCurrentPower());
                    ch->changeHealth(val);
                    
                    if (ch == this) {
                        actorDamage = val;
                    }
                    else {
                        targetDamage = val;
                    }
                }
                else if (word=="Power") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentPower(), ch->getCurrentPower());
                    ch->setCurrentPower(val);
                }
                else if (word=="PP") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentPP(), 1);
                    ch->setCurrentPP(val);
                }
                else if (word=="PPRegen") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentPPRegen(), ch->getCurrentPower());
                    ch->setCurrentPPRegen(val);
                }
                else if (word=="Status") {
                    getline(iss, word);
                    ch->applyStatus(word, getCurrentPower()); //pass in power of caster
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
        if (word=="HPT") {
            getline(issline, word, ' ');
            int hpt = getValueForCommand(word, getCurrentHealth(), casterPower) - getCurrentHealth();
            thisStatus.healthPerTurn = hpt;
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
        
        changeHealth(getCurrentHealth() + currentStatus->healthPerTurn); //do damage
        if (currentStatus->causesIncap) {
            shouldBeIncap = 1;
        }
        
    }
    
    isIncap = shouldBeIncap;
}

void Character::changeHealth(int newHealth) {
    if (getCurrentShield()>0) {
        int deltaHealth = newHealth - getCurrentHealth();
        if (deltaHealth <= 0) { //if a damaging change and not a healing one
            int newDelta = deltaHealth + getCurrentShield(); //mitigate with shield
            if (newDelta > 0) { //shield holds
                setCurrentShield(newDelta);
            }
            else {
                setCurrentHealth(getCurrentHealth() + newDelta); //shield breaks
                setCurrentShield(0);
            }
        }
    }
    else setCurrentHealth(newHealth); // no shield or not damaging
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

string Character::displayStringForMove(string com, Character *target, int targetDamage, int actorDamage) {
    ostringstream output;
    
    istringstream iss(com);
    string word;
    
    int foundDisplay = 0;
    while (getline(iss, word, ' ')) {
        //skip the first line, becuase it is the keyword Display
        if (foundDisplay == 0) {
            if (word.compare("Display") == 0) {
                foundDisplay = 1;
            }
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
                output << target->getName();
            }
            else if (word == "$ACTOR_HEALTH") {
                output << this->getCurrentHealth();
            }
            else if (word == "$TARGET_HEALTH") {
                output << target->getCurrentHealth();
            }
            else if (word == "$ACTOR_DAMAGE") {
                output << actorDamage;
            }
            else if (word == "$TARGET_DAMAGE") {
                output << targetDamage;
            }
            
        }
        
        output << " ";
        
    }
    
    output<<endl;
    return output.str();
}

bool Character::canCastMove(string moveName) {
    //open file
    string fileName = pathForFile("Moves/" + moveName + ".move");
    ifstream file(fileName.c_str());
    //check for open
    if (!file) {
        cout<<"File "<<moveName<<" failed to open"<<endl;
        return 0;
    }
    
    //get each line from file
    string line;
    while (getline(file, line)) {
        istringstream issline(line);
        string word;
        while (getline(issline, word, ' ')) {
            if (word=="Actor") {
                getline(issline, word, ' ');
                if (word=="PP") {
                    getline(issline, word, ' ');
                    int val = getValueForCommand(word, getCurrentPP(), 1);
                    if (val<0) { //not enough pp
                        return false;
                    }
                }
            }
        }
    }
    return true; //enough pp!
}

int Character::ppCostForMove(string move) {
    string fileName = pathForFile("Moves/" + move + ".move");
    ifstream file(fileName.c_str());
    //check for open
    if (!file) {
        cout<<"File "<<move<<" failed to open"<<endl;
        return 0;
    }
    
    //get each line from file
    string line;
    while (getline(file, line)) {
        istringstream issline(line);
        string word;
        while (getline(issline, word, ' ')) {
            if (word=="Actor") {
                getline(issline, word, ' ');
                if (word=="PP") {
                    getline(issline, word, ' ');
                    int val = getValueForCommand(word, getCurrentPP(), 1);
                    return val;
                }
            }
        }
    }
    return 0;
}

//---------------------

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
    currentPower = power;
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
    currentPPRegen = PPRegen;
}

int Character::getCurrentShield() {
    return currentShield;
}

void Character::setCurrentShield(int shield) {
    if (currentShield < 0) {
        shield = 0;
    }
        currentShield = shield;
}

string Character::getName() {
    return name;
}

vector<string> Character::getMoves() {
    return moves;
}

string Character::getSpriteFile() {
    return spriteFullPath;
}

int Character::getMaxHealth() {
    return maxHealth;
}

int Character::getMaxPP() {
    return maxPP;
}

int Character::getIsIncap() {
    return isIncap;
}

string Character::getDisplayLog() {
    return displayLog;
}

void Character::clearDisplayLog() {
    displayLog = "";
}