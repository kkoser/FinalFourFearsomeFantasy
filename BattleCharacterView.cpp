//
//  BattleCharacterView.cpp
//  FFFF
//
//  Created by Zach Waterson on 4/26/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "BattleCharacterView.h"

BattleCharacterView::BattleCharacterView(string n, int x, int y, int cHealth, int mHealth, int cPP, int mPP, int cShield, bool incap, string spriteLoc, SDL_Renderer *rend) {
    name = n;
    xpos = x;
    ypos = y;
    currentHealth = cHealth;
    maxHealth = mHealth;
    currentPP = cPP;
    maxPP = mPP;
    currentShield = cShield;
    isIncap = incap;
    spriteLocation = spriteLoc;
    renderer = rend;
    
    //init image
    image = ImageView(x, y + 75, spriteLoc, renderer);
    animateDelta = 0.7;
    
    //init name
    nameLabel = TextLabel(x,y + 195, name, defaultFont, 24);
    nameLabel.setColor(255, 255, 255);

    //init shield text
    stringstream shieldText;
    shieldText << currentShield << " Shield";
    shieldLabel = TextLabel(x, y, shieldText.str());
    shieldLabel.setColor(255,255,255);
    
    //init green health bar
    healthBar = StatBar(x, y + 20, currentHealth, maxHealth, "Health", 0, 255, 0, 255);
    
    //init blue PP bar
    PPBar = StatBar(x, y + 50, currentPP, maxPP, "PP", 0, 0, 255, 255);
    
}

void BattleCharacterView::draw() {
    image.draw();
    nameLabel.draw(renderer);
    shieldLabel.draw(renderer);
    healthBar.draw(renderer);
    PPBar.draw(renderer);
}

void BattleCharacterView::animate() {
    if(image.getDegs()>3) {
        animateDelta = -0.7;
    }
    else if(image.getDegs() < -3) {
        animateDelta = 0.7;
    }
    image.setDegs(image.getDegs() + animateDelta);
}

//SETTERS / GETTERS

void BattleCharacterView::setPos(int x, int y) {
    xpos = x;
    ypos = y;
}

int BattleCharacterView::getXPos() {
    return xpos;
}

int BattleCharacterView::getYPos() {
    return ypos;
}

void BattleCharacterView::setCurrentHealth(int cHealth) {
    currentHealth = cHealth;
}

void BattleCharacterView::setCurrentPP(int cPP) {
    currentPP = cPP;
}

void BattleCharacterView::setCurrentShield(int cShield) {
    currentShield = cShield;
}

void BattleCharacterView::setIsIncap(bool incap) {
    isIncap = incap;
}
