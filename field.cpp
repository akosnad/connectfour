#include "field.hpp"

#include <iostream>

using namespace std;

static const int wh = 24;
static const int nx = 7;
static const int ny = 6;

Field::Field(Container* parent, int x, int y)
    : Widget(parent, x, y, wh * nx, wh * ny), Container() {
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

void Field::handle_click(int x, int y) {
    cout << "click: " << x << ":" << y << " - " << _cells[y][x]->get_state() << endl;
}

void Field::draw() {
    draw_children();
}

void Field::handle(genv::event ev) {
    handle_children_events(ev);
}
