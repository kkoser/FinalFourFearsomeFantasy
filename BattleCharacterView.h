//
//  BattleCharacterView.h
//  FFFF
//
//  Created by Zach Waterson on 4/26/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __FFFF__BattleCharacterView__
#define __FFFF__BattleCharacterView__

#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "StatBar.h"
#include "TextLabel.h"
#include "ImageView.h"
#include <sstream>


using namespace std;

class BattleCharacterView {
    
public:
    BattleCharacterView(string n = "name", int x = 0, int y = 0, int cHealth = 100, int mHealth = 100, int cPP = 20, int mPP = 20, int cShield = 0, bool incap = 0, string spriteLoc = "", SDL_Renderer *rend = NULL);
    
    void setPos(int x, int y);
    int getXPos();
    int getYPos();
    void setCurrentHealth(int cHealth);
    void setCurrentPP(int cPP);
    void setCurrentShield(int cShield);
    void setIsIncap(bool incap);
    void setIsAnimating(bool anim);
    bool getIsAnimating();
    void setIsTargeted(bool targ);
    bool getIsTargeted();
    void setHasCursor(bool curs);
    bool getHasCursor();
    void setHasStatus(bool stat);
    bool gethasStatus();
    
    void draw();
    

private:
    int xpos;
    int ypos;
    int currentHealth;
    int maxHealth;
    int currentPP;
    int maxPP;
    int currentShield;
    
    bool isAnimating;
    double animateDelta; //amount to change animation by
    void animate();
    
    bool isTargeted;
    bool hasCursor;
    bool hasStatus;
    bool isIncap;

    string name;
    string spriteLocation;
    
    //things to draw
    ImageView image;
    TextLabel nameLabel;
    TextLabel shieldLabel;
    StatBar healthBar;
    StatBar PPBar;
    ImageView cursorImage;
    ImageView statusImage;
    ImageView incapImage;
    ImageView deadImage;
    
    SDL_Renderer *renderer;
    
};

#endif /* defined(__FFFF__BattleCharacterView__) */
