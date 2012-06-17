#include "Player.h"
#include "Card.h"
#include "Referee.h";
#include <iostream>
#include <string>

using namespace std;

Player::Player(){}

Player::~Player(){}

vector<Card> Player::cHand(){
	return cHand_;
}


void HumanPlayer::play(Table& tTable, Referee& rR){
	string sTemp;
	while (cin>>sTemp){

	}
};

void CompPlayer::play(Table& tTable, Referee& rR){
	string sTemp;
	//locate all 8 possible cards+
	vector<Card> cAllowed;
	if ((tTable.cHearts().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cHearts().at(0).getSuit(), Rank((tTable.cHearts().at(0).getRank()-1))));
	if ((tTable.cHearts().at(12).getRank()+1)>13)
		cAllowed.push_back(Card(tTable.cHearts().at(0).getSuit(), Rank((tTable.cHearts().back().getRank()+1))));

	if ((tTable.cClubs().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cClubs().at(0).getSuit(), Rank((tTable.cClubs().at(0).getRank()-1))));
	if ((tTable.cClubs().at(12).getRank()+1)>13)
		cAllowed.push_back(Card(tTable.cClubs().at(0).getSuit(), Rank((tTable.cClubs().back().getRank()+1))));

	if ((tTable.cDiamonds().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cDiamonds().at(0).getSuit(), Rank((tTable.cDiamonds().at(0).getRank()-1))));
	if ((tTable.cDiamonds().at(12).getRank()+1)>13)
		cAllowed.push_back(Card(tTable.cDiamonds().at(0).getSuit(), Rank((tTable.cDiamonds().back().getRank()+1))));

	if ((tTable.cSpades().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cSpades().at(0).getSuit(), Rank((tTable.cSpades().at(0).getRank()-1))));
	if ((tTable.cSpades().at(12).getRank()+1)>13)
		cAllowed.push_back(Card(tTable.cSpades().at(0).getSuit(), Rank((tTable.cSpades().back().getRank()+1))));
	
	for (int i = 0; i < cHand_.size(); i++){	//find the right card to place
		for (int j = 0; j < cAllowed.size(); j++){
			if (cHand_.at(i) == cAllowed.at(j)){
				rR.checkPlay(*this, cHand_.at(i));
				return;
			}
		}
	}
	this->discard(rR);
}

void CompPlayer::discard(Referee& rR){
	rR.checkDiscard(*this, cHand_.back());
	cHand_.pop_back();		
	return;
}

void temp(){
	Player A;
	A = CompPlayer();
}