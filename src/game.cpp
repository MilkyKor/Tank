#include "game.hpp"
#include <cmath>

GameMaster::GameMaster()
    : active(false), gravity(0.4f), wind(0.0f), angle(45), power(20), tank_pos({100, 530}) {}

void GameMaster::shoot() {
    float rad = angle * 3.14159f / 180.0f;
    velocity = { power * std::cos(rad), -power * std::sin(rad) };
    projectile_pos = get_barrel_exit();
    active = true;
}

Vec2 GameMaster::get_projectile_pos() {
    if (!active) return {-1, -1};
    projectile_pos.x += velocity.x + wind;
    projectile_pos.y += velocity.y;
    velocity.y += gravity;

    if (projectile_pos.y > 580) {
        active = false;
    }
    return projectile_pos;
}

bool GameMaster::projectile_active() {
    return active;
}

void GameMaster::increase_angle() {
    if (angle < 90) angle += 5;
}

void GameMaster::decrease_angle() {
    if (angle > 0) angle -= 5;
}

void GameMaster::increase_power() {
    if (power < 50) power += 1;
}

void GameMaster::decrease_power() {
    if (power > 5) power -= 1;
}

int GameMaster::get_angle() const {
    return angle;
}

int GameMaster::get_power() const {
    return power;
}


Vec2 GameMaster::get_barrel_exit()
{
    float rad = angle * 3.14159f / 180.0f;
    float length = 30.0f;
    float width = 6.0f;

    float dx = std::cos(rad);
    float dy = -std::sin(rad);

    float nx = -dy;
    float ny = dx;

    float base_x = tank_pos.x + 20;
    float base_y = tank_pos.y -10;

    // végsõ két sarok a csõ végén
    float x3 = base_x - nx * (width / 2) + dx * length;
    float y3 = base_y - ny * (width / 2) + dy * length;

    float x4 = base_x + nx * (width / 2) + dx * length;
    float y4 = base_y + ny * (width / 2) + dy * length;

    // középpont a csõ végén
    return {
        (x3 + x4) / 2,
        (y3 + y4) / 2
    };
}
