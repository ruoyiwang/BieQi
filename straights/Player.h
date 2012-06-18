#ifndef _PLAYER_
#define _PLAYER_

#include "Table.h"
//#include "Referee.h";

class Referee;

class Player{
friend class Referee;
public:
	Player(int);
	~Player();
	virtual bool play(Table&, Referee&, Card&) = 0;	
	virtual bool discard(Referee&, Card&) = 0;
	int iPlayerId();
	std::vector<Card> cHand();
protected:
	std::vector<Card> cHand_;
	std::vector<Card> cDiscarded_;
	int iScore_;
	int iPlayerId_;
	bool checkInHand(Card&);
	void removeFromHand(Card&);
};

class HumanPlayer:public Player{
public:
	HumanPlayer(int);
	bool play(Table&, Referee&, Card&);		//asks the user for input on which card to play
	bool discard(Referee&, Card&);
};

class CompPlayer:public Player{
public:
	CompPlayer(int);
	CompPlayer(HumanPlayer*);
	bool play(Table&, Referee&, Card&);
	bool discard(Referee& , Card&);
};

#endif