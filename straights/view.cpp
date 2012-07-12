#include "observer.h"
#include "subject.h"
#include "DeckGUI.h"
#include "view.h"

using namespace std;

View::View() :vbMainPanel(false, 10), hbControlBox(true, 10), 
		vbTableBox(true, 10), hbClubBox(true, 10), hbDiamondbBox(true, 10), 
		hbHeartBox(true, 10), hbSpadeBox(true, 10), lblTableLabel("Cards on Table"),frmTable("Cards on Table"),  
		hbPlayerBox(true, 10), vbPlayer1(true, 10), vbPlayer2(true, 10),
		vbPlayer3(true, 10), vbPlayer4(true, 10),
		hbHandBox(true, 10),
		btGameStart("Game Start"), btGameEnd("Game End!"), enSeed(){
	set_title("Straights");
	set_border_width(20);
	add(vbMainPanel);

	vbMainPanel.add(hbControlBox);
	vbMainPanel.add(frmTable);
	vbMainPanel.add(hbPlayerBox);
	vbMainPanel.add(hbHandBox);
	
	hbControlBox.add(btGameStart);
	hbControlBox.add(enSeed);
	hbControlBox.add(btGameEnd);
	
	lblTableLabel.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
	frmTable.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
	frmTable.add(vbTableBox);

	vbTableBox.add(hbClubBox);
	vbTableBox.add(hbDiamondbBox);
	vbTableBox.add(hbHeartBox);
	vbTableBox.add(hbSpadeBox);
	
	hbPlayerBox.add(vbPlayer1);
	hbPlayerBox.add(vbPlayer2);
	hbPlayerBox.add(vbPlayer3);
	hbPlayerBox.add(vbPlayer4);
	

	show_all();
}

View::~View(){}

void View::update(){

}