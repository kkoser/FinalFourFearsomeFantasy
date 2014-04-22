//
//  CharacterView.h
//  FFFF
//
//  Created by Casey Hanley on 3/27/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//
// Simple class for the character's position and rotation values in Battle Mode.
// This is what will be used for character animations in Battle Mode.

#include <SDL2/SDL.h>
#include "LTexture.h"
#include <string>

#ifndef FFFF_CharacterView_h
#define FFFF_CharacterView_h

class CharacterView{
public:
    CharacterView(); //constructor
    CharacterView(int x, int y, string filename, SDL_Renderer *gRenderer); //non-default constructor
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
    void draw(SDL_Renderer * gRenderer); //for convenience
private:
    int xLoc;
    int yLoc;
    double degs; //degrees of rotation
    int faceDir; //direction they are facing (1=up, 2=down, 3=left, 4=right)
    SDL_RendererFlip flipDir;
    
    LTexture battleTexture;
    
    
    
};

#endif
