#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Referee.h"

class Model{
private:
	int iSeed;
	int iCurrentPlayer;
	std::vector<Player*> playerList;
	std::vector<Player*> gamePlayerList;
	Table cardTable;
	Referee referee;
public:
	Model();
	~Model();
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4);

};