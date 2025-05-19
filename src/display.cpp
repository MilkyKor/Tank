
#include "display.hpp"
#include "graphics.hpp"
#include "player.hpp"
#include "iostream"
#include <cmath>

using namespace genv;

Display::Display(App* parent, int x, int y, int sx, int sy, Game* g)
    : Widget(parent, x, y, sx, sy), game(g){}


void Display::draw() {

    if (game_state == State::StartMenu) {
        gout << color(200, 200, 200) << move_to(0, 0) << box(_size_x, _size_y)
             << color(0, 0, 0)
             << move_to(250, 250) << text("Tank Battle")
             << move_to(180, 350) << text("Press SPACE to start");
        return;
    }

    if (game_state == State::Victory) {
        int loser = game->get_loser();
        std::string winner = (loser == 0) ? "Player 2" : "Player 1";

        gout << color(255, 255, 255) << move_to(0, 0) << box(_size_x, _size_y)
             << color(0, 0, 0)
             << move_to(200, 250) << text(winner + " wins!")
             << move_to(150, 350) << text("Press R to restart")
             << move_to(150, 400) << text("Press ESC to quit");
        return;
    }

    gout << move_to(_x, _y) << color(150, 200, 150) << box(_size_x, _size_y);

    Player* current = game->get_current_player();

    gout << color(0, 0, 0)
     << move_to(10, 20)
     << text("Current: Player ")
     << text(std::to_string(1 + game->get_current_index()));

    gout << move_to(10, 40)
         << text("Angle: ") << text(std::to_string(current->get_angle()));

    gout << move_to(10, 60)
         << text("Power: ") << text(std::to_string(current->get_power()));

    // wind

        gout << color(0, 0, 0)
             << move_to(10, 80)
             << text("Wind: ") << text(std::to_string(int(game->get_wind())));

    // Föld
    gout << color(50, 100, 50) << move_to(0, _y + _size_y - 20) << box(_size_x, 20);

    // Tank
    for (int i = 0; i < 2; ++i) {
    Player* p = (i == 0) ? game->get_current_player() : game->get_other_player();
    Vec2 pos = p->get_position();

    // Tank body
    gout << color(100, 100, 100)
         << move_to(pos.x, pos.y)
         << box(50, 25);

    // Barrel
    float rad = p->get_angle() * 3.14159f / 180.0f;
    float len = 40, wid = 8;
    float dx = std::cos(rad), dy = -std::sin(rad);
    float nx = -dy, ny = dx;
    float bx = pos.x + 25, by = pos.y + 12;

    float x1 = bx + nx * (wid / 2);
    float y1 = by + ny * (wid / 2);
    float x2 = bx - nx * (wid / 2);
    float y2 = by - ny * (wid / 2);
    float x3 = x2 + dx * len;
    float y3 = y2 + dy * len;
    float x4 = x1 + dx * len;
    float y4 = y1 + dy * len;

    gout << color(50, 50, 50)
         << move_to(x1, y1) << line_to(x2, y2)
         << line_to(x3, y3) << line_to(x4, y4)
         << line_to(x1, y1);
    }
    // Lövedék
    if (game->projectile_active()) {
    Vec2 proj = game->get_projectile_pos();
    switch (game->get_projectile_type()) {
        case ProjectileType::Big:
            gout << color(200, 0, 200)
                 << move_to(proj.x - 4, proj.y - 4)
                 << box(12, 12);
            break;
        case ProjectileType::Spread:
            gout << color(255, 150, 0)
                 << move_to(proj.x - 6, proj.y - 2)
                 << box(6, 32);
            break;
        case ProjectileType::Homing:
            gout << color(0, 200, 200)
                 << move_to(proj.x, proj.y)
                 << box(4, 4);
            break;
        default:
            gout << color(255, 0, 0)
                 << move_to(proj.x, proj.y)
                 << box(4, 4);
            break;
    }
}

    // irány
    std::vector<Vec2> preview = game->get_trajectory_preview();

    for (const Vec2& p : preview) {
        gout << color(255, 255, 255)
         << move_to(p.x, p.y) << box(3, 3);
    }

    //hp
    for (int i = 0; i < 2; ++i) {
    Player* p = game->get_player(i);
    std::string label = "P" + std::to_string(i+1) + " HP: " + std::to_string(p->get_hp());
    gout << color(0, 0, 0) << move_to(100, 60 + i * 20) << text(label);
    }
    std::string type_str;
    switch (game->get_projectile_type()) {
        case ProjectileType::Normal: type_str = "Normal"; break;
        case ProjectileType::Spread: type_str = "Spread"; break;
        case ProjectileType::Big: type_str = "Big"; break;
        case ProjectileType::Homing: type_str = "Homing"; break;
    }
    gout << move_to(10, 100) << text("Projectile: " + type_str);
}

void Display::handle(event ev) {
    // START MENÜ
    if (game_state == State::StartMenu) {
        if (ev.type == ev_key && ev.keycode == ' ') {
            game_state = State::Playing;
        }
        return;
    }

    // VICTORY
    if (game_state == State::Victory) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_escape) {
            exit(0);
        }
        if (ev.keycode == 'r') {
            *game = Game();
            game_state = State::StartMenu;
        }
    }
    return;
}

    if (ev.type == ev_key && !game->projectile_active()) {
        Player* player = game->get_current_player();

        switch (ev.keycode) {
            case key_right:
                player->decrease_angle();
                break;
            case key_left:
                player->increase_angle();
                break;
            case key_up:
                player->increase_power();
                break;
            case key_down:
                player->decrease_power();
                break;
            case 'a':
                player->move_left();
                break;
            case 'd':
                player->move_right();
                break;
            case ' ':
                game->shoot();
                break;
            case '1':
                game->set_projectile_type(ProjectileType::Normal);
                break;
            case '2':
                game->set_projectile_type(ProjectileType::Spread);
                break;
            case '3':
                game->set_projectile_type(ProjectileType::Big);
                break;
            case '4':
                game->set_projectile_type(ProjectileType::Homing);
            break;
        }

    }
    if (projectile_was_active && !game->projectile_active()) {
        game->next_turn();
    }

    if (game->get_loser() != -1) {
        game_state = State::Victory;
    }

    // Frissítsd az elõzõ állapotot
    projectile_was_active = game->projectile_active();
}
