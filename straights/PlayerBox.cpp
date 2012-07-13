#include <sstream>
#include "PlayerBox.h"
#include <string>

using namespace std;

PlayerBox::PlayerBox(): iPlayerPoints_(0), iPlayerDiscards_(0), sPlayerBtnContent_("Human"), Gtk::Frame(){
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
	update();
}
void PlayerBox::setComputerPlayer(){
	sPlayerBtnContent_ = "Computer";
	update();
}
void PlayerBox::setRangeBtn(){
	sPlayerBtnContent_ = "Range";
	update();
}

void PlayerBox::setRangeBtnDisabled(){
	sPlayerBtnContent_ = "Range";
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