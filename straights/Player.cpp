#include "Player.h"
#include "Card.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

Player::Player(int iPlayerId):iPlayerId_(iPlayerId){}

Player::~Player(){}

int Player::iPlayerId(){
	return iPlayerId_;
}

vector<Card> Player::cHand(){
	return cHand_;
}

HumanPlayer::HumanPlayer(int iPlayerId): Player(iPlayerId){}

CompPlayer::CompPlayer(int iPlayerId): Player(iPlayerId){}

bool HumanPlayer::play(Table& tTable, Referee& rR, Card& cCard){
	//check to see if card is even on hand
	//if the card is not even in the user's hand, return right away
	if (!checkInHand(cCard)){
		cout<<"This is not a legal play."<<endl;
		return false;
	}
	//check with ref
	if (rR.checkPlay(*this, cCard)){	//if true then remove from hand, ref will put card on table
		removeFromHand(cCard);
		return true;
	}
	else
		return false;
}

bool HumanPlayer::discard(Referee& rR, Card& cCard){
	//check to see if card is even on hand
	//if the card is not even in the user's hand, return right away
	if (!checkInHand(cCard)){
		cout<<"This is not a legal play."<<endl;
		return false;
	}
	//check with ref, too see if player is not lying
	if (rR.checkDiscard(*this, cCard)){	//if true then remove from hand, ref will put card on table
		removeFromHand(cCard);
		return true;
	}
	else
		return false;
}

bool CompPlayer::play(Table& tTable, Referee& rR, Card& cCard){
	string sTemp;
	//locate all 8 possible cards+
	vector<Card> cAllowed;
	if ((tTable.cHearts().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cHearts().at(0).getSuit(), Rank((tTable.cHearts().at(0).getRank()-1))));
	if ((tTable.cHearts().at(12).getRank()+1)<13)
		cAllowed.push_back(Card(tTable.cHearts().at(0).getSuit(), Rank((tTable.cHearts().back().getRank()+1))));

	if ((tTable.cClubs().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cClubs().at(0).getSuit(), Rank((tTable.cClubs().at(0).getRank()-1))));
	if ((tTable.cClubs().at(12).getRank()+1)<13)
		cAllowed.push_back(Card(tTable.cClubs().at(0).getSuit(), Rank((tTable.cClubs().back().getRank()+1))));

	if ((tTable.cDiamonds().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cDiamonds().at(0).getSuit(), Rank((tTable.cDiamonds().at(0).getRank()-1))));
	if ((tTable.cDiamonds().at(12).getRank()+1)<13)
		cAllowed.push_back(Card(tTable.cDiamonds().at(0).getSuit(), Rank((tTable.cDiamonds().back().getRank()+1))));

	if ((tTable.cSpades().at(0).getRank()-1)>0)
		cAllowed.push_back(Card(tTable.cSpades().at(0).getSuit(), Rank((tTable.cSpades().at(0).getRank()-1))));
	if ((tTable.cSpades().at(12).getRank()+1)<13)
		cAllowed.push_back(Card(tTable.cSpades().at(0).getSuit(), Rank((tTable.cSpades().back().getRank()+1))));
	
	for (unsigned int i = 0; i < cHand_.size(); i++){	//find the right card to place
		for (unsigned int j = 0; j < cAllowed.size(); j++){
			if (cHand_.at(i) == cAllowed.at(j)){
				if (rR.checkPlay(*this, cHand_.at(i))){
					cout<<"Player "<<iPlayerId_<<" plays "<<cHand_.at(i)<<endl;
					return true;
				}
			}
		}
	}
	return discard(rR, cHand_.at(0));
}

bool CompPlayer::discard(Referee& rR, Card& cCard){
	if(rR.checkDiscard(*this, cCard)){
		cout<<"Player "<<iPlayerId_<<" discards "<<cCard<<endl;
		cHand_.erase(cHand_.begin());
		return true;
	}
	return false;
}

//private member function to check if a card is in the player's hand
bool Player::checkInHand(Card& cCard){
	for (unsigned int i = 0; i < cHand_.size(); i++){
		if (cCard == cHand_.at(i))
			return true;
	}
	return false;
}

//removes the corresponding card from hand;
void Player::removeFromHand(Card& cCard){
	for (unsigned int i = 0; i < cHand_.size(); i++){
		if (cCard == cHand_.at(i))
			cHand_.erase(cHand_.begin()+i);
	}
}