//
//  LTexture.h
//  FFFF
//
//  Created by Casey Hanley on 3/27/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//

#include <SDL2/SDL.h>
#include "SDL2_ttf/SDL_ttf.h"
#include <string>
using namespace std;

#ifndef FFFF_LTexture_h
#define FFFF_LTexture_h

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( string path, SDL_Renderer * gRenderer );
    
    //Creates image from font string
    bool loadFromRenderedText( string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font *gFont );
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( SDL_Renderer * gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif
