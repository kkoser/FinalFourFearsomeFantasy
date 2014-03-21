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
	int standardArmor;

	int currentHealth; //current health in battle

	//these are augmented in battle and reset afterwords
	int currentPower;
	int currentPP;
	int currentPPRegen;
	int currentArmor;

	//these are not increased by level points
	int level;
	int exp;
	int expToNext;
	int accuracy;

	string name;
	vector<Move> moves;
	Move activeMoves[4];

	string spriteName;

public:
	MainCharacter(string fileName);

	void actOnCharacter(Character &ch, Move m);
};