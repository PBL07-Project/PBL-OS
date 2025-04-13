#include "homepage.h"

HomePage::HomePage()
: Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10),
  m_title(),
  m_btnLogin("Login"),
  m_btnRegister("Register")
{
    set_border_width(20);
    
    // Setup the title with markup.
    m_title.set_halign(Gtk::ALIGN_CENTER);
    m_title.set_valign(Gtk::ALIGN_CENTER);
    m_title.set_margin_bottom(30);
    m_title.set_use_markup(true);
    m_title.set_markup("<span font='28' foreground='#FF4500'><b>DEEPCHAT</b></span>\n"
                       "<span font='16' foreground='#2E8B57'>A Realtime Messaging App with OS Level Fundamentals</span>");
    // Set widget names for CSS.
    m_title.set_name("homeTitle");
    m_btnLogin.set_name("loginButton");
    m_btnRegister.set_name("registerButton");
    
    pack_start(m_title, Gtk::PACK_SHRINK);
    pack_start(m_btnLogin, Gtk::PACK_SHRINK);
    pack_start(m_btnRegister, Gtk::PACK_SHRINK);
    
    m_btnLogin.signal_clicked().connect([this](){
         m_signal_show_login.emit();
    });
    m_btnRegister.signal_clicked().connect([this](){
         m_signal_show_register.emit();
    });
    
    show_all_children();
}

sigc::signal<void>& HomePage::signal_show_login() {
    return m_signal_show_login;
}

sigc::signal<void>& HomePage::signal_show_register() {
    return m_signal_show_register;
}