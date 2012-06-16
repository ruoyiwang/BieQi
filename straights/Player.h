#include "Table.h"


class Player{
public:
	Player();
	~Player();
	virtual bool play();
protected:
	std::vector<Card> cHand;
};

class HumanPlayer:Player{
public:
	bool play();
private:
	
};

class CompPlayer:Player{
public:
	bool play();

};