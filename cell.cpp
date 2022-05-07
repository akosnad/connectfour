#include "cell.hpp"

using namespace genv;
using namespace std;

Cell::Cell(Container* parent, int x, int y, int wh, function<void()> on_click)
    : Widget(parent, x, y, wh, wh), _color(CellColor::unfilled), _on_click(on_click) {
}

void Cell::draw() {
    gout << color(255, 255, 255) << move_to(_x, _y) << box(_w, _h);
    if(_color == CellColor::red)
        gout << color(255, 63, 63);
    else if(_color == CellColor::yellow)
        gout << color(255, 255, 63);
    else if(_color == CellColor::unfilled)
        gout << color(63, 63, 63);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4, _h - 4);
}

void Cell::handle(event ev) {
    if(ev.type == ev_mouse && ev.button == -btn_left) {
        _on_click();
    }
}
