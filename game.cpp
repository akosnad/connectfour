#include "game.hpp"
#include <sstream>

using namespace std;
using namespace genv;

const int GAP = 24;
const int FIELD_X = 24;
const int FIELD_Y = 100;

Game::Game(Container* parent, int x, int y, int w, int h,
        function<void()> on_quit
) : Box(parent, x, y, w, h) {
    _focus_on_hover = true;
    quit_button = new Button(this, GAP, GAP, 100, 24, "Quit game", on_quit);
    field = new Field(this, FIELD_X, FIELD_Y, [this](int x, int y){ handle_cell_drop(x, y); });
    hovering_cell = new Sprite(this, FIELD_X, FIELD_Y - WH, WH, WH);
    hovering_cell->load_from_bitmap("./assets/d_red.bmp");
    status_text = new TextBox(this, GAP, FIELD_Y + WH * NY + GAP, 200, "");

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

void Game::change_player() {
    first_player = !first_player;
    update_status();
    if(first_player)
        hovering_cell->load_from_bitmap("./assets/d_red.bmp");
    else
        hovering_cell->load_from_bitmap("./assets/d_yellow.bmp");
}


bool Game::find_game_end_condition(int last_x, int last_y) {
    if(placed_so_far >= 7 * 6) {
        draw = true;
    } else if(check_matching_cells(last_x, last_y)) {
        won = true;
        update_status();
    }
    return won || draw;
}

bool Game::check_matching_cells(int x, int y) {
    return check_matching_cells_inner(x, y, 8, 0)       // horizontal
        || check_matching_cells_inner(x, y, 0, 8)       // vertical
        || check_matching_cells_inner(x, y, 8, 8)       // diagonal right-down
        || check_matching_cells_inner(x, y, 8, -8)      // diagonal right-up
        ;
}

bool Game::check_matching_cells_inner(int x, int y, int sx, int sy) {
    int dx = sx == 0 ? 0 : abs(sx) / sx;
    int dy = sy == 0 ? 0 : abs(sy) / sy;

    int x_start = x - sx / 2;
    int y_start = y - sy / 2;

    int count = 0;
    bool match = false;
    CellColor curr = player_color();

    for(int i = 0, j = 0; i <= abs(sx) && j <= abs(sy); i+=abs(dx), j+=abs(dy)) {
        int cx = x_start + i * dx;
        int cy = y_start + j * dy;
        if(cx >= 0 && cy >= 0 && cx < NX && cy < NY) {
            CellColor cell = field->get_cell(cx, cy);
            if(match && curr != cell) {
                match = false;
                count = 0;
            } else if(curr == cell) {
                match = true;
                count++;
                if(count == 4) return true;
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

void Game::handle(event ev) {
    if(ev.type == ev_mouse) {
        int col = (ev.pos_x - FIELD_X) / WH;
        if(col >= 0 && col < NX)
            hovering_cell->move(FIELD_X + col * WH, FIELD_Y - WH);
    }
    handle_children_events(ev);
}
