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
#include "SDL2_image/SDL_image.h"


#ifndef FFFF_Dot_h
#define FFFF_Dot_h

//The dot (character) that will move around on the screen
class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 17;
    static const int DOT_HEIGHT = 31;
    
    //Maximum axis velocity of the dot
    static const int DOT_VEL = 4;
    
    //Initializes the variables
    Dot();
    Dot(int PosX, int PosY);
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the dot
    void move();
    
    //Moves the dot with a moving background ("Rel"ative to background)
    void moveRel(int mChangeX, int mChangeY); //for scouting
    void moveRel2(int mChangeX, int mChangeY, int zone); //only move if zone is valid
    void moveBack(int mChangeX, int mChangeY); //to move the scout back with main character
    
    //Shows the dot on the screen
    void render(SDL_Renderer * gRenderer, LTexture gDotTexture);
    
    //Shows the dot on the screen relative to the camera
    void renderRel( SDL_Renderer * gRenderer, int camX, int camY, LTexture * gDotTexture, SDL_RendererFlip flipType );
    
    //Position accessors
    int getPosX();
    int getPosY();
    void moveAbs(int x, int y);
    

    
    //populate the map array (take this out if can figure out map class)
    void initializeMap();
    
    int checkZone();
    
private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    
    //The velocity of the dot
    int mVelX, mVelY;
    
    //map stuff (take this out if can figure out map class)
    static const int mapWidth = 82;
    static const int mapHeight = 150;
    int mapArray[mapHeight][mapWidth];
  

};


#endif
