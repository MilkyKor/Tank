#ifndef PLAYER_HPP
#define PLAYER_HPP
struct Vec2 {
    float x, y;
};

class Player {
public:
    Player(Vec2 pos, int start_angle);

    void move_left();
    void move_right();
    void increase_angle();
    void decrease_angle();
    void increase_power();
    void decrease_power();


    Vec2 get_position() const;
    int get_angle() const;
    int get_power() const;
    int get_hp() const;
    void take_damage(int dmg);

    Vec2 get_barrel_exit() const;

private:
    int hp = 100;
    Vec2 position;
    int angle;
    int power;
};

#endif
