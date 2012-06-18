#ifndef _REFEREE_
#define _REFEREE_

#include "Card.h"
#include "Player.h"

class Referee{
public:
	Referee():cardPlayed(0){};
	bool checkGameEnd(std::vector<Player*>);
	bool checkRoundEnd(Table&, std::vector<Player*>);
	int dealing(Table&, std::vector<Player*>);	// returns the player with 7 of spades
	std::vector<Card> getLegalPlays(Table&, std::vector<Card>);
	void placeCard(Card, Table&);
	void discardCard(Card, Player*);
	Player* rangeQuit(Player*&);
private:
	void placeCardHelper(Card, std::vector<Card>&);
	int cardPlayed;
};
#endif