#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <vector>

class Table{
friend class Referee;

public:
	Table();
	// accessors
	std::vector<Card> cHearts(); 
	std::vector<Card> cClubs();
	std::vector<Card> cDiamonds();
	std::vector<Card> cSpades();
	std::vector<Card> getDeck();
private:
	// a private class, we think that deck only appears on the table
	class Deck{
		friend class Referee;
		public:
			Deck();
			std::vector<Card> cCards();
		private:
			std::vector<Card> cCards_;	
	};
	
	Deck Deck_; // deck on the table

	// cards on the table
	std::vector<Card> cHearts_;
	std::vector<Card> cClubs_;
	std::vector<Card> cDiamonds_;
	std::vector<Card> cSpades_;
};

#endif