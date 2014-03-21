#include <string>
#include <vector>

using namespace std;

class Enemy {
private: 
	//these can be upgraded using level points
	int maxHealth;
	int standardPower;
	int maxPP; //mana for moves
	int standardPPRegen;
	int armor;
	int accuracy;
	string name;

	//these are augmented in battle and reset afterwords (except health)
	int currentHealth;
	int currentPower;
	int currentPP;
	int currentPPRegen;

	Move activeMoves[4];

	string spriteName;

public:
	Enemy(string fileName);

	void actOnCharacter(Character &ch, Move m);
	//Do we only plan to act on one character at a time? No splash/group attacks/heals
};