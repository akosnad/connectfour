#include "cell.hpp"

using namespace genv;
using namespace std;

Cell::Cell(Container* parent, int x, int y, int wh, function<void()> on_click)
    : Widget(parent, x, y, wh, wh), _state(0), _on_click(on_click) {
}

void Cell::draw() {
    gout << color(255, 255, 255) << move_to(_x, _y) << box(_w, _h);
    if(_state == 1)
        gout << color(255, 63, 63);
    else if(_state == 2)
        gout << color(255, 255, 63);
    else
        gout << color(63, 63, 63);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4, _h - 4);
}

void Cell::handle(event ev) {
    if(ev.type == ev_mouse && ev.button == -btn_left) {
        if(_state == 0)
            _state = 1;
        else if(_state == 1)
            _state = 2;
        else
            _state = 0;

        _on_click();
    }
}
