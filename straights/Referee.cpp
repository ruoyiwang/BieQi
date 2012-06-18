#include "Referee.h"
#include "Player.h"

#include <vector>


using namespace std;

bool Referee::checkPlay(Player& p, Card& c){
	return true;
}

bool Referee::checkDiscard(Player& p, Card& c){
	return true;
}

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
	Rank lastCardRank = (*suit.end()).getRank();

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


bool Referee::checkGameEnd(){
	return true;
}

