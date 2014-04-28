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
#include "BattleCharacterView.h"
#include <cmath>
#include <sstream>

class BattleViewController : public ViewController {
private:
    LTexture bgText;
    LTexture text;
    
    //vectors of views
    vector<BattleCharacterView> mainCharViews;
    vector<BattleCharacterView> enemyViews;
    
    //vectors of models
    vector<MainCharacter *> mainChars;
    vector<Enemy *> enemies;
    
    //pointer to active character
    Character *activeCharacter;
    BattleCharacterView *activeCharacterView;
    string selectedMove;
    int selectedPos; //keeps track of what player is selected. Cannot use iterator because they are different classes
                     //its the index of the array of the character choosing their move
    vector<Character *> targets;
    
    
    ImageView backgroundImage;
    
    TextLabel activeMoves[4];
    
    TextLabel displayLabel;
    vector<string>displayText;
    
    void drawActiveMoves();
    
    vector<BattleCharacterView> plotViewsAroundCircle(int x, int y, int radius, vector<Character *> chars);
    
    void animateActiveCharacter();
    
    void handleEvent(SDL_Event e);
    void nextCharacer();
    void updateCharacterViews();
    
    void displayNextLine();
    
    
public:
    BattleViewController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren);
    
    virtual int draw(SDL_Event e);
};

#endif /* defined(__FinalFourFearsomeFantasy__BattleController__) */
