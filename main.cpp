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
#include "ExampleViewController.h"
#include "MainMenuViewController.h"

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
	if( !elsaBattleTexture.loadFromFile( "elsaBattle.png", gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !katBattleTexture.loadFromFile( "katBattle.png", gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !jackBattleTexture.loadFromFile( "jackBattle.png", gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !albusBattleTexture.loadFromFile( "albusBattle.png", gRenderer ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
    //Load dialogue textures
	if( !albusDialogueTexture.loadFromFile( "albusDialogue.png", gRenderer ) )
	{
		printf( "Failed to load albus's texture image!\n" );
		success = false;
	}
    if( !katDialogueTexture.loadFromFile( "katDialogue.png", gRenderer ) )
	{
		printf( "Failed to load kat's texture image!\n" );
		success = false;
	}
    if( !elsaDialogueTexture.loadFromFile( "elsaDialogue.png", gRenderer ) )
	{
		printf( "Failed to load elsa's texture image!\n" );
		success = false;
	}
    if( !jackDialogueTexture.loadFromFile( "jackDialogue.png", gRenderer ) )
	{
		printf( "Failed to load jack's texture image!\n" );
		success = false;
	}
    
    //Load Sprite Side Views
    if( !katSpriteSide.loadFromFile( "katSpriteSide.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteSide.loadFromFile( "albusSpriteSide.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteSide.loadFromFile( "elsaSpriteSide.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteSide.loadFromFile( "jackSpriteSide.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //load Sprite Front Views
    if( !katSpriteFront.loadFromFile( "katSpriteFront.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteFront.loadFromFile( "albusSpriteFront.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteFront.loadFromFile( "elsaSpriteFront.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteFront.loadFromFile( "jackSpriteFront.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}

    //load sprite Back Views
    if( !katSpriteBack.loadFromFile( "katSpriteBack.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteBack.loadFromFile( "albusSpriteBack.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteBack.loadFromFile( "elsaSpriteBack.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteBack.loadFromFile( "jackSpriteBack.png", gRenderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
	//Load background textures
	if( !ArendelleTexture.loadFromFile( "arendelle.jpg", gRenderer ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    if( !NorthMountBGTexture.loadFromFile( "battleNorthMountain.jpg", gRenderer ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    
    //Load Maps
    if( !mapTexture[0].loadFromFile( "map0.png", gRenderer ) )
	{
		printf( "Failed to load map0 background texture image!\n" );
		success = false;
	}
   if( !mapTexture[1].loadFromFile( "map1.png", gRenderer ) )
	{
		printf( "Failed to load map1 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[2].loadFromFile( "map2.png", gRenderer ) )
	{
		printf( "Failed to load map2 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[3].loadFromFile( "map3.png", gRenderer ) )
	{
		printf( "Failed to load map3 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[4].loadFromFile( "map4.png", gRenderer ) )
	{
		printf( "Failed to load map4 background texture image!\n" );
		success = false;
	}
//    if( !mapTexture[5].loadFromFile( "map5.png", gRenderer ) )
//	{
//		printf( "Failed to load map5 background texture image!\n" );
//		success = false;
//	}
//    if( !mapTexture[6].loadFromFile( "map6.png", gRenderer ) )
//	{
//		printf( "Failed to load map6 background texture image!\n" );
//		success = false;
//	}
//    if( !mapTexture[7].loadFromFile( "map7.png", gRenderer ) )
//	{
//		printf( "Failed to load map7 background texture image!\n" );
//		success = false;
//	}
    
    //Load bottom viewport texture
	if( !BViewTexture.loadFromFile( "BattleStats.jpg", gRenderer ) )
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
            //Event handler
			SDL_Event e;
            
            MainMenuViewController baseVC(gRenderer);
            
            			//While application is running
			while( !quit )
			{

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 && !quit)
				{

					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
                        break;
					}
                    
                    baseVC.draw(e);
                    
                 //Update screen
                SDL_RenderPresent( gRenderer );
                SDL_Delay(1);

                
			}
            
		}
	}
    cout<<"Closing the application"<<endl;
    
	//Free resources and close SDL
	close();
    }
    
	return 0;
}


