#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>

class View : public Gtk::Window{
public:
	View( Controller*, Model* );
	virtual ~View();
	virtual void update();

private:
	
}

#endif