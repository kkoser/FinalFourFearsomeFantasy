//
//  ExampleViewController.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/21/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__ExampleViewController__
#define __FinalFourFearsomeFantasy__ExampleViewController__

#include "ViewController.h"
#include "TextLabel.h"
#include "ImageView.h"
#include "StatBar.h"
#include "BattleCharacterView.h"

#include <iostream>
class ExampleViewController : public ViewController {
private:
    BattleCharacterView testBattle;
public:
    ExampleViewController(SDL_Renderer *ren);
    
    virtual int draw(SDL_Event e);
};
#endif /* defined(__FinalFourFearsomeFantasy__ExampleViewController__) */
