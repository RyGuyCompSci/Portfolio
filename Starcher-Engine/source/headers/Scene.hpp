#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <time.h>
#include "Object.hpp"
#include "View.hpp"
#include "HitBox.hpp"

class Scene{
	private:
			std::vector<View *> viewList;
			std::vector<Object *> objectList;
			std::vector<Object *> originalObjectList;
	public:
			int width;
			int height;
			bool destroyed;
			int id; //Where in the GameEngine list does this scene appear
            float gravity;
            float cof;
            float termVel;
			Scene(int width, int height);
			~Scene();
			void process(double delta); //Should make call to Object _process functions and to View _process functions
			void render(sf::RenderWindow *window); //render(SFML window)
			View *getView(unsigned int index);
			int addObject(Object *object);
			int addView(View *view);
			void setID(int id);
			std::vector<Object *> getObjectList();
			void destroyObject(Object *obj);
            void scaleAllObjects(float xScale, float yScale);
};
#endif
