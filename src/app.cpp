#include "app.hpp"

#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;

App::App(int w, int h)
{
    gout.open(w,h);
}

void App::register_widget(Widget * widget)
{
    widgets.push_back(widget);
}

void App::event_loop()
{
    gin.timer(30);
    event ev;
    int focus = -1;
    while (gin >> ev || true)  // Végtelen ciklus (még ha nincs esemény is)
    {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            for (size_t i = 0; i < widgets.size(); ++i) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    focus = i;
                }
            }
        }

        if (focus != -1) {
            widgets[focus]->handle(ev);
        }

        // Frissítés mindig
        gout << color(255,255,255) << move_to(0,0) << box(gout.twidth(" "), gout.cdescent()); // clear

        for (Widget* w : widgets) {
            w->draw();
        }
        gout << refresh;
    }
}
