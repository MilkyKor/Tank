#include "button.hpp"

using namespace genv;

Button::Button(App *parent, int x,int y,int sx,int sy,std::string label,std::function<void()> f)
        : Widget(parent,x,y,sx,sy),_label(label),_pushed(0), _f(f)
{}

void Button::draw()
{
    gout.load_font("LiberationSans-Regular", 30);

    gout << color(128,128,128) << move_to(_x, _y) << box(_size_x, _size_y)
         << move_to(_x + (_size_x - gout.twidth(_label)) / 2,
                    _y + (_size_y - (gout.cascent() + gout.cdescent()) / 2));



    if(_pushed)
    {
        gout <<color(255,255,255);
    }
    else
    {
        gout <<color(0,0,0);
    }

    gout << text(_label);
}

void Button::handle(event ev)
{
    if(ev.type == ev_mouse)
    {
        if(ev.button == btn_left)
        {
            push();
            action();
        }
        else if(ev.button == -btn_left)
        {
            unpush();
        }
    }
}

void Button::action(){
    _f();
}
void Button::push()
{
    _pushed = 1;
}
void Button::unpush()
{
    _pushed = 0;
}
Button::~Button()
{}
