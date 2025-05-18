#ifndef GAME_HPP
#define GAME_HPP
#include <vector>

#include "player.hpp"

class Game {
public:
    Game();

    void shoot();
    void next_turn();
    Player* get_current_player();
    Player* get_other_player();
    bool projectile_active();
    Vec2 get_projectile_pos();
    std::vector<Vec2> get_trajectory_preview();
    int get_current_index() const;
    float get_wind() const { return wind; }
    Player* get_player(int i);

private:
    Player players[2];
    int current;
    Vec2 projectile_pos;
    Vec2 velocity;
    bool active;
    float gravity;
    float wind;
};

#endif
