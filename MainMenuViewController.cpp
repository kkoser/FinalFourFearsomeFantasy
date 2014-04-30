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
    
    string pathName = pathForFile("Audio/DearlyBeloved.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
    Mix_PlayMusic(music, -1);
    
    switch(Mix_GetMusicType(NULL))
    {
        case MUS_NONE:
        MUS_CMD:
            printf("Command based music is playing.\n");
            break;
        MUS_WAV:
            printf("WAVE/RIFF music is playing.\n");
            break;
        MUS_MOD:
            printf("MOD music is playing.\n");
            break;
        MUS_MID:
            printf("MIDI music is playing.\n");
            break;
        MUS_OGG:
            printf("OGG music is playing.\n");
            break;
        MUS_MP3:
            printf("MP3 music is playing.\n");
            break;
        default:
            printf("Unknown music is playing.\n");
            break;
    }
}

MainMenuViewController::~MainMenuViewController() {
    Mix_FreeMusic(music);
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
        /*
        //test
        //temporary character stuff
        vector<MainCharacter *> chars;
        vector<Enemy *> enemies;
        MainCharacter Elsa(pathForFile("Characters/Elsa.character"));
        MainCharacter Elsa2(pathForFile("Characters/Elsa.character"));
        MainCharacter Elsa3(pathForFile("Characters/Elsa.character"));
        chars.push_back(&Elsa);
        chars.push_back(&Elsa2);
        chars.push_back(&Elsa3);
        Enemy goblin(pathForFile("Characters/Goblin.character"));
        Enemy goblin2(pathForFile("Characters/Troll.character"));
        enemies.push_back(&goblin);
        enemies.push_back(&goblin2);
        
        BattleViewController *vc = new BattleViewController(chars, enemies, pathForFile("Images/arendelle.jpg"), renderer);
        //end test
        */
        
        pushViewController(vc);
    }
    return 1;
}

void MainMenuViewController::pushViewController(ViewController *vc) {
    ViewController::pushViewController(vc);
    //stop the music!
    Mix_PauseMusic();
    //Mix_HaltMusic();
}

void MainMenuViewController::becomeTop() {
    ViewController::becomeTop();
    //Mix_ResumeMusic();
    Mix_PlayMusic(music, -1);
}


