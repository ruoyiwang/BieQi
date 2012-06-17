#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"

class Player{
public:
	friend class referee;
	Player();
	~Player();
	virtual Card play(Table&);	
	virtual Card discard();
	std::vector<Card> cHand();
protected:
	std::vector<Card> cHand_;
	int iScore_;
};

class HumanPlayer:public Player{
public:
	Card HumanPlayer::play(Table&);		//asks the user for input on which card to play
	Card discard();
};

class CompPlayer:public Player{
public:
	Card CompPlayer::play(Table&);
	Card discard();
};

#endif