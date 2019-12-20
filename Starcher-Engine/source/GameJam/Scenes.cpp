#include "Objects.h"
#include "Game.h"
#include "Scenes.h"
#include "GlobalVars.h"

// Background *parallelBG = new Background((unsigned int) 1);
// Player *parallelPlayer = new Player(0, (unsigned int) 3, 64, 64);
// Background *earthBG = new Background((unsigned int) 0);
// Player *earthPlayer = new Player(0, (unsigned int) 3, 64, 64);

Scene *TutorialEarth() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *earthBG = new Background((unsigned int) 0);
    s->addObject(earthBG);
    Player *earthPlayer = new Player(0, (unsigned int) 3, 0, WINDOW_HEIGHT - 96, 0, 0, false);
    s->addObject(earthPlayer);
    Enemy *e = new Enemy(64, 490);
    s->addObject(e);

    for(int i = 0; i < num_lives; i++) {
        Object *h = new Object(16*i + 16, 0);
        h->setSprite((unsigned int) 11);
        s->addObject(h);
    }
    
    return s;
}

Scene *TutorialParallel() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *parallelBG = new Background((unsigned int) 1);
    s->addObject(parallelBG);
    Player *parallelPlayer = new Player(1, (unsigned int) 5, 64, 64);
    s->addObject(parallelPlayer);
    Enemy *e = new Enemy(256, 256);
    s->addObject(e);

    for(int i = 0; i < num_lives; i++) {
        Object *h = new Object(0,16*i);
        h->setSprite((unsigned int) 11);
        s->addObject(h);
    }

    return s;
}

Scene *PlatformOneEarth() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *earthBG = new Background((unsigned int) 0);
    Player *earthPlayer = new Player(0, (unsigned int) 3, 64, 64);
    

    //add scene objects
    s->addObject(earthBG);
    s->addObject(earthPlayer);

    return s;
}

Scene *PlatformOneParallel() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *parallelBG = new Background((unsigned int) 1);
    Player *parallelPlayer = new Player(1, (unsigned int) 5, 64, 64);
    

    //add scene objects
    s->addObject(parallelBG);
    s->addObject(parallelPlayer);

    return s;
}

Scene *EnemyOneEarth() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *earthBG = new Background((unsigned int) 0);
    Player *earthPlayer = new Player(0, (unsigned int) 3, 64, 64);
    

    //add scene objects
    s->addObject(earthBG);
    s->addObject(earthPlayer);

    return s;
}

Scene *EnemyOneParallel() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *parallelBG = new Background((unsigned int) 1);
    Player *parallelPlayer = new Player(1, (unsigned int) 5, 64, 64);
    

    //add scene objects
    s->addObject(parallelBG);
    s->addObject(parallelPlayer);

    return s;
}

Scene *PlatformTwoEarth() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *earthBG = new Background((unsigned int) 0);
    Player *earthPlayer = new Player(0, (unsigned int) 3, 64, 64);
    

    //add scene objects
    s->addObject(earthBG);
    s->addObject(earthPlayer);

    return s;
}

Scene *PlatformTwoParallel() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *parallelBG = new Background((unsigned int) 1);
    Player *parallelPlayer = new Player(1, (unsigned int) 5, 64, 64);
    

    //add scene objects
    s->addObject(parallelBG);
    s->addObject(parallelPlayer);

    return s;
}

Scene *BossRoomEarth() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *earthBG = new Background((unsigned int) 0);
    Player *earthPlayer = new Player(0, (unsigned int) 3, 64, 64);
    

    //add scene objects
    s->addObject(earthBG);
    s->addObject(earthPlayer);

    return s;
}

Scene *BossRoomParallel() {
    Scene *s = new Scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background *parallelBG = new Background((unsigned int) 1);
    Player *parallelPlayer = new Player(1, (unsigned int) 5, 64, 64);
    

    //add scene objects
    s->addObject(parallelBG);
    s->addObject(parallelPlayer);

    return s;
}

