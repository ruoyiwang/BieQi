#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Referee.h"

class Model{
private:
	int iSeed_;
	int iCurrentPlayer_;
	std::vector<Player*> playerList_;
	std::vector<Player*> gamePlayerList_;
	Table cardTable_;
	Referee referee_;
public:
	Model();
	~Model();
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed);
	void gamePlay(int iCurPlayer);
};