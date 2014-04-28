//
//  ImageView.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/23/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//
//This class based on CharacterView by Casey Hanley :)

#include "ImageView.h"

ImageView::ImageView() {
    renderer = NULL;
    xLoc = 0;
    yLoc = 0;
    degs = 0;
    flipDir = SDL_FLIP_NONE;
}

ImageView::ImageView(int x, int y, string fileName, SDL_Renderer *ren) {
    xLoc = x;
    yLoc = y;
    degs = 0;
    textFile = fileName;
    renderer = ren;
    flipDir = SDL_FLIP_NONE;
    
}

ImageView::ImageView(ImageView const &other) {
    xLoc = other.xLoc;
    yLoc = other.yLoc;
    textFile = other.textFile;
    renderer = other.renderer;

}

void ImageView::load() {
    if (!(texture.getWidth() > 0)) {
        texture.loadFromFile(textFile, renderer);
    }
    
}

void ImageView::draw(SDL_Renderer *ren) {
    renderer = ren;
    draw();
}

void ImageView::draw() {
    load();
    texture.render(renderer, xLoc, yLoc, NULL, degs, NULL, flipDir);
}

int ImageView::getX(){
    return xLoc;
}
//------------------------------------------------------------------------------
int ImageView::getY(){
    return yLoc;
}
//------------------------------------------------------------------------------
void ImageView::moveRel(int x, int y){
    xLoc=getX()+x;
    yLoc=getY()+y;
}
//------------------------------------------------------------------------------
void ImageView::moveAbs(int x, int y){
    xLoc=x;
    yLoc=y;
}
//------------------------------------------------------------------------------
void ImageView::setDegs(double value){
    degs=value;
}
//------------------------------------------------------------------------------
double ImageView::getDegs(){
    return degs;
}
//------------------------------------------------------------------------------
SDL_RendererFlip ImageView::getDir(){
    return flipDir;
}
//------------------------------------------------------------------------------
SDL_RendererFlip ImageView::flipLeft(){
    flipDir=SDL_FLIP_NONE;
    return flipDir;
}
//------------------------------------------------------------------------------
SDL_RendererFlip ImageView::flipRight(){
    flipDir=SDL_FLIP_HORIZONTAL;
    return flipDir;
}