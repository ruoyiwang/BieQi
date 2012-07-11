//$Id: examplewindow.h 705 2006-07-19 02:55:32Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window {
public:
	ExampleWindow();
	virtual ~ExampleWindow();
	
protected:
		virtual void register_stock_items();
	virtual void add_stock_item(const Glib::RefPtr<Gtk::IconFactory>& factory,
								const std::string& filepath,
								const Glib::ustring& id, const Glib::ustring& label);
private:
	bool m_button_state;
	
	//Signal handlers:
	virtual void on_action_file_new();
	virtual void on_action_file_quit();
	virtual void on_action_others();
	virtual void on_button_click();
	
	//Child widgets:
	Gtk::VBox                      m_Box;
	Gtk::Button                    m_button;
	Glib::RefPtr<Gtk::UIManager>   m_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	Glib::RefPtr<Gtk::Action>      m_refActionFileMenu;        // Used to enable/disable the player menu.
};

#endif //GTKMM_EXAMPLEWINDOW_H
