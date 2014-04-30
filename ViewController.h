//
//  ViewController.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__ViewController__
#define __FinalFourFearsomeFantasy__ViewController__

#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <string>
#include <vector>
#include "LTexture.h"
#include "Settings.h"

class ViewController {
protected:
    SDL_Renderer *renderer;
    ViewController *base = NULL;
    ViewController *top = NULL;
    Mix_Music *music; //pointer to music

public:
    //the basic constructor. The renderer should be for the window that the VC should draw in
    ViewController(SDL_Renderer *ren);
    
    //pop this viewcontroller from the stack. The base becomes the new top
    //NOTE: This should only be used on the top VC
    virtual void dismiss();
    //called by dismiss on the top
    virtual void becomeTop();
    //add a new viewcontroller to the stack. call dismiss on the new VC to remove and bring control back to this one
    virtual void pushViewController(ViewController *vc);
    
    //the main method of the viewcontroller
    //****call ViewController::draw first, and check result to see if you should be drawing!!!!
    virtual int draw(SDL_Event e);
    
    void setBase(ViewController *vc);
    
    ~ViewController();
};

#endif /* defined(__FinalFourFearsomeFantasy__ViewController__) */
