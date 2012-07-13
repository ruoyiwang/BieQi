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
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed); // gamestart mehtods
	void play(int cardIndex);
	void rageQuit();
	void endGame();
};

#endif