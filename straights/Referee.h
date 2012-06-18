#ifndef _REFEREE_
#define _REFEREE_

#include "Card.h"
#include "Player.h"

class Referee{
public:
	Referee(){};
	static bool checkPlay(Player& p, Card& c);
	static bool checkDiscard(Player& p, Card& c);
	static bool checkGameEnd();
	static int dealing(Table&, std::vector<Player*>);	// returns the player with 7 of spades
	static std::vector<Card> getLegalPlays(Table&, std::vector<Card>);
private:
};
#endif