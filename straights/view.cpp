#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "observer.h"
#include "subject.h"
#include "DeckGUI.h"
#include "view.h"

using namespace std;

View::View() :vbMainPanel_(false, 10), hbControlBox_(true, 10), 
		vbTableBox_(true, 10), lblTableLabel_("Cards on Table"),frmTable_("Cards on Table"),  
		hbPlayerBox_(true, 10),	hbHandBox_(true, 10), frmHand_("Your Hand"),
		btnGameStart_("Game Start"), btnGameEnd("Game End!"), enSeed_(),
		Deck_(DeckGUI()){
	set_title("Straights");
	set_border_width(20);
	add(vbMainPanel_);

	vbMainPanel_.add(hbControlBox_);
	vbMainPanel_.add(frmTable_);
	vbMainPanel_.add(hbPlayerBox_);
	vbMainPanel_.add(frmHand_);
	frmHand_.add(hbHandBox_);

	hbControlBox_.add(btnGameStart_);
	hbControlBox_.add(enSeed_);
	hbControlBox_.add(btnGameEnd);
	
	lblTableLabel_.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	frmTable_.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	frmTable_.add(vbTableBox_);


	for (int i = 0; i < 4; i++){
		vbTableBox_.add(hbCardBox_[i]);

		hbCardBox_[i].set_spacing(7);
		hbCardBox_[i].set_border_width(7);

		hbPlayerBox_.add(frmPlayer_[i]);
		frmPlayer_[i].add(vbPlayer_[i]);
		vbPlayer_[i].add(btnPlayer_[i]);

		btnPlayer_[i].set_label("Human");
		vbPlayer_[i].add(lblPlayerPoints_[i]);
		lblPlayerPoints_[i].set_label("0 points");
		vbPlayer_[i].add(lblPlayerDiscards_[i]);
		lblPlayerDiscards_[i].set_label("0 discards");

		ostringstream ss;
		ss<<i;

		frmPlayer_[i].set_label("Player " + ss.str());
	}

	for (int i = 0; i < 13; i++){
		imgClubs_[i].set(Deck_.image(ACE, HEART));
		imgDiamonds_[i].set(Deck_.image(ACE, HEART));
		imgHearts_[i].set(Deck_.image(ACE, HEART));
		imgSpades_[i].set(Deck_.image(ACE, HEART));
		imgHand_[i].set(Deck_.image(ACE, HEART));

		btnHand_[i].add(imgHand_[i]);

		hbCardBox_[0].add(imgClubs_[i]);
		hbCardBox_[1].add(imgDiamonds_[i]);
		hbCardBox_[2].add(imgHearts_[i]);
		hbCardBox_[3].add(imgSpades_[i]);

		hbHandBox_.add(btnHand_[i]);
	}

	show_all();
}

View::~View(){}

void View::update(){

}