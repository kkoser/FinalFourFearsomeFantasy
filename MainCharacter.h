#include <string>
#include <vector>

using namespace std;

class MainCharacter {
private: 
	//these can be upgraded using level points
	int maxHealth;
	int standardPower;
	int maxPP; //mana for moves
	int standardPPRegen;

	//these are augmented in battle and reset afterwords (except health)
	int currentHealth;
	int currentPower;
	int currentPP;
	int currentPPRegen;

	//these are not increased by level points
	int level;
	int exp;
	int expToNext;
	int armor;
	int accuracy;

	string name;
	vector<Move> moves;
	Move activeMoves[4];

	string spriteName;

public:
	MainCharacter(string fileName);

	void actOnCharacter(Character &ch, Move m);
};