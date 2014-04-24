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
#include "TextLabel.h"
#include "ImageView.h"


class BattleViewController : public ViewController {
private:
    LTexture bgText;
    LTexture text;
    
    vector<CharacterView *> mainCharViews;
    vector<CharacterView *> enemyViews;
    
    vector<MainCharacter *> mainChars;
    vector<Enemy *> enemies;
    
    MainCharacter *activeCharacter;
    
    void loadSprites();
    
    ImageView backgroundImage;
    
    TextLabel move1;
    TextLabel move2;
    TextLabel move3;
    TextLabel move4;

public:
    BattleViewController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren);
    
    virtual int draw(SDL_Event e);
};

#endif /* defined(__FinalFourFearsomeFantasy__BattleController__) */
