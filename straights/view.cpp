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
#include "Card.h"

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
		imgClubs_[i].set(Deck_.null());
		imgDiamonds_[i].set(Deck_.null());
		imgHearts_[i].set(Deck_.null());
		imgSpades_[i].set(Deck_.null());
		imgHand_[i].set(Deck_.null());

		btnHand_[i].add(imgHand_[i]);
		btnHand_[i].signal_clicked().connect(sigc::bind( sigc::mem_fun( *this, &View::btnHandClicked ), i ));
		btnHand_[i].set_sensitive(false);

		hbCardBox_[0].add(imgClubs_[i]);
		hbCardBox_[1].add(imgDiamonds_[i]);
		hbCardBox_[2].add(imgHearts_[i]);
		hbCardBox_[3].add(imgSpades_[i]);

		hbHandBox_.add(btnHand_[i]);
	}

	// event liseners
	btnGameStart_.signal_clicked().connect(sigc::mem_fun( *this, &View::btnGameStartClicked ));
	btnGameEnd_.signal_clicked().connect(sigc::mem_fun( *this, &View::btnGameEndClicked ));
	model_->subscribe(this);
	show_all();
}

View::~View(){}

void View::update(){
	Table cardTable = model_->cardTable();
	std::vector<Card> cHearts_ = cardTable.cHearts();
	std::vector<Card> cClubs_ = cardTable.cClubs();
	std::vector<Card> cDiamonds_ = cardTable.cDiamonds();
	std::vector<Card> cSpades_ = cardTable.cSpades();
	
	gameState enmCurrentState = model_->enmCurrentState();

	if (enmCurrentState == INGAME){
		//update table
		for (int i = 0; i < cHearts_.size(); i++){
			Card curCard = cHearts_.at(i);
			imgHearts_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}
		for (int i = 0; i < cDiamonds_.size(); i++){
			Card curCard = cDiamonds_.at(i);
			imgDiamonds_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}
		for (int i = 0; i < cClubs_.size(); i++){
			Card curCard = cClubs_.at(i);
			imgClubs_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}
		for (int i = 0; i < cSpades_.size(); i++){
			Card curCard = cSpades_.at(i);
			imgSpades_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}

		//update card on hand
		Player *curPlayer = model_->gamePlayerList().at(model_->iCurrentPlayer());

		for (int i = 0; i < curPlayer->cHand().size(); i++){
			Card curCard = curPlayer->cHand().at(i);
			imgHand_[i].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
			btnHand_[i].set_sensitive(true);
		}
		for (int i = curPlayer->cHand().size(); i < 13; i++){
			imgHand_[i].set(Deck_.null());
			btnHand_[i].set_sensitive(false);
		}
		
		int iPlayerId = curPlayer->iPlayerId();
		pbPlayer_[iPlayerId-1].setPlayerPoints(curPlayer->iRealTimeScore());
		pbPlayer_[iPlayerId-1].setPlayerDiscard(curPlayer->iDiscards());

		for (int i = 0; i < 4; i++){
			if (i == (iPlayerId-1))
				pbPlayer_[i].setActive();
			else
				pbPlayer_[i].setInactive();
		}

	}
	else if (enmCurrentState == GAMESTART){
		for (int i = 0; i < 13; i++){
			imgHand_[i].set(Deck_.null());
			btnHand_[i].set_sensitive(false);
			imgClubs_[i].set(Deck_.null());
			imgDiamonds_[i].set(Deck_.null());
			imgHearts_[i].set(Deck_.null());
			imgSpades_[i].set(Deck_.null());
			imgHand_[i].set(Deck_.null());
		}
		for (int i = 0; i < 4; i++){
			pbPlayer_[i].setRageBtn();
		}
	}
	else if (enmCurrentState == ROUNDEND){
		//update table
		for (int i = 0; i < 13; i++){
			imgHand_[i].set(Deck_.null());
			btnHand_[i].set_sensitive(true);
			imgClubs_[i].set(Deck_.null());
			imgDiamonds_[i].set(Deck_.null());
			imgHearts_[i].set(Deck_.null());
			imgSpades_[i].set(Deck_.null());
		}

		//update card on hand
		Player *curPlayer = model_->gamePlayerList().at(model_->iCurrentPlayer());

		for (int i = 0; i < curPlayer->cHand().size(); i++){
			Card curCard = curPlayer->cHand().at(i);
			imgHand_[i].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
			btnHand_[i].set_sensitive(true);
		}
		for (int i = curPlayer->cHand().size(); i < 13; i++){
			imgHand_[i].set(Deck_.null());
			btnHand_[i].set_sensitive(false);
		}
		
		int iPlayerId = curPlayer->iPlayerId();
		pbPlayer_[iPlayerId-1].setPlayerPoints(curPlayer->iRealTimeScore());
		pbPlayer_[iPlayerId-1].setPlayerDiscard(curPlayer->iDiscards());

		
		Gtk::MessageDialog msgdlgRoundEnd(*this, "End of Round");
		msgdlgRoundEnd.set_secondary_text(model_->sRoundEndDialog());
		msgdlgRoundEnd.run();

	}
	else if (enmCurrentState == GAMEEND || enmCurrentState == FORCEDGAMEEND){

		int iMin = 100;
		for (int i = 0; i < 13; i++){
			imgHand_[i].set(Deck_.null());
			btnHand_[i].set_sensitive(false);
			imgClubs_[i].set(Deck_.null());
			imgDiamonds_[i].set(Deck_.null());
			imgHearts_[i].set(Deck_.null());
			imgSpades_[i].set(Deck_.null());
			imgHand_[i].set(Deck_.null());
		}
		for (int i = 0; i < 4; i++){
			pbPlayer_[i].setActive();
			pbPlayer_[i].setHumanPlayer();
		}

		if (enmCurrentState != FORCEDGAMEEND){
			for (int i = 0; i < 4; i++){
				Player *curPlayer = model_->playerList().at(i);
				if (iMin > curPlayer->iScore()){
					iMin = curPlayer->iScore();
				}
			}
			for (int i = 0; i < 4; i++){
				Player *curPlayer = model_->playerList().at(i);
				if (iMin == curPlayer->iScore()){
					Gtk::MessageDialog msgdlgRoundEnd(*this, "End of Game");
					ostringstream ss;
					ss<<"Player"<<i+1<<"has won";
					msgdlgRoundEnd.set_secondary_text(ss.str());
					msgdlgRoundEnd.run();
				}
			}
		}
	}
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
	controller_->endGame();
}

void View::btnHandClicked(int i){
	cout << i <<endl;
	controller_->play(i);
}