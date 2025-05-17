#include "display.hpp"
#include "graphics.hpp"
#include <cmath>

using namespace genv;

Display::Display(App* parent, int x, int y, int sx, int sy, GameMaster* g)
    : Widget(parent, x, y, sx, sy), game(g) {}

void Display::draw() {
    gout << move_to(_x, _y) << color(150, 200, 150) << box(_size_x, _size_y);

    // Föld
    gout << color(50, 100, 50) << move_to(0, _y + _size_y - 20) << box(_size_x, 20);

    // Tank
    gout << color(100, 100, 100);
    Vec2 base = {100, _y + _size_y - 20};
    gout << move_to(base.x, base.y - 20) << box(40, 20);

    // Csõ mint téglalap
     float angle = game->get_angle() * 3.14159f / 180.0f;
     float length = 30.0f;
     float width = 6.0f;

    // Tank pozíciója
     float base_x = base.x + 20;  // közép
     float base_y = base.y - 10;  // felsõ szél

    // Tégla csõ 4 sarka - körbeforgatva
     float dx = std::cos(angle);
     float dy = -std::sin(angle);  // negatív mert lefelé nõ a Y

    // keresztirány a vastagsághoz
     float nx = -dy;
     float ny = dx;

    // 4 sarok
     float x1 = base_x + nx * (width / 2);
     float y1 = base_y + ny * (width / 2);

     float x2 = base_x - nx * (width / 2);
     float y2 = base_y - ny * (width / 2);

     float x3 = x2 + dx * length;
     float y3 = y2 + dy * length;

     float x4 = x1 + dx * length;
     float y4 = y1 + dy * length;

    // Rajzoljunk csövet
     gout << color(50, 50, 50);
     gout << move_to(x1, y1) << line_to(x2, y2)
     << line_to(x3, y3) << line_to(x4, y4)
     << line_to(x1, y1);

    // Lövedék
    if (game->projectile_active()) {
        Vec2 pos = game->get_projectile_pos();
        gout << color(255, 0, 0) << move_to(pos.x, pos.y) << box(6, 6);
    }

    // Debug info
    gout << move_to(500, 20) << color(0,0,0)
         << text("Szog: " + std::to_string(game->get_angle()) +
                 " Power: " + std::to_string(game->get_power()));
}

void Display::handle(event ev) {
    if (ev.type == ev_key) {
        switch (ev.keycode) {
            case key_right:
                game->increase_angle();
                break;
            case key_left:
                game->decrease_angle();
                break;
            case key_up:
                game->increase_power();
                break;
            case key_down:
                game->decrease_power();
                break;
            case ' ':
                game->shoot();
                break;
        }
    }
}
