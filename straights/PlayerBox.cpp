#include <sstream>
#include <string>
#include "PlayerBox.h"
#include "Controller.h"

using namespace std;

PlayerBox::PlayerBox(): iPlayerPoints_(0), iPlayerDiscards_(0), sPlayerBtnContent_("Human"), iIsHuman_(true), Gtk::Frame(){
	add(vbPlayerBox_);
	vbPlayerBox_.add(btnPlayer_);
	vbPlayerBox_.add(lblPlayerPoints_);
	vbPlayerBox_.add(lblPlayerDiscards_);

	btnPlayer_.signal_clicked().connect( sigc::mem_fun( *this,  &PlayerBox::playerBtnClicked));

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

void PlayerBox::playerBtnClicked(){
	if (sPlayerBtnContent_=="Human")
		setComputerPlayer();
	else if (sPlayerBtnContent_=="Computer")
		setHumanPlayer();
	else if (sPlayerBtnContent_=="Rage"){

	}
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