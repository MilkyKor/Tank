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
    Vec2 base_velocity = { p->get_power() * std::cos(rad), -p->get_power() * std::sin(rad) };
    Vec2 start_pos = p->get_barrel_exit();

    active = true;

    switch (current_projectile) {
        case ProjectileType::Normal:
            velocity = base_velocity;
            projectile_pos = start_pos;
            break;

        case ProjectileType::Spread:
            velocity = base_velocity;
            projectile_pos = start_pos;
            break;

        case ProjectileType::Big:
            velocity = base_velocity;
            projectile_pos = start_pos;
            break;

        case ProjectileType::Homing:
            velocity = base_velocity;
            projectile_pos = start_pos;
            break;
    }
}

Vec2 Game::get_projectile_pos() {
    if (!active) return {-1, -1};

    // Elõzõ pozíció elmentése az interpolációhoz (ha késõbb finomítani akarjuk)
    Vec2 prev_pos = projectile_pos;
    // légellenállás
    velocity.x *= 0.99;
    velocity.y *= 0.99;

    // Mozgás frissítése
    projectile_pos.x += velocity.x + wind;
    projectile_pos.y += velocity.y;
    velocity.y += gravity;

    // Ütközés vizsgálat - ha eltalálja az ellenfelet
    Vec2 opp_pos = get_other_player()->get_position();

    // hit box
    float proj_width = 4;  // alapértelmezett
    float proj_height = 4;

    switch (current_projectile) {
        case ProjectileType::Spread:
            proj_width = 6;
            proj_height = 50;
            break;
        case ProjectileType::Big:
            proj_width = 12;
            proj_height = 12;
            break;
        default:
            break;
}

// hitbox a lövedék mérete alapján
bool hit_x = projectile_pos.x + proj_width/2 >= opp_pos.x &&
             projectile_pos.x - proj_width/2 <= opp_pos.x + 50;
bool hit_y = projectile_pos.y + proj_height/2 >= opp_pos.y &&
             projectile_pos.y - proj_height/2 <= opp_pos.y + 25;

if (hit_x && hit_y) {
    int dmg = 20;
    switch (current_projectile) {
        case ProjectileType::Spread: dmg = 10; break;
        case ProjectileType::Big: dmg = 15; break;
        case ProjectileType::Homing: dmg = 8; break;
        default: break;
    }
    get_other_player()->take_damage(dmg);
    active = false;
}

    // Talajba csapódás
    if (projectile_pos.y > 580) {
        active = false;
    }

    if (current_projectile == ProjectileType::Homing) {
        Vec2 target = get_other_player()->get_position();
        float dx = target.x - projectile_pos.x;
        float dy = target.y - projectile_pos.y;
        float dist = std::sqrt(dx*dx + dy*dy);
        if (dist > 0.1f) {
            velocity.x += dx / dist * 0.5;
            velocity.y += dy / dist * 0.5;
        }
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

int Game::get_loser() {
    if (players[0].get_hp() <= 0) return 0;
    if (players[1].get_hp() <= 0) return 1;
    return -1;
}
