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
    
    displayLabel = TextLabel(0,530, "", defaultFont, 24);
    
    //init active character
    activeCharacter = *mainChars.begin();
    activeCharacterView = &*mainCharViews.begin();
    activeCharacterView->setIsAnimating(true);
    selectedPos = 0;
    selectedMove = "";
    arrowSelectedPos = 0;
    
    drawActiveMoves();
    
    //music!
    Mix_Music *music;
    
    string pathName = pathForFile("Audio/FFXIIIBattle.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
    Mix_PlayMusic(music, -1);
    


}

vector<BattleCharacterView> BattleViewController::plotViewsAroundCircle(int x, int y, int radius, vector<Character *> chars) {
    //calculate position of character along circle
    int deltaAngle = (2*M_PI)/chars.size(); //get fraction of circle per person
    
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
    //if an enemy is acting and not a player character
    if (selectedPos >= mainChars.size()) {
        //this is an enemy character, so we dont get their move, they choose
        vector<Character *> chars = vector<Character *>(mainChars.begin(), mainChars.end());
        ((Enemy *)activeCharacter)->actOnCharacters(chars);
        
        displayText = vector<string>();
        istringstream stream(activeCharacter->getDisplayLog());
        activeCharacter->clearDisplayLog();
        string line;
        while (getline(stream, line, '\n')) {
            displayText.push_back(line);
        }
        
        displayNextLine();
        
        //need to update all of the mainChar views
        updateCharacterViews();
        
        nextCharacter();
        return;
    }
    //otherwise get player input
    if (e.type == SDL_KEYDOWN) {
        //is there text on the screen?
        if (displayText.size() > 0) {
            displayNextLine();
            if (displayText.size() == 0) {
                nextCharacter();
                //displayLabel.setText("");
            }
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
                case SDLK_4:
                    selectedMove = activeCharacter->getMoves()[3];
                    activeMoves[3].setColor(255,0,0);
                    break;
                default:
                    break;
            }
            
            if (selectedMove.compare("") != 0) {
                //they selected a move this time, so update the display label
                int numTargets = activeCharacter->numTargetsForMove(selectedMove);
                stringstream stream;
                stream << selectedMove << " takes ";
                if (numTargets == 0) {
                    stream << "all";
                }
                else {
                    stream << numTargets;
                }
                stream << " targets"<<endl;
                displayLabel.setText(stream.str());
            }
            
        }
        else {
            //they have selected a move, now select a character to act it on
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    targets.push_back(enemies[0]);
                    enemyViews[0].setIsAnimating(true);
                    break;
                case SDLK_2:
                    targets.push_back(enemies[1]);
                    enemyViews[1].setIsAnimating(true);
                    break;
                case SDLK_3:
                    targets.push_back(enemies[2]);
                    enemyViews[2].setIsAnimating(true);
                    break;
                case SDLK_LEFT:
                    arrowSelectedPos-=1;
                    break;
                case SDLK_RIGHT:
                    arrowSelectedPos+=1;
                    break;
                case SDLK_SPACE:
                    //push back selected arrow if move allows it
                    break;
                case SDLK_RETURN:
                    //this one actually does the move
                    if (targets.size() > 0) {
                        activeCharacter->actMoveOnTarget(selectedMove, targets);
                        
                        updateCharacterViews();
                        
                        //displayLabel.setText(activeCharacter->getDisplayLog());
                        displayText = vector<string>();
                        istringstream stream(activeCharacter->getDisplayLog());
                        activeCharacter->clearDisplayLog();
                        string line;
                        while (getline(stream, line, '\n')) {
                            displayText.push_back(line);
                        }
                        
                        displayNextLine();
                        activeCharacterView->setIsAnimating(false);
                        
                        
                        //nextCharacter();
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
            
            //nextCharacter();
            
        }
    }
}

int updateCursorForSelectedCharacter() {
    
}

void BattleViewController::nextCharacter() {
    //now clear up and switch to the next character
    selectedMove = "";
    selectedPos++;
    
    activeCharacterView->setIsAnimating(false);
    
    selectedPos = selectedPos > (mainChars.size() + enemies.size()-1) ? 0 : selectedPos;
    if (selectedPos >= mainChars.size()) {
        activeCharacter = enemies[selectedPos-mainChars.size()];
        activeCharacterView = &enemyViews[selectedPos -mainChars.size()];
        
    }
    else {
        activeCharacter = mainChars[selectedPos];
        activeCharacterView = &mainCharViews[selectedPos];
    }
    
    activeCharacterView->setIsAnimating(true);
    
    //clear out the selected move labels
    for (int i = 0; i < 4; i++) {
        activeMoves[i].setColor(0, 0, 0);
    }
    
    activeCharacter->regenPP();
    activeCharacterView->setCurrentPP(activeCharacter->getCurrentPP());
    
    targets = vector<Character *>();
    
    if (activeCharacter->getCurrentHealth() <= 0 || activeCharacter->getIsIncap()) {
        //nextCharacter();
    }
}

void BattleViewController::displayNextLine() {
    displayLabel.setText(displayText[0]);
    displayText.erase(displayText.begin());
}

void BattleViewController::updateCharacterViews() {
    for (int i = 0; i < mainChars.size(); i++) {
        mainCharViews[i].setCurrentHealth(mainChars[i]->getCurrentHealth());
        mainCharViews[i].setCurrentPP(mainChars[i]->getCurrentPP());
        mainCharViews[i].setCurrentShield(mainChars[i]->getCurrentShield());
        mainCharViews[i].setIsAnimating(false);
    }
    for (int i = 0; i < enemyViews.size(); i++) {
        enemyViews[i].setCurrentHealth(enemies[i]->getCurrentHealth());
        enemyViews[i].setCurrentPP(enemies[i]->getCurrentPP());
        enemyViews[i].setCurrentShield(enemies[i]->getCurrentShield());
        enemyViews[i].setIsAnimating(false);
    }
}

