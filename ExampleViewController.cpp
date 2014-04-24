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
    
    label = TextLabel(10, 10, "Hello World!", "AndaleMono.ttf", 16);
    img = ImageView(200, 200, pathForFile("Images/elsaBattle.png"), renderer);
    
}

int ExampleViewController::draw(SDL_Event e) {
    if(ViewController::draw(e) == 0) {
        return 0;
    }
    
    img.moveRel(4,0);
    
    img.draw(renderer);
    label.draw(renderer);
    
    if (e.type == SDL_KEYDOWN) {
        dismiss();
    }
    return 1;
}