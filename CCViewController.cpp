//
//  CCViewController.cpp
//  FFFF
//
//  Created by Zach Waterson on 4/29/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "CCViewController.h"


CCViewController::CCViewController(SDL_Renderer *rend) : ViewController(rend) {
    //load textures etc
    
    backgroundImage = ImageView(0, 0, pathForFile("Images/CCBackgroundImage.png"), renderer);
    
    string pathName = pathForFile("Audio/DesideratusBellum.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
}

CCViewController::~CCViewController() {
    Mix_FreeMusic(music);
}

int CCViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!
    
    
    backgroundImage.draw();
    
    if (e.key.keysym.sym == SDLK_1) {
        //katniss left behind
        OpenWorldViewController *vc = new OpenWorldViewController(renderer, 1);
        pushViewController(vc);
    }
    else if (e.key.keysym.sym == SDLK_2) {
        //albus left behind
        OpenWorldViewController *vc = new OpenWorldViewController(renderer, 2);
        pushViewController(vc);
    }
    else if (e.key.keysym.sym == SDLK_3) {
        //elsa left behind
        OpenWorldViewController *vc = new OpenWorldViewController(renderer, 3);
        pushViewController(vc);
    }
    else if (e.key.keysym.sym == SDLK_4) {
        //jack left behind
        OpenWorldViewController *vc = new OpenWorldViewController(renderer, 4);
        pushViewController(vc);
    }
    return 1;
}

void CCViewController::pushViewController(ViewController *vc) {
    Mix_HaltMusic();
    ViewController::pushViewController(vc);
    //stop the music!
    //Mix_PauseMusic();
    
}

void CCViewController::becomeTop() {
    ViewController::becomeTop();
    //Mix_ResumeMusic();
    
    Mix_PlayMusic(music, -1);
}