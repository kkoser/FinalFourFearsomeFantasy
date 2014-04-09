//
//  BattleController.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__BattleController__
#define __FinalFourFearsomeFantasy__BattleController__

#include "ViewController.h"
#include "CharacterView.h"
#include "Character.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Settings.h"


class BattleController : public ViewController {
private:
    LTexture bgText;
    
    vector<CharacterView *> mainCharViews;
    vector<CharacterView *> enemyViews;
    
    vector<MainCharacter *> mainChars;
    vector<Enemy *> enemies;
    
    void loadSprites();

public:
    BattleController(vector<Character *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren);
};

#endif /* defined(__FinalFourFearsomeFantasy__BattleController__) */
