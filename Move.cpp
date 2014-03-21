//
//  Move.cpp
//  FFFF
//
//  Created by Zach Waterson on 3/21/14.
//  Copyright (c) 2014 Zach Waterson. All rights reserved.
//

#include "Move.h"

using namespace std;

//constructor
Move::Move(string filename) {
    ifstream file(filename.c_str());
    
    if (!file) {
        cout<<"File "<<filename<<" failed to open"<<endl;
    }
    else {
        //read in name and flavor text
        getline(file, name);
        getline(file, flavorText);
        
        //read in stats
        string temp;
        getline(file, temp);
        power = atoi(temp.c_str());

        getline(file, temp);
        isSingleTarget = atoi(temp.c_str());

        getline(file, temp);
        targetsEnemy = atoi(temp.c_str());

        getline(file, temp);
        if (temp == "NOSTATUS") {
            statusToApply = NOSTATUS;
        }
        else if (temp == "DPT") {
            statusToApply = DPT;
        }
        else if (temp == "SHIELD") {
            statusToApply = SHIELD;
        }
        else if (temp == "INCAP") {
            statusToApply = INCAP;
        }
        else cout << "Error reading status of move "<< filename <<endl;
        
        getline(file, temp);
        statusPower = atoi(temp.c_str());
        
        getline(file, temp);
        if (temp == "NOATTRIBUTE") {
            attributeToAugment = NOATTRIBUTE;
        }
        else if ( temp == "POWER") {
            attributeToAugment = POWER;
        }
        else if ( temp == "CURRENTPP") {
            attributeToAugment = CURRENTPP;
        }
        else if ( temp == "PPREGEN") {
            attributeToAugment = PPREGEN;
        }
        else if ( temp == "ARMOR") {
            attributeToAugment = ARMOR;
        }
        else cout << "Error reading attribute of move "<< filename <<endl;

        
        getline(file, temp);
        attributeMultiplier = atof(temp.c_str());
    }
	
}