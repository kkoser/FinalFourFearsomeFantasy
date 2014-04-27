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
    
    //plot main characters around circle
    vector<Character *> tempVector(mainChars.begin(), mainChars.end());
    mainCharViews = plotViewsAroundCircle(775, 140, 165, tempVector);
    
    //repeat for enemies
    vector<Character *> tempVector2(enemies.begin(), enemies.end());
    enemyViews = plotViewsAroundCircle(200, 140, 165, tempVector2);
    
    //load background too
    
    backgroundImage = ImageView(0, 0, pathForFile("Images/arendelle.jpg"), renderer);

    
    //init move labels
    //move labels
    activeMoves[0] = TextLabel(565, 530, "1: ", defaultFont, 24);
    activeMoves[1] = TextLabel(565, 580, "2: ", defaultFont, 24);
    activeMoves[2] = TextLabel(875, 530, "3: ", defaultFont, 24);
    activeMoves[3] = TextLabel(875, 580, "4: ", defaultFont, 24);
    activeMoves[0].setColor(0, 0, 0);
    activeMoves[1].setColor(0, 0, 0);
    activeMoves[2].setColor(0, 0, 0);
    activeMoves[3].setColor(0, 0, 0);
    
    //init active character
    activeCharacter = *mainChars.begin();
    activeCharacterView = &*mainCharViews.begin();
    
    drawActiveMoves();
    
    //music!
    Mix_Music *music;
    
    string pathName = pathForFile("Audio/FFXIIIBattle.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
    Mix_PlayMusic(music, -1);
    
    selectedMove = "";

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

void BattleViewController::drawActiveMoves() {
    
    //clear old moves
    activeMoves[0].setText("1: ");
    activeMoves[1].setText("2: ");
    activeMoves[2].setText("3: ");
    activeMoves[3].setText("4: ");

    vector<string> moves = activeCharacter->getMoves();
    
    //update labels
    for (int i = 0; i < moves.size(); i++) {
        stringstream text;
        text << i+1 << ": " << moves[i];
        activeMoves[i].setText(text.str());
    }
    //draw
    activeMoves[0].draw(renderer);
    activeMoves[1].draw(renderer);
    activeMoves[2].draw(renderer);
    activeMoves[3].draw(renderer);

}


int BattleViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //draw!

    //draw the background
    backgroundImage.draw();

    //animate active character
    activeCharacterView->animate();
    
    //draw the mainCharacters
    typename vector<BattleCharacterView>::iterator iter;
    for (iter = mainCharViews.begin(); iter != mainCharViews.end(); ++iter) {
        iter->draw();
    }
    
    //draw the enemies
    typename vector<BattleCharacterView>::iterator iter2;
    for (iter2 = enemyViews.begin(); iter2 != enemyViews.end(); ++iter2) {
        iter2->draw();
    }
    
    
    //draw the moves of the active character
    drawActiveMoves();
    
    //check for user input
    handleEvent(e);
    
    
    return 1;
}

void BattleViewController::handleEvent(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        if (selectedMove.compare("") == 0) {
            //there is no selected move, so they are selecting one
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    selectedMove = activeCharacter->getMoves()[0];
                    break;
                case SDLK_2:
                    selectedMove = activeCharacter->getMoves()[1];
                    break;
                case SDLK_3:
                    selectedMove = activeCharacter->getMoves()[2];
                    break;
                default:
                    break;
            }
        }
        else {
            //they have selected a move, now select a character to act it on
            Character *target;
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    target = enemies[0];
                    break;
                case SDLK_2:
                    target = enemies[1];
                    break;
                case SDLK_3:
                    target = enemies[2];
                    break;
                default:
                    break;
            }
            vector<Character *> targets;
            targets.push_back(target);
            activeCharacter->actMoveOnTarget(selectedMove, targets);
            
            //now clear up and switch to the next character
            selectedMove = "";
        }
    }
}

