#include "login.h"
#include "database.h"
#include <gtkmm/messagedialog.h>

Login::Login()
: Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10),
  m_btnLogin("Login"),
  m_btnBack("Back")
{
    set_border_width(20);
    
    m_entryUsername.set_placeholder_text("Username");
    m_entryPassword.set_placeholder_text("Password");
    m_entryPassword.set_visibility(false);
    
    // Set widget names for CSS.
    m_entryUsername.set_name("loginEntry");
    m_entryPassword.set_name("loginEntry");
    m_btnLogin.set_name("loginButton");
    m_btnBack.set_name("backButton");

    pack_start(m_entryUsername, Gtk::PACK_SHRINK);
    pack_start(m_entryPassword, Gtk::PACK_SHRINK);
    pack_start(m_btnLogin, Gtk::PACK_SHRINK);
    pack_start(m_btnBack, Gtk::PACK_SHRINK);
    
    m_btnLogin.signal_clicked().connect([this](){
         Database db;
         bool success = db.authenticateUser(m_entryUsername.get_text(), m_entryPassword.get_text());
         std::string message = "Login " + std::string(success ? "successful!" : "failed.");
         Gtk::MessageDialog dialog(message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
         dialog.run();
         // On success, transition to your chat interface (not implemented here).
    });
    
    m_btnBack.signal_clicked().connect([this](){
         m_signal_show_home.emit();
    });
    
    show_all_children();
}

sigc::signal<void>& Login::signal_show_home() {
    return m_signal_show_home;
}