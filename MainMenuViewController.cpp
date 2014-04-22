//
//  MainMenuViewController.cpp
//  FFFF
//
//  Created by Zach Waterson on 4/21/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "MainMenuViewController.h"

MainMenuViewController::MainMenuViewController(SDL_Renderer *rend) : ViewController(rend) {
    //load textures etc
    
    bgImage.loadFromFile(pathForFile("Images/mainMenuBackground.jpg"), renderer);
    
}

int MainMenuViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!
    
    
    bgImage.render(renderer, 0, 0);
    
    if (e.key.keysym.sym == SDLK_RETURN) {
        ExampleViewController *vc = new ExampleViewController(renderer);
        pushViewController(vc);
    }
    return 1;
}
