//
//  OpenWorldViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "OpenWorldViewController.h"
#include "Dot.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "LTexture.h"

//---------------------------------------------------------

OpenWorldViewController::OpenWorldViewController(SDL_Renderer *ren) : ViewController(ren) {
    
    loadTextures();
    
    layoutReset=1;
    activeCharacter=ELSA;
    charDir=DOWN;
    stepCount=0;

    blank = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    for(int q=0;q<8;q++) camera[q]= blank;
    
    mapNumber=0;
    charDirTemp=1;
    zone=9;
    
    for(int q=0; q<8; q++) startPosX[q]=50;
    for(int q=0; q<8; q++) startPosY[q]=50;
    
    startPosX[0]=752;
    startPosY[0]=176;
    startPosX[1]=80;
    startPosY[1]=784;
    startPosX[2]=544;
    startPosY[2]=2300;
    startPosX[3]=1728;
    startPosY[3]=304;
    
    quit=false;

}

bool OpenWorldViewController::loadTextures() {
    
    bool success=true;
    
    if( !katSpriteSide.loadFromFile( pathForFile("Images/katSpriteSide.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteSide.loadFromFile( pathForFile("Images/albusSpriteSide.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteSide.loadFromFile( pathForFile("Images/elsaSpriteSide.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteSide.loadFromFile( pathForFile("Images/jackSpriteSide.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //load Sprite Front Views
    if( !katSpriteFront.loadFromFile( pathForFile("Images/katSpriteFront.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteFront.loadFromFile( pathForFile("Images/albusSpriteFront.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteFront.loadFromFile( pathForFile("Images/elsaSpriteFront.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteFront.loadFromFile( pathForFile("Images/jackSpriteFront.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //load sprite Back Views
    if( !katSpriteBack.loadFromFile( pathForFile("Images/katSpriteBack.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteBack.loadFromFile( pathForFile("Images/albusSpriteBack.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteBack.loadFromFile( pathForFile("Images/elsaSpriteBack.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteBack.loadFromFile( pathForFile("Images/jackSpriteBack.png"), renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
	//Load background textures
	if( !ArendelleTexture.loadFromFile( pathForFile("Images/arendelle.jpg"), renderer ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    if( !NorthMountBGTexture.loadFromFile( pathForFile("Images/battleNorthMountain.jpg"), renderer ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    
    //Load Maps
    if( !mapTexture[0].loadFromFile( pathForFile("Images/map0.png"), renderer ) )
	{
		printf( "Failed to load map0 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[1].loadFromFile( pathForFile("Images/map1.png"), renderer ) )
	{
		printf( "Failed to load map1 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[2].loadFromFile( pathForFile("Images/map2.png"), renderer ) )
	{
		printf( "Failed to load map2 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[3].loadFromFile( pathForFile("Images/map3.png"), renderer ) )
	{
		printf( "Failed to load map3 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[4].loadFromFile( pathForFile("Images/map4.png"), renderer ) )
	{
		printf( "Failed to load map4 background texture image!\n" );
		success = false;
	}
    //Load music
    elsaMusic = Mix_LoadMUS( "Audio/LetItGo.wav" );
    if( elsaMusic == NULL )
    {
        printf( "Failed to load Elsa music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jackMusic = Mix_LoadMUS( "Audio/hesAPirate.wav" );
    if( jackMusic == NULL )
    {
        printf( "Failed to load Jack Music SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    katMusic = Mix_LoadMUS( "Audio/ArrowsAtTheSky.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load Kat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    albusMusic = Mix_LoadMUS( "Audio/hedwigsTheme.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load Albus music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    cityMusic = Mix_LoadMUS( "Audio/GoT.wav" );
    if( cityMusic == NULL )
    {
        printf( "Failed to load city music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    mustafarMusic = Mix_LoadMUS( "Audio/anakinVSobi.wav" );
    if( cityMusic == NULL )
    {
        printf( "Failed to load mustafar music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    elsaSoundEffect = Mix_LoadWAV( "Audio/elsaSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load kat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jackSoundEffect = Mix_LoadWAV( "Audio/jackSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load jack sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    katSoundEffect = Mix_LoadWAV( "Audio/katSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load kat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    albusSoundEffect = Mix_LoadWAV( "Audio/albusSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load albus sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;

}

int OpenWorldViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e) == 0) {
        return 0;
    }
    else{
        if( e.type == SDL_KEYDOWN){
                switch( e.key.keysym.sym )
                {
                        //set Albus as active
                    case SDLK_1:
                        activeCharacter=ALBUS;
                        Mix_PlayChannel( -1, albusSoundEffect, 0 );
                        break;
                        
                        //set Elsa as active
                    case SDLK_2:
                        activeCharacter=ELSA;
                        Mix_PlayChannel( -1, elsaSoundEffect, 0 );
                        break;
                        
                        //set Jack as active
                    case SDLK_3:
                        activeCharacter=JACK;
                        Mix_PlayChannel( -1, jackSoundEffect, 0 );
                        break;
                        
                        //set Kat as active
                    case SDLK_4:
                        activeCharacter=KAT;
                        Mix_PlayChannel( -1, katSoundEffect, 0 );
                        break;
                        
                }
                
            }

            //Handle input for the character and scout
            leader.handleEvent( e );
            mapScout.handleEvent( e );
            
        //}
        
            //check for layout switch
            if(zone != 9){
                
                switch(zone){
                    case 0:
                        mapNumber=0;
                        layoutReset=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 1:
                        mapNumber=1;
                        layoutReset=1;
                        mapScout.initializeMap(1);
                        Mix_HaltMusic();
                        break;
                    case 2:
                        mapNumber=2;
                        layoutReset=1;
                        mapScout.initializeMap(2);
                        Mix_HaltMusic();
                        break;
                    case 3:
                        mapNumber=3;
                        layoutReset=1;
                        mapScout.initializeMap(3);
                        Mix_HaltMusic();
                        break;
                    case 4:
                        mapNumber=4;
                        layoutReset=1;
                        mapScout.initializeMap(4);
                        Mix_HaltMusic();
                        break;
                    case 5:
                        mapNumber=5;
                        layoutReset=1;
                        mapScout.initializeMap(5);
                        Mix_HaltMusic();
                        break;
                    case 10:
                        //layout=BATTLE_LAYOUT;
                        layoutReset=1;
                        Mix_HaltMusic();
                        break;
                    case 11:
                        mapNumber=0;
                        layoutReset=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                        
                    default: break;
                }
            }

        //MOVE THE CHARACTERS AND CAMERA

        //Move the character
        //if(!layoutReset){
            
            mapScout.moveSmoothUnrestricted(mapNumber); //move scout ahead
            zone = mapScout.checkZone(mapNumber); //determine the zone
            
            //switch character direction
            charDirTemp = leader.getCharDir( mapScout.getPosX(), mapScout.getPosY(), charDirTemp );
            switch(charDirTemp){
                case 0: charDir = UP; break;
                case 1: charDir = DOWN; break;
                case 2: charDir = LEFT; break;
                case 3: charDir = RIGHT; break;
            }
            mapScout.moveBackSmooth(mapNumber); //move scout back
            leader.moveSmooth(zone,mapNumber); //move character ahead
            mapScout.moveSmooth(zone,mapNumber); //move scout ahead, too
            
            cout<<"X: "<<leader.getPosX()<<" Y: "<<leader.getPosY()<<endl;
            cout<<"Layout Reset: "<<layoutReset<<endl;
        
        //}
        
        //Center the camera over the dot
        camera[mapNumber].x = ( leader.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
        camera[mapNumber].y = ( leader.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
        
        //Keep the camera in bounds
        if( camera[mapNumber].x < 0 )
        {
            camera[mapNumber].x = 0;
        }
        if( camera[mapNumber].y < 0 )
        {
            camera[mapNumber].y = 0;
        }
        if( camera[mapNumber].x > LEVEL_WIDTH[mapNumber] - camera[mapNumber].w )
        {
            camera[mapNumber].x = LEVEL_WIDTH[mapNumber] - camera[mapNumber].w;
        }
        if( camera[mapNumber].y > LEVEL_HEIGHT[mapNumber] - camera[mapNumber].h )
        {
            camera[mapNumber].y = LEVEL_HEIGHT[mapNumber] - camera[mapNumber].h;
        }
        
        
        if( Mix_PlayingMusic() == 0 )
        {
            switch(mapNumber){
                case 0:
                    Mix_PlayMusic( cityMusic, -1 );
                    break;
                case 1:
                    Mix_PlayMusic( mustafarMusic, -1 );
                    break;
                case 2:
                    Mix_PlayMusic( elsaMusic, -1 );
                    break;
                case 3:
                    Mix_PlayMusic( katMusic, -1 );
                    break;
                case 4:
                    Mix_PlayMusic( albusMusic, -1 );
                    break;
                case 5:
                    Mix_PlayMusic( jackMusic, -1 );
                    break;
            }
        }
        
        //Top viewport
        topViewport.x = 0;
        topViewport.y = SCREEN_HEIGHT / 4;
        topViewport.w = SCREEN_WIDTH;
        topViewport.h = SCREEN_HEIGHT;
        
        //Bottom viewport
        bottomViewport.x = 0;
        bottomViewport.y = 0;
        bottomViewport.w = SCREEN_WIDTH;
        bottomViewport.h = SCREEN_HEIGHT / 4;
        
        //fullViewport
        fullViewport.x = 0;
        fullViewport.y = 0;
        fullViewport.w = SCREEN_WIDTH;
        fullViewport.h = SCREEN_HEIGHT;
        SDL_RenderSetViewport( renderer, &fullViewport );
        
        
        if(layoutReset){
            
            stepCount=0;
            leader.moveAbs(startPosX[mapNumber], startPosY[mapNumber]);
            mapScout.moveAbs(startPosX[mapNumber], startPosY[mapNumber]);
            charDir=DOWN;
            layoutReset=0;
            
        }
        
        //Render background
        mapTexture[mapNumber].render( renderer, 0, 0, &camera[mapNumber] );
        
        if (activeCharacter==KAT){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteSide, SDL_FLIP_NONE );
        }
        else if( activeCharacter==ALBUS){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteSide, SDL_FLIP_NONE );
        }
        else if( activeCharacter==ELSA){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteSide, SDL_FLIP_NONE );
        }
        else if( activeCharacter==JACK){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteSide, SDL_FLIP_NONE );
        }
    
        
    
    
    return 1;
}
}
