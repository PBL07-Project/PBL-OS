#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "db/db.h"

class MyWindow : public Gtk::Window {
public:
    MyWindow() {
        set_title("Chat App - Login/Register");
        set_default_size(400, 200);
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.example.chatapp");
    Database db;
    if (!db.connect("sql12.freesqldatabase.com", "sql12772615", "96Q3vgiAiB", "sql12772615", 3306)) {
        return 1;
    }
    MyWindow window;
    return app->run(window);
}
