#include "Controller.h"
#include "model.h"

Controller::Controller(Model* m): model_(m){
}
// gamestart mehtod
void Controller::gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed){
	model_->gameStart(bHuman1,bHuman2,bHuman3,bHuman4,seed);
}

// play method used between model and view
void Controller::play(int cardIndex){
	model_->gamePlay(cardIndex);
}

// rage quit button clicked
void Controller::endGame(){
	model_->endGame();
}

// end game button clicked
void Controller::rageQuit(){
	model_->rageQuit();
}
