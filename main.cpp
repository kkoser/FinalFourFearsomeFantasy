//
//  main.cpp
//  FFFF
//
//  Created by Casey Hanley on 3/27/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "Dot.h"
#include "LTexture.h"
#include "CharacterView.h"
#include "Settings.h"
using namespace std;

//The dimensions of the level (if you change this, change it in Dot.cpp, too)
const int LEVEL_WIDTH[8] = {1200,1312,1312,1792,1344,1312,1312,1312};
const int LEVEL_HEIGHT[8] = {656,880,2400,704,1248,2400,2400,2400};

//Screen dimension constants (if you change this, change it in Dot.cpp, too)
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 650;

//------------------------------------------------------------------------------
//              INITIALIZE VARIABLES/FUNCTIONS
//------------------------------------------------------------------------------

//Key press surfaces constants
enum KeyPressSurfaces{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

enum WindowLayouts{
	BATTLE_LAYOUT,
    OPEN_LAYOUT
};

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

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window * gWindow = NULL;

//The window renderer
SDL_Renderer * gRenderer = NULL;

//Globally used font
TTF_Font * gFont = NULL;

//Text texture
LTexture textAndaleTexture;

//Battle Images
LTexture elsaBattleTexture;
LTexture katBattleTexture;
LTexture jackBattleTexture;
LTexture albusBattleTexture;

//Dialogue Images
LTexture elsaDialogueTexture;
LTexture katDialogueTexture;
LTexture jackDialogueTexture;
LTexture albusDialogueTexture;

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

//Dot (character) textures for exploration mode
//LTexture gDotTexture;

//------------------------------------------------------------------------------
//              RUN INITIALIZATION FUNCTION
//------------------------------------------------------------------------------
bool init(){
	//Initialization flag
	bool success = true;
    
	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
        
		//Create window
		gWindow = SDL_CreateWindow( "Final Fantasy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
                
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
                
                //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
                
			}
        }
    }
    
	return success;
}
//------------------------------------------------------------------------------
//              START OF A DYNAMIC TEXT DISPLAY FUNCTION
//------------------------------------------------------------------------------
bool getText(){
    bool success = true;
    
    //Open the font
    gFont = TTF_OpenFont( "AndaleMono.ttf", 16 );
    if( gFont == NULL )
    {
        printf( "Failed to load andale mono font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255 };
        if( !textAndaleTexture.loadFromRenderedText( "5: Elsa's Theme", textColor, gRenderer, gFont ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    
    return success;
}
//------------------------------------------------------------------------------
//              LOAD ALL IMAGES/SPRITES/MUSIC FILES
//------------------------------------------------------------------------------
bool loadMedia(){
	//Loading success flag
	bool success = true;
    
    //Load battle textures
	if( !elsaBattleTexture.loadFromFile( pathForFile("Images/elsaBattle.png"), gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !katBattleTexture.loadFromFile( pathForFile("Images/katBattle.png"), gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !jackBattleTexture.loadFromFile( pathForFile("Images/jackBattle.png"), gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !albusBattleTexture.loadFromFile( pathForFile("Images/albusBattle.png"), gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
    //Load dialogue textures
	if( !albusDialogueTexture.loadFromFile( pathForFile("Images/albusDialogue.png"), gRenderer ) )
	{
		printf( "Failed to load albus's texture image!\n" );
		success = false;
	}
    if( !katDialogueTexture.loadFromFile( pathForFile("Images/katDialogue.png"), gRenderer ) )
	{
		printf( "Failed to load kat's texture image!\n" );
		success = false;
	}
    if( !elsaDialogueTexture.loadFromFile( pathForFile("Images/elsaDialogue.png"), gRenderer ) )
	{
		printf( "Failed to load elsa's texture image!\n" );
		success = false;
	}
    if( !jackDialogueTexture.loadFromFile( pathForFile("Images/jackDialogue.png"), gRenderer ) )
	{
		printf( "Failed to load jack's texture image!\n" );
		success = false;
	}
    
    //Load Sprite Side Views
    if( !katSpriteSide.loadFromFile( pathForFile("Images/katSpriteSide.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteSide.loadFromFile( pathForFile("Images/albusSpriteSide.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteSide.loadFromFile( pathForFile("Images/elsaSpriteSide.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteSide.loadFromFile( pathForFile("Images/jackSpriteSide.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //load Sprite Front Views
    if( !katSpriteFront.loadFromFile( pathForFile("Images/katSpriteFront.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteFront.loadFromFile( pathForFile("Images/albusSpriteFront.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteFront.loadFromFile( pathForFile("Images/elsaSpriteFront.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteFront.loadFromFile( pathForFile("Images/jackSpriteFront.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}

    //load sprite Back Views
    if( !katSpriteBack.loadFromFile( pathForFile("Images/katSpriteBack.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteBack.loadFromFile( pathForFile("Images/albusSpriteBack.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteBack.loadFromFile( pathForFile("Images/elsaSpriteBack.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteBack.loadFromFile( pathForFile("Images/jackSpriteBack.png"), gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
	//Load background textures
	if( !ArendelleTexture.loadFromFile( pathForFile("Images/arendelle.jpg"), gRenderer ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    if( !NorthMountBGTexture.loadFromFile( pathForFile("Images/battleNorthMountain.jpg"), gRenderer ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    
    //Load Maps
    if( !mapTexture[0].loadFromFile( pathForFile("Images/map0.png"), gRenderer ) )
	{
		printf( "Failed to load map0 background texture image!\n" );
		success = false;
	}
   if( !mapTexture[1].loadFromFile( pathForFile("Images/map1.png"), gRenderer ) )
	{
		printf( "Failed to load map1 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[2].loadFromFile( pathForFile("Images/map2.png"), gRenderer ) )
	{
		printf( "Failed to load map2 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[3].loadFromFile( pathForFile("Images/map3.png"), gRenderer ) )
	{
		printf( "Failed to load map3 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[4].loadFromFile( pathForFile("Images/map4.png"), gRenderer ) )
	{
		printf( "Failed to load map4 background texture image!\n" );
		success = false;
	}
//    if( !mapTexture[5].loadFromFile( pathForFile("Images/map5.png"), gRenderer ) )
//	{
//		printf( "Failed to load map5 background texture image!\n" );
//		success = false;
//	}
//    if( !mapTexture[6].loadFromFile( pathForFile("Images/map6.png"), gRenderer ) )
//	{
//		printf( "Failed to load map6 background texture image!\n" );
//		success = false;
//	}
//    if( !mapTexture[7].loadFromFile( pathForFile("Images/map7.png"), gRenderer ) )
//	{
//		printf( "Failed to load map7 background texture image!\n" );
//		success = false;
//	}
    
    //Load bottom viewport texture
	if( !BViewTexture.loadFromFile( pathForFile("Images/BattleStats.jpg"), gRenderer ) )
	{
		printf( "Failed to load bottom viewport texture image!\n" );
		success = false;
	}

    //Load music
    elsaMusic = Mix_LoadMUS( "LetItGo.wav" );
    if( elsaMusic == NULL )
    {
        printf( "Failed to load Elsa music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jackMusic = Mix_LoadMUS( "hesAPirate.wav" );
    if( jackMusic == NULL )
    {
        printf( "Failed to load Jack Music SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    katMusic = Mix_LoadMUS( "ArrowsAtTheSky.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load Kat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    albusMusic = Mix_LoadMUS( "hedwigsTheme.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load Albus music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    cityMusic = Mix_LoadMUS( "GoT.wav" );
    if( cityMusic == NULL )
    {
        printf( "Failed to load city music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    mustafarMusic = Mix_LoadMUS( "anakinVSobi.wav" );
    if( cityMusic == NULL )
    {
        printf( "Failed to load mustafar music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    elsaSoundEffect = Mix_LoadWAV( "elsaSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load kat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    jackSoundEffect = Mix_LoadWAV( "jackSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load jack sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    katSoundEffect = Mix_LoadWAV( "katSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load kat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    albusSoundEffect = Mix_LoadWAV( "albusSoundEffect.wav" );
    if( katMusic == NULL )
    {
        printf( "Failed to load albus sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
	return success;
}
//------------------------------------------------------------------------------
//              FREE SOME MEMORY
//------------------------------------------------------------------------------
void close(){
    
    //Free loaded images
    
	elsaBattleTexture.free();
    katBattleTexture.free();
    jackBattleTexture.free();
    albusBattleTexture.free();
    
    elsaDialogueTexture.free();
    katDialogueTexture.free();
    jackDialogueTexture.free();
    albusDialogueTexture.free();
    
    elsaSpriteSide.free();
    katSpriteSide.free();
    jackSpriteSide.free();
    albusSpriteSide.free();
    elsaSpriteFront.free();
    katSpriteFront.free();
    jackSpriteFront.free();
    albusSpriteFront.free();
    elsaSpriteBack.free();
    katSpriteBack.free();
    jackSpriteBack.free();
    albusSpriteBack.free();
    
    ArendelleTexture.free();
    mapTexture[1].free();
    mapTexture[2].free();
    CaveBGTexture.free();
    IslandBGTexture.free();
    ForestBGTexture.free();
    BViewTexture.free();
    
    textAndaleTexture.free();
    
    //Free the music
    Mix_FreeMusic( elsaMusic );
    Mix_FreeMusic( katMusic );
    Mix_FreeMusic( jackMusic );
    Mix_FreeMusic( albusMusic );
    elsaMusic = NULL;
    katMusic = NULL;
    jackMusic = NULL;
    albusMusic = NULL;
    
    //Free the sound effects
    Mix_FreeChunk( soundEffect1 );
    soundEffect1 = NULL;
    Mix_FreeChunk( elsaSoundEffect );
    elsaSoundEffect = NULL;
    Mix_FreeChunk( jackSoundEffect );
    jackSoundEffect = NULL;
    Mix_FreeChunk( katSoundEffect );
    katSoundEffect = NULL;
    Mix_FreeChunk( albusSoundEffect );
    albusSoundEffect = NULL;

    
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
    
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
    
	//Quit SDL subsystems
    Mix_Quit();
	IMG_Quit();
    TTF_Quit();
	SDL_Quit();
    
}
//------------------------------------------------------------------------------
//              PLAY THE GAME WITH USER INPUT
//------------------------------------------------------------------------------
int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
            
//------------------------------------------------------------------------------
//              INITIALIZE VARIABLES
//------------------------------------------------------------------------------
            //Characters for Battle
            CharacterView Elsa(720,500);
            CharacterView Albus(750,350);
            CharacterView Jack(650,430);
            CharacterView Kat(850,430);
            
            
			//Event handler
			SDL_Event e;
            
            //Play the music
            
            //initial layout
            WindowLayouts layout=OPEN_LAYOUT;
            int layoutReset=1;
            
            //initial active character
            MainCharacters activeCharacter=ELSA;
            
            //initial Character Direction
            Direction charDir=UP;
            
            //Angle of rotation iterator for oscillating
            float elsaRotIterator=0;
            float jackRotIterator=0;
            float albusRotIterator=0;
            float katRotIterator=0;
            
            //open dialogue file
            string filename=pathForFile("Dialogue/SampleScript.dialogue");
            ifstream file(filename.c_str());
            //check for open
            if (!file) {
                cout<<"File "<<filename<<" failed to open"<<endl;
            }
            
            //declare dialogue line
            string diaLine;
            
            //initialize color
            SDL_Color whiteColor = { 255, 255, 255};
            
            //read from file
            getline(file,diaLine);
            
            //initialize step counter for battles
            int stepCount=0;
            
            //the dot to move around the screen
            Dot leader;
            
            //The camera area
			SDL_Rect camera[8];
            for(int q=0;q<8;q++) camera[q]= { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            
            //initialize map number
            int mapNumber=0;
            
            //initialize character direction
            int charDirTemp=1;

            //initialize zone as valid
            int zone=9;
            
            Dot mapScout;
            
            int startPosX[8];
            for(int q=0; q<8; q++) startPosX[q]=50;
            int startPosY[8];
            for(int q=0; q<8; q++) startPosY[q]=50;
            
            startPosX[0]=752;
            startPosY[0]=176;
            startPosX[1]=80;
            startPosY[1]=784;
            startPosX[2]=544;
            startPosY[2]=2300;
            startPosX[3]=1728;
            startPosY[3]=304;
            
            
			//While application is running
			while( !quit )
			{

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
                    
                    getText(); //load in text

                    
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    
//------------------------------------------------------------------------------
//              HANDLE KEYPRESSES
//------------------------------------------------------------------------------
                    
                    //Process User Input
					else if( e.type == SDL_KEYDOWN )
					{
                        
						switch( e.key.keysym.sym )
						{
                            //move character up
                            case SDLK_UP:
                                if(activeCharacter==ELSA) Elsa.moveRel(0,-15);
                                if(activeCharacter==KAT) Kat.moveRel(0,-15);
                                if(activeCharacter==JACK) Jack.moveRel(0,-15);
                                if(activeCharacter==ALBUS) Albus.moveRel(0,-15);
                                stepCount++;
                                if(layout==OPEN_LAYOUT) cout<<"Steps: "<<stepCount<<endl;
                                break;
                                
                            //move character down
                            case SDLK_DOWN:
                                if(activeCharacter==ELSA) Elsa.moveRel(0,15);
                                if(activeCharacter==KAT) Kat.moveRel(0,15);
                                if(activeCharacter==JACK) Jack.moveRel(0,15);
                                if(activeCharacter==ALBUS) Albus.moveRel(0,15);
                                stepCount++;
                                if(layout==OPEN_LAYOUT) cout<<"Steps: "<<stepCount<<endl;
                                break;
                                
                            //move character left
                            case SDLK_LEFT:
                                if(activeCharacter==ELSA){
                                    Elsa.moveRel(-15,0);
                                    Elsa.flipLeft();
                                }
                                if(activeCharacter==KAT){
                                    Kat.moveRel(-15,0);
                                    Kat.flipLeft();
                                }
                                if(activeCharacter==JACK){
                                    Jack.moveRel(-15,0);
                                    Jack.flipLeft();
                                }
                                if(activeCharacter==ALBUS){
                                    Albus.moveRel(-15,0);
                                    Albus.flipLeft();
                                }
                                stepCount++;
                                if(layout==OPEN_LAYOUT) cout<<"Steps: "<<stepCount<<endl;
                                break;
                                
                            //move character right
                            case SDLK_RIGHT:
                                if(activeCharacter==ELSA){
                                    Elsa.moveRel(15,0);
                                    Elsa.flipRight();
                                }
                                if(activeCharacter==KAT){
                                    Kat.moveRel(15,0);
                                    Kat.flipRight();
                                }
                                if(activeCharacter==JACK){
                                    Jack.moveRel(15,0);
                                    Jack.flipRight();
                                }
                                if(activeCharacter==ALBUS){
                                    Albus.moveRel(15,0);
                                    Albus.flipRight();
                                }
                                stepCount++;
                                if(layout==OPEN_LAYOUT) cout<<"Steps: "<<stepCount<<endl;
                                break;
                                
                                
                            //cycle through dialogue
                            case SDLK_RETURN:
                                getline(file,diaLine);
                                break;
                                
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
                                
                            //set battle layout
                            case SDLK_b:
                                layout=BATTLE_LAYOUT;
                                layoutReset=1;
                                Mix_HaltMusic();
                                break;

						}
                        
                
					}
                    
                    //Handle input for the character and scout
					leader.handleEvent( e );
                    mapScout.handleEvent( e );
                    
                    //check for layout switch
                    if(zone != 9 && layout==OPEN_LAYOUT){
                        
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
                                layout=BATTLE_LAYOUT;
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
                    
                    
                }
                
                
//------------------------------------------------------------------------------
//              MOVE THE CHARACTERS AND CAMERA
//------------------------------------------------------------------------------
                //Move the character
                if(!layoutReset && layout==OPEN_LAYOUT){
                    
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
                    
                }

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
                
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //declare viewports
                SDL_Rect fullViewport;
                SDL_Rect topViewport;
                SDL_Rect bottomViewport;
                
//------------------------------------------------------------------------------
//              BATTLE LAYOUT
//------------------------------------------------------------------------------
                switch(layout){
                    case BATTLE_LAYOUT:
                    
                        if( Mix_PlayingMusic() == 0 )
                        {
                            //Play the music
                            Mix_PlayMusic( elsaMusic, -1 );
                        }
                    
                        if(layoutReset){
                            //reset positions
                            Elsa.moveAbs(720,500);
                            Albus.moveAbs(750, 350);
                            Jack.moveAbs(650, 430);
                            Kat.moveAbs(850, 430);
                            Elsa.flipLeft();
                            Albus.flipLeft();
                            Jack.flipLeft();
                            Kat.flipLeft();
                            
                            layoutReset=0;
                        }
      
                        //Top viewport
                        topViewport.x = 0;
                        topViewport.y = SCREEN_HEIGHT / 3;
                        topViewport.w = SCREEN_WIDTH;
                        topViewport.h = SCREEN_HEIGHT;
                        SDL_RenderSetViewport( gRenderer, &topViewport );
                        
                        //Render background texture to screen
                        ArendelleTexture.render(gRenderer, 0,150);
                        
                        //Render battle characters to the screen
                        elsaBattleTexture.render( gRenderer, Elsa.getX(), Elsa.getY(), NULL, Elsa.getDegs(), NULL, Elsa.getDir() );
                        katBattleTexture.render( gRenderer, Kat.getX(), Kat.getY(), NULL, Kat.getDegs(), NULL, Kat.getDir() );
                        jackBattleTexture.render( gRenderer, Jack.getX(), Jack.getY(), NULL, Jack.getDegs(), NULL, Jack.getDir() );
                        albusBattleTexture.render( gRenderer, Albus.getX(), Albus.getY(), NULL, Albus.getDegs(), NULL, Albus.getDir() );
                        
                        //Check for Rendering Dialogue Textures to the Screen
                        if(activeCharacter==ELSA){
                            elsaDialogueTexture.render( gRenderer, 10, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, SDL_FLIP_NONE );
                        }
                        if(activeCharacter==KAT){
                            katDialogueTexture.render( gRenderer, 0, 2*SCREEN_HEIGHT/3+40, NULL, NULL, NULL, SDL_FLIP_NONE );
                        }
                        if(activeCharacter==JACK){
                            jackDialogueTexture.render( gRenderer, 10, 2*SCREEN_HEIGHT/3+60, NULL, NULL, NULL, SDL_FLIP_NONE );
                        }
                        if(activeCharacter==ALBUS){
                            albusDialogueTexture.render( gRenderer, 20, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, SDL_FLIP_NONE );
                        }
                       
                        //Bottom viewport
                        bottomViewport.x = 0;
                        bottomViewport.y = 0;
                        bottomViewport.w = SCREEN_WIDTH;
                        bottomViewport.h = SCREEN_HEIGHT / 3;
                        SDL_RenderSetViewport( gRenderer, &bottomViewport );
                        
                        
                        //Render battleStat boxes to the screen
                        BViewTexture.render(gRenderer, 0,0);
                        
                        //Render text
                        textAndaleTexture.loadFromRenderedText( "1: Choose Albus", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 20, 20 );
                        textAndaleTexture.loadFromRenderedText( "2: Choose Elsa", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 20, 45 );
                        textAndaleTexture.loadFromRenderedText( "3: Choose Jack", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 20, 70 );
                        textAndaleTexture.loadFromRenderedText( "4: Choose Kat", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 20, 95 );
                        textAndaleTexture.loadFromRenderedText( "Arrow Keys: Move", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 20, 120 );
                        
                        
                        textAndaleTexture.loadFromRenderedText( "5: Elsa's Theme", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 380, 20 );
                        textAndaleTexture.loadFromRenderedText( "6: Jack's Theme", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 380, 45 );
                        textAndaleTexture.loadFromRenderedText( "7: Kat's Theme", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 380, 70 );
                        textAndaleTexture.loadFromRenderedText( "8: Albus' Theme", whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 380, 95 );
                        textAndaleTexture.loadFromRenderedText( diaLine, whiteColor, gRenderer, gFont );
                        textAndaleTexture.render( gRenderer, 380, 120 );
                        
                        
                        if (activeCharacter==ELSA){
                            elsaRotIterator++;
                            Elsa.setDegs(Elsa.getDegs()+sin(elsaRotIterator));
                        }
                        else if (activeCharacter==ALBUS){
                            albusRotIterator++;
                            Albus.setDegs(Albus.getDegs()+sin(albusRotIterator));
                        }
                        else if (activeCharacter==JACK){
                            jackRotIterator++;
                            Jack.setDegs(Jack.getDegs()+sin(jackRotIterator));
                        }
                        else if (activeCharacter==KAT){
                            katRotIterator++;
                            Kat.setDegs(Kat.getDegs()+sin(katRotIterator));
                        } 
                    
                        break;
                
//------------------------------------------------------------------------------
//              OPEN LAYOUT
//------------------------------------------------------------------------------
                    case OPEN_LAYOUT:
                        
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
                        SDL_RenderSetViewport( gRenderer, &fullViewport );
                        
                        
                        if(layoutReset){
                            
                            
                            stepCount=0;
                            leader.moveAbs(startPosX[mapNumber], startPosY[mapNumber]);
                            mapScout.moveAbs(startPosX[mapNumber], startPosY[mapNumber]);
                            charDir=UP;
                            
                            layoutReset=0;
                            
                        }
                        
                        //Render background
                        mapTexture[mapNumber].render( gRenderer, 0, 0, &camera[mapNumber] );
                        
                        //move Katniss around if she is selected
                        if (activeCharacter==KAT){
                            if (charDir==UP) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteBack, Kat.getDir() );
                            else if (charDir==DOWN) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteFront, Kat.getDir() );
                            else if (charDir==LEFT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteSide, Kat.getDir() );
                            else if (charDir==RIGHT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &katSpriteSide, Kat.getDir() );
                        }
                        else if( activeCharacter==ALBUS){
                                if (charDir==UP) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteBack, Albus.getDir() );
                                else if (charDir==DOWN) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteFront, Albus.getDir() );
                                else if (charDir==LEFT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteSide, Albus.getDir() );
                                else if (charDir==RIGHT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &albusSpriteSide, Albus.getDir() );
                        }
                        else if( activeCharacter==ELSA){
                            if (charDir==UP) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteBack, Elsa.getDir() );
                            else if (charDir==DOWN) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteFront, Elsa.getDir() );
                            else if (charDir==LEFT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteSide, Elsa.getDir() );
                            else if (charDir==RIGHT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &elsaSpriteSide, Elsa.getDir() );
                        }
                        else if( activeCharacter==JACK){
                            if (charDir==UP) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteBack, Jack.getDir() );
                            else if (charDir==DOWN) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteFront, Jack.getDir() );
                            else if (charDir==LEFT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteSide, Jack.getDir() );
                            else if (charDir==RIGHT) leader.renderRel( gRenderer, camera[mapNumber].x, camera[mapNumber].y, &jackSpriteSide, Jack.getDir() );
                        }
                        
                        
                        //SDL_RenderSetViewport( gRenderer, &bottomViewport );
                        
                        
                        //Render battleStat boxes to the screen
                        //BViewTexture.render(gRenderer, 0,0);
                        
//                        //Check for Rendering Dialogue Textures to the Screen
//                        if(activeCharacter==ELSA){
//                            elsaDialogueTexture.render( gRenderer, 10, 0, NULL, NULL, NULL, SDL_FLIP_NONE );
//                        }
//                        if(activeCharacter==KAT){
//                            katDialogueTexture.render( gRenderer, 0, 0, NULL, NULL, NULL, SDL_FLIP_NONE );
//                        }
//                        if(activeCharacter==JACK){
//                            jackDialogueTexture.render( gRenderer, 10, 0, NULL, NULL, NULL, SDL_FLIP_NONE );
//                        }
//                        if(activeCharacter==ALBUS){
//                            albusDialogueTexture.render( gRenderer, 20, 0, NULL, NULL, NULL, SDL_FLIP_NONE );
//                        }
                        
                        break;
                        
                    default:
                        cout<<"NO LAYOUT SELECTED!"<<endl; break;
                    
                }
                
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
                SDL_Delay(30);

                
			}
            
		}
	}
    
	//Free resources and close SDL
	close();
    
	return 0;
}


