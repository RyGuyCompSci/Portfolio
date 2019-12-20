#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include <functional>
#include "../headers/Scene.hpp"
#include <vector>
#include <ctime>

extern std::vector<std::function<Scene *()>> levels;
extern std::clock_t switch_timer;
extern int playerOneX, playerOneY, playerTwoX, playerTwoY;
extern int num_lives;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int PLAYER_HEIGHT = 96;
const int PLAYER_WIDTH = 64;

#endif