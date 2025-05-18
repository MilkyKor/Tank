
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "widgets.hpp"
#include "game.hpp"

enum class State {
    StartMenu,
    Playing,
    Victory,
    Settings
};

class Display : public Widget {
public:
    Display(App*, int, int, int, int, Game*);
    void draw() override;
    void handle(genv::event ev) override;

private:
    Game* game;
    bool projectile_was_active = false;
    State game_state = State::StartMenu;
};

#endif
