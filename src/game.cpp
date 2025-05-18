#include "game.hpp"
#include <cmath>

Game::Game()
    : players{ Player({100, 555}, 45), Player({650, 555}, 135) },current(0), active(false), gravity(0.4), wind(0)
{

}

Player* Game::get_current_player() {
    return &players[current];
}

Player* Game::get_other_player() {
    return &players[1 - current];
}

void Game::shoot() {
    Player* p = get_current_player();
    float rad = p->get_angle() * 3.14 / 180;
    velocity = { p->get_power() * std::cos(rad), -p->get_power() * std::sin(rad) };
    projectile_pos = p->get_barrel_exit();
    active = true;
}

Vec2 Game::get_projectile_pos() {
    if (!active) return {-1, -1};

    // Elõzõ pozíció elmentése az interpolációhoz (ha késõbb finomítani akarjuk)
    Vec2 prev_pos = projectile_pos;

    // Mozgás frissítése
    projectile_pos.x += velocity.x + wind;
    projectile_pos.y += velocity.y;
    velocity.y += gravity;

    // Ütközés vizsgálat - ha eltalálja az ellenfelet
    Vec2 opp_pos = get_other_player()->get_position();

    // hit box
    bool hit_x = projectile_pos.x >= opp_pos.x  && projectile_pos.x <= opp_pos.x + 50;
    bool hit_y = projectile_pos.y >= opp_pos.y && projectile_pos.y <= opp_pos.y + 20;

    if (hit_x && hit_y) {
    get_other_player()->take_damage(20);
    active = false;
}

    // Talajba csapódás
    if (projectile_pos.y > 580) {
        active = false;
    }

    return projectile_pos;
}


std::vector<Vec2> Game::get_trajectory_preview() {
    std::vector<Vec2> preview;
    if (!projectile_active()) {
        Vec2 pos = get_current_player()->get_barrel_exit();
        float angle = get_current_player()->get_angle() * 3.14 / 180;
        float power = get_current_player()->get_power();
        Vec2 vel = { power * std::cos(angle), -power * std::sin(angle) };
        Vec2 current = pos;
        current.y;
        for (int i = 0; i < 10; ++i) {
            current.x += vel.x + wind;
            current.y += vel.y;
            vel.y += gravity;
            if (current.y > 580)
                break;
            preview.push_back(current);
        }
    }
    return preview;
}


bool Game::projectile_active() {
    return active;
}

void Game::next_turn() {
    current = 1 - current;
    wind = (rand() % 21 - 10) / 2;
}

int Game::get_current_index() const {
    return current;
}
Player* Game::get_player(int i)
{
    return &players[i];
}

