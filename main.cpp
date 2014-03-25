#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"
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
    
    //Creates image from font string
    bool loadFromRenderedText( string textureText, SDL_Color textColor );
    
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
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Text texture
LTexture textAndaleTexture;

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
LTexture NorthMountBGTexture;
LTexture CaveBGTexture;
LTexture IslandBGTexture;
LTexture ForestBGTexture;
LTexture BViewTexture;

//Map Textures
LTexture practiceMapTexture;

//Scene Alpha texture
LTexture gModulatedTexture;

//The music that will be played
Mix_Music *elsaMusic = NULL;
Mix_Music *albusMusic = NULL;
Mix_Music *katMusic = NULL;
Mix_Music *jackMusic = NULL;

//The sound effects that will be used
Mix_Chunk *soundEffect1 = NULL;
Mix_Chunk *albusSoundEffect = NULL;
Mix_Chunk *elsaSoundEffect = NULL;
Mix_Chunk *jackSoundEffect = NULL;
Mix_Chunk *katSoundEffect = NULL;

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
bool LTexture::loadFromRenderedText( string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mTexture != NULL;
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
        if( !textAndaleTexture.loadFromRenderedText( "5: Elsa's Theme", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
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
		printf( "Failed to load albus's texture image!\n" );
		success = false;
	}
    if( !katDialogueTexture.loadFromFile( "katDialogue.png" ) )
	{
		printf( "Failed to load kat's texture image!\n" );
		success = false;
	}
    if( !elsaDialogueTexture.loadFromFile( "elsaDialogue.png" ) )
	{
		printf( "Failed to load elsa's texture image!\n" );
		success = false;
	}
    if( !jackDialogueTexture.loadFromFile( "jackDialogue.png" ) )
	{
		printf( "Failed to load jack's texture image!\n" );
		success = false;
	}
    
    //Load Sprite Side Views
    if( !katSpriteSide.loadFromFile( "katSpriteSide.png" ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
//    if( !albusSpriteSide.loadFromFile( "albusSpriteSide.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    if( !elsaSpriteSide.loadFromFile( "elsaSpriteSide.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    if( !jackSpriteSide.loadFromFile( "jackSpriteSide.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    
    //load Sprite Front Views
    if( !katSpriteFront.loadFromFile( "katSpriteFront.png" ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
//    if( !albusSpriteFront.loadFromFile( "albusSpriteFront.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    if( !elsaSpriteFront.loadFromFile( "elsaSpriteFront.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    if( !jackSpriteFront.loadFromFile( "jackSpriteFront.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    
    //load sprite Back Views
    if( !katSpriteBack.loadFromFile( "katSpriteBack.png" ) )
	{
		printf( "Failed to load kat's sprite texture image!\n" );
		success = false;
	}
//    if( !albusSpriteBack.loadFromFile( "albusSpriteBack.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    if( !elsaSpriteBack.loadFromFile( "elsaSpriteBack.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
//    if( !jackSpriteBack.loadFromFile( "jackSpriteBack.jpg" ) )
//	{
//		printf( "Failed to load kat's sprite texture image!\n" );
//		success = false;
//	}
    
	//Load background textures
	if( !NorthMountBGTexture.loadFromFile( "arendelle.jpg" ) )
	{
		printf( "Failed to load north mountain background texture image!\n" );
		success = false;
	}
    
    //Load Maps
    if( !practiceMapTexture.loadFromFile( "practiceMap.png" ) )
	{
		printf( "Failed to load practice map background texture image!\n" );
		success = false;
	}
    
    //Load bottom viewport texture
	if( !BViewTexture.loadFromFile( "BattleStats.jpg" ) )
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
    
    NorthMountBGTexture.free();
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
            
            //initial Character Direction
            Direction charDir=LEFT;
            
            //Play the music
            Mix_PlayMusic( elsaMusic, -1 ); //start playing Elsa's music
            
            //Angle of rotation iterator for oscillating
            float elsaRotIterator=0;
            float jackRotIterator=0;
            float albusRotIterator=0;
            float katRotIterator=0;
            
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
                                charDir=UP;
                                break;
                                
                            //move character down
                            case SDLK_DOWN:
                                if(activeCharacter==ELSA) Elsa.moveRel(0,15);
                                if(activeCharacter==KAT) Kat.moveRel(0,15);
                                if(activeCharacter==JACK) Jack.moveRel(0,15);
                                if(activeCharacter==ALBUS) Albus.moveRel(0,15);
                                charDir=DOWN;
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
                                charDir=LEFT;
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
                                charDir=RIGHT;
                                break;
                                
                            case SDLK_5: //Elsa's Music
                                //If there is no music playing
                                if( Mix_PlayingMusic() == 0 )
                                {
                                    //Play the music
                                    Mix_PlayMusic( elsaMusic, -1 );
                                }
                                //If music is being played
                                else
                                {
                                    //If the music is paused
                                    if( Mix_PausedMusic() == 1 )
                                    {
                                        //Resume the music
                                        Mix_ResumeMusic();
                                    }
                                    //If the music is playing
                                    else
                                    {
                                        //Pause the music
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                            
                            case SDLK_6: //Jack's Music
                                //If there is no music playing
                                if( Mix_PlayingMusic() == 0 )
                                {
                                    //Play the music
                                    Mix_PlayMusic( jackMusic, -1 );
                                }
                                //If music is being played
                                else
                                {
                                    //If the music is paused
                                    if( Mix_PausedMusic() == 1 )
                                    {
                                        //Resume the music
                                        Mix_ResumeMusic();
                                    }
                                    //If the music is playing
                                    else
                                    {
                                        //Pause the music
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                            
                            case SDLK_7: //Kat's Music
                                //If there is no music playing
                                if( Mix_PlayingMusic() == 0 )
                                {
                                    //Play the music
                                    Mix_PlayMusic( katMusic, -1 );
                                }
                                //If music is being played
                                else
                                {
                                    //If the music is paused
                                    if( Mix_PausedMusic() == 1 )
                                    {
                                        //Resume the music
                                        Mix_ResumeMusic();
                                    }
                                    //If the music is playing
                                    else
                                    {
                                        //Pause the music
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                                
                            case SDLK_8: //Kat's Music
                                //If there is no music playing
                                if( Mix_PlayingMusic() == 0 )
                                {
                                    //Play the music
                                    Mix_PlayMusic( albusMusic, -1 );
                                }
                                //If music is being played
                                else
                                {
                                    //If the music is paused
                                    if( Mix_PausedMusic() == 1 )
                                    {
                                        //Resume the music
                                        Mix_ResumeMusic();
                                    }
                                    //If the music is playing
                                    else
                                    {
                                        //Pause the music
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                                
                            case SDLK_9:
                                //Stop the music
                                Mix_HaltMusic();
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
                    NorthMountBGTexture.render(0,150);
                    
                    //Render battle characters to the screen
                    elsaBattleTexture.render( Elsa.getX(), Elsa.getY(), NULL, Elsa.getDegs(), NULL, Elsa.getDir() );
                    katBattleTexture.render( Kat.getX(), Kat.getY(), NULL, Kat.getDegs(), NULL, Kat.getDir() );
                    jackBattleTexture.render( Jack.getX(), Jack.getY(), NULL, Jack.getDegs(), NULL, Jack.getDir() );
                    albusBattleTexture.render( Albus.getX(), Albus.getY(), NULL, Albus.getDegs(), NULL, Albus.getDir() );
                    
                    //Check for Rendering Dialogue Textures to the Screen
                    if(activeCharacter==ELSA){
                        elsaDialogueTexture.render( 10, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                    if(activeCharacter==KAT){
                        katDialogueTexture.render( 0, 2*SCREEN_HEIGHT/3+40, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                    if(activeCharacter==JACK){
                        jackDialogueTexture.render( 10, 2*SCREEN_HEIGHT/3+60, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                    if(activeCharacter==ALBUS){
                        albusDialogueTexture.render( 20, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                   
                    //Bottom viewport
                    SDL_Rect bottomViewport;
                    bottomViewport.x = 0;
                    bottomViewport.y = 0;
                    bottomViewport.w = SCREEN_WIDTH;
                    bottomViewport.h = SCREEN_HEIGHT / 3;
                    SDL_RenderSetViewport( gRenderer, &bottomViewport );
                    
                    //Render battleStat boxes to the screen
                    BViewTexture.render(0,0);
                    
                    //Render text (put into a class later to make it easier w/ functions and shit)
                    textAndaleTexture.loadFromRenderedText( "1: Choose Albus", { 255, 255, 255 } );
                    textAndaleTexture.render( 20, 20 );
                    textAndaleTexture.loadFromRenderedText( "2: Choose Elsa", { 255, 255, 255 } );
                    textAndaleTexture.render( 20, 45 );
                    textAndaleTexture.loadFromRenderedText( "3: Choose Jack", { 255, 255, 255 } );
                    textAndaleTexture.render( 20, 70 );
                    textAndaleTexture.loadFromRenderedText( "4: Choose Kat", { 255, 255, 255 } );
                    textAndaleTexture.render( 20, 95 );
                    textAndaleTexture.loadFromRenderedText( "Arrow Keys: Move", { 255, 255, 255 } );
                    textAndaleTexture.render( 20, 120 );
                    
                    
                    textAndaleTexture.loadFromRenderedText( "5: Elsa's Theme", { 255, 255, 255 } );
                    textAndaleTexture.render( 380, 20 );
                    textAndaleTexture.loadFromRenderedText( "6: Jack's Theme", { 255, 255, 255 } );
                    textAndaleTexture.render( 380, 45 );
                    textAndaleTexture.loadFromRenderedText( "7: Kat's Theme", { 255, 255, 255 } );
                    textAndaleTexture.render( 380, 70 );
                    textAndaleTexture.loadFromRenderedText( "8: Albus' Theme", { 255, 255, 255 } );
                    textAndaleTexture.render( 380, 95 );
                    textAndaleTexture.loadFromRenderedText( "9: Stop Music (To Play Different Song)", { 255, 255, 255 } );
                    textAndaleTexture.render( 380, 120 );
                    
                    
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
                    
                    
                    //Top viewport
                    SDL_Rect fullViewport;
                    fullViewport.x = 0;
                    fullViewport.y = 0;
                    fullViewport.w = SCREEN_WIDTH;
                    fullViewport.h = SCREEN_HEIGHT;
                    SDL_RenderSetViewport( gRenderer, &fullViewport );
                    
                    //Render map texture to screen
                    practiceMapTexture.render(0,0);
                    
                    //move Katniss around if she is selected
                    if (charDir==UP) katSpriteBack.render( Kat.getX(), Kat.getY(), NULL, Kat.getDegs(), NULL, SDL_FLIP_NONE );
                    else if (charDir==DOWN) katSpriteFront.render( Kat.getX(), Kat.getY(), NULL, Kat.getDegs(), NULL, SDL_FLIP_NONE );
                    else if (charDir==LEFT || charDir==RIGHT) katSpriteSide.render( Kat.getX(), Kat.getY(), NULL, Kat.getDegs(), NULL, Kat.getDir() );
                    
                    
                    //Check for Rendering Dialogue Textures to the Screen
                    if(activeCharacter==ELSA){
                        elsaDialogueTexture.render( 10, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                    if(activeCharacter==KAT){
                        katDialogueTexture.render( 0, 2*SCREEN_HEIGHT/3+40, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                    if(activeCharacter==JACK){
                        jackDialogueTexture.render( 10, 2*SCREEN_HEIGHT/3+60, NULL, NULL, NULL, SDL_FLIP_NONE );
                    }
                    if(activeCharacter==ALBUS){
                        albusDialogueTexture.render( 20, 2*SCREEN_HEIGHT/3+50, NULL, NULL, NULL, SDL_FLIP_NONE );
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


