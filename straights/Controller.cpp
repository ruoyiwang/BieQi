#include "Controller.h"
#include "model.h"

Controller::Controller(Model* m): model_(m){
}

void Controller::gameStart(bool bHuman1, bool bHuman2, bool bHuman3, bool bHuman4, int seed){
	model_->gameStart(bHuman1,bHuman2,bHuman3,bHuman4,seed);
}