//
//  Enemy.h
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#ifndef __FinalFourFearsomeFantasy__Enemy__
#define __FinalFourFearsomeFantasy__Enemy__

#include <iostream>
#include "Character.h"

class Enemy : public Character {
public:
    //constructor invokes basic Character constructor
    Enemy(string file);
    int XPOnKill; //xp it gives when it dies
    
    //AI decision function. Recieves all of the valid Character targets, and chooses what move to act on what target(s)
    //Subclasses override this for specific AI behavior
    void actOnCharacters(vector<Character *> chars);
private:
    
};

#endif /* defined(__FinalFourFearsomeFantasy__Enemy__) */
