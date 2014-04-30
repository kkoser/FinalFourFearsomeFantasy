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
#include "Dot.h"
#include "ImageView.h"

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
    Mix_Chunk *albusSoundEffect = NULL;
    Mix_Chunk *elsaSoundEffect = NULL;
    Mix_Chunk *jackSoundEffect = NULL;
    Mix_Chunk *katSoundEffect = NULL;
    
    enum MainCharacters{
        ALBUS,
        ELSA,
        JACK,
        KAT
    };
    
    enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    
    MainCharacters activeCharacter;
    int layoutReset;
    Direction charDir;
    int stepCount;
    
    Dot leader;
    Dot mapScout;

    
    int mapNumber;
    int charDirTemp;
    int zone;
    
    int startPosX[8];
    int startPosY[8];
    
    int returnPosX[8];
    int returnPosY[8];
    
    SDL_Rect blank;
    SDL_Rect camera[8];
    
    SDL_Rect fullViewport;
    SDL_Rect topViewport;
    SDL_Rect bottomViewport;
    
    bool quit;
    
    const int LEVEL_WIDTH[8] = {1200,1312,1312,1792,1344,1600,1712,1600};
    const int LEVEL_HEIGHT[8] = {656,880,2400,704,1248,1440,880,1280};

    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 650;

    bool loadTextures();
    
    int isReturning;
    int mapReturningFrom;
    
    
public:
    OpenWorldViewController(SDL_Renderer *ren);
    
    virtual void pushViewController(ViewController *vc);
    virtual void becomeTop();
    
    virtual int draw(SDL_Event e);
    
};


#endif /* defined(__FinalFourFearsomeFantasy__OpenWorldViewController__) */
