//
//  Dot.cpp
//  FFFF
//
//  Created by Casey Hanley on 3/27/14.
//  Copyright (c) 2014 Casey Hanley. All rights reserved.
//

#include "Dot.h"
#include "Settings.h"

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
using namespace std;


//------------------------------------------------------------------------------
Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    mapHeight[0]=41+2;
    mapWidth[0]=75+2;
    
    mapHeight[1]=55+2;
    mapWidth[1]=82+2;
    
    mapHeight[2]=150+2;
    mapWidth[2]=82+2;
    
    mapHeight[3]=44+2;
    mapWidth[3]=112+2;
    
    mapHeight[4]=78+2;
    mapWidth[4]=84+2;
    
    mapHeight[5]=90+2;
    mapWidth[5]=100+2;
    
    mapHeight[6]=55+2;
    mapWidth[6]=107+2;
    
    mapHeight[7]=80+2;
    mapWidth[7]=100+2;
    
    keyPressed=0;
    
    
}
//------------------------------------------------------------------------------
Dot::Dot(int PosX, int PosY)
{
    //Initialize the offsets
    mPosX = PosX;
    mPosY = PosY;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    mapHeight[0]=41+2;
    mapWidth[0]=75+2;
    
    mapHeight[1]=55+2;
    mapWidth[1]=82+2;
    
    mapHeight[2]=150+2;
    mapWidth[2]=82+2;
    
    mapHeight[3]=150+2;
    mapWidth[3]=82+2;
    
    mapHeight[4]=78+2;
    mapWidth[4]=84+2;
    
    mapHeight[5]=90+2;
    mapWidth[5]=100+2;
    
    mapHeight[6]=55+2;
    mapWidth[6]=107+2;
    
    mapHeight[7]=80+2;
    mapWidth[7]=100+2;
    
    keyPressed=0;
    
}

//------------------------------------------------------------------------------
void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; keyPressed=1;
                break;
            case SDLK_DOWN: mVelY += DOT_VEL; keyPressed=1;
                break;
            case SDLK_LEFT: mVelX -= DOT_VEL; keyPressed=1;
                break;
            case SDLK_RIGHT: mVelX += DOT_VEL; keyPressed=1;
                break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; keyPressed=1;
                break;
            case SDLK_DOWN: mVelY -= DOT_VEL; keyPressed=1;
                break;
            case SDLK_LEFT: mVelX += DOT_VEL; keyPressed=1;
                break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; keyPressed=1;
                break;
        }
    }
}
//------------------------------------------------------------------------------
void Dot::moveSmoothUnrestricted(int mapNumber) //with velocity
{

    //Move the dot left or right
    mPosX += mVelX;
    
    //If the dot went too far to the right
    if( ( (mPosX+8)/16 +1) > mapWidth[mapNumber] )
    {
        //Move back
        mPosX += mVelX;
    }
    else if ( ((mPosX+8)/16 +1) < 0 ){
        //Move back
        mPosX += mVelX;
    }
    
    //Move the dot up or down
    mPosY += mVelY;
    
    //If the dot went too far up or down
    if( ( ((mPosY+25)/16 +1) > mapHeight[mapNumber] ) )
    {
        //Move back
        mPosY += mVelY;
    }
    else if ( ((mPosY+25)/16 +1) < 0 ){
        //Move back
        mPosY += mVelY;
    }
}
//------------------------------------------------------------------------------
void Dot::moveSmooth(int zone,int mapNumber) //with velocity
{
    if(zone!=8){
        mPosX += mVelX;
    }

    //If the dot went too far to the right
    if( ( (mPosX+8)/16 +1) > mapWidth[mapNumber] )
    {
        //Move back
        mPosX += mVelX;
    }
    else if ( ((mPosX+8)/16 +1) < 0 ){
        //Move back
        mPosX += mVelX;
    }
    
    //Move the dot up or down
    if(zone!=8){
        mPosY += mVelY;
    }
    
    //If the dot went too far up or down
    if( ( ((mPosY+25)/16 +1) > mapHeight[mapNumber] ) )
    {
        //Move back
        mPosY += mVelY;
    }
    else if ( ((mPosY+25)/16 +1) < 0 ){
        //Move back
        mPosY += mVelY;
    }

    
}
//------------------------------------------------------------------------------
void Dot::moveBackSmooth(int mapNumber) //with velocity
{

    //Move the dot left or right
    mPosX -= mVelX;

    //If the dot went too far to the right
    if( ( (mPosX+8)/16 +1) > mapWidth[mapNumber] )
    {
        //Move back
        mPosX -= mVelX;
    }
    else if ( ((mPosX+8)/16 +1) < 0 ){
        //Move back
        mPosX -= mVelX;
    }
    
    //Move the dot up or down
    mPosY -= mVelY;
    
    //If the dot went too far up or down
    if( ( ((mPosY+25)/16 +1) > mapHeight[mapNumber] ) )
    {
        //Move back
        mPosY -= mVelY;
    }
    else if ( ((mPosY+25)/16 +1) < 0 ){
       //Move back
       mPosY -= mVelY;
    }
}

//------------------------------------------------------------------------------
int Dot::checkZone(int mapNumber){
    int zone;
    
    zone = mapArray[(mPosY+25)/16 +1][(mPosX+8)/16 +1];
    
    return zone;
}
//------------------------------------------------------------------------------
int Dot::getCharDir(int scoutX, int scoutY, int currentDir){
    
    //0=up 1=down 2=left 3=right
    int difX,difY;
    difX = scoutX - mPosX;
    difY = scoutY - mPosY;

    if(keyPressed){
        keyPressed=0;
        
        if(difY==0){
            if(difX<0) return 2;
            if(difX>0) return 3;
        }
        if(difX==0){
            if(difY<0) return 0;
            if(difY>0) return 1;
        }
        
        if( abs(difX) > abs(difY) ){
            if(difX>0) return 3;
            else if(difX<0) return 2;
        }
        
        else if( abs(difX) < abs(difY) ){
            if(difY>0) return 0;
            else if(difY<0) return 1;
        }
    }
    return currentDir;
    
    
    
}
//------------------------------------------------------------------------------
void Dot::moveAbs(int x, int y){
    mPosX=x;
    mPosY=y;
}
//------------------------------------------------------------------------------
void Dot::render(SDL_Renderer * gRenderer, LTexture gDotTexture)
{
    //Show the dot
	gDotTexture.render( gRenderer, mPosX, mPosY );
}
//------------------------------------------------------------------------------
void Dot::renderRel( SDL_Renderer * gRenderer, int camX, int camY, LTexture * gDotTexture, SDL_RendererFlip flipType )
{
    //Show the dot relative to the camera
	gDotTexture->render( gRenderer, mPosX - camX, mPosY - camY, NULL, NULL, NULL, flipType );
}
//------------------------------------------------------------------------------
int Dot::getPosX()
{
	return mPosX;
}
//------------------------------------------------------------------------------
int Dot::getPosY()
{
	return mPosY;
}
//------------------------------------------------------------------------------
void Dot::clearVels(){
    mVelX=0;
    mVelY=0;
}
//------------------------------------------------------------------------------
void Dot::initializeMap(int mapNumber){
    
    string filename;
    switch(mapNumber){
        case 0:
            filename="MapFiles/map0.csv";
            break;
        case 1:
            filename="MapFiles/map1.csv";
            break;
        case 2:
            filename="MapFiles/map2.csv";
            break;
        case 3:
            filename="MapFiles/map3.csv";
            break;
        case 4:
            filename="MapFiles/map4.csv";
            break;
        case 5:
            filename="MapFiles/map5.csv";
            break;
        case 6:
            filename="MapFiles/map6.csv";
            break;
        case 7:
            filename="MapFiles/map7.csv";
            break;
    }
    
    filename = pathForFile(filename);
    
    string zone;
    int zoneInt;
    ifstream myfile;
    myfile.open(filename.c_str());
    if (myfile.is_open()){
        for(int y=0; y<mapHeight[mapNumber]; y++){
            for(int x=0; x<mapWidth[mapNumber]; x++){
                getline ( myfile, zone, ',' );
                //cout<<zone;
                zoneInt = atoi(zone.c_str());
                mapArray[y][x] = zoneInt;
                //cout<<mapArray[y][x];
                //if(x<mapWidth[mapNumber]-1) cout<<",";
            }
            cout<<endl;
        }
        myfile.close();
    }
    else cout<<"Error opening file";
    
}
