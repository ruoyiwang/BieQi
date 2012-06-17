#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"
#include "Referee.h";

class Player{
public:
	friend class referee;
	Player();
	~Player();
	virtual void play(Table tTable, Referee rR);	
	virtual void discard(Referee rR);
	std::vector<Card> cHand();
protected:
	std::vector<Card> cHand_;
	int iScore_;
};

class HumanPlayer:public Player{
public:
	void HumanPlayer::play(Table tTable, Referee rR);		//asks the user for input on which card to play
	void discard(Referee rR);
};

class CompPlayer:public Player{
public:
	void CompPlayer::play(Table tTable, Referee rR);
	void discard(Referee rR);
};

#endif