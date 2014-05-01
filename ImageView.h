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
#include "Settings.h"

class ImageView {
private:
    int xLoc;
    int yLoc;
    double degs; //degrees of rotation
    SDL_RendererFlip flipDir = SDL_FLIP_NONE;
    
    LTexture texture;
    string textFile;
    
    SDL_Renderer *renderer;
    
    void load(); //used for lazy loading
    
public:
    //default constructor
    ImageView();
    //copy constructor to fix image rendering issue
    ImageView( ImageView const &other);
    ImageView(int x, int y, string fileName, SDL_Renderer *ren);
    ~ImageView();
    
    int getX();
    int getY();
    double getDegs();
    SDL_RendererFlip getDir();
    void setDegs(double value);
    void moveRel(int x, int y); //move relative to current pos.
    void moveAbs(int x, int y); //move to absolute location in window
    SDL_RendererFlip flipRight();
    SDL_RendererFlip flipLeft();
    
    void draw(SDL_Renderer *ren);
    void draw(); //uses the last renderer
    
    
};

#endif /* defined(__FinalFourFearsomeFantasy__ImageView__) */
