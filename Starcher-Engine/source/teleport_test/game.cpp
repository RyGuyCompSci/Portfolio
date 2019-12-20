#include "../headers/Globals.hpp"                                                                                 
#include "../headers/GameEngine.hpp"
#include "game.h"
#include "scenes.h"
#include "objects.h"
#include "globalvars.h"

std::string resources = "resources/r2/";

std::vector<std::function<Scene *()>> levels = {earth_one, earth_two};

using namespace std;

int main(int argc, char **argv, char **evnp)
{
    GameEngine engine = *(new GameEngine(WINDOW_WIDTH,WINDOW_HEIGHT,"Teleporation Simulator"));

    // sprite 0
    Sprite *earth_1_bg = new Sprite(resources + "background.png");
    earth_1_bg->setRepeated(true);
    earth_1_bg->setSize(GAME_WIDTH, 256);
	// sprite 1
	Sprite *earth_2_bg = new Sprite(resources + "background2.png");
	earth_2_bg->setRepeated(true);
	earth_2_bg->setSize(GAME_WIDTH, 256);
    // sprite 2
    Sprite *player = new Sprite(resources + "runner_standing.png");

    engine.addScene(earth_one());
    engine.addScene(earth_two());
    engine.startGame();

    return 0;

}

