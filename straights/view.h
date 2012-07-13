#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "PlayerBox.h"
#include "Observer.h"
#include "DeckGUI.h"

class View : public Gtk::Window, public Observer{
public:
	View();
	virtual ~View();
	virtual void update();

private:
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
	Gtk::Button btnGameEnd;

	DeckGUI Deck_;
	
	Gtk::Image imgClubs_[13];
	Gtk::Image imgDiamonds_[13];
	Gtk::Image imgHearts_[13];
	Gtk::Image imgSpades_[13];

	Gtk::Image imgHand_[13];
	Gtk::Button btnHand_[13];
};

#endif