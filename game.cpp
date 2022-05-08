#include "game.hpp"
#include <sstream>

using namespace std;

Game::Game(Container* parent, int x, int y, int w, int h,
        function<void()> on_quit
) : Box(parent, x, y, w, h) {
    _focus_on_hover = true;
    quit_button = new Button(this, 24, 24, 100, 24, "Quit game", on_quit);
    field = new Field(this, 200, 200, [this](int x, int y){ handle_cell_drop(x, y); });
    status_text = new TextBox(this, 260, 24, 200, "");

    first_player = true;
    won = false;
    draw = false;
    placed_so_far = 0;
    update_status();
}

void Game::handle_cell_drop(int x, int y) {
    if(won || draw)
        return;

    field->set_cell(x, y, player_color());
    placed_so_far++;
    if(!find_game_end_condition(x, y))
        change_player();
}

bool Game::find_game_end_condition(int last_x, int last_y) {
    if(placed_so_far >= 7 * 6) {
        draw = true;
    } else {
        // horizontal
        int y_start = last_y - 3 > 0 ? last_y - 3 : 0;
        int y_end   = last_y + 3 < 6 ? last_y + 3 : 6;
        for(int y = y_start; y < y_end; y++) {
            int count = 0;
            int x_start = last_x - 3 > 0 ? last_x - 3 : 0;
            int x_end   = last_x + 3 < 7 ? last_x + 3 : 7;
            for(int x = x_start; x < x_end; x++) {
                if(field->get_cell(x, y) == player_color())
                    count++;
                if(count >= 4) {
                    won = true;
                    update_status();
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::update_status() {
    stringstream ss;
    if(draw)
        ss << "It's a draw!";
    else {
        if(!won)
            ss << "Current player: ";
        if(first_player)
            ss << "First";
        else
            ss << "Second";
        if(won)
            ss << " player wins!";
    }

    status_text->set_text(ss.str());
}
