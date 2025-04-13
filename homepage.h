#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <sigc++/signal.h>

class HomePage : public Gtk::Box {
public:
    HomePage();
    virtual ~HomePage() = default;
    
    // Signal accessor functions.
    sigc::signal<void>& signal_show_login();
    sigc::signal<void>& signal_show_register();
    
protected:
    Gtk::Label m_title;
    Gtk::Button m_btnLogin;
    Gtk::Button m_btnRegister;
    
    // Private signal objects.
    sigc::signal<void> m_signal_show_login;
    sigc::signal<void> m_signal_show_register;
};

#endif // HOMEPAGE_H