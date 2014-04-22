//
//  OpenWorldViewController.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__OpenWorldViewController__
#define __FinalFourFearsomeFantasy__OpenWorldViewController__

#include <iostream>
#include "ViewController.h"

class OpenWorldViewController : public ViewController {
private:
    //Sprites
    LTexture elsaSpriteSide;
    LTexture katSpriteSide;
    LTexture jackSpriteSide;
    LTexture albusSpriteSide;
    LTexture elsaSpriteFront;
    LTexture katSpriteFront;
    LTexture jackSpriteFront;
    LTexture albusSpriteFront;
    LTexture elsaSpriteBack;
    LTexture katSpriteBack;
    LTexture jackSpriteBack;
    LTexture albusSpriteBack;
    
    //Background Images
    
    LTexture ArendelleTexture;
    LTexture NorthMountBGTexture;
    LTexture CaveBGTexture;
    LTexture IslandBGTexture;
    LTexture ForestBGTexture;
    LTexture BViewTexture; //bottom viewport boxes
    
    //Map Textures
    LTexture mapTexture[8];
    
    //The music that will be played
    Mix_Music *elsaMusic = NULL;
    Mix_Music *albusMusic = NULL;
    Mix_Music *katMusic = NULL;
    Mix_Music *jackMusic = NULL;
    Mix_Music *cityMusic = NULL;
    Mix_Music *mustafarMusic = NULL;
    
    //The sound effects that will be used
    Mix_Chunk *soundEffect1 = NULL;
    Mix_Chunk *albusSoundEffect = NULL;
    Mix_Chunk *elsaSoundEffect = NULL;
    Mix_Chunk *jackSoundEffect = NULL;
    Mix_Chunk *katSoundEffect = NULL;

    void loadTextures();
public:
    OpenWorldViewController(SDL_Renderer *ren);
    
    virtual int draw(SDL_Event e);
};


#endif /* defined(__FinalFourFearsomeFantasy__OpenWorldViewController__) */
