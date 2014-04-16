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

ViewController::~ViewController() {
    SDL_DestroyRenderer( renderer );
}