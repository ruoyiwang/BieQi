#include <sstream>
#include <string>
#include "PlayerBox.h"

using namespace std;

PlayerBox::PlayerBox(): iPlayerPoints_(0), iPlayerDiscards_(0), sPlayerBtnContent_("Human"), iIsHuman_(true), Gtk::Frame(){
	add(vbPlayerBox_);
	vbPlayerBox_.add(btnPlayer_);
	vbPlayerBox_.add(lblPlayerPoints_);
	vbPlayerBox_.add(lblPlayerDiscards_);

	update();
}

PlayerBox::~PlayerBox(){}

void PlayerBox::update(){
	btnPlayer_.set_label(sPlayerBtnContent_);
	ostringstream ss;
	ss<<iPlayerPoints_;
	lblPlayerPoints_.set_label(ss.str() + " points");
	ss.str(""); // empty ss
	ss<<iPlayerDiscards_;
	lblPlayerDiscards_.set_label(ss.str() + " discards");
}

PlayerBox& PlayerBox::operator= (const PlayerBox& ){
	return *this;
}

// mutators
void PlayerBox::setHumanPlayer(){
	sPlayerBtnContent_ = "Human";
	iIsHuman_ = true;
	update();
}
void PlayerBox::setComputerPlayer(){
	sPlayerBtnContent_ = "Computer";
	iIsHuman_ = false;
	update();
}
void PlayerBox::setRageBtn(){
	sPlayerBtnContent_ = "Rage";
	update();
}

void PlayerBox::setRageBtnDisabled(){
	sPlayerBtnContent_ = "Rage";
	update();
}

void PlayerBox::setPlayerPoints(int i){
	iPlayerPoints_ = i;
	update();
}

void PlayerBox::setPlayerDiscard(int i){
	iPlayerDiscards_ = i;
	update();
}
void PlayerBox::setPlayerId(int i){
	ostringstream ss;
	ss<<i;

	set_label("Player " + ss.str());
}

string PlayerBox::getPlayerBtnContent(){
	return sPlayerBtnContent_;
}

Gtk::Button* PlayerBox::getButton(){
	return &btnPlayer_;
}

bool PlayerBox::isHumamPlayer(){
	return iIsHuman_;
}


void PlayerBox::setActive(){
	btnPlayer_.set_sensitive(true);
}
void PlayerBox::setInactive(){
	btnPlayer_.set_sensitive(false);
}