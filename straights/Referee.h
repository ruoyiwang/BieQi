#include "Card.h";
#include "Player.h";

class Referee{
public:
	static bool checkPlay(Player&, Card&);
	static bool checkDiscard(Player&, Card&);
	static bool checkGameEnd();
private:

};
