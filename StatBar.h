//
//  StatBar.h
//  FFFF
//
//  Created by Zach Waterson on 4/24/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __FFFF__StatBar__
#define __FFFF__StatBar__

#include <iostream>
#include <SDL2/SDL.h>
#include "TextLabel.h"
#include <sstream>

class StatBar {
public:
    //height and width should be left at default
    StatBar(int px = 0, int py = 0, int cStat = 50, int mStat = 100, string sName = "", Uint8 r = 0, Uint8 g = 255, Uint8 b = 0, Uint8 a = 255,  int h = 20, int w = 125);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
    void draw(SDL_Renderer *renderer);
    void setCurrentStat(int cStat);
    int getCurrentWidth();
    
    void updateColorOnContext();

private:
    int x;
    int y;
    int currentStat;
    int maxStat;
    int height;
    int currentWidth;
    int maxWidth;
    string statName;

    SDL_Rect bar;
    SDL_Rect barOutline;
    TextLabel statLabel;
    string labelText;
    
    
    //store renderer colors
    Uint8 rendRed;
    Uint8 rendGreen;
    Uint8 rendBlue;
    Uint8 rendAlpha;
    
    //store bar colors
    Uint8 barRed;
    Uint8 barGreen;
    Uint8 barBlue;
    Uint8 barAlpha;
    
    //store full bar colors
    Uint8 fullBarRed;
    Uint8 fullBarGreen;
    Uint8 fullBarBlue;
    Uint8 fullBarAlpha;
    
    
};

#endif /* defined(__FFFF__StatBar__) */
