//
//  MainMenuViewController.h
//  FFFF
//
//  Created by Zach Waterson on 4/21/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#ifndef __FFFF__MainMenuViewController__
#define __FFFF__MainMenuViewController__

#include <iostream>
#include "ViewController.h"
#include "ExampleViewController.h"


class MainMenuViewController : public ViewController {
    
public:
    MainMenuViewController(SDL_Renderer *rend);
    virtual int draw(SDL_Event e);
    virtual void pushViewController(ViewController *vc);
    virtual void becomeTop();
    
private:
    LTexture bgImage;
    
};

#endif /* defined(__FFFF__MainMenuViewController__) */
