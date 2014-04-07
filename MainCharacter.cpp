//
//  MainCharacter.cpp

//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "MainCharacter.h"


MainCharacter::MainCharacter(string fileName) : Character(fileName) {
    file = fileName;
}

MainCharacter::~MainCharacter() {
    //save the character to the file so that the levels will persist
    this->writeToFile(file);
}

void MainCharacter::writeToFile(string fileName) {
    
}