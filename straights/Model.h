#ifndef __MODEL__
#define __MODEL__

#include <vector>
#include <cstdlib>
#include "Player.h"
#include "Referee.h"
#include "Command.h"
#include "Card.h"
#include "Subject.h"

enum gameState {GAMESTART, INGAME, ROUNDEND, GAMEEND, FORCEDGAMEEND};

class Model : public Subject{
private:
	int iSeed_;								//var to keep the seed
	int iCurrentPlayer_;					//var to keep track of what the current player is
	std::vector<Player*> playerList_;		//vector to keep track of all the players
	std::vector<Player*> gamePlayerList_;	//re-order of the above vector in order of who's going first
	Table cardTable_;						//var to store the table class
	Referee referee_;						//var to store the referee
	
	void pirntTableStatus();				//private member function used to print table status to cout
	std::vector<Card> printPlayerStatus();	//private member function used to print player status to cout

	bool HumanPlayerGamePlay(Card cardPlayed, Command cmd);
											//helper function to let the humans play the cards
	void printDeck(Table& cardTable);		//helper functions
	void printCardList(std::vector<Card> suit);	

	Player* invitePlayer(int i, bool bHuman);	//function used to add player to the game
	std::vector<Player*> sortPlayerList(int startingPlayerId);
											//function used to re-order th eplayers

	gameState enmCurrentState_;				//enumerator to keep track of the current state of the game
	void setCurrentState(gameState);		//function used to set the current state

	void GameClean();						//the game reset, which reset everything to default

	bool checkRoundAndGameEndOrPerformIncrement();
											//check if the round ended and either go on or stop the round/game
	bool performRoundEnd();					//performs the tasks needed to close a round
	bool performGameEnd();					//performs the tasks needed to close a game
	std::string sRoundEndDialog_;			//the string which would be prompt after a round is finished
	void sRoundEndDialogConstructor();		//the function used to make the above string

public:
	Model();
	~Model();
	//game start and game play is for the controller to use
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed);
	void gamePlay(int iHandCardIndex);		//function used to play a card

	//the rest are the accessors for the view's update
	Table cardTable();
	std::vector<Player*> playerList();		//function which used to return play list and the one in diff order
	std::vector<Player*> gamePlayerList();	
	int iCurrentPlayer();					//returns the current play's index
	gameState enmCurrentState();			//returns the state as the enumerator
	void rageQuit();						//rage quit
	void endGame();							//ends the game called by the button
	std::string sRoundEndDialog();			//returns the msg that spse to be displayed after each round
};

#endif