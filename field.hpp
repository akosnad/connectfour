#ifndef _FIELD_H
#define _FIELD_H

#include "widgets.hpp"
#include "container.hpp"
#include "cell.hpp"
#include <vector>

const int WH = 36;
const int NX = 7;
const int NY = 6;

class Field : public Widget, public Container {
    std::vector<std::vector<Cell*>> _cells;
    int _active_player;
    int _hovered_col;
    std::function<void(int x, int y)> _on_try_drop;
public:
    Field(Container* parent, int x, int y, std::function<void(int, int)> on_try_drop);
    virtual void draw();
    virtual void handle(genv::event);

    void handle_click(int x, int y);
    int next_empty(int col);
    void set_cell(int x, int y, CellColor);
    CellColor get_cell(int x, int y) const;
};

#endif
