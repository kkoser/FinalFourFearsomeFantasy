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
void ViewController::becomeTop(ViewController *baseVC) {
    if (baseVC != NULL) {
        base = baseVC;
    }
    SDL_RenderClear(renderer);
}

//remove the ViewController from the window
//not sure how to implement - talk to casey
void ViewController::dismiss() {
    if (base != NULL) {
        base->becomeTop(NULL);
    }
}

void ViewController::pushViewController(ViewController *vc) {
    if (top != NULL) {
        top = vc;
    }
}

void ViewController::draw(SDL_Event e) {
    SDL_RenderClear(renderer);
    std::cout<<"Drawing a baseVC!"<<endl;
    
    if (top != NULL) {
        top->draw(e);
        return;
    }

    //custom drawing code here
}

ViewController::~ViewController() {
    //dont want to destroy the renderer, its used by all VCs for that window
    //SDL_DestroyRenderer( renderer );
}