//
//  Enemy.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/8/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(string file) : Character(file) {
    
}

//the basic implementation simply acts the first move on the first character
void Enemy::actOnCharacters(vector<Character *> enemies, vector<Character *> team) {
    Character *target = enemies[0];
    //string move = moves[0];
    vector<Character *> targets(1);
    string selMove = this->selectMove(enemies, team);
    targets[0] = target;
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
					int power=stoi(word,NULL,10);
					if(benefit && power>0){ //Restoring Health
						if((double)currentHealth/(double)maxHealth<.8) moveVals[i]+=1;
						if((double)currentHealth/(double)maxHealth<.6) moveVals[i]+=2;
						if((double)currentHealth/(double)maxHealth<.4) moveVals[i]+=3;
						if((double)currentHealth/(double)maxHealth<.2) moveVals[i]+=1;
						moveVals[i]+=2*((targetNum<team.size())?targetNum:team.size());
					}
					if(!benefit){
						if(power<-2) moveVals[i]+=2;
						if(power<-1.5) moveVals[i]+=2;
						if(power<-1.25) moveVals[i]+=1;
						if(power<-1) moveVals[i]+=1;
						if(power<-.75) moveVals[i]+=1;
						moveVals[i]++;
					}
				}
				else if (word=="PP"){
					getline(iss, word);
					//Do not select move if not enough PP is available for it
					if (0>currentPP-stoi(word,NULL,10)) moveVals[i]-=1000;
					double PPpercent=(double)currentPP/(double)maxPP;
					if (PPpercent<.5 && stoi(word,NULL,10)>0) moveVals[i]++;
					if (PPpercent<.3 && stoi(word,NULL,10)>0) moveVals[i]+=2;
					if (PPpercent<.1 && stoi(word,NULL,10)>0) moveVals[i]+=3;
					if (PPpercent>.5 && stoi(word,NULL,10)<0) moveVals[i]++;
					if (PPpercent>.7 && stoi(word,NULL,10)<0) moveVals[i]+=2;
					if (PPpercent>.9 && stoi(word,NULL,10)<0) moveVals[i]+=4;
				}
				else if (word=="Power"){
					getline(iss, word);
					int powVal=stoi(word,NULL,10);
					double healthPercent=(double)currentHealth/(double)maxHealth;
					if(powVal<1 && benefit) moveVals[i]--;
					if(powVal>1 && benefit) moveVals[i]++;
					if(powVal>1 && benefit && healthPercent>.5) moveVals[i]++;
					if(powVal>1 && benefit && healthPercent>.7) moveVals[i]+=2;
					if(powVal>1 && benefit && healthPercent>.9) moveVals[i]+=3;
					if(!benefit && powVal<1) moveVals[i]+=3;
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
	int moveSelection=rand()%total;
	currentMove=moves.begin();
	for (int i=0; i<moves.size(); i++){
		if (moveVals[i]>0){
			moveSelection-=moveVals[i];
		}
		if (total<=0) return *currentMove;
		currentMove++;
	}
	return "Rest"; //Hopefully it never gets here
}
