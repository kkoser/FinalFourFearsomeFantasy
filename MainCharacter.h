#include <string.h>
#include <vector.h>

class MainCharacter {
private: 
	int health;
	int power;
	int pp;
	int ppRegen;

	int level;
	int exp;
	int expToNext;

	string name;
	vector<Move> moves;
	Move activeMoves[4];

	string spriteName;

public:
	MainCharacter(string fileName);

	void actOnCharacter(Character &ch, Move m);
};