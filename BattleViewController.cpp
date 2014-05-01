//
//  BattleController.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "BattleViewController.h"

BattleViewController::BattleViewController(vector<MainCharacter *> chars, vector<Enemy *> enem, string locName, SDL_Renderer *ren) : ViewController(ren) {
    
    //music!
    string pathName = pathForFile("Audio/FFXIIIBattle.wav");
    music = Mix_LoadMUS(pathName.c_str());
    
    mainChars = chars;
    enemies = enem;
    
    //init vc
    victory = 0;
    defeat = 0;
    finalText = TextLabel(360, 320, "", defaultFont, 48, renderer);
    finalText.setColor(0,0,0);
    displayingFinalText = 0;
    
    //plot main characters around circle
    vector<Character *> tempVector(mainChars.begin(), mainChars.end());
    mainCharViews = plotViewsAroundCircle(775, 152, 175, tempVector);
    
    //repeat for enemies
    vector<Character *> tempVector2(enemies.begin(), enemies.end());
    enemyViews = plotViewsAroundCircle(200, 152, 175, tempVector2);
    
    //load background too
    
    backgroundImage = ImageView(0, 0, locName, renderer);

    
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

    displayLabel = TextLabel(0,530, "", defaultFont, 24, renderer);
    
    //init active character
    activeCharacter = *mainChars.begin();
    activeCharacterView = &*mainCharViews.begin();
    activeCharacterView->setIsAnimating(true);
    selectedPos = 0;
    selectedMove = "";
    arrowSelectedPos = 0;
    
    updateActiveMoves();
    drawActiveMoves();
    

    
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

BattleViewController::~BattleViewController() {
    while (enemies.size() > 0) {
        Enemy* enemy = enemies[0];
        enemies.erase(enemies.begin() + 0);
        delete enemy;
    }
    while (mainChars.size() > 0) {
        MainCharacter* character = mainChars[0];
        mainChars.erase(mainChars.begin() + 0);
        delete character;
    }
    
    Mix_FreeMusic(music);
}

vector<BattleCharacterView> BattleViewController::plotViewsAroundCircle(int x, int y, int radius, vector<Character *> chars) {
    //calculate position of character along circle
    float deltaAngle = (2.0*M_PI)/chars.size(); //get fraction of circle per person
    
    float angle = M_PI/4.0;
    
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
    //draw
    activeMoves[0].draw(renderer);
    activeMoves[1].draw(renderer);
    activeMoves[2].draw(renderer);
    activeMoves[3].draw(renderer);

}

void BattleViewController::updateActiveMoves() {
    //clear old moves
    activeMoves[0].setText("1: ");
    activeMoves[1].setText("2: ");
    activeMoves[2].setText("3: ");
    activeMoves[3].setText("4: ");
    
    vector<string> moves = activeCharacter->getMoves();
    
    //update labels
    for (int i = 0; i < moves.size(); i++) {
        int pp = activeCharacter->ppCostForMove(moves[i]);
        stringstream text;
        text << i+1 << ": " << moves[i] << ", PP: "<<pp;
        activeMoves[i].setText(text.str());
    }
}



int BattleViewController::draw(SDL_Event e) {
    
    if(ViewController::draw(e)==0) { //returns 0 if this view controller should not draw
        return 0;
    }
    //display ending screen
    if (victory || defeat) {
        finalText.draw();
        displayingFinalText = 1;
    }
    else {
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
        
    }
    //check for user input
    handleEvent(e);
    
    
    return 1;
}

void BattleViewController::handleEvent(SDL_Event e) {
    
    //check if should dismiss
    if (displayingFinalText) {
        if (e.type == SDL_KEYDOWN) {
            dismiss();
        }
    }
    
    //is there text on the screen?
    if (displayText.size() > 0) {
        if (e.type == SDL_KEYDOWN) {
            displayNextLine();
            if (displayText.size() == 0) {
                nextCharacter();
                //displayLabel.setText("");
            }
        }
        
        return;
    }
    //if an enemy is acting and not a player character
    if (selectedPos >= mainChars.size()) {
        //this is an enemy character, so we dont get their move, they choose
        vector<Character *> enems = vector<Character *>(enemies.begin(), enemies.end());
        vector<Character *> mains = vector<Character *>(mainChars.begin(), mainChars.end());
        ((Enemy *)activeCharacter)->actOnCharacters(mains, enems);
        
        displayText = vector<string>();
        istringstream stream(activeCharacter->getDisplayLog());
        activeCharacter->clearDisplayLog();
        string line;
        while (getline(stream, line, '\n')) {
            displayText.push_back(line);
        }
        displayText.push_back("");
        
        displayNextLine();
        
        //clear all of the move labels
        //for (int i = 0; i < 4; i++) {
        //    activeMoves[0].setText("");
        //}
        
        //need to update all of the mainChar views
        updateCharacterViews();
        
        //nextCharacter();
        //return;
    }
    //otherwise get player input
    if (e.type == SDL_KEYDOWN) {
        //is there text on the screen?
//        if (displayText.size() > 0) {
//            displayNextLine();
//            if (displayText.size() == 0) {
//                nextCharacter();
//                //displayLabel.setText("");
//            }
//        }
        if (!moveFinal) {
            //there is no selected move, so they are selecting one
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    for (int i = 0; i < 4; i++) {
                        activeMoves[i].setColor(0,0,0);
                    }
                    if(activeCharacter->canCastMove(activeCharacter->getMoves()[0])) {
                        selectedMove = activeCharacter->getMoves()[0];
                        activeMoves[0].setColor(255,0,0);
                    }
                    else displayLabel.setText("Not enough PP");
                    break;
                case SDLK_2:
                    for (int i = 0; i < 4; i++) {
                        activeMoves[i].setColor(0,0,0);
                    }
                    if(activeCharacter->canCastMove(activeCharacter->getMoves()[1])) {
                        selectedMove = activeCharacter->getMoves()[1];
                        activeMoves[1].setColor(255,0,0);
                    }
                    else displayLabel.setText("Not enough PP");
                    break;
                case SDLK_3:
                    for (int i = 0; i < 4; i++) {
                        activeMoves[i].setColor(0,0,0);
                    }
                    if(activeCharacter->canCastMove(activeCharacter->getMoves()[2])) {
                        selectedMove = activeCharacter->getMoves()[2];
                        activeMoves[2].setColor(255,0,0);
                    }
                    else displayLabel.setText("Not enough PP");
                    break;
                case SDLK_4:
                    for (int i = 0; i < 4; i++) {
                        activeMoves[i].setColor(0,0,0);
                    }
                    if(activeCharacter->canCastMove(activeCharacter->getMoves()[3])) {
                        selectedMove = activeCharacter->getMoves()[3];
                        activeMoves[3].setColor(255,0,0);
                    }
                    else displayLabel.setText("Not enough PP");
                    break;
                case SDLK_RETURN:
                    if (selectedMove.compare("") != 0) {
                        moveFinal = true;
                    }
                    break;
                case SDLK_ESCAPE:
                    dismiss();
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
                else if (numTargets == -1) {
                    stream << "all friendly";
                }
                else if (numTargets == -2) {
                    stream << "all enemy";
                }
                else if (numTargets == -3) {
                    stream << "the caster as";
                }
                else {
                    stream << numTargets;
                }
                stream << " target(s)."<<endl;
                displayLabel.setText(stream.str());
                //get cursor showing
                if (moveFinal) {
                    //they selected a final move, so show the selector
                    //if the move takes an ALL target, select it for them
                    int numTargets = activeCharacter->numTargetsForMove(selectedMove);
                    if (numTargets == 0) {
                        targets.insert(targets.end(),mainChars.begin(), mainChars.end());
                        targets.insert(targets.end(), enemies.begin(), enemies.end());
                        for (int i = 0; i < mainCharViews.size(); i++) {
                            mainCharViews[i].setIsTargeted(true);
                        }
                        for (int i = 0; i < enemyViews.size(); i++) {
                            enemyViews[i].setIsTargeted(true);
                        }
                    }
                    else if (numTargets == -1){
                        targets.insert(targets.end(),mainChars.begin(), mainChars.end());
                        for (int i = 0; i < mainCharViews.size(); i++) {
                            mainCharViews[i].setIsTargeted(true);
                        }
                    }
                    else if (numTargets == -2) {
                        targets.insert(targets.end(), enemies.begin(), enemies.end());
                        for (int i = 0; i < enemyViews.size(); i++) {
                            enemyViews[i].setIsTargeted(true);
                        }
                    }
                    else if (numTargets == -3) {
                        targets.push_back(activeCharacter);
                        activeCharacterView->setIsTargeted(true);
                    }
                    else {
                        getViewForIndex(arrowSelectedPos)->setHasCursor(true);
                    }
                }
                
                
            }
            
        }
        else {
            //they have selected a move, now select a character to act it on
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    getViewForIndex(arrowSelectedPos)->setHasCursor(false);
                    changeArrowSelectedPos(+1);
                    getViewForIndex(arrowSelectedPos)->setHasCursor(true);
                    break;
                case SDLK_RIGHT:
                    getViewForIndex(arrowSelectedPos)->setHasCursor(false);
                    changeArrowSelectedPos(-1);
                    getViewForIndex(arrowSelectedPos)->setHasCursor(true);
                    break;
                case SDLK_SPACE:
                    //push back selected arrow if move allows it
                    if (targets.size() < activeCharacter->numTargetsForMove(selectedMove)) {
                        if (arrowSelectedPos >= mainCharViews.size()) {
                            enemyViews[arrowSelectedPos - mainChars.size()].setIsTargeted(true);
                            
                            //if not already there
                            if (find(targets.begin(), targets.end(), enemies[arrowSelectedPos - mainChars.size()]) == targets.end()) {
                                targets.push_back(enemies[arrowSelectedPos - mainChars.size()]);
                            }
                        }
                        else {
                            mainCharViews[arrowSelectedPos].setIsTargeted(true);
                            if (find(targets.begin(), targets.end(), mainChars[arrowSelectedPos]) == targets.end()) {
                                targets.push_back(mainChars[arrowSelectedPos]);
                            }
                        }
                    }
                    else displayLabel.setText("Max targets reached. Press Return to cast");

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
                        
                        displayText.push_back("");
                        
                        
                        activeCharacterView->setIsAnimating(false);
                        moveFinal = false;
                        selectedMove = "";
                        
                        displayNextLine();
                        if (displayText.size() == 0) {
                            nextCharacter();
                        }
                        
                        
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

bool BattleViewController::arePlayersDead() {
    for (int i = 0; i < mainChars.size(); i++) {
        if (mainChars[i]->getCurrentHealth() > 0) {
            return 0;
        }
    }
    return 1;
}

bool BattleViewController::areEnemiesDead() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getCurrentHealth() > 0) {
            return 0;
        }
    }
    return 1;
}

BattleCharacterView* BattleViewController::getViewForIndex(int index) {
    BattleCharacterView* chosenView;
    if (index >= mainCharViews.size()) {
        chosenView = &enemyViews[index - mainCharViews.size()];
    }
    else {
        chosenView = &mainCharViews[index];
    }
    return chosenView;
}

void BattleViewController::changeArrowSelectedPos(int delta) {
    arrowSelectedPos += delta;
    //if greater
    if (arrowSelectedPos == (mainCharViews.size() + enemyViews.size())) {
        arrowSelectedPos = 0;
    }
    else if (arrowSelectedPos == -1) {
        arrowSelectedPos = ((int)mainCharViews.size() + (int)enemyViews.size()-1);
    }
    else {
        cout << "Cursor error; moved by more than one." <<endl;
    }
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
    
      activeCharacter->updateStatuses();
      activeCharacter->regenPP();
//    activeCharacterView->setCurrentPP(activeCharacter->getCurrentPP());
//    activeCharacterView->setIsIncap(activeCharacter->getIsIncap());

    targets = vector<Character *>();
    
    //clear targets and cursors
    for (int i = 0; i < mainCharViews.size(); i++) {
        mainCharViews[i].setIsTargeted(false);
        mainCharViews[i].setHasCursor(false);
    }
    for (int i = 0; i < enemyViews.size(); i++) {
        enemyViews[i].setIsTargeted(false);
        enemyViews[i].setHasCursor(false);
    }
    
    updateActiveMoves();
    updateCharacterViews();
    
    moveFinal = false;
    
    //check for victory
    if (arePlayersDead()) {
        defeat = 1;
        finalText.setText("You lose the game.");
        finalText.setColor(255, 0, 0);
    }
    else if (areEnemiesDead()) {
        victory = 1;
        finalText.setText("You win the battle!");
        finalText.setColor(0, 255, 0);
    }
    
    if (activeCharacter->getCurrentHealth() <= 0 || activeCharacter->getIsIncap()) {
        displayLabel.setText(activeCharacter->getName() + " is unable to battle this turn");
        nextCharacter();
        cout << "HE DEAD"<<endl;
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
        //mainCharViews[i].setIsAnimating(false);
        mainCharViews[i].setIsIncap(mainChars[i]->getIsIncap());
        mainCharViews[i].setHasStatus(mainChars[i]->getNumberOfStatuses());
    }
    for (int i = 0; i < enemies.size(); i++) {
        enemyViews[i].setCurrentHealth(enemies[i]->getCurrentHealth());
        enemyViews[i].setCurrentPP(enemies[i]->getCurrentPP());
        enemyViews[i].setCurrentShield(enemies[i]->getCurrentShield());
        //enemyViews[i].setIsAnimating(false);
        enemyViews[i].setIsIncap(enemies[i]->getIsIncap());
        enemyViews[i].setHasStatus(enemies[i]->getNumberOfStatuses());
    }
}

void BattleViewController::becomeTop() {
    ViewController::becomeTop();
    Mix_PlayMusic(music, -1);
}
void BattleViewController::dismiss() {
    Mix_HaltMusic();
    ViewController::dismiss();
}
