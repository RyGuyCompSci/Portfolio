#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <vector>
#include <ctime>

extern std::vector<std::function<Scene *()>> levels;
extern int player_x;
extern int player_y;
extern std::clock_t initial_switch;
extern unsigned int current_scene;
const int GAME_WIDTH = 65536;
const int WINDOW_HEIGHT = 256;
const int WINDOW_WIDTH = 512;


#endif
