//
//  Enemy.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(string file) : Character() {
    
}

//the basic implementation simply acts the first move on the first character
void Enemy::actOnCharacters(vector<Character *> chars) {
    Character *target = chars[0];
    string move = moves[0];
    vector<Character *> targets(1);
    targets[0] = target;
    this->actMoveOnTarget(move, targets);
}