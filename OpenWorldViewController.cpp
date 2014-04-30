//
//  OpenWorldViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "OpenWorldViewController.h"
#include "BattleViewController.h"
#include "ExampleViewController.h"
#include "Dot.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "LTexture.h"
#include <time.h>
#include <stdlib.h>

//---------------------------------------------------------

OpenWorldViewController::OpenWorldViewController(SDL_Renderer *ren) : ViewController(ren) {
    
    //srand (time(NULL));
    
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
    startPosX[1]=65;
    startPosY[1]=840;
    startPosX[2]=544;
    startPosY[2]=2350;
    startPosX[3]=1750;
    startPosY[3]=304;
    startPosX[4]=65;
    startPosY[4]=25;
    
    for(int q=0; q<8; q++) returnPosX[q]=50;
    for(int q=0; q<8; q++) returnPosY[q]=50;

    returnPosX[1]=1110;
    returnPosY[1]=10;
    returnPosX[2]=480;
    returnPosY[2]=20;
    returnPosX[3]=20;
    returnPosY[3]=605;
    returnPosX[4]=535;
    returnPosY[4]=575;
    
    isReturning = 0;
    mapReturningFrom=0;
    
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
    elsaMusic = Mix_LoadMUS( pathForFile("Audio/LetItGo.wav" ).c_str());
    if( elsaMusic == NULL )
    {
        printf( "Failed to load Elsa music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jackMusic = Mix_LoadMUS( pathForFile("Audio/hesAPirate.wav" ).c_str());
    if( jackMusic == NULL )
    {
        printf( "Failed to load Jack Music SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    katMusic = Mix_LoadMUS( pathForFile("Audio/gapraWhitewood.wav" ).c_str());
    if( katMusic == NULL )
    {
        printf( "Failed to load Kat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    albusMusic = Mix_LoadMUS( pathForFile("Audio/hedwigsTheme.wav").c_str());
    if( katMusic == NULL )
    {
        printf( "Failed to load Albus music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    cityMusic = Mix_LoadMUS( pathForFile("Audio/GoT.wav" ).c_str());
    if( cityMusic == NULL )
    {
        printf( "Failed to load city music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    mustafarMusic = Mix_LoadMUS( pathForFile("Audio/anakinVSobi.wav").c_str() );
    if( cityMusic == NULL )
    {
        printf( "Failed to load mustafar music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    elsaSoundEffect = Mix_LoadWAV( pathForFile("Audio/elsaSoundEffect.wav" ).c_str());
    if( katMusic == NULL )
    {
        printf( "Failed to load kat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jackSoundEffect = Mix_LoadWAV( pathForFile("Audio/jackSoundEffect.wav").c_str());
    if( katMusic == NULL )
    {
        printf( "Failed to load jack sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    katSoundEffect = Mix_LoadWAV( pathForFile("Audio/katSoundEffect.wav").c_str());
    if( katMusic == NULL )
    {
        printf( "Failed to load kat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    albusSoundEffect = Mix_LoadWAV( pathForFile("Audio/albusSoundEffect.wav").c_str());
    if( katMusic == NULL )
    {
        printf( "Failed to load albus sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;

}

//------------------------------------------------------------------------------------------
int OpenWorldViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e) == 0) {
        return 0;
    }
    else{
        //if(e.type <= 0) return 1;
        if( e.type == SDL_KEYDOWN ){
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
                        
                    case SDLK_UP:
                        stepCount++;
                        cout<<"Steps: "<<stepCount<<endl;
                        break;
                        
                    case SDLK_DOWN:
                        stepCount++;
                        cout<<"Steps: "<<stepCount<<endl;
                        break;
                        
                    case SDLK_LEFT:
                        stepCount++;
                        cout<<"Steps: "<<stepCount<<endl;
                        break;
                        
                    case SDLK_RIGHT:
                        stepCount++;
                        cout<<"Steps: "<<stepCount<<endl;
                        break;
                    case SDLK_ESCAPE:
                        dismiss();
                        return 1;
                        break;
                        
                }
                
            }

            //Handle input for the character and scout
            leader.handleEvent( e );
            mapScout.handleEvent( e );
        
            //ZONE SWITCHING
            if(zone != 9){
                
                switch(zone){
                    case 0:
                        mapNumber=0;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 1:
                        mapNumber=1;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(1);
                        Mix_HaltMusic();
                        break;
                    case 2:
                        mapNumber=2;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(2);
                        Mix_HaltMusic();
                        break;
                    case 3:
                        mapNumber=3;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(3);
                        Mix_HaltMusic();
                        break;
                    case 4:
                        mapNumber=4;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(4);
                        Mix_HaltMusic();
                        break;
                    case 5:
                        mapNumber=5;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(5);
                        Mix_HaltMusic();
                        break;
                    case 10:
                        //layout=BATTLE_LAYOUT;
                        //layoutReset=1;
                        Mix_HaltMusic();
                        break;
                    case 11:
                        mapNumber=0;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 12:
                        mapNumber=0;
                        mapReturningFrom=4;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 17:
                        mapNumber=0;
                        mapReturningFrom=1;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 18:
                        mapNumber=0;
                        mapReturningFrom=2;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 19:
                        mapNumber=0;
                        mapReturningFrom=3;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 20:
                        mapNumber=0;
                        mapReturningFrom=4;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                        
                    default: break;
                }
            }

        //MOVE THE CHARACTERS AND CAMERA
        
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
        
//        //Top viewport
//        topViewport.x = 0;
//        topViewport.y = SCREEN_HEIGHT / 4;
//        topViewport.w = SCREEN_WIDTH;
//        topViewport.h = SCREEN_HEIGHT;
//        
//        //Bottom viewport
//        bottomViewport.x = 0;
//        bottomViewport.y = 0;
//        bottomViewport.w = SCREEN_WIDTH;
//        bottomViewport.h = SCREEN_HEIGHT / 4;
        
        //fullViewport
        fullViewport.x = 0;
        fullViewport.y = 0;
        fullViewport.w = SCREEN_WIDTH;
        fullViewport.h = SCREEN_HEIGHT;
        SDL_RenderSetViewport( renderer, &fullViewport );
        
        if(layoutReset){
            
            stepCount=0;
            if(isReturning){
                leader.moveAbs(returnPosX[mapReturningFrom], returnPosY[mapReturningFrom]);
                mapScout.moveAbs(returnPosX[mapReturningFrom], returnPosY[mapReturningFrom]);
                isReturning = 0;
            }
            else{
                leader.moveAbs(startPosX[mapNumber], startPosY[mapNumber]);
                mapScout.moveAbs(startPosX[mapNumber], startPosY[mapNumber]);
            }
            charDir=DOWN;
            layoutReset=0;
            
        }
        
        //Render background
        mapTexture[mapNumber].render( renderer, 0, 0, &camera[mapNumber] );
        
        if (activeCharacter==KAT){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteSide, SDL_FLIP_HORIZONTAL );
        }
        else if( activeCharacter==ALBUS){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteSide, SDL_FLIP_HORIZONTAL );
        }
        else if( activeCharacter==ELSA){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteSide, SDL_FLIP_HORIZONTAL );
        }
        else if( activeCharacter==JACK){
            if (charDir==UP) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteBack, SDL_FLIP_NONE );
            else if (charDir==DOWN) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteFront, SDL_FLIP_NONE );
            else if (charDir==LEFT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteSide, SDL_FLIP_NONE );
            else if (charDir==RIGHT) leader.renderRel( renderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteSide, SDL_FLIP_HORIZONTAL );
        }
        
        //CHECK FOR BATTLE SWITCHING
        
        //int battleSteps = 10 + rand()%20;
        if(stepCount>25 && mapNumber!=0){
            stepCount=0;
            //Mix_HaltMusic();
            cout<<"Switch to Battle Mode"<<endl;
            
            vector<MainCharacter *> chars;
            vector<Enemy *> enemies;
            
            MainCharacter *Elsa = new MainCharacter(pathForFile("Characters/Elsa.character"));
            MainCharacter *Elsa2 = new MainCharacter(pathForFile("Characters/Elsa.character"));
            MainCharacter *Elsa3 = new MainCharacter(pathForFile("Characters/Elsa.character"));
            chars.push_back(Elsa);
            chars.push_back(Elsa2);
            chars.push_back(Elsa3);
            
            Enemy *goblin = new Enemy(pathForFile("Characters/Goblin.character"));
            Enemy *goblin2 = new Enemy(pathForFile("Characters/Troll.character"));
            enemies.push_back(goblin);
            enemies.push_back(goblin2);
            
            BattleViewController *vc = new BattleViewController(chars, enemies, pathForFile("Images/arendelle.jpg"), renderer);

            pushViewController(vc);
            
        }
    return 1;
    }
}

//------------------------------------------------------------------------------------------

void OpenWorldViewController::pushViewController(ViewController *vc) {
    Mix_PauseMusic();
    
    ViewController::pushViewController(vc);
    
}

void OpenWorldViewController::becomeTop() {
    ViewController::becomeTop();
    
    leader.clearVels();
    mapScout.clearVels();
    
    //cout<<"X: "<<leader.getPosX()<<" Y: "<<leader.getPosY()<<endl;
    //Mix_ResumeMusic();
}

void OpenWorldViewController::dismiss() {
    Mix_HaltMusic();
    ViewController::dismiss();
    
}

