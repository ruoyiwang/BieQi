#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"
//#include "Referee.h";

class Referee;

class Player{
public:
	friend class referee;
	Player(int iPlayerId);
	~Player();
	virtual bool play(Table&, Referee&, Card&);	
	virtual bool discard(Referee&, Card&);
	std::vector<Card> cHand();
protected:
	std::vector<Card> cHand_;
	int iScore_;
	int iPlayerId_;
	bool checkInHand(Card&);
	void removeFromHand(Card&);
};

class HumanPlayer:public Player{
public:
	bool HumanPlayer::play(Table&, Referee&, Card&);		//asks the user for input on which card to play
	bool discard(Referee& rR, Card&);
};

class CompPlayer:public Player{
public:
	bool CompPlayer::play(Table&, Referee&, Card&);
	bool discard(Referee& rR, Card&);
};

#endif