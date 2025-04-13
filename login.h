#ifndef LOGIN_H
#define LOGIN_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <sigc++/signal.h>
#include <string>

class Login : public Gtk::Box {
public:
    Login();
    virtual ~Login() = default;
    // Signal accessor to return to the home page.
    sigc::signal<void>& signal_show_home();
protected:
    Gtk::Entry m_entryUsername;
    Gtk::Entry m_entryPassword;
    Gtk::Button m_btnLogin;
    Gtk::Button m_btnBack;
    
    sigc::signal<void> m_signal_show_home;
};

#endif // LOGIN_H