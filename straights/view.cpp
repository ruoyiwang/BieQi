#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "observer.h"
#include "subject.h"
#include "DeckGUI.h"
#include "view.h"

using namespace std;

View::View() :vbMainPanel(false, 10), hbControlBox(true, 10), 
		vbTableBox(true, 10), lblTableLabel("Cards on Table"),frmTable("Cards on Table"),  
		hbPlayerBox(true, 10),	hbHandBox(true, 10), frmHand("Your Hand"),
		btnGameStart("Game Start"), btnGameEnd("Game End!"), enSeed(){
	set_title("Straights");
	set_border_width(20);
	add(vbMainPanel);

	vbMainPanel.add(hbControlBox);
	vbMainPanel.add(frmTable);
	vbMainPanel.add(hbPlayerBox);
	vbMainPanel.add(frmHand);
	frmHand.add(hbHandBox);

	hbControlBox.add(btnGameStart);
	hbControlBox.add(enSeed);
	hbControlBox.add(btnGameEnd);
	
	lblTableLabel.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	frmTable.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	frmTable.add(vbTableBox);

	for (int i = 0; i < 4; i++){
		vbTableBox.add(hbCardBox[i]);
		hbPlayerBox.add(frmPlayer[i]);
		frmPlayer[i].add(vbPlayer[i]);
		vbPlayer[i].add(btnPlayer[i]);
		btnPlayer[i].set_label("Human");
		vbPlayer[i].add(lblPlayerPoints[i]);
		lblPlayerPoints[i].set_label("0 points");
		vbPlayer[i].add(lblPlayerDiscards[i]);
		lblPlayerDiscards[i].set_label("0 discards");

		char buffer [33];
		itoa (i,buffer,10);
		string temp = buffer;
		string in = "Player " + temp;
		frmPlayer[i].set_label(in);
	}

	show_all();
}

View::~View(){}

void View::update(){

}