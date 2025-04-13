#include "register.h"
#include "database.h"
#include <gtkmm/messagedialog.h>

Register::Register()
: Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10),
  m_btnRegister("Register"),
  m_btnBack("Back")
{
    set_border_width(20);
    
    m_entryUsername.set_placeholder_text("Username");
    m_entryEmail.set_placeholder_text("Email");
    m_entryPassword.set_placeholder_text("Password");
    m_entryPassword.set_visibility(false);
    m_entryConfirmPassword.set_placeholder_text("Confirm Password");
    m_entryConfirmPassword.set_visibility(false);

    // Set widget names for CSS.
    m_entryUsername.set_name("registerEntry");
    m_entryEmail.set_name("registerEntry");
    m_entryPassword.set_name("registerEntry");
    m_entryConfirmPassword.set_name("registerEntry");
    m_btnRegister.set_name("registerButton");
    m_btnBack.set_name("backButton");

    pack_start(m_entryUsername, Gtk::PACK_SHRINK);
    pack_start(m_entryEmail, Gtk::PACK_SHRINK);
    pack_start(m_entryPassword, Gtk::PACK_SHRINK);
    pack_start(m_entryConfirmPassword, Gtk::PACK_SHRINK);
    pack_start(m_btnRegister, Gtk::PACK_SHRINK);
    pack_start(m_btnBack, Gtk::PACK_SHRINK);
    
    m_btnRegister.signal_clicked().connect([this](){
         if(m_entryPassword.get_text() != m_entryConfirmPassword.get_text()){
             Gtk::MessageDialog dialog("Passwords do not match.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
             dialog.run();
             return;
         }
         Database db;
         bool success = db.registerUser(m_entryUsername.get_text(), m_entryPassword.get_text(), m_entryEmail.get_text());
         std::string message = "Registration " + std::string(success ? "successful!" : "failed. Try a different username.");
         Gtk::MessageDialog dialog(message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
         dialog.run();
    });
    
    m_btnBack.signal_clicked().connect([this](){
         m_signal_show_home.emit();
    });
    
    show_all_children();
}

sigc::signal<void>& Register::signal_show_home() {
    return m_signal_show_home;
}