//
//  BattleController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "BattleViewController.h"

BattleViewController::BattleViewController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren) : ViewController(ren) {
    mainChars = chars;
    enemies = enem;
    
    //plot characters around circle
    vector<Character *> tempVector(mainChars.begin(), mainChars.end());
    mainCharViews = plotViewsAroundCircle(750, 140, 165, tempVector);
    
    //repeat for enemies
    
    //load background too
    
    backgroundImage = ImageView(0, 0, pathForFile("Images/arendelle.jpg"), renderer);
    //move labels
    move1 = TextLabel(550, 575, "Icy Wind", defaultFont, 24);
    move2 = TextLabel(550, 625, "Healing Salve", defaultFont, 24);
    move3 = TextLabel(850, 575, "Explosion", defaultFont, 24);
    move4 = TextLabel(850, 625, "Ronnicus Explodicus", defaultFont, 24);
    move1.setColor(255, 255, 255);
    move2.setColor(255, 255, 255);
    move3.setColor(255, 255, 255);
    move4.setColor(255, 255, 255);

}

vector<BattleCharacterView> BattleViewController::plotViewsAroundCircle(int x, int y, int radius, vector<Character *> chars) {
    //calculate position of character along circle
    int deltaAngle = (2*M_PI)/mainChars.size(); //get fraction of circle per person
    
    //center of character "circle"
    int angle = 0;
    
    //make vector
    vector<BattleCharacterView> views;
    
    vector<Character *>::iterator currentChar;
    for (currentChar = chars.begin(); currentChar != chars.end(); ++currentChar) {
        
        //make view
        BattleCharacterView charView((*currentChar)->getName(), x+radius*cos(angle),y + radius*sin(angle), (*currentChar)->getCurrentHealth(), (*currentChar)->getMaxHealth(), (*currentChar)->getCurrentPP(), (*currentChar)->getMaxPP(), (*currentChar)->getCurrentShield(), (*currentChar)->getIsIncap(), (*currentChar)->getSpriteFile(), renderer);
        
        //add to vector
        views.push_back(charView);
        angle = angle + deltaAngle; //update position on circle
    }
    return views;
}

int BattleViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!

    backgroundImage.draw();

    
    //draw the mainCharacters
    typename vector<BattleCharacterView>::iterator iter;
    for (iter = mainCharViews.begin(); iter != mainCharViews.end(); ++iter) {
        iter->draw();
    }
    
    //draw the enemies
    
    //draw the background
    
    
    //draw the moves of the active character
    move1.draw(renderer);
    move2.draw(renderer);
    move3.draw(renderer);
    move4.draw(renderer);
    
    
    
    return 1;
}