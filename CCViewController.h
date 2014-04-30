//
//  CCViewController.h
//  FFFF
//
//  Created by Zach Waterson on 4/29/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __FFFF__CCViewController__
#define __FFFF__CCViewController__

#include <iostream>
#include "ViewController.h"
#include "ImageView.h"
#include "OpenWorldViewController.h"
#include "MainCharacter.h"

class CCViewController : public ViewController {
public:
    CCViewController(SDL_Renderer *rend);
    ~CCViewController();
    virtual int draw(SDL_Event e);
    virtual void pushViewController(ViewController *vc);
    virtual void becomeTop();
    
private:
    ImageView backgroundImage;
    ImageView redXImage;
    int characterToLeaveBehind = 0;
};

#endif /* defined(__FFFF__CCViewController__) */
