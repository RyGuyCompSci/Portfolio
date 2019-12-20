#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../irrKlang-64bit-1.6.0/include/irrKlang.h"
#include "Scene.hpp"
#include "View.hpp"
#include <functional>

class GameEngine {
	private:
			std::vector<Scene *> sceneList;
			Scene *activeScene;
			void processScene();
			void renderScene();
			//SFML Window object kept here.
			sf::RenderWindow *window;
			sf::Event event;
			int winWidth;
			int winHeight;
            int sceneID;
	public:
			GameEngine(int width,int height,std::string title);
			clock_t thisFrame;
			clock_t lastFrame;
			double delta;
			void startGame();
			void endGame();
			void playSound(char *filename, bool loop=false);
			void stopAllSounds();
			void addObject(Object *obj);
			int addScene(Scene *scene);
			int resetScene(std::function<Scene *()> buildFunction,int sceneID);
			bool delScene(int sceneID);
			bool setActiveScene(int sceneID);
			Scene *getActiveScene();
			Scene *getScene(int id);
			int nextScene();
			int prevScene();

};

#endif
