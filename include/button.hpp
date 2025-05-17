#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widgets.hpp"

#include "functional"

class Button : public Widget
{
    public:
        Button(App *, int,int,int,int,std::string,std::function<void()>);
        virtual ~Button();

        virtual void draw() override;
        virtual void handle(genv::event ev) override;

        void push();
        void unpush();

        void action();
    protected:
        std::string _label;
        bool _pushed;
        std::function<void()> _f;
    private:
};

#endif // BUTTON_HPP
