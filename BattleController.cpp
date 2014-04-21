//
//  BattleController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "BattleController.h"

BattleController::BattleController(vector<Character *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren) : ViewController(ren) {
}

BattleController::BattleController(SDL_Renderer *ren) : ViewController(ren) {
    
}

void BattleController::draw(SDL_Event e) {
    ViewController::draw(e);
}