#ifndef _GAME_H
#define _GAME_H

#include "box.hpp"
#include "button.hpp"
#include "field.hpp"
#include "textbox.hpp"
#include <functional>

class Game : public Box {
    Button *quit_button;
    Field *field;
    Sprite *hovering_cell;
    TextBox *status_text;
    bool first_player, won, draw;
    int placed_so_far;

    inline CellColor player_color() {
        if(first_player)
            return CellColor::red;
        return CellColor::yellow;
    }

    void change_player();
    void handle_cell_drop(int x, int y);
    bool check_matching_cells_inner(int x, int y, int sx, int sy);
    bool check_matching_cells(int last_x, int last_y);
    bool find_game_end_condition(int last_x, int last_y);
    void update_status();
public:
    Game(Container* parent, int x, int y, int w, int h,
            std::function<void()> on_quit
    );
    virtual void handle(genv::event ev);
};

#endif
