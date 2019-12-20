#include "headers/GameEngine.hpp"
#include "headers/Globals.hpp"
#include <iostream>

using namespace irrklang;
using namespace std;

//The number of clock cycles per millisecond
#define CLOCKS_PER_MS ((float)(CLOCKS_PER_SEC/1000))


GameEngine *activeEngine = NULL;
ISoundEngine *audioEngine = createIrrKlangDevice();
int windowWidth = 0;
int windowHeight = 0;
double averageDelta = 50.0;

GameEngine::GameEngine(int width, int height,string title){
	if(!audioEngine) printf("Could not start engine\n");
	this->window = new sf::RenderWindow(sf::VideoMode(width,height),title);
	this->winWidth = width;
	this->winHeight = height;
	windowWidth = width;
	windowHeight = height;
	this->window->setFramerateLimit(60);
	this->activeScene = NULL;
	this->thisFrame = clock();
	this->lastFrame = clock();

}

void GameEngine::startGame(){
	GameEngine *tmp = this;
	activeEngine = tmp;

	while(this->window->isOpen()){//Main game loop

		//Render
		renderScene();

		//Process key presses and other window events
		while(this->window->pollEvent(this->event)){
			if(this->event.type == sf::Event::Closed){
				this->window->close();
			}

		}

		//Process game objects
		processScene();	
	}
	audioEngine->drop();
}

void GameEngine::renderScene(){
	//Render
	if(this->activeScene!=NULL){
		this->activeScene->render(this->window);
	}
}

void GameEngine::processScene(){
	thisFrame = clock();
	if(thisFrame >= lastFrame){
	    delta = (thisFrame - lastFrame)/CLOCKS_PER_MS;
	} else {
	    delta = thisFrame;
	}
	this->activeScene->process(delta);
	lastFrame = thisFrame;
}

void GameEngine::endGame(){
	this->window->close();
}

void GameEngine::playSound(char *filename, bool loop) {
	audioEngine->play2D(filename, loop);
}

void GameEngine::stopAllSounds() {
	audioEngine->stopAllSounds();
}

int GameEngine::addScene(Scene *scene){
	scene->setID(sceneList.size());
	this->sceneList.push_back(scene);
	if(this->sceneList.size()<2){
		this->activeScene = scene;
	}

	return 0;
}

bool GameEngine::delScene(int sceneID){
    this->sceneList.erase(sceneList.begin()+sceneID);
    return true;
}

bool GameEngine::setActiveScene(int sceneID){
    if((long unsigned int) sceneID < this->sceneList.size() && sceneID > -1){
        this->activeScene = this->sceneList[sceneID];
        this->activeScene->setID(sceneID);
        return true;
   }
    else{
        return false;
   }
}

Scene *GameEngine::getScene(int sceneID){
	if((long unsigned int) sceneID < this->sceneList.size()){
		return sceneList[sceneID];
	}else{
		return NULL;
	}
}

Scene *GameEngine::getActiveScene(){
	return this->activeScene;
}

int GameEngine::nextScene(){
    this->activeScene = this->sceneList[sceneID+1];
    return 0;
}
int GameEngine::prevScene(){
    this->activeScene = this->sceneList[sceneID-1];
    return 0; 
}

void GameEngine::addObject(Object *obj){
	if(this->activeScene!=NULL){
		this->activeScene->addObject(obj);
	}
	return;
}

int GameEngine::resetScene(std::function<Scene *()> buildFunction,int sceneID){
	bool setActive = false;
	getScene(sceneID)->destroyed = true;
	if(getScene(sceneID)==this->activeScene){
		setActive = true;
	}
	if(setActive==true){
		setActiveScene(sceneID);
	}
	Scene *newScene = buildFunction();
	this->sceneList[sceneID] = newScene;
	return 0;
}
