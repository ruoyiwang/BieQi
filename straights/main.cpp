#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "Command.h"
#include "Table.h"
#include "Referee.h"
#include "Player.h"

using namespace std;

Player* invitePlayer(int i){
	string command;

	while (1){
		cout << "Is player "<<  i <<"  a human(h) or a computer(c)?" << endl;
		cin >> command;

		if (command[0] == 'c')
			return new CompPlayer(i);
		else if (command[0] == 'h')
			return new HumanPlayer(i);
	}
}

vector<Player*> sortPlayerList(vector<Player*> playerList, int startingPlayerId){
	vector<Player*> newPlayerList;

	for (int i = startingPlayerId; i < 4; i++)
		newPlayerList.push_back(playerList[i]);
	for (int i = 0 ; i < startingPlayerId; i++)
		newPlayerList.push_back(playerList[i]);

	return newPlayerList;
}

void printCardList(vector<Card> suit){
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
	"7", "8", "9", "10", "J", "Q", "K"};
	
	for (unsigned int i = 0 ; i < suit.size();i++)
		cout <<  " "  << ranks[suit[i].getRank()]; 
}

// prints out cards currently on the table
void pirntTableStatus(Table& cardTable){
	cout <<"Cards on the table:"<<endl;
	cout << "Clubs:";
	printCardList(cardTable.cClubs()); 
	cout <<endl;

	cout << "Diamonds:";
	printCardList(cardTable.cDiamonds());
	cout <<endl;
	cout << "Hearts:";
	printCardList(cardTable.cHearts()) ;
	cout<<endl;

	cout << "Spades:";
	printCardList(cardTable.cSpades());
	cout<<endl;
}

// prints out play's current status
vector<Card> printPlayerStatus(Player* player, Table& cardTable, Referee& referee){
	vector<Card> hand = player->cHand();
	cout << "Your hand:";
	for (int i =0 ; i < hand.size();i++)
		cout << " " << hand[i];
	cout << endl;

	cout << "Legal plays:";
	vector<Card> legalPlays = referee.getLegalPlays(cardTable, player->cHand()); // get legal plays from referee
	for (int i = 0 ; i < legalPlays.size();i++)
		cout << " " << legalPlays[i];
	cout << endl;

	return legalPlays; // returns legal plays
}

void printDeck(Table& cardTable){
	vector<Card> deck = cardTable.getDeck();
	for (int i = 0 ; i < deck.size(); i++){
		cout << deck[i] << " ";
		if ( (i+1) % 13 == 0)
			cout << endl;
	}
}

// test if the card is a legal play
bool testValidPaly(Card playCard, vector<Card> legalPlay){
	for (unsigned int i = 0 ;  i < legalPlay.size(); i++){
		if(playCard == legalPlay[i])
			return true;
	}
	cout << "This is not a legal play." <<endl;
	return false;
}

void humanPlayerGamePlay(Player* player, Table& cardTable, Referee& referee){
	bool validCard = false;
	pirntTableStatus(cardTable);
	vector<Card> legalPlay = printPlayerStatus(player, cardTable, referee);

	bool cmdFlag = false;
	while (!cmdFlag){ // loops until a 
		Command cmd;
		cin >> cmd;
		
		switch (cmd.type)
		{
			case PLAY:
				if (testValidPaly(cmd.card, legalPlay)){
					cmdFlag = player->play(cardTable, referee, cmd.card);
				}
				break;
			case DISCARD:
				if (legalPlay.size() != 0){
					cout << "You have a legal play. You may not discard."<<endl;
					break;
				}
				cmdFlag = player->discard(referee, cmd.card);
				break;
			case DECK:
				printDeck(cardTable);
				break;
			case QUIT:
				exit(1);
				break;
			case RAGEQUIT:
				break;
			default:
				break;
		}
	}

}

// base game play helper function, decides different control flow for comp & human player
void gamePlay(Player* player, Table& cardTable, Referee& referee){
	HumanPlayer* castTest = dynamic_cast<HumanPlayer*> (player);
	if (castTest){
		humanPlayerGamePlay(player, cardTable, referee);
	}
	else player->play(cardTable, referee, Card(CLUB,ACE)); // computerPlayer, pass in a dummy card
}

vector<Player*> playerList;

int main(int argc, char* argv[]){
	if (argc > 1){
		int randSeed;
		istringstream(argv[1]) >> randSeed;

		srand(randSeed);
	}

	// 1. Invite Players
	for(int i = 0; i<4;i++)
		playerList.push_back( invitePlayer(i+1));

	// game loop
	while (true){
		Table cardTable;
		Referee referee;
	
		// 2. Shufﬂing and Dealing
		int startingPlayerId  = referee.dealing(cardTable, playerList) + 1; //referee.dealing() returns the player with 7 of spades

		cout <<"A new round begins. It's player <"<< startingPlayerId <<">'s turn to play."<<endl;
		// sort playList with the player with 7 of spades at first
		vector<Player*> gamePlayerList = sortPlayerList( playerList, startingPlayerId -1); // playerid - 1 = player's pos in vector
		
		// 3. Gameplay
		while (true){
			for (int i = 0 ; i < 4; i++)
				gamePlay(gamePlayerList[i], cardTable, referee);

			// checks if round ends
			if (referee.checkRoundEnd(cardTable, gamePlayerList))
				break;
		}
		// check if game ends
		if (referee.checkGameEnd(gamePlayerList))
			break;
	}

	// delete heap allocated players
	for (unsigned int i = 0; i < playerList.size();i++)
		delete playerList[i];
}