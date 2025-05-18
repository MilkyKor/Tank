#include "graphics.hpp"
#include "app.hpp"
#include "game.hpp"
#include "display.hpp"

using namespace genv;

class TankApp : public App {
public:
    TankApp(int w, int h) : App(w,h) {
        game = new Game();
        display = new Display(this, 0, 0, w, h, game);
    }

private:
    Game* game;
    Display* display;
};

int main() {
    TankApp app(800, 600);
    app.event_loop();
    return 0;
}
