#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "Observer.h"

class View : public Gtk::Window, public Observer{
public:
	View();
	virtual ~View();
	virtual void update();

private:
	Gtk::VBox vbMainPanel;

	Gtk::HBox hbControlBox;

	Gtk::VBox vbTableBox;
	Gtk::HBox hbClubBox;
	Gtk::HBox hbDiamondbBox;
	Gtk::HBox hbHeartBox;
	Gtk::HBox hbSpadeBox;

	Gtk::Label lblTableLabel;
	Gtk::Frame frmTable;

	Gtk::HBox hbPlayerBox;

	Gtk::VBox vbPlayer1;
	Gtk::VBox vbPlayer2;
	Gtk::VBox vbPlayer3;
	Gtk::VBox vbPlayer4;

	Gtk::HBox hbHandBox;

	Gtk::Button btGameStart;
	Gtk::Entry enSeed;
	Gtk::Button btGameEnd;
};

#endif