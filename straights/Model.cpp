#include <vector>
#include <iostream>
#include <string>
#include "Model.h"
#include "Card.h"

using namespace std;

Model::Model():enmCurrentState_(INGAME){

}

Model::~Model(){

}

void Model::gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed){
	GameClean();	//need to come before the seeding
	//srand48(seed);
	srand(seed);
	playerList_.push_back( invitePlayer(1, bHuman1));
	playerList_.push_back( invitePlayer(2, bHuman2));
	playerList_.push_back( invitePlayer(3, bHuman3));
	playerList_.push_back( invitePlayer(4, bHuman4));

	int startingPlayerId  = referee_.dealing(cardTable_, playerList_) + 1; //referee.dealing() returns the player with 7 of spades
	cout <<"A new round begins. It's player "<< startingPlayerId <<"'s turn to play."<<endl;
	gamePlayerList_ = sortPlayerList(startingPlayerId -1); // playerid - 1 = player's pos in vector
	iCurrentPlayer_ = startingPlayerId-1;

	setCurrentState(GAMESTART);
	notify();
	setCurrentState(INGAME);
	notify();
	return;
}

void Model::gamePlay(int iHandCardIndex){
	Player* player = gamePlayerList_.at(iCurrentPlayer_);
	HumanPlayer* castTest = dynamic_cast<HumanPlayer*> (player);
	Card cardPlayed = player->cHand().at(iHandCardIndex);

	if (castTest){
		Command cmd;
		cmd.card = cardPlayed;
		vector<Card> legalPlays = referee_.getLegalPlays(cardTable_, player->cHand());	//check what leagal play this player has
		if (legalPlays.size()!=0){
			cmd.type = PLAY;
		}
		else{
			cmd.type = DISCARD;
		}
		bool bValidPlay = HumanPlayerGamePlay(cardPlayed, cmd);	//if valid then just go on
		if (!bValidPlay){	//else return right away, this allows the the console print as well as letting user click again
			//call update here
			notify();
			return;
		}
	}
	else {
		Card dummyCard = Card(CLUB, ACE);
		// computerPlayer, pass in a dummy card
		player->play(cardTable_, referee_, dummyCard);
	} 



	//the round end algo
	bool bRoundEnd = referee_.checkRoundEnd(cardTable_, gamePlayerList_);
	if (bRoundEnd){
		setCurrentState(ROUNDEND);
		bool bGameEnd = referee_.checkGameEnd(gamePlayerList_);
		if (bGameEnd){
			cardTable_ = Table();
			setCurrentState(GAMEEND);
			//reset a bunch of stuff here
			referee_.clearTable(cardTable_);
			int startingPlayerId  = referee_.dealing(cardTable_, playerList_) + 1; //referee.dealing() returns the player with 7 of spades
			gamePlayerList_ = sortPlayerList(startingPlayerId -1); // playerid - 1 = player's pos in vector
			cout <<"A new round begins. It's player "<< startingPlayerId <<"'s turn to play."<<endl;
			referee_.clearTable(cardTable_);
			//reset the player class and shits
			//call update and return
			//CALL THE FUCKING UPDATE FUNCTION
			notify();
			return;
		}
		
		//reset a  bunch of shits here.
		referee_.clearTable(cardTable_);
		int startingPlayerId  = referee_.dealing(cardTable_, playerList_) + 1; //referee.dealing() returns the player with 7 of spades
		gamePlayerList_ = sortPlayerList(startingPlayerId -1); // playerid - 1 = player's pos in vector
		cout <<"A new round begins. It's player "<< startingPlayerId <<"'s turn to play."<<endl;
		iCurrentPlayer_ = 0;
		castTest = dynamic_cast<HumanPlayer*> (gamePlayerList_.at(0));

		if (castTest){	//if it's human, let the human do the thingys
			//CALL THE FUCKING UPDATE FUNCTION
			notify();
			return;
		}
		return gamePlay(1);;	//else it's a comp just pass in a random card
	}


	iCurrentPlayer_ = (iCurrentPlayer_ + 1)%4;

	player = gamePlayerList_.at(iCurrentPlayer_);
	castTest = dynamic_cast<HumanPlayer*> (player);
	if (!castTest)
		return gamePlay(1);

	//notify view to update;

	notify();
	return;
}

bool Model::HumanPlayerGamePlay(Card, Command cmd){
	Player* player = gamePlayerList_.at(iCurrentPlayer_);
	pirntTableStatus();
	vector<Card> legalPlay = printPlayerStatus();

	bool cmdFlag = false;

	switch (cmd.type)
	{
		case PLAY:
			if (referee_.checkValidPaly(cmd.card, legalPlay)){
				cmdFlag = player->play(cardTable_, referee_, cmd.card);
			}
			break;
		case DISCARD:
			if (legalPlay.size() != 0){
				cout << "You have a legal play. You may not discard."<<endl;
				break;
			}
			cmdFlag = player->discard(referee_, cmd.card);
			break;
		case DECK:
			printDeck(cardTable_);
			break;
		case QUIT:
			exit(1);
			break;
		case RAGEQUIT:
			player = referee_.rageQuit(player); // referee handles the angery player
			player->play(cardTable_, referee_, cmd.card); // excute computer play
			//gamePlayerList[playerPos] = player;
			//playerList[player->iPlayerId()-1] = player;
			cmdFlag = true; // exit cmd
			break;
		default:
			break;
	}
	return cmdFlag;
}


void Model::printDeck(Table& cardTable){
	vector<Card> deck = cardTable.getDeck();
	for (unsigned int i = 0 ; i < deck.size(); i++){
		cout << deck[i] << " ";
		if ( (i+1) % 13 == 0)
			cout << endl;
	}
}


vector<Card> Model::printPlayerStatus(){
	Player* player = gamePlayerList_.at(iCurrentPlayer_);
	vector<Card> hand = player->cHand();
	cout << "Your hand:";
	for (unsigned int i =0 ; i < hand.size();i++)
		cout << " " << hand[i];
	cout << endl;

	cout << "Legal Plays:";
	vector<Card> legalPlays = referee_.getLegalPlays(cardTable_, player->cHand()); // get legal plays from referee
	for (unsigned int i = 0 ; i < legalPlays.size();i++)
		cout << " " << legalPlays[i];
	cout << endl;

	return legalPlays; // returns legal plays
}

void Model::pirntTableStatus(){
	cout <<"Cards on the table:"<<endl;
	cout << "Clubs:";
	printCardList(cardTable_.cClubs()); 
	cout <<endl;

	cout << "Diamonds:";
	printCardList(cardTable_.cDiamonds());
	cout <<endl;
	cout << "Hearts:";
	printCardList(cardTable_.cHearts()) ;
	cout<<endl;

	cout << "Spades:";
	printCardList(cardTable_.cSpades());
	cout<<endl;
}

void Model::printCardList(vector<Card> suit){
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
	"7", "8", "9", "10", "J", "Q", "K"};
	
	for (unsigned int i = 0 ; i < suit.size();i++)
		cout <<  " "  << ranks[suit[i].getRank()]; 
}

Player* Model::invitePlayer(int i, bool bHuman){
	if (!bHuman)
		return new CompPlayer(i);
	else if (bHuman)
		return new HumanPlayer(i);
}

vector<Player*> Model::sortPlayerList(int startingPlayerId){
	vector<Player*> newPlayerList;

	for (int i = startingPlayerId; i < 4; i++)
		newPlayerList.push_back(playerList_[i]);
	for (int i = 0 ; i < startingPlayerId; i++)
		newPlayerList.push_back(playerList_[i]);

	return newPlayerList;
}

Table Model::cardTable(){
	return cardTable_;
}

vector<Player*> Model::playerList(){
	return playerList_;
}
vector<Player*> Model::gamePlayerList(){
	return gamePlayerList_;
}

int Model::iCurrentPlayer(){
	return iCurrentPlayer_;
}

gameState Model::enmCurrentState(){
	return enmCurrentState_;
}

void Model::setCurrentState(gameState state){
	enmCurrentState_ = state;
	return;
}

void Model::GameClean(){
	iSeed_ = 0;
	for (int i = 0; i < playerList_.size(); i++){
		delete playerList_.at(i);
	}
	playerList_.clear();
	gamePlayerList_.clear();
	cardTable_ = Table();
}