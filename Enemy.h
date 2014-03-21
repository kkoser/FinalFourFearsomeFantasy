#include <string>
#include <vector>

using namespace std;

class Enemy {
private: 
	int health;
	int power;
	int pp;
	int ppRegen;

	//Don't we want armor, accuracy, maxHealth, maxPP, maxPower, maxAccuracy, maxArmor
	//Do we want status effects?

	string name;
	//vector<Move> moves;
	Move activeMoves[4];

	string spriteName;

public:
	Enemy(string fileName);

	void actOnCharacter(Character &ch, Move m);
	//Do we only plan to act on one character at a time? No splash/group attacks/heals
};