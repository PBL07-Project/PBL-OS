#include <gtkmm.h>
#include "homepage.h"
#include "login.h"
#include "register.h"
#include <iostream>

class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow();
    virtual ~MainWindow() = default;
private:
    Gtk::Box m_VBox;
    Gtk::Stack m_Stack;
    Gtk::StackSwitcher m_Switcher;

    // Pages
    HomePage m_HomePage;
    Login m_LoginPage;
    Register m_RegisterPage;
};

MainWindow::MainWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_HomePage(),
  m_LoginPage(),
  m_RegisterPage()
{
    set_title("DeepChat: A Realtime Messaging App with OS Level Fundamentals");
    set_default_size(600, 400);

    add(m_VBox);

    // Load CSS for styling
    auto cssProvider = Gtk::CssProvider::create();
    try {
        cssProvider->load_from_path("style.css");
    }
    catch (const Glib::Error& ex) {
        std::cerr << "Failed to load CSS: " << ex.what() << std::endl;
    }
    Gtk::StyleContext::add_provider_for_screen(
        Gdk::Screen::get_default(),
        cssProvider,
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    // Place the StackSwitcher on top of the window.
    m_VBox.pack_start(m_Switcher, Gtk::PACK_SHRINK);
    m_VBox.pack_start(m_Stack);

    // Add pages to the stack with identifiers.
    m_Stack.add(m_HomePage, "homepage");
    m_Stack.add(m_LoginPage, "login");
    m_Stack.add(m_RegisterPage, "register");

    // The StackSwitcher automatically controls the stack.
    m_Switcher.set_stack(m_Stack);

    // Connect signals from pages to switch views.
    m_HomePage.signal_show_login().connect([this](){
         m_Stack.set_visible_child("login");
    });
    m_HomePage.signal_show_register().connect([this](){
         m_Stack.set_visible_child("register");
    });
    m_LoginPage.signal_show_home().connect([this](){
         m_Stack.set_visible_child("homepage");
    });
    m_RegisterPage.signal_show_home().connect([this](){
         m_Stack.set_visible_child("homepage");
    });

    show_all_children();
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.deepchat");
    MainWindow win;
    return app->run(win);
}