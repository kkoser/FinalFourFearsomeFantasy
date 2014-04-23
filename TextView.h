//
//  TextView.h
//  FFFF
//
//  Created by Casey Hanley on 4/23/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//

#ifndef __FFFF__TextView__
#define __FFFF__TextView__

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "LTexture.h"
using namespace std;

class TextView{
public:
    TextView(); //constructor
    TextView(int x, int y, string text, SDL_Renderer *gRenderer); //non-default constructor
    void draw(string text, int x, int y, SDL_Renderer * gRenderer); //for convenience
private:
    int x;
    int y;
    string text;
    LTexture font;
    TTF_Font * gFont;
    
};

#endif
