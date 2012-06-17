#ifndef _REFEREE_
#define _REFEREE_

#include "Card.h"
#include "Player.h"

class Referee{
public:
	Referee();
	static bool checkPlay(Player&, Card&);
	static bool checkDiscard(Player&, Card&);
	static bool checkGameEnd();
private:

};
#endif