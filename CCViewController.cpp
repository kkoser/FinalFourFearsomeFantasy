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
    redXImage = ImageView(0,0, pathForFile("Images/redX.png"), renderer);
    
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

    //get user input
    if (e.key.keysym.sym == SDLK_1) {
        //katniss left behind
        characterToLeaveBehind = 1;

    }
    else if (e.key.keysym.sym == SDLK_2) {
        //albus left behind
        characterToLeaveBehind = 2;

    }
    else if (e.key.keysym.sym == SDLK_3) {
        //elsa left behind
        characterToLeaveBehind = 3;

    }
    else if (e.key.keysym.sym == SDLK_4) {
        //jack left behind
        characterToLeaveBehind = 4;

    }
    else if (e.key.keysym.sym == SDLK_RETURN && characterToLeaveBehind != 0) {
        OpenWorldViewController *vc = new OpenWorldViewController(renderer, characterToLeaveBehind);
        pushViewController(vc);

    }
    
    //draw red x
    if (characterToLeaveBehind == 1) {
        redXImage.moveAbs(90, 75);
        redXImage.draw();
    }
    else if (characterToLeaveBehind == 2) {
        redXImage.moveAbs(90, 380);
        redXImage.draw();
    }
    else if (characterToLeaveBehind == 3) {
        redXImage.moveAbs(920, 75);
        redXImage.draw();
    }
    else if (characterToLeaveBehind == 4) {
        redXImage.moveAbs(920, 380);
        redXImage.draw();
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
    
    Mix_PlayMusic(music, 0);
}