#include "cell.hpp"

using namespace genv;
using namespace std;

Cell::Cell(Container* parent, int x, int y, int wh, function<void()> on_click)
    : Sprite(parent, x, y, wh, wh), _color(CellColor::unfilled), _on_click(on_click) {
        load_from_bitmap("./assets/unfilled.bmp");
}

void Cell::set_color(CellColor color) {
    if(color == CellColor::red)
        load_from_bitmap("./assets/red.bmp");
    else if(color == CellColor::yellow)
        load_from_bitmap("./assets/yellow.bmp");
    else
        load_from_bitmap("./assets/unfilled.bmp");

    _color = color;
}

void Cell::handle(event ev) {
    if(ev.type == ev_mouse && ev.button == -btn_left) {
        _on_click();
    }
}
