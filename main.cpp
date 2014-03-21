#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 650;

//------------------------------------------------------------------------------
//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( string path );
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};
//------------------------------------------------------------------------------
class Character{
public:
    Character(); //constructor
    Character(int x, int y); //non-default constructor
    int getX();
    int getY();
    double getDegs();
    SDL_RendererFlip getDir();
    void setDegs(double value);
    void setDir(int direction);
    void moveRel(int x, int y); //move relative to current pos.
    void moveAbs(int x, int y); //move to absolute location in window
    SDL_RendererFlip flipRight();
    SDL_RendererFlip flipLeft();
private:
    int xLoc;
    int yLoc;
    double degs; //degrees of rotation
    int faceDir; //direction they are facing (1=up, 2=down, 3=left, 4=right)
    SDL_RendererFlip flipDir;
    
    
    
};


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

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
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
//Sprite Sheets
LTexture elsaSpriteTexture;
LTexture katSpriteTexture;
LTexture jackSpriteTexture;
LTexture albusSpriteTexture;
//Background Images
LTexture NorthMountBGTexture;
LTexture CaveBGTexture;
LTexture IslandBGTexture;
LTexture ForestBGTexture;
LTexture BViewTexture;

//Scene Alpha texture
LTexture gModulatedTexture;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

//------------------------------------------------------------------------------
void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}
//------------------------------------------------------------------------------
void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
//------------------------------------------------------------------------------
void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}
//------------------------------------------------------------------------------
LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
//------------------------------------------------------------------------------
LTexture::~LTexture()
{
	free();
}
//------------------------------------------------------------------------------
int Character::getX(){
    return xLoc;
}
//------------------------------------------------------------------------------
int Character::getY(){
    return yLoc;
}
//------------------------------------------------------------------------------
void Character::moveRel(int x, int y){
    xLoc=getX()+x;
    yLoc=getY()+y;
}
//------------------------------------------------------------------------------
void Character::moveAbs(int x, int y){
    xLoc=x;
    yLoc=y;
}
//------------------------------------------------------------------------------
void Character::setDegs(double value){
    degs=value;
}
//------------------------------------------------------------------------------
double Character::getDegs(){
    return degs;
}
//------------------------------------------------------------------------------
void Character::setDir(int direction){
    faceDir=direction;
}
//------------------------------------------------------------------------------
SDL_RendererFlip Character::getDir(){
    return flipDir;
}
//------------------------------------------------------------------------------
SDL_RendererFlip Character::flipLeft(){
    flipDir=SDL_FLIP_NONE;
    return flipDir;
}
//------------------------------------------------------------------------------
SDL_RendererFlip Character::flipRight(){
    flipDir=SDL_FLIP_HORIZONTAL;
    return flipDir;
}
//------------------------------------------------------------------------------
Character::Character(){
    //initialize stuff
    xLoc=0;
    yLoc=0;
    degs=0;
    flipDir=SDL_FLIP_NONE;
}
//------------------------------------------------------------------------------
Character::Character(int x, int y){
    //initialize stuff
    xLoc=x;
    yLoc=y;
    degs=0;
    flipDir=SDL_FLIP_NONE;
}
//------------------------------------------------------------------------------
bool LTexture::loadFromFile( string path )
{
	//Get rid of preexisting texture
	free();
    
	//The final texture
	SDL_Texture* newTexture = NULL;
    
	//Load image from specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
        
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
    
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
//------------------------------------------------------------------------------
void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
//------------------------------------------------------------------------------
void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
//------------------------------------------------------------------------------
int LTexture::getWidth()
{
	return mWidth;
}
//------------------------------------------------------------------------------
int LTexture::getHeight()
{
	return mHeight;
}
//------------------------------------------------------------------------------
bool init(){
	//Initialization flag
	bool success = true;
    
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
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
                
			}
        }
    }
    
	return success;
}
//------------------------------------------------------------------------------
bool loadMedia(){
	//Loading success flag
	bool success = true;
    
    //Load battle textures
	if( !elsaBattleTexture.loadFromFile( "elsaBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !katBattleTexture.loadFromFile( "katBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !jackBattleTexture.loadFromFile( "jackBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !albusBattleTexture.loadFromFile( "albusBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
    //Load dialogue textures
	if( !albusDialogueTexture.loadFromFile( "albusDialogue.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !katDialogueTexture.loadFromFile( "katDialogue.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !elsaDialogueTexture.loadFromFile( "elsaDialogue.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    if( !jackDialogueTexture.loadFromFile( "jackDialogue.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
	//Load background textures
	if( !NorthMountBGTexture.loadFromFile( "arendelle.jpg" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    
    //Load bottom viewport texture
	if( !BViewTexture.loadFromFile( "BattleStats.jpg" ) )
	{
		printf( "Failed to load bottom viewport texture image!\n" );
		success = false;
	}

	else
	{
		//Set sprite clips
		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  64;
		gSpriteClips[ 0 ].h = 205;
        
		gSpriteClips[ 1 ].x =  64;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  64;
		gSpriteClips[ 1 ].h = 205;
		
		gSpriteClips[ 2 ].x = 128;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  64;
		gSpriteClips[ 2 ].h = 205;
        
		gSpriteClips[ 3 ].x = 196;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  64;
		gSpriteClips[ 3 ].h = 205;
	}
    
	return success;
}
//------------------------------------------------------------------------------
void close(){
    
    //Free loaded images
	elsaBattleTexture.free();
	NorthMountBGTexture.free();
    
    //Free loaded images
	gSpriteSheetTexture.free();
    
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
    
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
    
}
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
            
            //Characters
            Character Elsa(720,500);
            Character Albus(750,350);
            Character Jack(650,430);
            Character Kat(850,430);
            
			//Event handler
			SDL_Event e;
            
            //initial layout
            WindowLayouts layout=BATTLE_LAYOUT;
            
            //initial active character
            MainCharacters activeCharacter=ELSA;
            
            //Angle of rotation iterator for oscillating
            int elsaRotIterator=0;
            int jackRotIterator=0;
            int albusRotIterator=0;
            int katRotIterator=0;
            
            //Color Modulation components
            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;
            
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
                    
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    
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
                                break;
                                
                            //move character down
                            case SDLK_DOWN:
                                if(activeCharacter==ELSA) Elsa.moveRel(0,15);
                                if(activeCharacter==KAT) Kat.moveRel(0,15);
                                if(activeCharacter==JACK) Jack.moveRel(0,15);
                                if(activeCharacter==ALBUS) Albus.moveRel(0,15);
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
                                break;
                              
                            //set Albus as active
                            case SDLK_1:
                                activeCharacter=ALBUS;
                                break;
                            
                            //set Elsa as active
                            case SDLK_2:
                                activeCharacter=ELSA;
                                break;
                                
                            //set Jack as active
                            case SDLK_3:
                                activeCharacter=JACK;
                                break;
                                
                            //set Kat as active
                            case SDLK_4:
                                activeCharacter=KAT;
                                break;
                                
                            //set open-world layout
                            case SDLK_o:
                                layout=OPEN_LAYOUT;
                                break;
                                
                            //set battle layout
                            case SDLK_b:
                                layout=BATTLE_LAYOUT;
                                break;
                                
                            default:
                                break;
						}
					}
                }
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                if(layout == BATTLE_LAYOUT){
                
                    //Top viewport
                    SDL_Rect topViewport;
                    topViewport.x = 0;
                    topViewport.y = SCREEN_HEIGHT / 3;
                    topViewport.w = SCREEN_WIDTH;
                    topViewport.h = SCREEN_HEIGHT;
                    SDL_RenderSetViewport( gRenderer, &topViewport );
                    
                    //Render background texture to screen
                    NorthMountBGTexture.setColor(r,g,b);
                    NorthMountBGTexture.render(0,150);
                    
                    //Render battle characters to the screen
                    elsaBattleTexture.render( Elsa.getX(), Elsa.getY(), NULL, Elsa.getDegs(), NULL, Elsa.getDir() );
                    katBattleTexture.render( Kat.getX(), Kat.getY(), NULL, Kat.getDegs(), NULL, Kat.getDir() );
                    jackBattleTexture.render( Jack.getX(), Jack.getY(), NULL, Jack.getDegs(), NULL, Jack.getDir() );
                    albusBattleTexture.render( Albus.getX(), Albus.getY(), NULL, Albus.getDegs(), NULL, Albus.getDir() );
                    
                    //Bottom viewport
                    SDL_Rect bottomViewport;
                    bottomViewport.x = 0;
                    bottomViewport.y = 0;
                    bottomViewport.w = SCREEN_WIDTH;
                    bottomViewport.h = SCREEN_HEIGHT / 3;
                    SDL_RenderSetViewport( gRenderer, &bottomViewport );
                    
                    //Render battleStat boxes to the screen
                    BViewTexture.render(0,0);
                    
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
                    
                  
                }
                else if(layout == OPEN_LAYOUT){
                    
                    //Check for Rendering Dialogue Textures to the Screen
                    if(activeCharacter==ELSA){
                        elsaDialogueTexture.render( 10, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, Elsa.getDir() );
                    }
                    if(activeCharacter==KAT){
                        katDialogueTexture.render( 0, 2*SCREEN_HEIGHT/3+40, NULL, NULL, NULL, Kat.getDir() );
                    }
                    if(activeCharacter==JACK){
                        jackDialogueTexture.render( 10, 2*SCREEN_HEIGHT/3+60, NULL, NULL, NULL, Jack.getDir() );
                    }
                    if(activeCharacter==ALBUS){
                        albusDialogueTexture.render( 20, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, Albus.getDir() );
                    }
                }
                
                //Update screen
                SDL_RenderPresent( gRenderer );
                SDL_Delay(20);
                
                
			}
            
		}
	}
    
	//Free resources and close SDL
	close();
    
	return 0;
}


