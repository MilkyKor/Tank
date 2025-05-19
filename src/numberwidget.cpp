#include "numberwidget.hpp"
#include "graphics.hpp"
using namespace genv;

NumberWidget::NumberWidget(int x, int y, int sx, int sy, int minv, int maxv, int start_val)
    : Widget(x, y, sx, sy), min_val(minv), max_val(maxv), value(start_val) {}

void NumberWidget::draw() {
    gout << move_to(_x, _y) << color(220, 220, 220) << box(_size_x, _size_y);
    gout << move_to(_x + 10, _y + 10) << color(0, 0, 0) << text(std::to_string(value));

    gout << move_to(_x + _size_x - 45, _y) << color(200, 100, 100) << box(20, _size_y);
    gout << move_to(_x + _size_x - 40, _y + 10) << color(0, 0, 0) << text("-");

    gout << move_to(_x + _size_x - 20, _y) << color(100, 200, 100) << box(20, _size_y);
    gout << move_to(_x + _size_x - 15, _y + 10) << color(0, 0, 0) << text("+");
}

void NumberWidget::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        int mx = ev.pos_x;
        int my = ev.pos_y;

        if (mx >= _x + _size_x - 45 && mx < _x + _size_x - 25 && is_selected(mx, my)) {
            if (value > min_val) value--;
        }
        else if (mx >= _x + _size_x - 20 && mx < _x + _size_x && is_selected(mx, my)) {
            if (value < max_val) value++;
        }
    }

    if (ev.type == ev_key) {
        int s = (ev.keycode == key_pgup || ev.keycode == key_pgdn) ? 10 : 1;

        if (ev.keycode == key_up || ev.keycode == key_pgup) {
            value = std::min(value + s, max_val);
        } else if (ev.keycode == key_down || ev.keycode == key_pgdn) {
            value = std::max(value - s, min_val);
        }
    }
}

int NumberWidget::get_int_value() const {
    return value;
}
