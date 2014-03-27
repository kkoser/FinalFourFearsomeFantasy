//
//  CharacterView.cpp
//  FFFF
//
//  Created by Casey Hanley on 3/27/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//

#include "CharacterView.h"

#include <SDL2/SDL.h>
#include <stdio.h>

int CharacterView::getX(){
    return xLoc;
}
//------------------------------------------------------------------------------
int CharacterView::getY(){
    return yLoc;
}
//------------------------------------------------------------------------------
void CharacterView::moveRel(int x, int y){
    xLoc=getX()+x;
    yLoc=getY()+y;
}
//------------------------------------------------------------------------------
void CharacterView::moveAbs(int x, int y){
    xLoc=x;
    yLoc=y;
}
//------------------------------------------------------------------------------
void CharacterView::setDegs(double value){
    degs=value;
}
//------------------------------------------------------------------------------
double CharacterView::getDegs(){
    return degs;
}
//------------------------------------------------------------------------------
void CharacterView::setDir(int direction){
    faceDir=direction;
}
//------------------------------------------------------------------------------
SDL_RendererFlip CharacterView::getDir(){
    return flipDir;
}
//------------------------------------------------------------------------------
SDL_RendererFlip CharacterView::flipLeft(){
    flipDir=SDL_FLIP_NONE;
    return flipDir;
}
//------------------------------------------------------------------------------
SDL_RendererFlip CharacterView::flipRight(){
    flipDir=SDL_FLIP_HORIZONTAL;
    return flipDir;
}
//------------------------------------------------------------------------------
CharacterView::CharacterView(){
    //initialize stuff
    xLoc=0;
    yLoc=0;
    degs=0;
    flipDir=SDL_FLIP_NONE;
}
//------------------------------------------------------------------------------
CharacterView::CharacterView(int x, int y){
    //initialize stuff
    xLoc=x;
    yLoc=y;
    degs=0;
    flipDir=SDL_FLIP_NONE;
}
