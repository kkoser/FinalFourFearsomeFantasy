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

//Key press surfaces constants
enum KeyPressSurfaces{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
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
LTexture gelsaTexture;
LTexture gkatTexture;
LTexture gjackTexture;
LTexture galbusTexture;
LTexture gBackgroundTexture;
LTexture gBViewTexture;

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
    
    //Load elsa texture
	if( !gelsaTexture.loadFromFile( "elsaBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
    //Load kat texture
	if( !gkatTexture.loadFromFile( "katBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
    //Load jack texture
	if( !gjackTexture.loadFromFile( "jackBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
    
    //Load albus texture
	if( !galbusTexture.loadFromFile( "albusBattle.png" ) )
	{
		printf( "Failed to load elsa' texture image!\n" );
		success = false;
	}
	
    //Load front alpha texture
	//if( !gModulatedTexture.loadFromFile( "ElsaPoseAlpha2.png" ) )
	//{
	//	printf( "Failed to load front texture!\n" );
	//	success = false;
	//}
	else
	{
		//Set standard alpha blending
		gModulatedTexture.setBlendMode( SDL_BLENDMODE_BLEND );
	}
    
	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "arendelle.jpg" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    
    //Load bottom viewport texture
	if( !gBViewTexture.loadFromFile( "BattleStats.jpg" ) )
	{
		printf( "Failed to load bottom viewport texture image!\n" );
		success = false;
	}
    
    //Load sprite sheet texture
	//if( !gSpriteSheetTexture.loadFromFile( "foo.png" ) )
	//{
	//	printf( "Failed to load walking animation texture!\n" );
	//	success = false;
	//}
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
	gelsaTexture.free();
	gBackgroundTexture.free();
    
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
            
			//Event handler
			SDL_Event e;
            
            //Angle of rotation
            double degrees = 0;
            
            //Flip type
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            
            //Current animation frame
			//int frame = 0;
            
            //Color Modulation components
            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;
            
            //Alpha Modulation component
            Uint8 a = 0;
            
            //character Positions
            int elsaX = 750;
            int elsaY = 400;
            int katX = 750;
            int katY = 250;
            int jackX = 600;
            int jackY = 300;
            int albusX = 900;
            int albusY = 300;
            
            //			//Set default current surface
            //			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
            
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
                    //On keypress change rgb values
					else if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
                                //Increase red
							case SDLK_q:
                                r += 32;
                                break;
                                
                                //Increase green
							case SDLK_w:
                                g += 32;
                                break;
                                
                                //Increase blue
							case SDLK_e:
                                b += 32;
                                break;
                                
                                //Decrease red
							case SDLK_a:
                                r -= 32;
                                break;
                                
                                //Decrease green
							case SDLK_s:
                                g -= 32;
                                break;
                                
                                //Decrease blue
							case SDLK_d:
                                b -= 32;
                                break;
                                
                                //Decrease blue
							case SDLK_p:
                                r -= 32;
                                g -= 32;
                                b -= 32;
                                break;
                                
                                //Decrease blue
							case SDLK_o:
                                r += 32;
                                g += 32;
                                b += 32;
                                break;
                                
                                //Increase transparency
							case SDLK_z:
                                //Cap if over 255
                                if( a + 15 > 255/2 )
                                {
                                    a = 255/2;
                                }
                                //Increment otherwise
                                else
                                {
                                    a += 15;
                                }
                                break;
                                
                                //Decrease transparency
							case SDLK_x:
                                //Cap if below 0
                                if( a - 15 < 0 )
                                {
                                    a = 0;
                                }
                                //Decrement otherwise
                                else
                                {
                                    a -= 15;
                                }
                                break;
                                
                                //move elsa up
                            case SDLK_UP:
                                elsaY-=15;
                                break;
                                
                                //move elsa down
                            case SDLK_DOWN:
                                elsaY+=15;
                                break;
                                
                                //move elsa left
                            case SDLK_LEFT:
                                flipType = SDL_FLIP_NONE;
                                elsaX-=15;
                                break;
                                
                                //move elsa right
                            case SDLK_RIGHT:
                                flipType = SDL_FLIP_HORIZONTAL;
                                elsaX+=15;
                                break;
                                
                            case SDLK_c:
                                degrees -= 7.5;
                                break;
                                
                            case SDLK_v:
                                degrees += 7.5;
                                break;
                                
                            case SDLK_r:
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;
                                
                            case SDLK_t:
                                flipType = SDL_FLIP_NONE;
                                break;
                                
                            case SDLK_y:
                                flipType = SDL_FLIP_VERTICAL;
                                break;
                                
                            default:
                                break;
						}
					}
                }
                
                
                
                //for(int i=0; i<5; elsaX-=3, i++){
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //Top viewport
                SDL_Rect topViewport;
                topViewport.x = 0;
                topViewport.y = SCREEN_HEIGHT / 3;
                topViewport.w = SCREEN_WIDTH;
                topViewport.h = SCREEN_HEIGHT;
                SDL_RenderSetViewport( gRenderer, &topViewport );
                
                //Render background texture to screen
                gBackgroundTexture.setColor(r,g,b);
                gBackgroundTexture.render(0,150);
                
                //Render characters to the screen
                gelsaTexture.render( elsaX, elsaY, NULL, degrees, NULL, flipType );
                gkatTexture.render( katX, katY, NULL, degrees, NULL, flipType );
                gjackTexture.render( jackX, jackY, NULL, degrees, NULL, flipType );
                galbusTexture.render( albusX, albusY, NULL, degrees, NULL, flipType );
                
                //Render front blended Elsa
                gModulatedTexture.setAlpha( a );
                gModulatedTexture.render( elsaX, elsaY, NULL, degrees, NULL, flipType );
                
                //Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = 0;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 3;
                SDL_RenderSetViewport( gRenderer, &bottomViewport );
                
                //Render battleStat boxes to the screen
                gBViewTexture.render(0,0);
                
                
                
                
                
                //                //Render current frame
                //				SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
                //				gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
                
                SDL_Delay(30);
                
                //SDL_Delay(100);
                
                //                //Go to next frame
                //				++frame;
                //
                //				//Cycle animation
                //				if( frame / 4 >= WALKING_ANIMATION_FRAMES )
                //				{
                //					frame = 0;
                //				}
                
                //}
                
			}
            
		}
	}
    
	//Free resources and close SDL
	close();
    
	return 0;
}


