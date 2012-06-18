#include "Player.h"
#include "Card.h"
#include "Referee.h"

#include <iostream>
#include <string>

using namespace std;

Player::Player(int iPlayerId):iPlayerId_(iPlayerId),iScore_(0){}

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
	removeFromHand(cCard);
	rR.placeCard(cCard, tTable);
	return true;
}

bool HumanPlayer::discard(Referee& rR, Card& cCard){
	//check to see if card is even on hand
	//if the card is not even in the user's hand, return right away
	if (!checkInHand(cCard)){
		cout<<"This is not a legal play."<<endl;
		return false;
	}

	removeFromHand(cCard);
	rR.discardCard(cCard, this);
	return true;
}

bool CompPlayer::play(Table& tTable, Referee& rR, Card& cCard){
	string sTemp;
	//locate all 8 possible cards+
	vector<Card> cAllowed = rR.getLegalPlays(tTable, cHand());
	
	for (unsigned int i = 0; i < cHand_.size(); i++){	//find the right card to place
		for (unsigned int j = 0; j < cAllowed.size(); j++){
			if (cHand_.at(i) == cAllowed.at(j)){
				cCard = cHand_.at(i);
				cout<<"Player "<<iPlayerId_<<" plays "<<cCard<<endl;
				cHand_.erase(cHand_.begin() + i);
				rR.placeCard(cCard, tTable);
				return true;
			}
		}
	}
	return discard(rR, cHand_.at(0));
}

bool CompPlayer::discard(Referee& rR, Card& cCard){
	cout<<"Player "<<iPlayerId_<<" discards "<<cCard<<endl;
	rR.discardCard(cCard, this);
	cHand_.erase(cHand_.begin());
	return true;
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