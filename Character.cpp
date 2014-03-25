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
    while (file.good()) {
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