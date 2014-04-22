//
//  ExampleViewController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "ExampleViewController.h"

ExampleViewController::ExampleViewController(SDL_Renderer *r) : ViewController(r) {
    //load textures here
    
    gFont = TTF_OpenFont( "AndaleMono.ttf", 16 );
    //text.loadFromFile( "elsaBattle.png", renderer);
    
}

int ExampleViewController::draw(SDL_Event e) {
    if(ViewController::draw(e) == 0) {
        return 0;
    }
    
    //now draw the text
    SDL_Color textColor;
    if (base == NULL) {
        textColor = { 0, 0, 0 };
    }
    else {
        textColor = {0,0,255};
    }
    
    text.loadFromRenderedText("Test", textColor, renderer, gFont);
    text.render(renderer, 10, 10);
    
    if (e.type == SDL_KEYDOWN) {
        //lets try pushing a new vc
        ExampleViewController *newVC = new ExampleViewController(renderer);
        pushViewController(newVC);
    }
    return 1;
}