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
    isAnimating = 0; //init no animate
    isTargeted = 0;
    hasCursor = 0;
    hasStatus = 0;
    
    
    //init image
    image = ImageView(x, y + 75, spriteLoc, renderer);
    animateDelta = 0.7;
    
    //init Cursor, status, dead, incap
    cursorImage = ImageView(x-50, y + 20, pathForFile("Images/FF7Cursor.png"), renderer);
    statusImage = ImageView(x, y + 220, pathForFile("Images/statusIcon.png"), renderer);
    incapImage = ImageView(x + 20, y + 220, pathForFile("Images/incapIcon.png"), renderer);
    deadImage = ImageView(x + 40, y + 220, pathForFile("Images/deadIcon.png"), renderer);
    
    
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
    if (isAnimating) {
        animate();
    }
    //set red if targeted
    if (isTargeted) {
        nameLabel.setColor(255, 0, 0);
    }
    else {
        nameLabel.setColor(255, 255, 255);
    }
    
    //various icons
    if (hasCursor) {
        cursorImage.draw(renderer);
    }
    if (hasStatus) {
        statusImage.draw(renderer);
    }
    if (isIncap) {
        incapImage.draw();
    }
    if (currentHealth <= 0) {
        deadImage.draw(renderer);
    }
}

void BattleCharacterView::animate() {
    if(image.getDegs()>3) {
        animateDelta = -0.5;
    }
    else if(image.getDegs() < -3) {
        animateDelta = 0.5;
    }
    image.setDegs(image.getDegs() + animateDelta);
}

//SETTERS / GETTERS

void BattleCharacterView::setHasStatus(bool stat) {
    hasStatus = stat;
}

bool BattleCharacterView::gethasStatus() {
    return hasStatus;
}

void BattleCharacterView::setHasCursor(bool curs) {
    hasCursor = curs;
}

bool BattleCharacterView::getHasCursor() {
    return hasCursor;
}

void BattleCharacterView::setIsTargeted(bool targ) {
    isTargeted = targ;
}

bool BattleCharacterView::getIsTargeted() {
    return isTargeted;
}

void BattleCharacterView::setIsAnimating(bool anim) {
    isAnimating = anim;
}

bool BattleCharacterView::getIsAnimating() {
    return isAnimating;
}

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
    healthBar.setCurrentStat(currentHealth);
}

void BattleCharacterView::setCurrentPP(int cPP) {
    currentPP = cPP;
    PPBar.setCurrentStat(currentPP);
}

void BattleCharacterView::setCurrentShield(int cShield) {
    currentShield = cShield;
    stringstream shieldText;
    shieldText << currentShield << " Shield";
    shieldLabel.setText(shieldText.str());
}

void BattleCharacterView::setIsIncap(bool incap) {
    isIncap = incap;
}
