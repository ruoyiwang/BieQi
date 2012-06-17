#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"
#include "Referee.h";

class Referee;

class Player{
public:
	friend class referee;
	Player();
	~Player();
	virtual void play(Table&, Referee&);	
	virtual void discard(Referee&);
	std::vector<Card> cHand();
protected:
	std::vector<Card> cHand_;
	int iScore_;
};

class HumanPlayer:public Player{
public:
	void HumanPlayer::play(Table&, Referee&);		//asks the user for input on which card to play
	void discard(Referee& rR);
};

class CompPlayer:public Player{
public:
	void CompPlayer::play(Table&, Referee&);
	void discard(Referee& rR);
};

#endif