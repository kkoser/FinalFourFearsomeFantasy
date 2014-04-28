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
    
    displayLabel = TextLabel(0,530, "test", defaultFont, 24);
    
    //init active character
    activeCharacter = *mainChars.begin();
    activeCharacterView = &*mainCharViews.begin();
    selectedPos = 0;
    selectedMove = "";
    
    drawActiveMoves();
    
    //music!
    Mix_Music *music;
    
    string pathName = pathForFile("Audio/FFXIIIBattle.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
    Mix_PlayMusic(music, -1);
    


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
    displayLabel.draw(renderer);

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
    if (selectedPos >= mainChars.size()) {
        //this is an enemy character, so we dont get their move, they choose
        vector<Character *> chars = vector<Character *>(mainChars.begin(), mainChars.end());
        ((Enemy *)activeCharacter)->actOnCharacters(chars);
        
        displayText = vector<string>();
        istringstream stream(activeCharacter->getDisplayLog());
        string line;
        while (getline(stream, line, '\n')) {
            displayText.push_back(line);
        }
        
        displayNextLine();
        
        //need to update all of the mainChar views
        for (int i = 0; i < mainChars.size(); i++) {
            mainCharViews[i].setCurrentHealth(mainChars[i]->getCurrentHealth());
            //BattleCharacterView view = mainCharViews[i];
        }
        nextCharacer();
        return;
    }
    if (e.type == SDL_KEYDOWN) {
        if (displayText.size() > 0) {
            displayNextLine();
        }
        else if (selectedMove.compare("") == 0) {
            //there is no selected move, so they are selecting one
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    selectedMove = activeCharacter->getMoves()[0];
                    activeMoves[0].setColor(255,0,0);
                    break;
                case SDLK_2:
                    selectedMove = activeCharacter->getMoves()[1];
                    activeMoves[1].setColor(255,0,0);
                    break;
                case SDLK_3:
                    selectedMove = activeCharacter->getMoves()[2];
                    activeMoves[2].setColor(255,0,0);
                    break;
                default:
                    break;
            }
            
        }
        else {
            //they have selected a move, now select a character to act it on
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    targets.push_back(enemies[0]);
                    //enemyViews[0].animate();
                    break;
                case SDLK_2:
                    targets.push_back(enemies[1]);
                    //enemyViews[1].animate();
                    break;
                case SDLK_3:
                    targets.push_back(enemies[2]);
                    //enemyViews[2].animate();
                    break;
                case SDLK_RETURN:
                    //this one actually does the move
                    if (targets.size() > 0) {
                        activeCharacter->actMoveOnTarget(selectedMove, targets);
                        activeCharacterView->setCurrentPP(activeCharacter->getCurrentPP());
                        for (int i = 0; i < enemies.size(); i++) {
                            enemyViews[i].setCurrentHealth(enemies[i]->getCurrentHealth());
                        }
                        //displayLabel.setText(activeCharacter->getDisplayLog());
                        displayText = vector<string>();
                        istringstream stream(activeCharacter->getDisplayLog());
                        string line;
                        while (getline(stream, line, '\n')) {
                            displayText.push_back(line);
                        }
                        
                        displayNextLine();
                        
                        
                        nextCharacer();
                    }
                    break;
                default:
                    break;
            }
//            target = enemies[selected];
//            vector<Character *> targets;
//            targets.push_back(target);
//            activeCharacter->actMoveOnTarget(selectedMove, targets);
//            activeCharacterView->setCurrentPP(activeCharacter->getCurrentPP());
            
            //update the CharacterViews here
            //BattleCharacterView charView = enemyViews[selected];
            //charView.setCurrentHealth(target->getCurrentHealth());
            //
            
            //nextCharacer();
            
        }
    }
}

void BattleViewController::nextCharacer() {
    //now clear up and switch to the next character
    selectedMove = "";
    selectedPos++;
    selectedPos = selectedPos > (mainChars.size() + enemies.size()-1) ? 0 : selectedPos;
    if (selectedPos >= mainChars.size()) {
        activeCharacter = enemies[selectedPos-mainChars.size()];
        activeCharacterView = &enemyViews[selectedPos -mainChars.size()];
    }
    else {
        activeCharacter = mainChars[selectedPos];
        activeCharacterView = &mainCharViews[selectedPos];
    }
    
    //clear out the selected move labels
    for (int i = 0; i < 4; i++) {
        activeMoves[i].setColor(0, 0, 0);
    }
    
    targets = vector<Character *>();
}

void BattleViewController::displayNextLine() {
    displayLabel.setText(displayText[0]);
    displayText.erase(displayText.begin());
}

