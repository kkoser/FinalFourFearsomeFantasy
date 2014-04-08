//
//  ViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "ViewController.h"

ViewController::ViewController(SDL_Window *win) {
    //create the renderer
    if( win == NULL )
    {
        printf( "Invalid window for ViewController" );
    }
    else
    {
        //Create renderer for window
        renderer = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        }
    }
}

//remove the ViewController from the window
//not sure how to implement - talk to casey
void ViewController::dismiss() {
    
}

ViewController::~ViewController() {
    SDL_DestroyRenderer( renderer );
}