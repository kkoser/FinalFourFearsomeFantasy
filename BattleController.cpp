//
//  BattleController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "BattleController.h"

BattleController::BattleController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren) : ViewController(ren) {
    mainChars = chars;
    enemies = enem;
    
    typename vector<MainCharacter *>::const_iterator iter;
    for (iter = mainChars.begin(); iter != mainChars.end(); ++iter) {
        //find the sprites!
    }
    
    //repeat for enemies
    
}

int BattleController::draw(SDL_Event e) {
    ViewController::draw(e);
    
    //draw the mainCharacters
     typename vector<CharacterView *>::const_iterator iter;
    for (iter = mainCharViews.begin(); iter != mainCharViews.end(); ++iter) {
        
    }
    
    return 1;
}