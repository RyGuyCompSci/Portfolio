#include "headers/Globals.hpp"
#include <iostream>

#define Keys sf::Keyboard
void basicMove(float *xA, float *yA, float speed, double delta){

	delta = delta / 100.0;

	if(Keys::isKeyPressed(Keys::D)){
        *xA += speed * delta;
    }
    if(Keys::isKeyPressed(Keys::A)){
        *xA -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::W)){
        *yA -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::S)){
        *yA += speed * delta;
    }
}

void directMove(float *x, float *y, float speed, double delta){

	delta = delta / 100.0;

	if(Keys::isKeyPressed(Keys::D)){
        *x += speed * delta;
    }
    if(Keys::isKeyPressed(Keys::A)){
        *x -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::W)){
        *y -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::S)){
        *y += speed * delta;
    }
}

void createObject(Object *obj){
	if(activeEngine!=NULL){
		activeEngine->addObject(obj);
	}
	return;
}

void destroyObject(Object *obj){
	activeEngine->getActiveScene()->destroyObject(obj);
	return;
}

bool setActiveScene(int sceneID){

	return activeEngine->setActiveScene(sceneID);
}

void playSound(char *filename, bool loop) {
	activeEngine->playSound(filename, loop);
}

void stopAllSounds() {
    activeEngine->stopAllSounds();
}

int getSceneWidth(int sceneID){
    if(activeEngine!=NULL){
	    int width;
	    Scene *scene = activeEngine->getScene(sceneID);
	    if(scene!=NULL){
		    width = scene->width;
	    }else{
		    width = -1;
	    }
	    return width;
	}else{
		return -1;
	}
}
int getSceneWidth(){
	if(activeEngine!=NULL){
		int width;
		Scene *scene = activeEngine->getActiveScene();
		if(scene!=NULL){
			width = scene->width;
		}else{
			width = -1;
		}
		return width;
	}else{
		return -1;
	}
}

int getSceneHeight(){
	if(activeEngine!=NULL){
		int height;
		Scene *scene = activeEngine->getActiveScene();
		if(scene!=NULL){
			height = scene->height;
		}else{
			height = -1;
		}
		return height;
	}else{
		return -1;
	}
}

int getSceneHeight(int sceneID){
    if(activeEngine!=NULL){
	    int height;
	    Scene *scene = activeEngine->getScene(sceneID);
	    if(scene!=NULL){
		    height = scene->height;
	    }else{
		    height = -1;
	    }
	    return height;
	}else{
		return -1;
	}
}
int getWindowWidth(){
	return windowWidth;
}
int getWindowHeight(){
	return windowHeight;
}
int resetScene(std::function<Scene *()> buildFunction,int sceneID){
	if(activeEngine!=NULL){
		activeEngine->resetScene(buildFunction,sceneID);
		return 0;
	}
	return -1;
}
bool inView(Object* obj, int sceneID, int viewID){
    return activeEngine->getScene(sceneID)->getView(viewID)->inView(obj);
}
