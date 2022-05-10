#include "field.hpp"

#include <iostream>

using namespace std;
using namespace genv;

Field::Field(Container* parent, int x, int y, function<void(int x, int y)> on_try_drop)
    : Widget(parent, x, y, WH * NX, WH * NY), Container(),
    _on_try_drop(on_try_drop) {
        _focus_on_hover = true;
        for(int i = 0; i < NY; i++) {
            vector<Cell*> row;
            for(int j = 0; j < NX; j++) {
                const int xx = _x + (j * WH);
                const int yy = _y + (i * WH);
                row.push_back(new Cell(this, xx, yy, WH, [this, i, j](){ handle_click(j, i); }));
            }
            _cells.push_back(row);
        }
}

void Field::draw() {
    draw_children();
}

void Field::handle(event ev) {
    handle_children_events(ev);
}



int Field::next_empty(int cx) {
    int cy = -1;
    for(int i = 0; i < NY; i++) {
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
