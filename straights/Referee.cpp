#include "Referee.h"
#include "Player.h"

#include <vector>
#include <iostream>

using namespace std;

namespace{

void shuffle(vector<Card>& deck){
	int n = 52;
	while ( n > 1 ) {
		//int k = (int) (lrand48() % n);
		int k = (int) (rand()%n);
		--n;
		Card c = deck[n];
		deck[n] = deck[k];
		deck[k] = c;
	}
}

// helper function for finding legal plays for one suit according to current cards on table
void legalPlaysForOneSuit (vector<Card> suit, Suit suitType,  vector<Card>&legalPlays ){
	// if no cards, 7 is the only option
	if (suit.size() == 0){
		legalPlays.push_back(Card(suitType, SEVEN));
		return;
	}
	// get first & the last card
	Rank firstCardRank = (*suit.begin()).getRank();
	Rank lastCardRank = suit.back().getRank();

	// if first card != ACE, the legal paly is the one before the first card
	if (firstCardRank !=ACE)
		legalPlays.push_back (Card(suitType, static_cast<Rank>(firstCardRank-1)));

	// same for finding last card
	if (lastCardRank != KING)
		legalPlays.push_back((Card(suitType, static_cast<Rank>(lastCardRank+1))));
}


}

// referee hands out the cards to players
int Referee::dealing(Table& cardTable, vector<Player*>playerList){
	shuffle(cardTable.Deck_.cCards_ ); // shuffle function
	int ret = 0; // ret value which will be the player who has 7 of spades

	for (int i = 0 ; i < 4 ; i++){
		for (int j = i*13 ; j < (i+1)*13; j++){
			Card curCard = cardTable.Deck_.cCards_[j];

			// test if the card is 7 of spades
			if (curCard.getRank() == SEVEN && curCard.getSuit() == SPADE)
				ret = i;

			// give the card to the player
			playerList[i]->cHand_.push_back(cardTable.Deck_.cCards_[j]);
		}
	}

	return ret;
}

vector<Card> Referee::getLegalPlays(Table& cardTable, vector<Card> hand){
	vector<Card> legalPlays;
	vector<Card> legalPlaysInHand;

	// find legal play for each suit
	legalPlaysForOneSuit(cardTable.cClubs(), CLUB, legalPlays);
	legalPlaysForOneSuit(cardTable.cDiamonds() , DIAMOND, legalPlays);
	legalPlaysForOneSuit(cardTable.cHearts(), HEART, legalPlays);
	legalPlaysForOneSuit(cardTable.cSpades(),SPADE, legalPlays);

	// decide the final legal plays according to player's hand
	for (unsigned int i = 0 ; i < legalPlays.size();i++){
		for (unsigned int j = 0 ; j < hand.size(); j++){
			if (legalPlays[i] == hand[j] ){
				legalPlaysInHand.push_back(hand[j]);
				break;
			}

		}
	}

	return legalPlaysInHand;
}


bool Referee::checkRoundEnd(Table& cardTable, vector<Player*> playerList){
	// if cardPlayed == 52 means all cards are used (including play/discard)
	if (cardPlayed == 52)
	{
		for (unsigned int i = 0; i < playerList.size(); i++){
			Player* curPlayer = playerList[i];
			vector<Card> discards = curPlayer->cDiscarded_;

			cout << "Player <" << curPlayer->iPlayerId_ << ">'s discards:";
			int newScore = 0;
			// print discards & calculate scores
			for (unsigned int j = 0 ; j < discards.size();j++){
				cout  << " " << discards[j];
				newScore += discards[j].getRank() + 1;
			}
			cout << endl;
			cout << "Player <" <<curPlayer->iPlayerId_<< ">'s score: " <<curPlayer->iScore_<< " + " << newScore << " = " << curPlayer->iScore_+newScore <<endl;
			// add score to player
			curPlayer->iScore_ = curPlayer->iScore_ + newScore;
			
			// empty discards list for next round
			while(curPlayer->cDiscarded_.size()!=0)
				curPlayer->cDiscarded_.pop_back();
		}
		return true;
	}
	else
		return false;
}


bool Referee::checkGameEnd(vector<Player*> playerList){
	int minScore = playerList[0]->iScore_;
	bool gameEndFlag = false;
	// check sroce on each player
	for (unsigned int i = 0 ; i < playerList.size();i++){
		Player* curPlayer = playerList[i];
		int playerScore = curPlayer->iScore_;

		// if score >= 80, games can stop
		if(playerScore >= 80){
			gameEndFlag = true;
			continue;
		}
		// store current lowest score
		minScore = min(minScore, playerScore);
	}

	if (gameEndFlag){
		for (unsigned int i = 0 ; i < playerList.size(); i++){
			Player* curPlayer = playerList[i];
			// print out winner(s)
			if (minScore == curPlayer->iScore_)
				cout << "Player <"<<curPlayer->iPlayerId_<<"> wins!"<<endl;
		}
	}

	return gameEndFlag;
}

void Referee::placeCardHelper(Card placingCard, vector<Card>& suit){
	// place card on certian suit on table
	if (placingCard.getRank() >= SEVEN)
		suit.push_back(placingCard);
	else
		suit.insert(suit.begin() , placingCard);
}

void Referee::placeCard(Card placingCard, Table& cardTable){
	// used for placing card on the table
	switch (placingCard.getSuit()){
		case CLUB:
			placeCardHelper ( placingCard,cardTable.cClubs_);
			break;
		case DIAMOND:
			placeCardHelper ( placingCard,cardTable.cDiamonds_);
			break;
		case HEART:
			placeCardHelper ( placingCard,cardTable.cHearts_);
			break;
		case SPADE:
			placeCardHelper ( placingCard,cardTable.cSpades_);
			break;
		default:
			break;
	}
	// inc # of cards played;
	cardPlayed++;
}

void Referee::discardCard(Card discardingCard, Player* player){
	// add discarded card to players data
	player->cDiscarded_.push_back(discardingCard);
	// inc # of cards played;
	cardPlayed++;
}


Player* Referee::rangeQuit(Player*& humanPlayer){
	Player* curHumPlayer = humanPlayer;
	Player* newCompPlayer = new CompPlayer(humanPlayer->iPlayerId_);

	cout << "Player <"<<humanPlayer->iPlayerId_<<"> ragequits. A computer will now take over." << endl;
	for (unsigned int i = 0 ; i< humanPlayer->cHand_.size();i++)
		newCompPlayer->cHand_.push_back(humanPlayer->cHand_[i]);

	for (unsigned int i = 0 ; i< humanPlayer->cDiscarded_.size();i++)
		newCompPlayer->cDiscarded_.push_back(humanPlayer->cDiscarded_[i]);

	newCompPlayer->iScore_ = humanPlayer->iScore_;
	humanPlayer = newCompPlayer;
	delete curHumPlayer;
	
	return humanPlayer;
}
