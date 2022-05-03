#include "window.hpp"
#include "textbox.hpp"
#include "button.hpp"
#include "box.hpp"

#include <functional>
#include <iostream>

using namespace genv;
using namespace std;

static const int W = 800;
static const int H = 600;

class StartupBox : public Box {
    TextBox* title;
    Button* new_game_button;
    Button* exit_button;
public:
    StartupBox(Container* parent,
            function<void()> on_start,
            function<void()> on_exit
    ) : Box(parent, 0, 0, W, H) {
        const string t =  "Connect Four by nadak";
        title = new TextBox(this, W / 2 - gout.twidth(t) / 2, 32, 250, t);
        new_game_button = new Button(this, W / 2 - 24, 100, 48, 24, "Start", on_start);
        exit_button = new Button(this, W / 2 - 24, 150, 48, 24, "Exit", on_exit);
    }
};

class GameBox : public Box {
    Button *quit_button;
public:
    GameBox(Container* parent,
            function<void()> on_quit
    ) : Box(parent, 0, 0, W, H) {
        quit_button = new Button(this, 24, 24, 100, 24, "Quit game", on_quit);
    }
};

class MainWindow : public Window {
    StartupBox *startup_box = nullptr;
    Box *game_box = nullptr;

    void new_game() {
        if(startup_box)
            delete startup_box;

        game_box = new GameBox(this, [this](){ main_menu();});
    }
    void main_menu() {
        if(game_box)
            delete game_box;

        startup_box = new StartupBox(this, [this](){ new_game(); }, [](){ exit(0); });
    }
public:
    MainWindow() : Window(W, H) {
        main_menu();
    }
    void event_handler(event ev) {}
};

int main() {
    MainWindow mw;
    return mw.event_loop();
}
