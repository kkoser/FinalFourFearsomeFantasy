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
    
    backgroundImage = ImageView(0, 0, pathForFile("Images/mainMenuBackground.png"), renderer);
    
    Mix_Music *music;
    
    string pathName = pathForFile("Audio/DearlyBeloved.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
    Mix_PlayMusic(music, -1);
    
}

int MainMenuViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!
    
    
    backgroundImage.draw();
    
    if (e.key.keysym.sym == SDLK_RETURN) {
        //ExampleViewController *vc = new ExampleViewController(renderer);
        OpenWorldViewController *vc = new OpenWorldViewController(renderer);
        pushViewController(vc);
    }
    return 1;
}

void MainMenuViewController::pushViewController(ViewController *vc) {
    ViewController::pushViewController(vc);
    //stop the music!
    Mix_PauseMusic();
}

void MainMenuViewController::becomeTop() {
    ViewController::becomeTop();
    Mix_ResumeMusic();
}


