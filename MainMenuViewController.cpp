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
    //load background images
    backgroundImage = ImageView(0, 0, pathForFile("Images/mainMenuBackground.png"), renderer);
    controlsImage = ImageView(0,0, pathForFile("Images/controlsBackgroundImage.png"), renderer);
    plotImage = ImageView(0,0, pathForFile("Images/plotBackgroundImage.png"), renderer);
    
    string pathName = pathForFile("Audio/DearlyBeloved.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
}

MainMenuViewController::~MainMenuViewController() {
    Mix_FreeMusic(music);
}

int MainMenuViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!
    
    //draw main menu first
    if (displayPlot) {
        plotImage.draw();
    }
    else if (displayControls) {
        controlsImage.draw();
    }
    else {
        backgroundImage.draw();
    }
    
    if (e.key.keysym.sym == SDLK_RETURN && e.type == SDL_KEYDOWN) {
        //first display controls
        if (displayControls == 0) {
            //display controls
            displayControls = 1;
        }
        //then display plot
        else if (displayPlot == 0) {
            //display plot
            displayPlot = 1;
        }
        //then move on
        else {
            //push on
            CCViewController *vc = new CCViewController(renderer);
            pushViewController(vc);
        }
    }
    return 1;
}

void MainMenuViewController::pushViewController(ViewController *vc) {
    Mix_HaltMusic();
    ViewController::pushViewController(vc);
    
}

void MainMenuViewController::becomeTop() {
    ViewController::becomeTop();
    //Mix_ResumeMusic();
    
    Mix_PlayMusic(music, -1);
}