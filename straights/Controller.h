#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

class Model;

/*********************************

	MVC - Controller

**********************************/

class Controller{
private:
	Model *model_;
public:
	Controller( Model* );	// constructor
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed); // gamestart mehtod
	void play(int cardIndex);	// play method used between model and view
	void rageQuit();	// rage quit button clicked
	void endGame();		// end game button clicked
};

#endif