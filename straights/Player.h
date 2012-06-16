#include "Table.h"

class Player{
public:
	friend class referee;
	Player();
	~Player();
	virtual void play();	
	virtual void discard();
	std::vector<Card> cHand();
protected:
	std::vector<Card> cHand_;
	int iScore_;
};

class HumanPlayer:Player{
public:
	void play();		//asks the user for input on which card to play
	void discard();
};

class CompPlayer:Player{
public:
	void play();
	void discard();
};