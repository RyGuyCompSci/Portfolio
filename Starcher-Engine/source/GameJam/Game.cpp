#include "Objects.h"
#include "Game.h"
#include "Scenes.h"
#include "GlobalVars.h"
#include "../headers/Globals.hpp"
#include "../headers/GameEngine.hpp"

using namespace std;

string resources = "resources/GameJam/";
vector<function<Scene *()>> levels = {
    TutorialEarth, 
    TutorialParallel, 
    PlatformOneEarth, 
    PlatformOneParallel, 
    EnemyOneEarth, 
    EnemyOneParallel, 
    PlatformTwoEarth, 
    PlatformTwoParallel, 
    BossRoomEarth, 
    BossRoomParallel
};

int main(int argc, char **argv, char **envp) {
    GameEngine engine = *(new GameEngine(WINDOW_WIDTH, WINDOW_HEIGHT, "Parallel"));

    // 0
    Sprite *earthBackground = new Sprite(resources + "EarthBackground.png");
    // earthBackground->setRepeated(true);
    earthBackground->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // 1
    Sprite *parallelBackground = new Sprite(resources + "ParallelBackground.png");
    // parallelBackground->setRepeated(true);
    parallelBackground->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // 2
    Sprite *earthGuy = new Sprite(resources + "EarthStanding.png");
    // 3
    Sprite *earthRunner = new Sprite(resources + "EarthRunner0.png");
    // earthRunner->addImage(resources + "EarthRunner1.png");
    earthRunner->addImage(resources + "EarthRunner2.png");
    // earthRunner->addImage(resources + "EarthRunner3.png");
    earthRunner->addImage(resources + "EarthRunner4.png");
    //4
    Sprite *earthRunnerL = new Sprite(resources + "EarthRunnerL0.png");
        // earthRunnerL->addImage(resources + "EarthRunnerL1.png");
        earthRunnerL->addImage(resources + "EarthRunnerL2.png");
        // earthRunnerL->addImage(resources + "EarthRunnerL3.png");
        earthRunnerL->addImage(resources + "EarthRunnerL4.png");

    // 5
    Sprite *parallelGuy = new Sprite(resources + "ParallelStanding.png");
    // 6
    Sprite *parallelRunner = new Sprite(resources + "ParallelRunner0.png");
    // parallelRunner->addImage(resources + "ParallelRunner1.png");
    parallelRunner->addImage(resources + "ParallelRunner2.png");
    // parallelRunner->addImage(resources + "ParallelRunner3.png");
    parallelRunner->addImage(resources + "ParallelRunner4.png");
    //7
    Sprite *parallelRunnerL = new Sprite(resources + "ParallelRunnerL0.png");
    // earthRunner->addImage(resources + "EarthRunnerL1.png");
    parallelRunnerL->addImage(resources + "ParallelRunnerL2.png");
    // earthRunner->addImage(resources + "EarthRunnerL3.png");
    parallelRunnerL->addImage(resources + "ParallelRunnerL4.png");

    // 8
    Sprite *enemy_still = new Sprite(resources + "turret0.png"); //off

    // 9
    Sprite *enemy = new Sprite(resources + "turret0.png");
    enemy->addImage(resources + "turret1.png");
    enemy->addImage(resources + "turret2.png");
    enemy->addImage(resources + "turret3.png");
    enemy->addImage(resources + "turret4.png");
    enemy->addImage(resources + "turret5.png");

    // 10
    Sprite *fire = new Sprite(resources + "Fire0.png");
    fire->addImage(resources + "Fire1.png");

    // 11
    Sprite *heart = new Sprite(resources + "heart.png");

    //add all scenes to the game
    // for(auto s : levels) {
    //     engine.addScene(s());
    // }

    engine.addScene(TutorialEarth());
    engine.addScene(TutorialParallel());
    // engine.addScene(PlatformOneEarth());
    // engine.addScene(PlatformOneParallel());
    // engine.addScene(EnemyOneEarth());
    // engine.addScene(EnemyOneParallel());
    // engine.addScene(PlatformTwoEarth());
    // engine.addScene(PlatformTwoParallel());
    // engine.addScene(BossRoomEarth());
    // engine.addScene(BossRoomParallel());

    engine.setActiveScene(0);
    engine.startGame();
}
