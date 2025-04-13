#ifndef REGISTER_H
#define REGISTER_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <sigc++/signal.h>
#include <string>

class Register : public Gtk::Box {
public:
    Register();
    virtual ~Register() = default;
    // Signal accessor to return to home page.
    sigc::signal<void>& signal_show_home();
protected:
    Gtk::Entry m_entryUsername;
    Gtk::Entry m_entryEmail;
    Gtk::Entry m_entryPassword;
    Gtk::Entry m_entryConfirmPassword;
    Gtk::Button m_btnRegister;
    Gtk::Button m_btnBack;
    
    sigc::signal<void> m_signal_show_home;
};

#endif // REGISTER_H