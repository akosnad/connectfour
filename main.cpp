#include "window.hpp"
#include "textbox.hpp"
#include "button.hpp"
#include "box.hpp"
#include "game.hpp"

#include <functional>

using namespace genv;
using namespace std;

static const int W = 400;
static const int H = 400;

class MainMenu : public Box {
    TextBox* title;
    Button* new_game_button;
    Button* exit_button;
public:
    MainMenu(Container* parent,
            function<void()> on_start,
            function<void()> on_exit
    ) : Box(parent, 0, 0, W, H) {
        _focus_on_hover = true;
        const string t =  "Connect Four by nadak";
        title = new TextBox(this, W / 2 - gout.twidth(t) / 2, 32, 250, t);
        new_game_button = new Button(this, W / 2 - 24, 100, 48, 24, "Start", on_start);
        exit_button = new Button(this, W / 2 - 24, 150, 48, 24, "Exit", on_exit);
    }
};

class MainWindow : public Window {
    MainMenu *main_menu = nullptr;
    Game *game = nullptr;

    void new_game() {
        if(main_menu)
            delete main_menu;

        game = new Game(this, 0, 0, W, H, [this](){ show_main_menu();});
    }
    void show_main_menu() {
        if(game)
            delete game;

        main_menu = new MainMenu(this, [this](){ new_game(); }, [](){ exit(0); });
    }
public:
    MainWindow() : Window(W, H) {
        show_main_menu();
    }
    void event_handler(event ev) {}
};

int main() {
    MainWindow mw;
    return mw.event_loop();
}
