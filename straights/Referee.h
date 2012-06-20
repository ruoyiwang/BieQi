#ifndef _REFEREE_
#define _REFEREE_

#include "Card.h"
#include "Player.h"

const int CARD_COUNT = 52;

/**
Referee is created due to the fact that players may cheat and therefore unfair for the player to check if
	the card being played if valid or not, from an OOD point of view
There fore the Referee class is made to validate and count the players scores as well as deciding if the game
	and round would end. Moreover, the referee class is also there to shuffle as the card dealer in real life
	would do and the referee class would deal the cards to the players.
Which, by doing this (adding the referee class, there will be no exceptions(threat) which the players can 
	create to the game.
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