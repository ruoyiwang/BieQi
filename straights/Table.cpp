#include "Table.h"

using namespace std;

Table::Table(){
}

vector<Card> Table::getDeck(){
	return Deck_.cCards();
}

vector<Card> Table::cHearts()const{
	return cHearts_;
}

vector<Card> Table::cClubs()const{
	return cClubs_;
}
vector<Card> Table::cDiamonds()const{
	return cDiamonds_;
}

vector<Card> Table::cSpades()const{
	return cSpades_;
}

// constructor for a new ordered deck
Table::Deck::Deck(){
	// init starting deck
	for (int suit = CLUB; suit < SUIT_COUNT; suit++)
		for (int rank = ACE; rank < RANK_COUNT; rank++)
			cCards_.push_back(Card( static_cast<Suit>(suit), static_cast<Rank>(rank)));
}

vector<Card> Table::Deck::cCards()const{
	return cCards_;
}


