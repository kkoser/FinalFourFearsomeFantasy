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
    SDL_RenderClear(renderer);
    
}

//remove the ViewController from the window
//not sure how to implement - talk to casey
void ViewController::dismiss() {
    
}

ViewController::~ViewController() {
    SDL_DestroyRenderer( renderer );
}