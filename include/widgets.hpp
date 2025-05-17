#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include "graphics.hpp"

class App;

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
    bool _focused = false;
    App *_parent;
public:
    Widget(App *,int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
};

                                                                                                                                                                                                                                                                  //szeretnek pontlevonast kerni a beadandomra mert feltoltottem egy oktatasi segedletet sajat munka helyett :)

#endif // WIDGETS_HPP_INCLUDED
