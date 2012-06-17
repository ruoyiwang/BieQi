#ifndef _REFEREE_
#define _REFEREE_

#include "Card.h"
#include "Player.h"

class Player; 

class Referee{
public:
	Referee();
	static bool checkPlay(Player& p, Card& c);
	static bool checkDiscard(Player& p, Card& c);
	static bool checkGameEnd();
private:

};
#endif