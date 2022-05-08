#include "window.hpp"
#include "textbox.hpp"
#include "button.hpp"
#include "box.hpp"
#include "field.hpp"

#include <functional>
#include <iostream>
#include <sstream>

using namespace genv;
using namespace std;

static const int W = 800;
static const int H = 600;

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

class Game : public Box {
    Button *quit_button;
    Field *field;
    TextBox *status_text;
    bool first_player;
public:
    Game(Container* parent,
            function<void()> on_quit
    ) : Box(parent, 0, 0, W, H) {
        _focus_on_hover = true;
        quit_button = new Button(this, 24, 24, 100, 24, "Quit game", on_quit);
        field = new Field(this, 200, 200, [this](int x, int y){ handle_cell_drop(x, y); });
        status_text = new TextBox(this, 260, 24, 200, "");

        first_player = true;
        update_status();
    }

    inline void change_player() {
        first_player = !first_player;
        update_status();
    }

    inline CellColor player_color() {
        if(first_player)
            return CellColor::red;
        return CellColor::yellow;
    }

    void handle_cell_drop(int x, int y) {
        field->set_cell(x, y, player_color());
        change_player();
    }

    void update_status() {
        stringstream ss;
        ss << "Current player: ";
        if(first_player)
            ss << "First";
        else
            ss << "Second";
        status_text->set_text(ss.str());
    }
};

class MainWindow : public Window {
    MainMenu *main_menu = nullptr;
    Game *game = nullptr;

    void new_game() {
        if(main_menu)
            delete main_menu;

        game = new Game(this, [this](){ show_main_menu();});
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
