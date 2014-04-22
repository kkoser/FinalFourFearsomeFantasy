//
//  ViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "ViewController.h"

ViewController::ViewController(SDL_Renderer *ren) {
    //save the renderer
    renderer = ren;
    //SDL_RenderClear(renderer);
    top = NULL;
    
}

//override this for custom transition animation
void ViewController::becomeTop() {
    free(top);
    top = NULL;
    SDL_RenderClear(renderer);
}

//remove the ViewController from the window
//not sure how to implement - talk to casey
void ViewController::dismiss() {
    if (base != NULL) {
        base->becomeTop();
    }
}

//used to push new viewcontrollers onto the navigation stack
//override to define custom animations
void ViewController::pushViewController(ViewController *vc) {
    if (top == NULL) {
        top = vc;
        vc->setBase(this);
    }
}

//this method is overriden to define custom display behavior
//the main method of viewcontrollers
//MUST call super:draw at beginning of method to ensure heirarchy stays intact
int ViewController::draw(SDL_Event e) {
    SDL_RenderClear(renderer);
    
    if (top != NULL) {
        top->draw(e);
        return 0;
    }
    
    return 1;

    //custom drawing code here
}

void ViewController::setBase(ViewController *vc) {
    base = vc;
}

ViewController::~ViewController() {
    //dont want to destroy the renderer, its used by all VCs for that window
    //SDL_DestroyRenderer( renderer );
}