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
    
    ifstream file(moveName.c_str());
    
    if (!file) {
        cout<<"File "<<moveName<<" failed to open"<<endl;
    }
    
    string line;
    while (getline(file, line)) {
        
        Character &ch = *this;
        
        istringstream iss(line);
        string word;
        while (getline(iss, word, ' ')) {
            if (word.compare("Display")) {
                this->displayForMove(line);
            }
            else if (word.compare("Target")) {
                ch = targets[0];
                
            }
            else if (word.compare("Actor")) {
                ch = *this;
            }
            else if (word.compare("Health")) {
                getline(iss, word);
                int val;
                if (word.compare("MAX")) {
                    val = ch.getHealth();
                }
                else if (word.compare("HALF")) {
                    val = ch.getHealth()/2;
                }
                if (word.compare("-MAX")) {
                    val = -1*ch.getHealth();
                }
                else if (word.compare("-HALF")) {
                    val = -1*ch.getHealth()/2;
                }
                
                else {
                    val = atoi(word.c_str()); //replace with numeric value of word
                }
                ch.setHealth(ch.getHealth()+val);
            }
            else if
            
        }
        
        //read line
        //tokenize into array of words
        //if statements for each keyword
    }
    
}

int Character::numTargetsForMove(string moveName) {
    ifstream file(moveName.c_str());
    
    if (!file) {
        cout<<"File "<<moveName<<" failed to open"<<endl;
    }
    
    string line;
    
    while (file.good()) {
        getline(file, line);
        //look for TARGETS keyword, otherwise move on
        //defaults to 1 if can't find target
    }
    
    return 1;
}

void Character::displayForMove(string str) {
    
}