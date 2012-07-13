#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>
#include "Model.h"
#include "Controller.h"
#include "DeckGUI.h"
#include "view.h"

using namespace std;

View::View(Controller* c, Model* m) : controller_(c), model_(m),vbMainPanel_(false, 10), hbControlBox_(true, 10), 
		vbTableBox_(true, 10), lblTableLabel_("Cards on Table"),frmTable_("Cards on Table"),  
		hbPlayerBox_(true, 10),	hbHandBox_(true, 10), frmHand_("Your Hand"),
		btnGameStart_("Game Start"), btnGameEnd_("Game End!")
{
	// set default seed
	enSeed_.set_text("0");
	enSeed_.set_alignment(Gtk::ALIGN_CENTER);

	// set window title
	set_title("Straights");
	set_border_width(20);
	// add main panel to window
	add(vbMainPanel_);

	// add components to main panel
	vbMainPanel_.add(hbControlBox_);
	vbMainPanel_.add(frmTable_);
	vbMainPanel_.add(hbPlayerBox_);
	vbMainPanel_.add(frmHand_);
	frmHand_.add(hbHandBox_);

	// add buttons to game control box
	hbControlBox_.add(btnGameStart_);
	hbControlBox_.add(enSeed_);
	hbControlBox_.add(btnGameEnd_);
	
	// set frame look
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

		Gtk::Button* btnPlayer = pbPlayer_[i].getButton();
		btnPlayer->signal_clicked().connect(sigc::bind( sigc::mem_fun( *this, &View::playerBtnClicked ), &pbPlayer_[i] ));
	}

	// cards boxes init
	emptyTableAndHands();
	for (int i = 0; i < 13; i++){

		// get hand buttons
		btnHand_[i].add(imgHand_[i]);
		// set event listen to the button
		btnHand_[i].signal_clicked().connect(sigc::bind( sigc::mem_fun( *this, &View::btnHandClicked ), i ));

		// add img arrays to table card boxes
		hbCardBox_[0].add(imgClubs_[i]);
		hbCardBox_[1].add(imgDiamonds_[i]);
		hbCardBox_[2].add(imgHearts_[i]);
		hbCardBox_[3].add(imgSpades_[i]);
		// add button to the box
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
	// get essential variables
	Table cardTable = model_->cardTable();
	std::vector<Card> cHearts_ = cardTable.cHearts();
	std::vector<Card> cClubs_ = cardTable.cClubs();
	std::vector<Card> cDiamonds_ = cardTable.cDiamonds();
	std::vector<Card> cSpades_ = cardTable.cSpades();
	
	//gets the current state of the game so that update can be performed properly
	gameState enmCurrentState = model_->enmCurrentState();

	//if the state is in game
	if (enmCurrentState == INGAME){
		//update table that is being displayed
		for (unsigned int i = 0; i < cHearts_.size(); i++){
			Card curCard = cHearts_.at(i);
			imgHearts_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}
		for (unsigned int i = 0; i < cDiamonds_.size(); i++){
			Card curCard = cDiamonds_.at(i);
			imgDiamonds_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}
		for (unsigned int i = 0; i < cClubs_.size(); i++){
			Card curCard = cClubs_.at(i);
			imgClubs_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}
		for (unsigned int i = 0; i < cSpades_.size(); i++){
			Card curCard = cSpades_.at(i);
			imgSpades_[curCard.getRank()].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
		}

		//update card on hand
		Player *curPlayer = model_->gamePlayerList().at(model_->iCurrentPlayer());

		for (unsigned int i = 0; i < curPlayer->cHand().size(); i++){
			Card curCard = curPlayer->cHand().at(i);
			imgHand_[i].set(Deck_.image(curCard.getRank(), curCard.getSuit()));
			btnHand_[i].set_sensitive(true);
		}
		for (unsigned int i = curPlayer->cHand().size(); i < 13; i++){
			imgHand_[i].set(Deck_.null());
			btnHand_[i].set_sensitive(false);
		}
		
		// update player inforamtion
		int iPlayerId = curPlayer->iPlayerId();
		pbPlayer_[iPlayerId-1].setPlayerPoints(curPlayer->iRealTimeScore());
		pbPlayer_[iPlayerId-1].setPlayerDiscard(curPlayer->iDiscards());

		// active current player & inactive other players
		for (int i = 0; i < 4; i++){
			if (i == (iPlayerId-1))
				pbPlayer_[i].setActive();
			else
				pbPlayer_[i].setInactive();
		}

	}
	//if the state is just as the game started
	else if (enmCurrentState == GAMESTART){
		// a new game started, empty cards on table and hands
		emptyTableAndHands();
		for (int i = 0; i < 4; i++){
			pbPlayer_[i].setRageBtn();
		}
		ostringstream ss;
	}
	else if (enmCurrentState == ROUNDEND){
		//update table
		emptyTableAndHands();

		//update card on hand
		Player *curPlayer = model_->gamePlayerList().at(model_->iCurrentPlayer());

		popUpMsgDialog("End of Round", model_->sRoundEndDialog());

		for (int i = 0; i < 4; i++){
			curPlayer = model_->playerList().at(i);
			pbPlayer_[i].setPlayerPoints(curPlayer->iRealTimeScore());
			pbPlayer_[i].setPlayerDiscard(curPlayer->iDiscards());
		}

	}
	//if the game either ended normally, or forced by the Game end button
	else if (enmCurrentState == GAMEEND || enmCurrentState == FORCEDGAMEEND){

		int iMin = 100;
		emptyTableAndHands();

		//reset all the buttons and players
		for (int i = 0; i < 4; i++){
			pbPlayer_[i].setActive();
			pbPlayer_[i].setHumanPlayer();
			pbPlayer_[i].setPlayerDiscard(0);
			pbPlayer_[i].setPlayerPoints(0);
		}

		//if it's forced, then we would need to get the minimum score and the winner where displaying is neccessary
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
					ostringstream ss;
					ss<<"Player "<<i+1<<" has won";

					popUpMsgDialog("End of Game", ss.str());
				}
			}
		}
	}
}

//functions used to empty the table and the hands
void View::emptyTableAndHands(){
	for (int i = 0; i < RANK_COUNT; i++){
		imgClubs_[i].set(Deck_.null());
		imgDiamonds_[i].set(Deck_.null());
		imgHearts_[i].set(Deck_.null());
		imgSpades_[i].set(Deck_.null());
		imgHand_[i].set(Deck_.null());
		btnHand_[i].set_sensitive(false);
	}
}

//function used to cll the msg dialog
void View::popUpMsgDialog(string title, string text){
	Gtk::MessageDialog msgdlg(*this, title);
	msgdlg.set_secondary_text(text);
	msgdlg.run();
}

//funtion used to pass the game start event to the controller
void View::btnGameStartClicked(){
	string seed = enSeed_.get_text();
	int iSeed = atoi(seed.c_str());

	controller_->gameStart(pbPlayer_[0].isHumamPlayer(),pbPlayer_[1].isHumamPlayer(),
							pbPlayer_[2].isHumamPlayer(),pbPlayer_[3].isHumamPlayer(), iSeed);
}

//funtion used to pass the players event to the controller
void View::playerBtnClicked(PlayerBox* curBtn){
	string btnContent = curBtn->getPlayerBtnContent();
	if (btnContent=="Human")
		curBtn->setComputerPlayer();
	else if (btnContent=="Computer")
		curBtn->setHumanPlayer();
	else if (btnContent=="Rage"){
		curBtn->setInactive();
		controller_->rageQuit();
	}
}

//funtion used to pass the game end event to the controller
void View::btnGameEndClicked(){
	controller_->endGame();
}

//funtion used to pass the card clicking event to the controller
void View::btnHandClicked(int i){
	cout << i <<endl;
	controller_->play(i);
}