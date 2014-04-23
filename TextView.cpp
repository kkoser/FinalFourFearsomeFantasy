//
//  TextView.cpp
//  FFFF
//
//  Created by Casey Hanley on 4/23/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//

#include "TextView.h"
#include <SDL2/SDL.h>
#include "SDL2_ttf/SDL_ttf.h"
#include "LTexture.h"
#include <stdio.h>
#include <string>

//------------------------------------------------------------------------------
void TextView::draw(string text, int x, int y, SDL_Renderer *gRenderer){
    SDL_Color whiteColor = {255, 255, 255};
    font.loadFromRenderedText( text, whiteColor, gRenderer, gFont );
    font.render( gRenderer, x, y );
    
}
//------------------------------------------------------------------------------
TextView::TextView(){
    x=0;
    y=0;
    text="nothing";
    gFont = TTF_OpenFont( "AndaleMono.ttf", 16 );
}
//------------------------------------------------------------------------------
TextView::TextView(int x, int y, string text, SDL_Renderer *gRenderer){
    x=x;
    y=y;
    text=text;
    gFont = TTF_OpenFont( "AndaleMono.ttf", 16 );
}
