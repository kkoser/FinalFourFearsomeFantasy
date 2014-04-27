//
//  ExampleViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "ExampleViewController.h"

ExampleViewController::ExampleViewController(SDL_Renderer *r) : ViewController(r) {

    testBattle = BattleCharacterView("Elsa", 300, 300, 75, 100, 18, 20, 5, false, pathForFile("Images/elsaBattle.png"), renderer);
    
}

int ExampleViewController::draw(SDL_Event e) {
    if(ViewController::draw(e) == 0) {
        return 0;
    }
    
    testBattle.draw();
    
    if (e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == SDLK_RETURN){
            dismiss();
        }
    }
    return 1;
}