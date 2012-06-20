#ifndef _TABLE_
#define _TABLE_

#include "Card.h"
#include <vector>

class Table{
friend class Referee;

public:
	Table();
	// accessors
	std::vector<Card> cHearts() const; 
	std::vector<Card> cClubs() const;
	std::vector<Card> cDiamonds() const;
	std::vector<Card> cSpades()const;
	std::vector<Card> getDeck();
private:
	// a private class, we think that deck only appears on the table
	class Deck{
		friend class Referee;
		public:
			Deck();
			std::vector<Card> cCards() const;
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