//
//  ImageView.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/23/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__ImageView__
#define __FinalFourFearsomeFantasy__ImageView__

#include <iostream>

#include <SDL2/SDL.h>
#include "LTexture.h"
#include <string>

class ImageView {
private:
    int xLoc;
    int yLoc;
    double degs; //degrees of rotation
    int faceDir; //direction they are facing (1=up, 2=down, 3=left, 4=right)
    SDL_RendererFlip flipDir;
    
    LTexture texture;
    
    SDL_Renderer *renderer;
    
public:
    ImageView();
    ImageView(int x, int y, string fileName, SDL_Renderer *ren);
    
    int getX();
    int getY();
    double getDegs();
    SDL_RendererFlip getDir();
    void setDegs(double value);
    void setDir(int direction);
    void moveRel(int x, int y); //move relative to current pos.
    void moveAbs(int x, int y); //move to absolute location in window
    SDL_RendererFlip flipRight();
    SDL_RendererFlip flipLeft();
    
    void draw(SDL_Renderer *ren);
    void draw(); //uses the last renderer
};

#endif /* defined(__FinalFourFearsomeFantasy__ImageView__) */
