//
//  Dot.h
//  FFFF
//
//  Created by Casey Hanley on 3/27/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//
// Class for a character moving around the screen in Open-World Mode.
// It's named "Dot" because I used a dot image in the SDL tutorials and it was
//  easy for me to remember.
// This will be the basis of character movement and exploration in Open-World Mode.
//

#include <SDL2/SDL.h>
#include "LTexture.h"

#ifndef FFFF_Dot_h
#define FFFF_Dot_h

//The dot (character) that will move around on the screen
class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    
    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;
    
    //Initializes the variables
    Dot();
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the dot
    void move();
    
    //Moves the dot with a moving background ("Rel"ative to background)
    void moveRel();
    
    //Shows the dot on the screen
    void render(SDL_Renderer * gRenderer, LTexture gDotTexture);
    
    //Shows the dot on the screen relative to the camera
    void renderRel( SDL_Renderer * gRenderer, int camX, int camY, LTexture gDotTexture );
    
    //Position accessors
    int getPosX();
    int getPosY();
    
private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    
    //The velocity of the dot
    int mVelX, mVelY;
};


#endif
