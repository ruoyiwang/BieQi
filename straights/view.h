#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "PlayerBox.h"
#include "Observer.h"
#include "DeckGUI.h"

class Controller;
class Model;

class View : public Gtk::Window, public Observer{
public:
	View(Controller*, Model*);
	virtual ~View();
	virtual void update();
	void playerBtnClicked(PlayerBox* curBtn);

private:
	Controller *controller_;
	Model *model_;

	Gtk::VBox vbMainPanel_;

	Gtk::HBox hbControlBox_;

	Gtk::VBox vbTableBox_;
	Gtk::HBox hbCardBox_[4];

	Gtk::Label lblTableLabel_;
	Gtk::Frame frmTable_;

	Gtk::HBox hbPlayerBox_;
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

	
	void btnGameStartClicked();
	void btnGameEndClicked();
	void btnHandClicked(int i);

};

#endif