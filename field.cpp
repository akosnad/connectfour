#include "field.hpp"

#include <iostream>

using namespace std;
using namespace genv;

static const int wh = 36;
static const int nx = 7;
static const int ny = 6;

Field::Field(Container* parent, int x, int y, function<void(int x, int y)> on_try_drop)
    : Widget(parent, x, y, wh * nx, wh * ny), Container(),
    _active_player(0), _hovered_col(-1), _on_try_drop(on_try_drop) {
        _focus_on_hover = true;
        for(int i = 0; i < ny; i++) {
            vector<Cell*> row;
            for(int j = 0; j < nx; j++) {
                const int xx = _x + (j * wh);
                const int yy = _y + (i * wh);
                row.push_back(new Cell(this, xx, yy, wh, [this, i, j](){ handle_click(j, i); }));
            }
            _cells.push_back(row);
        }
}

void Field::draw() {
    if(_hovered_col >= 0) {
        gout << color(255, 255, 255) << move_to(_x + _hovered_col * wh, _y - wh) << box(wh, wh);
    }
    draw_children();
}

void Field::handle(event ev) {
    if(ev.type == ev_mouse) {
        if(is_selected(ev))
            _hovered_col = (ev.pos_x - _x) / wh;
        else
            _hovered_col = -1;
    }
    handle_children_events(ev);
}



int Field::next_empty(int cx) {
    int cy = -1;
    for(int i = 0; i < ny; i++) {
        if(_cells[i][cx]->get_color() != CellColor::unfilled)
            break;
        cy = i;
    }
    return cy;
}

void Field::handle_click(int cx, int cy) {
    int ne = next_empty(cx);
    if(ne == -1)
        return;

    _on_try_drop(cx, ne);
}

void Field::set_cell(int cx, int cy, CellColor color) {
    _cells[cy][cx]->set_color(color);
}

CellColor Field::get_cell(int cx, int cy) const {
    return _cells[cy][cx]->get_color();
}
