#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Referee.h"
#include "Command.h"
#include "Card.h"
#include "Subject.h"

enum gameState {GAMESTART, INGAME, ROUNDEND, GAMEEND};

class Model : public Subject{
private:
	int iSeed_;
	int iCurrentPlayer_;
	std::vector<Player*> playerList_;
	std::vector<Player*> gamePlayerList_;
	Table cardTable_;
	Referee referee_;

	void pirntTableStatus();
	std::vector<Card> printPlayerStatus();

	bool HumanPlayerGamePlay(Card cardPlayed, Command cmd);
	
	void printDeck(Table& cardTable);
	void printCardList(std::vector<Card> suit);

	Player* invitePlayer(int i, bool bHuman);
	std::vector<Player*> sortPlayerList(int startingPlayerId);

	gameState enmCurrentState_;
	void setCurrentState(gameState);

	void GameClean();

	bool checkRoundAndGameEndOrPerformIncrement();
	bool performRoundEnd();
	bool performGameEnd();

public:
	Model();
	~Model();
	//game start and game play is for the controller to use
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed);
	void gamePlay(int iHandCardIndex);

	//the rest are the accessors for the view's update
	Table cardTable();
	std::vector<Player*> playerList();
	std::vector<Player*> gamePlayerList();
	int iCurrentPlayer();
	gameState enmCurrentState();
};

#endif