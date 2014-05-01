//
//  Enemy.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "Enemy.h"
#include <math.h>

Enemy::Enemy(string file) : Character(file) {
    
}

//the basic implementation simply acts the first move on the first character
void Enemy::actOnCharacters(vector<Character *> enemies, vector<Character *> team) {
    //string move = moves[0];
    vector<Character *> targets;
    string selMove = this->selectMove(enemies, team);
    targets = targetSelect(enemies, team, selMove);
    this->actMoveOnTarget(selMove, targets);
}

string Enemy::selectMove(vector<Character *> enemies, vector<Character *> team){
	int moveVals[moves.size()];
	
	typename vector<string>::iterator currentMove;
	currentMove=moves.begin();
	
	//Give weight to moves
	for (int i = 0; i < moves.size(); i++) {
        moveVals[i]=0; //Weight of choosing the move initially set to 0
		
		int benefit=1; //1 contributes positively, 0 negatively
		
		ifstream file;
		file.open(pathForFile("/Moves/" + *currentMove + ".move").c_str());
		
		if (!file) {
            cout<<"File "<<*currentMove<<" failed to open"<<endl;
            return "";
		}
		
        string line;
		//Begin adding weight to move based on move text and enemies
		while (getline(file, line)) {
			//Evaluate each word in line
			stringstream iss(line);
			string word;
			int targetNum=0;
			
			while (getline(iss,word,' ')){
				if (word=="Actor"){
					benefit=1;
				}
				else if (word=="Target"){
					benefit=0;
				}
				else if (word=="Targets"){
					getline(iss,word);
					if(word=="1") targetNum=1;
					if(word=="2") targetNum=2;
					if(targetNum==0) targetNum=3;
					if (enemies.size()>2 && targetNum==3) moveVals[i]+=5;
					if (enemies.size()==2 && targetNum==3) moveVals[i]+=3;
					if (enemies.size()==1 && targetNum==3) moveVals[i]-=2;
					if (enemies.size()>1 && targetNum==2) moveVals[i]+=3;
					if (enemies.size()==1 && targetNum==2) moveVals[i]-=1;
					if (enemies.size()>2 && targetNum==1) moveVals[i]+=1;
					if (enemies.size()==2 && targetNum==1) moveVals[i]+=2;
					if (enemies.size()==1 && targetNum==1) moveVals[i]+=6;
				}
				else if (word=="Health"){
					getline(iss, word);
					int power=getValueForCommand(word, 1, getCurrentPower());
					if(benefit && power>0){ //Restoring Health
						if((double)currentHealth/(double)maxHealth<.8) moveVals[i]+=1;
						if((double)currentHealth/(double)maxHealth<.6) moveVals[i]+=2;
						if((double)currentHealth/(double)maxHealth<.4) moveVals[i]+=3;
						if((double)currentHealth/(double)maxHealth<.2) moveVals[i]+=1;
						moveVals[i]+=2*((targetNum<team.size())?targetNum:team.size());
					}
					if(!benefit){
						if(power<getCurrentPower()) moveVals[i]+=2;
						moveVals[i]++;
					}
				}
				else if (word=="PP"){
					getline(iss, word);
					word.erase(0,1);
					//Do not select move if not enough PP is available for it
					if (0>currentPP-stod(word)) moveVals[i]-=1000;
					double PPpercent=(double)currentPP/(double)maxPP;
					if (PPpercent<.5 && stod(word)>0) moveVals[i]++;
					if (PPpercent<.3 && stod(word)>0) moveVals[i]+=2;
					if (PPpercent<.1 && stod(word)>0) moveVals[i]+=3;
					if (PPpercent>.5 && stod(word)<0) moveVals[i]++;
					if (PPpercent>.7 && stod(word)<0) moveVals[i]+=2;
					if (PPpercent>.9 && stod(word)<0) moveVals[i]+=4;
				}
				else if (word=="Power"){
					getline(iss, word);
					int val=getValueForCommand(word, 1, getCurrentPower());
					double healthPercent=(double)currentHealth/(double)maxHealth;
					if(val < getCurrentPower() && benefit) moveVals[i]--;
					if(val > getCurrentPower() && benefit) moveVals[i]++;
					if(val > getCurrentPower() && benefit && healthPercent>.5) moveVals[i]++;
					if(val > getCurrentPower() && benefit && healthPercent>.7) moveVals[i]+=2;
					if(val > getCurrentPower() && benefit && healthPercent>.9) moveVals[i]+=3;
					if(!benefit && val < getCurrentPower()) moveVals[i]+=3;
				}
				else if (word=="PPRegen"){
					getline(iss, word);
					double healthPercent=(double)currentHealth/(double)maxHealth;
					if(benefit && healthPercent>.5) moveVals[i]++;
					if(benefit && healthPercent>.7) moveVals[i]++;
					if(benefit && healthPercent>.9) moveVals[i]+=2;
				}
				else if (word=="Status"){
					getline(iss,word);
					istringstream issline(word);
					string word2;
					while (getline(issline, word2, ' ')){
                        if (word2=="HPT") moveVals[i]+=3;
                        if (word2=="Incap") moveVals[i]+=2;
                        if (word2=="Length") moveVals[i]+=3;
					}
				}
			}
		}
		currentMove++;
    }
	int total=0;
	for (int i=0; i<moves.size(); i++){
		if (moveVals[i]>0) total+=moveVals[i];
	}
    int moveSelection = 0;
    if (total > 0) {
        moveSelection=rand()%total;
    }
	
	currentMove=moves.begin();
	for (int i=0; i<moves.size(); i++){
		if (moveVals[i]>0){
			moveSelection-=moveVals[i];
		}
		if (moveSelection<=0) return *currentMove;
		currentMove++;
	}
	return "Rest"; //Hopefully it never gets here
}

vector<Character *> Enemy::targetSelect(vector<Character *> enemies, vector<Character *> team, string move){
	int targetVals[enemies.size()];
	vector<Character *> targets;
	vector<Character *> enemiesSorted;
	typename vector<Character *>::iterator currentTarget;
	currentTarget = enemies.begin();
	
	//Weight Targets on Strength
	for (int i = 0; i < enemies.size(); i++) {
		targetVals[i]=0;
		double enemPercentHP = (double)(*currentTarget)->getCurrentHealth()/(double)(*currentTarget)->getMaxHealth();
		double enemPercentPP = (double)(*currentTarget)->getCurrentPP()/(double)(*currentTarget)->getMaxPP();
		targetVals[i]+= (int)ceil(enemPercentHP*10);
		if (targetVals[i]>0) targetVals[i]+= (int)(enemPercentPP*4);
		currentTarget++;
	}
	
	ifstream file;
	file.open(pathForFile("/Moves/" + move + ".move").c_str());
	
	if (!file) {
		cout<<"File "<<move<<" failed to open"<<endl;
		return targets;
	}
	
	int targetCode = 0;
	string line;
	//Begin adding weight to move based on move text and enemies
	while (getline(file, line)) {
		//Evaluate each word in line
		stringstream iss(line);
		string word;
		while (getline(iss,word,' ')){
			if (word=="Targets"){
				getline(iss,word);
				if(word=="1") targetCode=1;
				else if (word=="2") targetCode=2;
				else if (word=="3") targetCode=3;
				else if (word=="ALL_ENEMIES") targetCode=4;
				else if (word=="ALL_FRIENDS") targetCode=5;
				else if (word=="SELF") targetCode=0;
			}
		}
	}
	
	//Sort Enemies
	for (int j=0; j<enemies.size(); j++){
		currentTarget = enemies.begin();
		int EnemyAdded=0;
		int total=0;
		for (int i=0; i<enemies.size(); i++){
			if (targetVals[i]>0) total+=targetVals[i];
		}
        if (total>0){
            int targetSelection=rand()%total;
            for (int i=0; i<enemies.size(); i++){
                if (targetVals[i]>0){
                    targetSelection-=targetVals[i];
                }
                if (targetSelection<=0 && EnemyAdded==0) {
                    enemiesSorted.push_back(*currentTarget);
                    targetVals[i]=0;
                    EnemyAdded=1;
                }
                currentTarget++;
            }
        }
		
	}
	
	switch(targetCode){
		case 0: //Self
			targets.push_back(this);
			break;
		case 4: //All enemies
			currentTarget = enemies.begin();
			for (int i=0; i<enemies.size(); i++){
				targets.push_back(*currentTarget);
				currentTarget++;
			}
			break;
		case 5: //All friends
			currentTarget = team.begin();
			for (int i=0; i<team.size(); i++){
				targets.push_back(*currentTarget);
				currentTarget++;
			}
			break;
		default: //some number of Targets
			currentTarget = enemiesSorted.begin();
			for (int i=0; i<enemiesSorted.size(); i++){
				if(i<targetCode){
					targets.push_back(*currentTarget);
					currentTarget++;
				}
			}
			break;
	}
	return targets;
}

