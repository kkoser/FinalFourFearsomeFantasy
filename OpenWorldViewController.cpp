//
//  OpenWorldViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "OpenWorldViewController.h"

OpenWorldViewController::OpenWorldViewController(SDL_Renderer *ren) : ViewController(ren) {
    
}

void OpenWorldViewController::loadTextures() {
    
    bool success;
    //Load Sprite Side Views
    if( !katSpriteSide.loadFromFile( "katSpriteSide.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteSide.loadFromFile( "albusSpriteSide.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteSide.loadFromFile( "elsaSpriteSide.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteSide.loadFromFile( "jackSpriteSide.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //load Sprite Front Views
    if( !katSpriteFront.loadFromFile( "katSpriteFront.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteFront.loadFromFile( "albusSpriteFront.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteFront.loadFromFile( "elsaSpriteFront.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteFront.loadFromFile( "jackSpriteFront.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //load sprite Back Views
    if( !katSpriteBack.loadFromFile( "katSpriteBack.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !albusSpriteBack.loadFromFile( "albusSpriteBack.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !elsaSpriteBack.loadFromFile( "elsaSpriteBack.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    if( !jackSpriteBack.loadFromFile( "jackSpriteBack.png", renderer ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
    
    //Load Maps
    if( !mapTexture[0].loadFromFile( "map0.png", renderer ) )
	{
		printf( "Failed to load map0 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[1].loadFromFile( "map1.png", renderer ) )
	{
		printf( "Failed to load map1 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[2].loadFromFile( "map2.png", renderer ) )
	{
		printf( "Failed to load map2 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[3].loadFromFile( "map3.png", renderer ) )
	{
		printf( "Failed to load map3 background texture image!\n" );
		success = false;
	}
    if( !mapTexture[4].loadFromFile( "map4.png", renderer ) )
	{
		printf( "Failed to load map4 background texture image!\n" );
		success = false;
	}


}

int OpenWorldViewController::draw(SDL_Event e) {
    
    /*if(ViewController::draw(e) == 0) {
        return 0;
    }
     */

    
    return 1;
}