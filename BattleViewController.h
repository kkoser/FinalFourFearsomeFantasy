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
    bool moveFinal = false;
    int selectedPos; //keeps track of what player is selected. Cannot use iterator because they are different classes
                     //its the index of the array of the character choosing their move
    int arrowSelectedPos; //the index of characters+enemies that the arrow keys are hovering over
    
    bool victory;
    bool defeat;
    bool displayingFinalText;
    TextLabel finalText;
    
    vector<Character *> targets;
    
    
    ImageView backgroundImage;
    
    TextLabel activeMoves[4];
    
    TextLabel displayLabel;
    vector<string>displayText;
    
    void drawActiveMoves();
    void updateActiveMoves();
    
    vector<BattleCharacterView> plotViewsAroundCircle(int x, int y, int radius, float startingAngle, vector<Character *> chars);
    
    void animateActiveCharacter();
    
    void handleEvent(SDL_Event e);
    void nextCharacter();
    void updateCharacterViews();
    
    void displayNextLine();
    
    BattleCharacterView* getViewForIndex(int index); //gets view corresponding to character + enemies array
    void changeArrowSelectedPos(int delta); //+1 or -1
    
    bool arePlayersDead(); //returns 1 if all friendlies dead
    bool areEnemiesDead(); //returns 1 if all enemies dead
    
    bool enemyActing; //used to only draw character moves
    
public:
    BattleViewController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren);
    ~BattleViewController();
        
    virtual int draw(SDL_Event e);
    
    virtual void becomeTop();
    virtual void dismiss();
};

#endif /* defined(__FinalFourFearsomeFantasy__BattleController__) */
