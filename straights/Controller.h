#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

class Model;

class Controller{
private:
	Model *model_;
public:
	Controller( Model* );
	void gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed);
	void play(int cardIndex);
	
};

#endif