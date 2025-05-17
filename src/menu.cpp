#include "menu.hpp"
#include "graphics.hpp"
#include "app.hpp"
using namespace genv;

Menu::Menu(App *parent,int x, int y, int sx, int sy, std::vector<std::string>& items, int visible_count)
    : Widget(parent,x, y, sx, sy), _items(items), _selected(0), _visible_count(visible_count), _scroll(0)
    {}

void Menu::draw() {
    gout << color(220, 220, 220) << move_to(_x, _y) << box(_size_x, _size_y);

    int item_height = _size_y / _visible_count;
    for (int i = 0; i < _visible_count; ++i) {
        int index = _scroll + i;
        if (index >= int(_items.size())) break;

        if (index == _selected) {
            gout << color(100, 150, 255);
        } else {
            gout << color(240, 240, 240);
        }

        gout << move_to(_x, _y + i * item_height) << box(_size_x, item_height);
        gout << color(0, 0, 0) << move_to(_x + 5, _y + i * item_height + item_height / 2 + 5)
             << text(_items[index]);
    }
}

void Menu::handle(event ev) {
    int item_height = _size_y / _visible_count;

    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        int rel_y = ev.pos_y - _y;
        int clicked_index = rel_y / item_height + _scroll;
        if (clicked_index >= 0 && clicked_index < int(_items.size())) {
            _selected = clicked_index;
        }
    }

    if (ev.type == ev_key) {
        if (ev.keycode == key_up && _selected > 0) {
            _selected--;
            if (_selected < _scroll) _scroll = _selected;
        }
        if (ev.keycode == key_down && _selected + 1 < int(_items.size())) {
            _selected++;
            if (_selected >= _scroll + _visible_count) _scroll = _selected - _visible_count + 1;
        }
    }
}

void Menu::update(std::vector<std::string> v) {
    _items = v;
    _selected = 0;
    _scroll = 0;
}
int Menu::get_value() const {
    if (_items.empty()) return -1;
    return _selected;
}
