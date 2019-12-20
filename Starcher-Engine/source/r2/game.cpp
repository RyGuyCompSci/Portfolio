#include "../headers/Globals.hpp"
#include "../headers/GameEngine.hpp"
#include "game.h"
#include "scenes.h"
#include "objects.h"
#include "globalvars.h"

std::string resources = "resources/r2/";

std::vector<std::function<Scene *()>> levels = {start, track};

using namespace std;

int main(int argc, char **argv, char **evnp)
{
    GameEngine engine = *(new GameEngine(WINDOW_WIDTH,WINDOW_HEIGHT,"Running Simulator 2019"));

    // sprite 0
    Sprite *background_sprite = new Sprite(resources + "background.png");
    background_sprite->setRepeated(true);
    background_sprite->setSize(GAME_WIDTH, 256);
    // sprite 1
    Sprite *runner_standing = new Sprite(resources + "runner_standing.png");
    // sprite 2
    Sprite *runner_running = new Sprite(resources + "runner_anims_01.png");
    runner_running->addImage(resources + "runner_anims_02.png");
    // sprite 3
    Sprite *hurdle = new Sprite(resources + "hurdle.png");
    // sprite 4
    Sprite *ground = new Sprite(resources + "ground.png");
    ground->setRepeated(true);
    ground->setSize(GAME_WIDTH,64);
    // sprite 5
    Sprite *runner_dead = new Sprite(resources + "runner_dead.png");

    engine.addScene(start());
    engine.addScene(track());
    engine.startGame();

    return 0;

}
