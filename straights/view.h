#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "PlayerBox.h"
#include "Observer.h"
#include "DeckGUI.h"
#include "Player.h"

class Controller;
class Model;

//class declaration
class View : public Gtk::Window, public Observer{
public:
	View(Controller*, Model*);	//constructors and destructor
	virtual ~View();
	virtual void update();
	void playerBtnClicked(PlayerBox* curBtn);	//clicking button

private:
	Controller *controller_;	//the controller
	Model *model_;				//the model

	Gtk::VBox vbMainPanel_;		//all the objects that are in the windows

	Gtk::HBox hbControlBox_;

	Gtk::VBox vbTableBox_;
	Gtk::HBox hbCardBox_[4];

	Gtk::Label lblTableLabel_;
	Gtk::Frame frmTable_;

	Gtk::HBox hbPlayerBox_;		//the abstracted PlayerBox
	PlayerBox pbPlayer_[4];

	Gtk::Frame frmHand_;
	Gtk::HBox hbHandBox_;

	Gtk::Button btnGameStart_;
	Gtk::Entry enSeed_;
	Gtk::Button btnGameEnd_;

	DeckGUI Deck_;				
	
	Gtk::Image imgClubs_[13];
	Gtk::Image imgDiamonds_[13];
	Gtk::Image imgHearts_[13];
	Gtk::Image imgSpades_[13];

	Gtk::Image imgHand_[13];
	Gtk::Button btnHand_[13];

	
	void btnGameStartClicked();		//clicking event for start
	void btnGameEndClicked();		//clicking event for end
	void btnHandClicked(int i);		//clicking event for choosing a card
	void popUpMsgDialog(std::string title, std::string text);		//event for popping up the msg box
	void emptyTableAndHands();		//reset functions
	void updatePlayerData(Player* curPlayer, int iPlayerId);
									//updating player data

};

#endif