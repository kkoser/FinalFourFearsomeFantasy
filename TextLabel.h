//
//  TextLabel.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/22/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__TextLabel__
#define __FinalFourFearsomeFantasy__TextLabel__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "LTexture.h"
#include "Settings.h"

using namespace std;

//default font
const std::string defaultFont = pathForFile("Fonts/Hero.ttf");

class TextLabel {
private:
    string text;
    LTexture texture;
    int x, y;
    TTF_Font *font = NULL;
    SDL_Color textColor;
    SDL_Renderer *renderer;
        
public:
    TextLabel(int x = 0, int y = 0, string str = "none", string fontName = defaultFont, int size = 16, SDL_Renderer *ren = NULL);
    ~TextLabel();
    void draw(SDL_Renderer *ren);
    void draw(); //uses the last renderer
    
    
    string getText();
    void setText(string str);
    
    int getX();
    int getY();
    void setX(int cx);
    void setY(int cy);
    
    SDL_Color getColor();
    void setColor(SDL_Color col);
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    
};


#endif /* defined(__FinalFourFearsomeFantasy__TextLabel__) */
