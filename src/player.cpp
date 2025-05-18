#include "player.hpp"
#include <cmath>

Player::Player(Vec2 pos, int start_angle)
    : position(pos), angle(start_angle), power(20) {}

void Player::move_left()  { position.x -= 5; }
void Player::move_right() { position.x += 5; }

void Player::increase_angle()  { if (angle < 180) angle += 5; }
void Player::decrease_angle()  { if (angle > 0)   angle -= 5; }

void Player::increase_power()  { if (power < 50) power += 1; }
void Player::decrease_power()  { if (power > 5)  power -= 1; }

Vec2 Player::get_position() const { return position; }
int Player::get_angle() const { return angle; }
int Player::get_power() const { return power; }

Vec2 Player::get_barrel_exit() const {
    float rad = angle * 3.14 / 180;
    float dx = std::cos(rad);
    float dy = -std::sin(rad);
    float nx = -dy;
    float ny = dx;
    float len = 30;
    float width = 6;
    float base_x = position.x + 25;
    float base_y = position.y - 12;

    float x3 = base_x - nx * (width / 2) + dx * len;
    float y3 = base_y - ny * (width / 2) + dy * len;
    float x4 = base_x + nx * (width / 2) + dx * len;
    float y4 = base_y + ny * (width / 2) + dy * len;

    return { (x3 + x4) / 2, (y3 + y4) / 2 };
}

int Player::get_hp() const{
    return hp;
}

void Player::take_damage(int dmg)
{
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}
