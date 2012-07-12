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
	Gtk::HBox hbCardBox[4];

	Gtk::Label lblTableLabel;
	Gtk::Frame frmTable;

	Gtk::HBox hbPlayerBox;
	Gtk::Frame frmPlayer[4];

	Gtk::VBox vbPlayer[4];

	Gtk::Button btnPlayer[4];
	Gtk::Label lblPlayerPoints[4];
	Gtk::Label lblPlayerDiscards[4];

	Gtk::Frame frmHand;
	Gtk::HBox hbHandBox;

	Gtk::Button btnGameStart;
	Gtk::Entry enSeed;
	Gtk::Button btnGameEnd;
};

#endif