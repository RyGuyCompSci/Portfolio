#ifndef GLOBALS_H
#define GLOBALS_H
#include "GameEngine.hpp"
#include <vector>
#include <functional>


extern std::vector<Sprite *> spriteIndex;
extern GameEngine *activeEngine;

extern void basicMove(float *xA, float *yA, float speed, double delta);

extern void directMove(float *x, float *y, float speed, double delta);

extern void createObject(Object *obj);

extern void destroyObject(Object *obj);

extern bool setActiveScene(int sceneID);

extern void playSound(char *filename, bool loop=false);

extern void stopAllSounds();

extern int getSceneWidth(int sceneID);

extern int getSceneWidth();

extern int getSceneHeight();

extern int getSceneHeight(int sceneID);

extern int windowWidth;

extern int windowHeight;

extern int getWindowWidth();

extern int getWindowHeight();

extern int resetScene(std::function<Scene *()>,int sceneID);

extern bool inView(Object *obj, int sceneID, int viewID);

extern double averageDelta;

#endif
