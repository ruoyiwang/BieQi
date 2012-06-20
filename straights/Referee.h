#ifndef _REFEREE_
#define _REFEREE_

#include "Card.h"
#include "Player.h"

const int CARD_COUNT = 52;

/**

**/
class Referee{
public:
	Referee():cardPlayed(0){}; // constructor, with cardPlayed inited as 0
	bool checkGameEnd(std::vector<Player*> const) const; // check if game ends
	bool checkRoundEnd(Table&, std::vector<Player*>const)const; // check if round ends
	int dealing(Table&, std::vector<Player*>);	// returns the player with 7 of spades
	std::vector<Card> getLegalPlays(Table& , std::vector<Card> ); // returns legal play for main&player
	void placeCard(Card, Table&); // help player place the card on the table
	void discardCard(Card, Player*); // help player discards the card
	Player* rageQuit(Player*&); // handles angray players
	void clearTable(Table&); // empty the cards on the table

	static bool checkValidPaly(Card , std::vector<Card> ); // check if the card is a valid play, referee won
private:
	void placeCardHelper(Card, std::vector<Card>&);
	int cardPlayed; // keeps track of card played
};
#endif