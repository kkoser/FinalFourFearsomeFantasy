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
#include "OpenWorldViewController.h"

#include "MainCharacter.h"
#include "Enemy.h"

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 650;

//------------------------------------------------------------------------------
//              INITIALIZE VARIABLES/FUNCTIONS
//------------------------------------------------------------------------------

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window * gWindow = NULL;

//The window renderer
SDL_Renderer * gRenderer = NULL;


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
void close(){

    
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
	else{

			//Main loop flag
			bool quit = false;

            //Event handler
			SDL_Event e;
            SDL_Event empty;

            //temporary character stuff
            vector<MainCharacter *> chars;
            vector<Enemy *> enemies;
        
            OpenWorldViewController baseVC(gRenderer);
            //ExampleViewController baseVC(gRenderer);

            //While application is running
			while( !quit )
			{

				//Handle events on queue
				SDL_PollEvent( &e );
				

					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    
                    baseVC.draw(e);
                    
                    
                 //Update screen
                SDL_RenderPresent( gRenderer );
<<<<<<< HEAD
                SDL_Delay(3);
                
                
                e = empty;
                
			
=======
                SDL_Delay(30);
                e=empty;

>>>>>>> FETCH_HEAD
            
            }
	
    cout<<"Closing the application"<<endl;
    
	//Free resources and close SDL
	close();
    }
    
	return 0;
}


