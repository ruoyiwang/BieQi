#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>
#include "Observer.h"
#include "Model.h"
#include "Controller.h"
#include "DeckGUI.h"
#include "view.h"

using namespace std;

View::View(Controller* c, Model* m) : controller_(c), model_(m),vbMainPanel_(false, 10), hbControlBox_(true, 10), 
		vbTableBox_(true, 10), lblTableLabel_("Cards on Table"),frmTable_("Cards on Table"),  
		hbPlayerBox_(true, 10),	hbHandBox_(true, 10), frmHand_("Your Hand"),
		btnGameStart_("Game Start"), btnGameEnd_("Game End!"), enSeed_()
{
	enSeed_.set_text("0");
	enSeed_.set_alignment(Gtk::ALIGN_CENTER);
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
	hbControlBox_.add(btnGameEnd_);
	
	lblTableLabel_.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	frmTable_.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	frmTable_.add(vbTableBox_);

	// play boxes init
	for (int i = 0; i < 4; i++){
		vbTableBox_.add(hbCardBox_[i]);

		hbCardBox_[i].set_spacing(7);
		hbCardBox_[i].set_border_width(7);

		pbPlayer_[i].setPlayerId(i+1);

		hbPlayerBox_.add(pbPlayer_[i]);
	}

	// cards boxes init
	for (int i = 0; i < 13; i++){
		imgClubs_[i].set(Deck_.image(ACE, HEART));
		imgDiamonds_[i].set(Deck_.image(ACE, HEART));
		imgHearts_[i].set(Deck_.image(ACE, HEART));
		imgSpades_[i].set(Deck_.image(ACE, HEART));
		imgHand_[i].set(Deck_.image(ACE, HEART));

		btnHand_[i].add(imgHand_[i]);
		btnHand_[i].signal_clicked().connect(sigc::bind( sigc::mem_fun( *this, &View::btnHandClicked ), i ));

		hbCardBox_[0].add(imgClubs_[i]);
		hbCardBox_[1].add(imgDiamonds_[i]);
		hbCardBox_[2].add(imgHearts_[i]);
		hbCardBox_[3].add(imgSpades_[i]);

		hbHandBox_.add(btnHand_[i]);
	}

	// event liseners
	btnGameStart_.signal_clicked().connect(sigc::mem_fun( *this, &View::btnGameStartClicked ));
	btnGameEnd_.signal_clicked().connect(sigc::mem_fun( *this, &View::btnGameEndClicked ));

	show_all();
}

View::~View(){}

void View::update(){

}


void View::btnGameStartClicked(){
	string seed = enSeed_.get_text();
	int iSeed = atoi(seed.c_str());

	controller_->gameStart(pbPlayer_[0].isHumamPlayer(),pbPlayer_[1].isHumamPlayer(),
							pbPlayer_[2].isHumamPlayer(),pbPlayer_[3].isHumamPlayer(), iSeed);
	/*
	Gtk::Dialog dialog("Straight Game Start", *this, true, true);
	Gtk::Button * okButton = dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	int result = dialog.run();
	
	switch (result) {
        case Gtk::RESPONSE_OK:
			break;
	}
	show_all();*/
}

void View::btnGameEndClicked(){
	
}

void View::btnHandClicked(int i){
	cout << i <<endl;
}