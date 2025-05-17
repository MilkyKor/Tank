#ifndef APP_HPP
#define APP_HPP

#include <vector>

class Widget;

class App
{
    public:
        App(int,int);

        void register_widget(Widget *);
        void event_loop();
    protected:
     std::vector<Widget*> widgets;
};

#endif // APP_HPP
