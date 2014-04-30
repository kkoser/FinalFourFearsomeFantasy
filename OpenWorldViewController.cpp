//
//  OpenWorldViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "OpenWorldViewController.h"
#include "ExampleViewController.h"
#include "Dot.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "LTexture.h"
#include <time.h>
#include <stdlib.h>

//---------------------------------------------------------

OpenWorldViewController::OpenWorldViewController(SDL_Renderer *ren, int charLeftBehind) : ViewController(ren) {
    
    srand ((int)time(NULL));
    
    loadTextures();
    
    layoutReset=1;
    charDir=DOWN;
    stepCount=0;
    characterLeftBehind = charLeftBehind;
    
    switch(characterLeftBehind){
        case 1:
            activeCharacter=ELSA;
            break;
        case 2:
            activeCharacter=ELSA;
            break;
        case 3:
            activeCharacter=ALBUS;
            break;
        case 4:
            activeCharacter=ELSA;
            break;
    }
    charIterator=0;
    dragonBallCount=0;
    for(int q=0; q<7; q++) dragonBallFound[q]=0;
    dragonBallJustFound=0;
    displayAllDragonBallsFound=0;
    dragonBallFoundString="";
    dragonBallCountString="";
    dragonBallFoundText = TextLabel(360, 320, dragonBallFoundString, defaultFont, 48, renderer);
    dragonBallCountText = TextLabel(16, 610, dragonBallCountString, defaultFont, 24, renderer);
    dragonBallFoundText.setColor(0,0,0);
    dragonBallCountText.setColor(255,255,255);
    
    allDragonBallsFoundString = "All Dragon Balls Found! Journey to the Castle.";
    allDragonBallsFoundText = TextLabel(330, 350, allDragonBallsFoundString, defaultFont, 24, renderer);
    allDragonBallsFoundText.setColor(0,0,0);

    

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
    startPosX[5]=250;
    startPosY[5]=1250;
    startPosX[6]=1680;
    startPosY[6]=30;
    startPosX[7]=1570;
    startPosY[7]=1065;
    
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
    returnPosX[5]=1100;
    returnPosY[5]=400;
    returnPosX[6]=15;
    returnPosY[6]=260;
    returnPosX[7]=30;
    returnPosY[7]=30;
    
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
    if( !mapTexture[5].loadFromFile( pathForFile("Images/map5.png"), renderer ) )
	{
		printf( "Failed to load map5 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[6].loadFromFile( pathForFile("Images/map6.png"), renderer ) )
	{
		printf( "Failed to load map5 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[7].loadFromFile( pathForFile("Images/map7.png"), renderer ) )
	{
		printf( "Failed to load map5 background texture image!\n" );
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
    desertMusic = Mix_LoadMUS( pathForFile("Audio/nascence.wav" ).c_str());
    if( desertMusic == NULL )
    {
        printf( "Failed to load desert music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    castleMusic = Mix_LoadMUS( pathForFile("Audio/dracarys.wav" ).c_str());
    if( castleMusic == NULL )
    {
        printf( "Failed to load castle music! SDL_mixer Error: %s\n", Mix_GetError() );
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
                    /*case SDLK_1:
                        dragonBallJustFound=1;
                        dragonBallCount=7;
                        dragonBallFoundString="Desert Dragon Ball Found!";
                        dragonBallFoundText.setX(290);
                        dragonBallFoundText.setY(300);
                        dragonBallFoundText.draw();
                        break;*/
                        
                    case SDLK_SPACE:
                        dragonBallJustFound=0;
                        displayAllDragonBallsFound=0;
                        break;
                        
                        //cycle through characters
                    case SDLK_RETURN:
                        
                        if(characterLeftBehind==1){ //kat
                            switch(charIterator){
                                case 0:
                                    activeCharacter=ALBUS;
                                    Mix_PlayChannel( -1, albusSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 1:
                                    activeCharacter=JACK;
                                    Mix_PlayChannel( -1, jackSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 2:
                                    activeCharacter=ELSA;
                                    Mix_PlayChannel( -1, elsaSoundEffect, 0 );
                                    charIterator=0;
                                    break;
                            }
                        }
                        else if(characterLeftBehind==2){ //albus
                            switch(charIterator){
                                case 0:
                                    activeCharacter=KAT;
                                    Mix_PlayChannel( -1, katSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 1:
                                    activeCharacter=JACK;
                                    Mix_PlayChannel( -1, jackSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 2:
                                    activeCharacter=ELSA;
                                    Mix_PlayChannel( -1, elsaSoundEffect, 0 );
                                    charIterator=0;
                                    break;
                            }
                        }
                        if(characterLeftBehind==3){ //ELSA
                            switch(charIterator){
                                case 0:
                                    activeCharacter=KAT;
                                    Mix_PlayChannel( -1, katSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 1:
                                    activeCharacter=JACK;
                                    Mix_PlayChannel( -1, jackSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 2:
                                    activeCharacter=ALBUS;
                                    Mix_PlayChannel( -1, albusSoundEffect, 0 );
                                    charIterator=0;
                                    break;
                            }
                        }
                        if(characterLeftBehind==4){ //jack
                            switch(charIterator){
                                case 0:
                                    activeCharacter=ALBUS;
                                    Mix_PlayChannel( -1, albusSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 1:
                                    activeCharacter=KAT;
                                    Mix_PlayChannel( -1, katSoundEffect, 0 );
                                    charIterator++;
                                    break;
                                case 2:
                                    activeCharacter=ELSA;
                                    Mix_PlayChannel( -1, elsaSoundEffect, 0 );
                                    charIterator=0;
                                    break;
                            }
                        }
                        
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
                    case 6:
                        mapNumber=6;
                        layoutReset=1;
                        isReturning=0;
                        mapScout.initializeMap(6);
                        Mix_HaltMusic();
                        break;
                    case 7:
                        if(dragonBallCount==7){
                            mapNumber=7;
                            layoutReset=1;
                            isReturning=0;
                            mapScout.initializeMap(7);
                            Mix_HaltMusic();
                        }
                        break;
                    case 10: //INITIAL MAIN BATTLE
                        
                        
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
                    case 16: //FINAL BATTLE
                        if(dragonBallCount==7){
                            //implement final battle
                        }
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
                    case 21:
                        mapNumber=0;
                        mapReturningFrom=5;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 22:
                        mapNumber=0;
                        mapReturningFrom=6;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(0);
                        Mix_HaltMusic();
                        break;
                    case 23:
                        mapNumber=6;
                        mapReturningFrom=7;
                        layoutReset=1;
                        isReturning=1;
                        mapScout.initializeMap(6);
                        Mix_HaltMusic();
                        break;
                        
                        //DRAGON BALLS
                    case 40:
                        if(dragonBallJustFound) dragonBallFoundString="City Dragon Ball Found!";
                        else dragonBallFoundString="";
                        if(!dragonBallFound[0]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[0]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(340);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(0,0,0);
                            allDragonBallsFoundText.setColor(0,0,0);
                            
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                    case 41:
                        if(dragonBallJustFound) dragonBallFoundString="Mustafar Dragon Ball Found!";
                        else dragonBallFoundString="";
                        if(!dragonBallFound[1]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[1]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(270);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(255,255,255);
                            allDragonBallsFoundText.setColor(255,255,255);
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                    case 42:
                        if(dragonBallJustFound) dragonBallFoundString="North Mountain Dragon Ball Found!";
                        else dragonBallFoundString="";
                        if(!dragonBallFound[2]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[2]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(200);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(0,0,0);
                            allDragonBallsFoundText.setColor(0,0,0);
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                    case 43:
                        if(dragonBallJustFound) dragonBallFoundString="Forbidden Forest Dragon Ball Found!";
                        else dragonBallFoundString="";
                        if(!dragonBallFound[3]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[3]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(180);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(255,255,255);
                            allDragonBallsFoundText.setColor(255,255,255);
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                    case 44:
                        if(dragonBallJustFound) dragonBallFoundString="Cave Dragon Ball Found!";
                        else dragonBallFoundString="";
                        if(!dragonBallFound[4]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[4]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(310);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(255,255,255);
                            allDragonBallsFoundText.setColor(255,255,255);
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                    case 45:
                        if(dragonBallJustFound) dragonBallFoundString="Lonely Island Dragon Ball Found!";
                        else dragonBallFoundString="";
                        if(!dragonBallFound[5]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[5]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(240);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(0,0,0);
                            allDragonBallsFoundText.setColor(0,0,0);
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                    case 46:
                        if(dragonBallJustFound) dragonBallFoundString="Desert Dragon Ball Found!";
                        else dragonBallFoundString="";
                        
                        if(!dragonBallFound[6]){ //only if you haven't found it yet
                            dragonBallCount++;
                            dragonBallFound[6]=1;
                            dragonBallJustFound=1;
                            dragonBallFoundText.setX(290);
                            dragonBallFoundText.setY(300);
                            dragonBallFoundText.setColor(0,0,0);
                            allDragonBallsFoundText.setColor(0,0,0);
                            dragonBallCountText.setColor(0,0,0);
                        }
                        if(dragonBallCount==7){
                            displayAllDragonBallsFound=1;
                        }
                        break;
                        
                    case 31: //treasure1
                        
                        break;
                    case 32: //treasure2
                        
                        break;
                    case 33: //treasure3
                        
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
        
        //cout<<zone<<endl;
        
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
                case 6:
                    Mix_PlayMusic( desertMusic, -1);
                    break;
                case 7:
                    Mix_PlayMusic( castleMusic, -1);
                    break;
            }
        }
        
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
        
        //display dragon ball count ALWAYS
        switch (dragonBallCount){
            case 0:
                dragonBallCountString = "Dragon Balls: 0/7";
                break;
            case 1:
                dragonBallCountString = "Dragon Balls: 1/7";
                break;
            case 2:
                dragonBallCountString = "Dragon Balls: 2/7";
                break;
            case 3:
                dragonBallCountString = "Dragon Balls: 3/7";
                break;
            case 4:
                dragonBallCountString = "Dragon Balls: 4/7";
                break;
            case 5:
                dragonBallCountString = "Dragon Balls: 5/7";
                break;
            case 6:
                dragonBallCountString = "Dragon Balls: 6/7";
                break;
            case 7:
                dragonBallCountString = "Dragon Balls: 7/7";
                break;
        }
        
        switch(mapNumber){
            case 0:
                dragonBallCountText.setColor(255,255,255);
                break;
            case 1:
                dragonBallCountText.setColor(255,255,255);
                break;
            case 2:
                dragonBallCountText.setColor(0,0,0);
                break;
            case 3:
                dragonBallCountText.setColor(255,255,255);
                break;
            case 4:
                dragonBallCountText.setColor(255,255,255);
                break;
            case 5:
                dragonBallCountText.setColor(0,0,0);
                break;
            case 6:
                dragonBallCountText.setColor(0,0,0);
                break;
            case 7:
                dragonBallCountText.setColor(0,0,0);
                break;
        }
        
        //display dragon ball found until you hit enter
        dragonBallFoundText.setText(dragonBallFoundString);
        if(dragonBallJustFound){
            dragonBallFoundText.draw();
        }
        
        dragonBallCountText.setText(dragonBallCountString);
        dragonBallCountText.draw();
        
        //display all dragon balls found
        if(dragonBallCount==7 && displayAllDragonBallsFound){
            allDragonBallsFoundText.draw();
        }
        
        //CHECK FOR BATTLE SWITCHING
        
        //int battleSteps = 10 + rand()%20;
        if(stepCount>rand()%40 + 50 && mapNumber!=0){
            stepCount=0;
            //Mix_HaltMusic();
            cout<<"Switch to Battle Mode"<<endl;
            
            vector<string> enemyFileLocations;
            enemyFileLocations.push_back(pathForFile("Characters/GoblinArsonist.character"));
            enemyFileLocations.push_back(pathForFile("Characters/Troll.character"));
          
            BattleViewController *vc = createBattleViewController(pathForFile("Images/arendelle.jpg"), enemyFileLocations);
            pushViewController(vc);
            
        }
    return 1;
    }
}

//------------------------------------------------------------------------------------------

BattleViewController* OpenWorldViewController::createBattleViewController(string backgroundLocation, vector<string> enemyFileLocations) {
    
    
    vector<MainCharacter *> chars;
    vector<Enemy *> enemies;
    
    //make main characters
    if (characterLeftBehind != 1) {
        MainCharacter *Kat = new MainCharacter(pathForFile("Characters/Kat.character"));
        chars.push_back(Kat);
    }
    if (characterLeftBehind != 2) {
        MainCharacter *Albus = new MainCharacter(pathForFile("Characters/Albus.character"));
        chars.push_back(Albus);
    }
    if (characterLeftBehind != 3) {
        MainCharacter *Elsa = new MainCharacter(pathForFile("Characters/Elsa.character"));
        chars.push_back(Elsa);
    }
    if (characterLeftBehind != 4) {
        MainCharacter *Jack = new MainCharacter(pathForFile("Characters/Jack.character"));
        chars.push_back(Jack);
    }

    //make enemies
    vector<string>::const_iterator currentEnemy;
    for (currentEnemy = enemyFileLocations.begin(); currentEnemy != enemyFileLocations.end(); ++currentEnemy) {
        Enemy *enemy = new Enemy(*currentEnemy);
        enemies.push_back(enemy);
    }
    
    BattleViewController *vc = new BattleViewController(chars, enemies, backgroundLocation, renderer);
    return vc;
}

vector<string> getEnemiesForArea(int mapNum) {
    vector<string> enemies;
    switch (mapNum) {
        case 0:
            //no enemies in the city
            break;
        case 1:
            //mustafar (volcano)
            break;
        case 2:
            //north mountain
            break;
        case 3:
            //forbidden forest
            break;
        case 4:
            //cave
            break;
        case 5:
            //lonely island
            break;
        case 6:
            //desert
            break;
        case 7:
            //castle
            break;
        default:
            break;
    }
    
    return enemies;
}

void OpenWorldViewController::pushViewController(ViewController *vc) {
    Mix_PauseMusic();
    
    ViewController::pushViewController(vc);
    
}

void OpenWorldViewController::becomeTop() {
    ViewController::becomeTop();
    
    leader.clearVels();
    mapScout.clearVels();
    
    //cout<<"X: "<<leader.getPosX()<<" Y: "<<leader.getPosY()<<endl;
    Mix_ResumeMusic();
}

void OpenWorldViewController::dismiss() {
    Mix_HaltMusic();
    ViewController::dismiss();
    
}

