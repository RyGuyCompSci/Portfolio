#include "scenes.h"
#include "objects.h"
#include "globalvars.h"
#include "../headers/Globals.hpp"
#include <string>
#include <vector>
#include <iostream>


Scene *start() {
    Scene *start_scene = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);

    background *bg = new background(0,0,0);

    player *runner = new player(16,129,0,0,false);
    runner->is_standing();

    ground *gr = new ground(0,WINDOW_HEIGHT-64,0,0,false);

    sceneTrigger *st = new sceneTrigger(0,0);

    start_scene ->getView(0)->setFollowing(runner,-256,512);
    start_scene->addObject(st);
    start_scene->addObject(bg);
    start_scene->addObject(gr);
    start_scene->addObject(runner);

    return start_scene;
}

Scene *track() {
    Scene *track_scene = new Scene(GAME_WIDTH, WINDOW_HEIGHT);
    background *bg = new background(0,0);

    player *runner = new player(16,128,1,PLAYER,true);
    ground *gr = new ground(0,WINDOW_HEIGHT-64,1,GROUND,false);


    track_scene->getView(0)->setFollowing(runner,-256,512);
    track_scene->addObject(bg);
    track_scene->addObject(gr);
    int prev = 128;
    for(int i = 1; i < 511; i++) {
        int x_pos = prev + (rand() % 512);
        std::cout << x_pos % 512 << std::endl;
        prev = x_pos + 48;
        track_scene->addObject(new hurdle(x_pos, 128, 1, ENEMY, false));
    }
    track_scene->addObject(runner);

    return track_scene;
}
