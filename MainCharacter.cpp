//
//  MainCharacter.cpp
<<<<<<< HEAD
//  tester
//
//  Created by Zach Waterson on 3/22/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "MainCharacter.h"
=======
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 3/20/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//
#include "MainCharacter.h"

MainCharacter::MainCharacter(string fileName) {
    file = fileName;
    activeMoves = NULL;
}

MainCharacter::~MainCharacter() {
    //save the character to the file so that the levels will persist
    this->writeToFile(file);
}
>>>>>>> FETCH_HEAD
