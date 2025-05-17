#ifndef GAME_HPP
#define GAME_HPP

struct Vec2 {
    float x, y;
};

class GameMaster {
public:
    GameMaster();

    void shoot();                  // aktu�lis angle + power alapj�n
    Vec2 get_projectile_pos();
    Vec2 get_barrel_exit();         // l�ved�k pontos kiindul�sa
    bool projectile_active();

    void increase_angle();         // angle += 5
    void decrease_angle();         // angle -= 5
    void increase_power();         // power += 1
    void decrease_power();         // power -= 1

    int get_angle() const;
    int get_power() const;
    Vec2 get_barrel_end();         // cs� v�g�nek poz�ci�ja

private:
    Vec2 projectile_pos;
    Vec2 velocity;
    bool active;
    float gravity;
    float wind;

    int angle;  // fokban
    int power;
    Vec2 tank_pos;
};

#endif
