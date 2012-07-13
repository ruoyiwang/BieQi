#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>



#include <gtkmm/main.h>

#include "view.h"
#include "Model.h"
#include "Controller.h"

using namespace std;

int main( int argc, char * argv[] ){
	Gtk::Main  kit( argc, argv );
	Model model;                          // Create model
    Controller controller( &model );      // Create controller
	View view( &controller, &model );     // Create the view -- is passed handle to controller and model
	Gtk::Main::run(view);

	return 0;

}