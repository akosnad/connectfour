#ifndef _FIELD_H
#define _FIELD_H

#include "widgets.hpp"
#include "container.hpp"
#include "cell.hpp"
#include <vector>

class Field : public Widget, public Container {
    std::vector<std::vector<Cell*>> _cells;
    int _active_player;
public:
    Field(Container* parent, int x, int y);
    virtual void draw();
    virtual void handle(genv::event);
    void handle_click(int x, int y);
};

#endif
