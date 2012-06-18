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

void legalPlaysForOneSuit (vector<Card> suit, Suit suitType,  vector<Card>&legalPlays ){
	if (suit.size() == 0){
		legalPlays.push_back(Card(suitType, SEVEN));
		return;
	}
	Rank firstCardRank = (*suit.begin()).getRank();
	Rank lastCardRank = suit.back().getRank();

	if (firstCardRank !=ACE)
		legalPlays.push_back (Card(suitType, static_cast<Rank>(firstCardRank-1)));

	if (lastCardRank != KING)
		legalPlays.push_back((Card(suitType, static_cast<Rank>(lastCardRank+1))));
}


}

int Referee::dealing(Table& cardTable, vector<Player*>playerList){
	shuffle(cardTable.Deck_.cCards_ );
	int ret = 0;

	for (int i = 0 ; i < 4 ; i++){
		for (int j = i*13 ; j < (i+1)*13; j++){
			Card curCard = cardTable.Deck_.cCards_[j];

			if (curCard.getRank() == SEVEN && curCard.getSuit() == SPADE)
				ret = i;

			playerList[i]->cHand_.push_back(cardTable.Deck_.cCards_[j]);
		}
	}

	return ret;
}

vector<Card> Referee::getLegalPlays(Table& cardTable, vector<Card> hand){
	vector<Card> legalPlays;
	vector<Card> legalPlaysInHand;

	legalPlaysForOneSuit(cardTable.cClubs(), CLUB, legalPlays);
	legalPlaysForOneSuit(cardTable.cDiamonds() , DIAMOND, legalPlays);
	legalPlaysForOneSuit(cardTable.cHearts(), HEART, legalPlays);
	legalPlaysForOneSuit(cardTable.cSpades(),SPADE, legalPlays);

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
	if (cardPlayed == 52)
	{
		for (unsigned int i = 0; i < playerList.size(); i++){
			Player* curPlayer = playerList[i];
			vector<Card> discards = curPlayer->cDiscarded_;

			cout << "Player <" << curPlayer->iPlayerId_ << ">'s discards:";
			int newScore = 0;
			for (unsigned int j = 0 ; j < discards.size();j++){
				cout  << " " << discards[j];
				newScore += discards[j].getRank() + 1;
			}
			cout << endl;
			cout << "Player <" <<curPlayer->iPlayerId_<< ">'s score: " <<curPlayer->iScore_<< " + " << newScore << " = " << curPlayer->iScore_+newScore <<endl;

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
	int minScore = 80;
	bool gameEndFlag = false;
	for (unsigned int i = 0 ; i < playerList.size();i++){
		Player* curPlayer = playerList[i];
		int playerScore = curPlayer->iScore_;

		if(playerScore >= 80){
			gameEndFlag = true;
			continue;
		}

		minScore = min(minScore, playerScore);
	}

	if (gameEndFlag){
		for (unsigned int i = 0 ; i < playerList.size(); i++){
			Player* curPlayer = playerList[i];
			if (minScore == curPlayer->iScore_)
				cout << "Player <"<<curPlayer->iPlayerId_<<"> wins!"<<endl;
		}
	}

	return gameEndFlag;
}

void Referee::placeCardHelper(Card placingCard, vector<Card>& suit){
	if (placingCard.getRank() >= SEVEN)
		suit.push_back(placingCard);
	else
		suit.insert(suit.begin() , placingCard);
}

void Referee::placeCard(Card placingCard, Table& cardTable){
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

	cardPlayed++;
}

void Referee::discardCard(Card discardingCard, Player* player){
	player->cDiscarded_.push_back(discardingCard);
	cardPlayed++;
}

