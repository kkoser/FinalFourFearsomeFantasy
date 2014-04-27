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

void MainCharacter::writeToFile(string fileName) {
    ofstream file;
    file.open(fileName.c_str());
    
    
}