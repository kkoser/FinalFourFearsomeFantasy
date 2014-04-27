//
//  StatBar.cpp
//  FFFF
//
//  Created by Zach Waterson on 4/24/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "StatBar.h"

StatBar::StatBar(int px, int py, int cStat, int mStat, string statName, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int h, int w) {
    x = px;
    y = py;
    currentStat = cStat;
    maxStat = mStat;
    height = h;
    maxWidth = w;
    
    bar.x = x;
    bar.y = y;
    bar.h = height;
    bar.w = maxWidth;
    
    barOutline.x = x;
    barOutline.y = y;
    barOutline.h = height;
    barOutline.w = maxWidth;
    
    fullBarRed = r;
    fullBarGreen = g;
    fullBarBlue = b;
    fullBarAlpha = a;
    
    //init label
    stringstream labelTemp;
    labelTemp << currentStat << "/" << maxStat << " " << statName;
    labelText = labelTemp.str();

    statLabel = TextLabel(x + maxWidth + 10, y, labelText);
    statLabel.setColor(255,255,255);
}

void StatBar::draw(SDL_Renderer *renderer) {

    
    //update dimensions
    bar.x = x;
    bar.y = y;
    bar.h = height;
    bar.w = getCurrentWidth();
    
    //update colors
    updateColorOnContext();
    
    //draw label
    statLabel.draw(renderer);

    //save old color
    SDL_GetRenderDrawColor(renderer, &rendRed, &rendGreen, &rendBlue, &rendAlpha);
    

    //set draw color for bar
    SDL_SetRenderDrawColor(renderer, barRed, barGreen, barBlue, barAlpha);
    SDL_RenderFillRect(renderer, &bar);
    
    //draw border in black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &barOutline);

    //change color back
    SDL_SetRenderDrawColor(renderer, rendRed, rendGreen, rendBlue, rendAlpha);
}

void StatBar::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {
    barRed = r;
    barGreen = g;
    barBlue = b;
    barAlpha = alpha;
}

void StatBar::updateColorOnContext() {
    //change color to yellow/red based on fraction gone
    float fractionOfStat = (float)currentStat/(float)maxStat;
    if(fractionOfStat < 0.33) {
        setColor(255, 0, 0, 255);
    }
    else if (fractionOfStat < 0.66) {
        setColor(255, 255, 0, 255);
    }
    else {
        setColor(fullBarRed, fullBarGreen, fullBarBlue, fullBarAlpha);
    }
}

int StatBar::getCurrentWidth() {
    //calculate width
    float fractionOfStat = (float)currentStat/(float)maxStat;
    currentWidth = maxWidth*fractionOfStat;
    return currentWidth;
}

void StatBar::setCurrentStat(int cStat) {
    //make stat fraction
    currentStat = cStat;
    stringstream labelTemp;
    labelTemp << currentStat << "/" << maxStat << statName;
    labelText = labelTemp.str();
    statLabel.setText(labelText);
}

