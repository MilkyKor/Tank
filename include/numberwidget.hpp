#ifndef NUMBERWIDGET_HPP
#define NUMBERWIDGET_HPP

#include "widgets.hpp"

class NumberWidget : public Widget {
    int value, min_val, max_val;
    int step = 1;
public:
    NumberWidget(int x, int y, int sx, int sy, int min_val, int max_val, int start_val);
    void draw() override;
    void handle(genv::event ev) override;

    int get_value() const;
};

#endif
