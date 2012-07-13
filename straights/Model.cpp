#include <vector>
#include <iostream>
#include <string>
#include "Model.h"
#include "Card.h"

using namespace std;

Model::Model(){

}

Model::~Model(){

}

void Model::gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed){

}

void Model::gamePlay(Card cardPlayed){
	Player* player = gamePlayerList_.at(iCurrentPlayer_);
	HumanPlayer* castTest = dynamic_cast<HumanPlayer*> (player);
	if (castTest){
		Command cmd;
		HumanPlayerGamePlay(cardPlayed, cmd);
	}
	else {
		Card dummyCard = Card(CLUB, ACE);
		// computerPlayer, pass in a dummy card
		player->play(cardTable_, referee_, dummyCard);
	} 

	iCurrentPlayer_ = (iCurrentPlayer_ + 1)%4;

	player = gamePlayerList_.at(iCurrentPlayer_);
	castTest = dynamic_cast<HumanPlayer*> (player);
	Card dummyCard = Card(CLUB, ACE);
	if (!castTest)
		gamePlay(dummyCard);

	//notify view to update;

	return;

}

void Model::HumanPlayerGamePlay(Card, Command cmd){
	Player* player = gamePlayerList_.at(iCurrentPlayer_);
	pirntTableStatus();
	vector<Card> legalPlay = printPlayerStatus();

	bool cmdFlag = false;
	while (!cmdFlag){ // loops until a 

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
	}

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