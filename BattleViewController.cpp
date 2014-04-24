//
//  BattleController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "BattleViewController.h"

BattleViewController::BattleViewController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren) : ViewController(ren) {
    mainChars = chars;
    enemies = enem;
    
    typename vector<MainCharacter *>::const_iterator iter;
    for (iter = mainChars.begin(); iter != mainChars.end(); ++iter) {
        //find the sprites!
    }
    
    //repeat for enemies
    
    //load background too
    
    //move labels
    move1 = TextLabel(550, 450, "Icy Wind", defaultFont, 24);
    move2 = TextLabel(550, 550, "Healing Salve", defaultFont, 24);
    move3 = TextLabel(850, 450, "Explosion", defaultFont, 24);
    move4 = TextLabel(850, 550, "Ronnicus Explodicus", defaultFont, 24);
    
}

int BattleViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!
    
    
    
    
    //draw the mainCharacters
    typename vector<CharacterView *>::const_iterator iter;
    for (iter = mainCharViews.begin(); iter != mainCharViews.end(); ++iter) {
        //iter->draw(renderer);
    }
    
    //draw the enemies
    
    //draw the background
    
    //draw the moves of the active character
    move1.draw(renderer);
    move2.draw(renderer);
    move3.draw(renderer);
    move4.draw(renderer);
    
    
    
    return 1;
}