#include "Card.h";
#include <vector>
class Table{
public:
	Table();
	~Table();
	std::vector<Card> cHearts();
	std::vector<Card> cClubs();
	std::vector<Card> cDiamonds();
	std::vector<Card> cSpades();

private:
	class StartingDeck{	//自动发牌机, you know...
	public:
		StartingDeck();
		~StartingDeck();
		std::vector<Card> cCards;
		bool PlaceCard(Card);
	private:
		std::vector<Card> cCards_;
	};
	std::vector<Card> cHearts_;
	std::vector<Card> cClubs_;
	std::vector<Card> cDiamonds_;
	std::vector<Card> cSpades_;
};