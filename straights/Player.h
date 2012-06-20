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
	int iPlayerId() const ; // accessor
	std::vector<Card> cHand() const; // accessor for main, used to print hand
protected:
	std::vector<Card>* getcHand();	// special accessor for CompPlayer, because compPlayer need to modify hand
	bool checkInHand(Card&);
	void removeFromHand(Card&);
private:
	std::vector<Card> cHand_; // hand 
	std::vector<Card> cDiscarded_; // vector of discards
	int iPlayerId_;
	int iScore_;

};

class HumanPlayer:public Player{
public:
	HumanPlayer(int);  // constructor
	bool play(Table&, Referee&, Card&);
	bool discard(Referee&, Card&);
};

class CompPlayer:public Player{
public:
	CompPlayer(int); // constructor
	bool play(Table&, Referee&, Card&);
	bool discard(Referee& , Card&);
};

#endif