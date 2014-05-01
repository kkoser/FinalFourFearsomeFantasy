//
//  Character.cpp
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "Character.h"

Character::Character() {

    //default character
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
    
    //open file
    ifstream file;
    file.open(fileName.c_str());
    
    if (!file) {
        cout<<"File "<<fileName<<" failed to open"<<endl;
        return;
    }
    
    //read values from file
    file >> name;
    file >> maxHealth;
    file >> standardPower;
    file >> maxPP;
    file >> standardPPRegen;
    file >> currentHealth; //CHANGE?
    file >> exp;
    //get full path of sprite
    file >> spriteName;
    spriteFullPath = pathForFile("Images/" + spriteName);

    
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
        
        Character *ch = this; //the target of each action of the move
        
        int hasRun = 0; //for once keyword
        

        
        //iterate through targets
        typename vector<Character *>::iterator currentTarget;
        for (currentTarget = targets.begin(); currentTarget != targets.end(); ++currentTarget) {
            
            //get each word from line
            istringstream iss(line);
            string word;
            
            
            //parse word from line
            while (getline(iss, word, ' ')) {
                if (word=="Once") {
                    if (hasRun == 1) {
                        break; //skips whole line if prefaced with "Once" and it has already been done to one target this move
                    }
                }
                //display text
                else if (word=="Display") {
                    displayLog =  displayLog + this->displayStringForMove(line, *currentTarget, targetDamage, actorDamage);
                }
                //change target of move action
                else if (word=="Target") {
                    ch = *currentTarget;
                }
                else if (word=="Actor") {
                    ch = this;
                }
                //stat changers
                else if (word=="Health") {
                    getline(iss, word);
                    int oldVal = ch->getCurrentHealth();
                    int val = getValueForCommand(word, ch->getCurrentHealth(), this->getCurrentPower());
                    ch->changeHealth(val);
                    
                    if (ch == this) {
                        actorDamage = oldVal-val;
                    }
                    else {
                        targetDamage = oldVal-val;
                    }
                }
                else if (word=="Power") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentPower(), this->getCurrentPower());
                    ch->setCurrentPower(val);
                }
                else if (word=="PP") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentPP(), 1);
                    ch->setCurrentPP(val);
                }
                else if (word=="PPRegen") {
                    getline(iss, word);
                    
                    int val = getValueForCommand(word, ch->getCurrentPPRegen(), this->getCurrentPower());
                    ch->setCurrentPPRegen(val);
                }
                else if (word=="Status") {
                    getline(iss, word);
                    ch->applyStatus(word, this->getCurrentPower()); //pass in power of caster
                }
                else if (word=="Shield") {
                    getline(iss, word);
                    ch->setCurrentShield(getValueForCommand(word, ch->getCurrentShield(), this->getCurrentPower()));
                }
                
                else {
                    cout << "Error reading word " << word << endl;
                }
                hasRun = 1; //for once keyword
            }
        }
    }
}

void Character::applyStatus(string line, int casterPower) {
    
    istringstream issline(line);
    string word;
    
    Status thisStatus;
    
    //parse line
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
    
    isIncap = shouldBeIncap; //update incap
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

//0 means all characters
//-1 is all Friendlies
//-2 is all enemies
//-3 indicates the actor is the target
int Character::numTargetsForMove(string moveName) {
    string fileName = pathForFile("Moves/" + moveName + ".move");
    //open file
    ifstream file(fileName.c_str());
    
    if (!file) {
        cout<<"File "<<moveName<<" failed to open"<<endl;
    }
    
    string line;
    
    //search file for targets keyword
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
                else if (word == "ALL_FRIENDS") {
                    return -1;
                }
                else if (word == "ALL_ENEMIES") {
                    return -2;
                }
                else if (word == "SELF") {
                    return -3;
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

    //parse sign
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
        //swap variables with values
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
                    int val = currentPP - getValueForCommand(word, getCurrentPP(), 1);
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
    if (health <= 0 || currentHealth <= 0) {
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

void Character::regenPP()   {
    setCurrentPP(getCurrentPP()+getCurrentPPRegen());
}

int Character::getNumberOfStatuses() {
    return (int)statuses.size();
}