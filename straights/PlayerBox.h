
#include <string>
#include <gtkmm.h>

/****************
 a wrapper class for player boxes
*****************/

class PlayerBox : public Gtk::Frame{
private:
	Gtk::VBox vbPlayerBox_;
	Gtk::Button btnPlayer_;
	Gtk::Label lblPlayerPoints_;
	Gtk::Label lblPlayerDiscards_;
	std::string sPlayerBtnContent_;
	int iPlayerPoints_;
	int iPlayerDiscards_;
	int iPlayerId_;
	void update();
public:
	PlayerBox();
	~PlayerBox();
	// mutators
	void setHumanPlayer();
	void setComputerPlayer();
	void setRangeBtn();
	void setRangeBtnDisabled();
	void setPlayerId(int i);
	void setPlayerPoints(int i);
	void setPlayerDiscard(int i);
	PlayerBox& operator= (const PlayerBox& );
	void playerBtnClicked();
};

