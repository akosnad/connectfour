#ifndef _CELL_H
#define _CELL_H

#include "widgets.hpp"
#include <functional>

enum class CellColor {
    red, yellow,
    unfilled
};

class Cell : public Widget {
    CellColor _color;
    std::function<void()> _on_click;
public:
    Cell(Container* parent, int x, int y, int wh, std::function<void()> on_click);
    virtual void draw();
    virtual void handle(genv::event);
    CellColor get_color() const { return _color; }
    void set_color(CellColor color) { _color = color; }
};

#endif
