#include "Table.h"

using namespace std;

Table::Table(){
}

void Table::placeCard(Card placingCard){
	switch (placingCard.getSuit()){
		case CLUB:
			cClubs_[placingCard.getRank()];
			break;
		case DIAMOND:
			cDiamonds_[placingCard.getRank()];
			break;
		case HEART:
			cHearts_[placingCard.getRank()];
			break;
		case SPADE:
			cSpades_[placingCard.getRank()];
			break;
		default:
			break;
	}
}

vector<Card> Table::cHearts(){
	return cHearts_;
}

vector<Card> Table::cClubs(){
	return cClubs_;
}
vector<Card> Table::cDiamonds(){
	return cDiamonds_;
}

vector<Card> Table::cSpades(){
	return cSpades_;
}

// constructor for a new ordered deck
Table::Deck::Deck(){
	// init starting deck
	for (int suit = CLUB; suit < SUIT_COUNT; suit++)
		for (int rank = ACE; rank < RANK_COUNT; rank++)
			cCards_.push_back(Card( static_cast<Suit>(suit), static_cast<Rank>(rank)));
}


