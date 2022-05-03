#ifndef _CELL_H
#define _CELL_H

#include "widgets.hpp"
#include <functional>

class Cell : public Widget {
    int _state;
    std::function<void()> _on_click;
public:
    Cell(Container* parent, int x, int y, int wh, std::function<void()> on_click);
    virtual void draw();
    virtual void handle(genv::event);
    int get_state() const { return _state; }
};

#endif
