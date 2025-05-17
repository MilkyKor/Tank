#ifndef MENU_HPP
#define MENU_HPP
#include "widgets.hpp"

class Menu : public Widget {
protected:
    std::vector<std::string> _items;
    int _selected;
    int _visible_count;
    int _scroll;

public:
    Menu(App *,int x, int y, int sx, int sy, std::vector<std::string>& items, int visible_count = 4);
    void draw() override;
    void handle(genv::event ev) override;
    int get_value() const;
    void update(std::vector<std::string>);
};

#endif // MENU_HPP
