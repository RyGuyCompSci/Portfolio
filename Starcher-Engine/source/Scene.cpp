#include "headers/Scene.hpp"
#include "headers/Globals.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//The number of clock cycles per millisecond
#define CLOCKS_PER_MS ((float)(CLOCKS_PER_SEC/1000))

using namespace std;

Scene::Scene(int width, int height){
    this->width = width;
    this->height = height;
	this->id = 0;
	this->destroyed = false;
    //this->gravity = 9.8;
	this->gravity = 0.5;
    this->termVel = 195;
    this->viewList = std::vector<View *>();
	View *tmp = new View(0,0,0,0,getWindowWidth(),getWindowHeight());
	this->addView(tmp);
}

int Scene::addObject(Object *object){
	this->objectList.push_back(object);
	return 0;
}

int Scene::addView(View *view){
	view->setSceneID(this->id);
	this->viewList.push_back(view);
	return 0;
}

View *Scene::getView(unsigned int index){
	if(index < this->viewList.size()){
		return viewList[index];
	}else{
		return NULL;
	}
}

void Scene::setID(int id){
	this->id = id;
    for(unsigned int i = 0; i < viewList.size(); i++){
        viewList[i]->setSceneID(this->id);
    }
	return;
}

//process 1 frame of the scene
void Scene::process(double delta){
    //printf("%f\r", delta);
    //std::fflush(stdout);
	for(unsigned int i = 0; i < this->objectList.size() && this->destroyed == false; i++){
        if(this->objectList[i]!=NULL){
            this->objectList[i]->xPrev = this->objectList[i]->x;
            this->objectList[i]->yPrev = this->objectList[i]->y;
			this->objectList[i]->_process(delta, gravity, termVel);
		}
	}
    //Process if this scene has been destroyed
    if(destroyed==true){
		delete this;
        return;
    }

	//Object collision processing

    //The objects being checked (for readability and limiting memory access in-code)
    Object* obj1;
    Object* obj2;

    //Checking each Object
    for(unsigned int i = 0; i < this->objectList.size(); i++){
        obj1 = this->objectList[i];
		//Check each hitbox for each object
        if(i < this->objectList.size() && this->objectList[i]!=NULL && obj1->collisionLayer >= 0){
            for(unsigned int j = i + 1; j < this->objectList.size(); j++){
                //Don't check against yourself
                obj2 = this->objectList[j];
                if(j < this->objectList.size() && this->objectList[j]!=NULL && obj2->collisionLayer >= 0){
                    for(unsigned int k = 0; k < obj1->hitBoxes.size(); k++){
						obj2 = this->objectList[j];
        				obj1 = this->objectList[i];
						if(obj2==NULL || obj1==NULL){
							continue;
						}
						if(obj1->hitBoxes[k]!=NULL){
							float x1 = obj1->hitBoxes[k]->offsetX + obj1->x;
							float y1 = obj1->hitBoxes[k]->offsetY + obj1->y;
							for(unsigned int l = 0; l < obj2->hitBoxes.size(); l++){
							if(obj2->hitBoxes[l]!=NULL){
								float x2 = obj2->hitBoxes[l]->offsetX + obj2->x;
								float y2 = obj2->hitBoxes[l]->offsetY + obj2->y;
									if(x1 + obj1->hitBoxes[k]->width > x2
									   && x1 < x2 + obj2->hitBoxes[l]->width
									   && y1 + obj1->hitBoxes[k]->height > y2
									   && y1 < y2 + obj2->hitBoxes[l]->height){
														//Handle Collision
														if(obj1!=NULL && obj2!=NULL){
															obj1->onCollide(obj2, k, l);
														}else{
															break;
														}
														obj2 = this->objectList[j];
														if(obj1!=NULL && obj2!=NULL){
															obj2->onCollide(obj1, l, k);
														}else{
															break;
														}
									}
								}else{
									//Clean up deleted hitboxes
									obj2->hitBoxes.erase(obj2->hitBoxes.begin()+l);
								}
							}
						}else{
							//Clean up deleted hitboxes
							obj1->hitBoxes.erase(obj1->hitBoxes.begin()+k);
						}
					}
                }
            }
        }
	}
	//Cleanup Object List
	for(unsigned int i = 0; i < this->objectList.size(); i++){
		if(this->objectList[i]==NULL){
			objectList.erase(objectList.begin()+i);
		}
	}
	//View processing
	for(unsigned int i = 0; i < this->viewList.size(); i++){
		this->viewList[i]->_process(delta);
	}
    //Process if this scene has been destroyed
    if(destroyed==true){
		delete this;
    }
}

//render 1 frame of the scene
void Scene::render(sf::RenderWindow *window){
	//Clear the window with the black color
	window->clear(sf::Color::Black);

	//Struct to hold object drawing data
	struct drawData objDraw;
	//Struct to hold position translation information
	struct position translation;
	//Sprite to hold object to draw
	sf::Sprite objSprite;
	//Text
	sf::Text objText;
	//Texture
	sf::Texture sprTexture;
	//HitBox list
	std::vector<HitBox *> hBoxes;
	//Debug box
	sf::RectangleShape rectangle;
	

	//Iterate through views
	for(unsigned int i = 0; i < this->viewList.size();i++){
		//cout << "Processing View: " << i << endl;
		//Iterate through objects
		for(unsigned int j = 0; j < this->objectList.size();j++){
			if(objectList[j]!=NULL){
				//Get data needed to render the object
				objDraw = objectList[j]->_draw();

				//Process View translation
				translation = this->viewList[i]->translate(objDraw.x,objDraw.y);

				objDraw.x = translation.x;
				objDraw.y = translation.y;

				if(objDraw.sprite!=NULL){
					//Draw Sprite
					//Retrieve the image with index imageIndex from the sprite pointed to by the
					//object we are trying to draw
					sprTexture = (objDraw.sprite->getImage(objDraw.imageIndex));
					sprTexture.setRepeated(objDraw.repeated);
					objSprite.setTexture(sprTexture,true);
					sf::IntRect r(0,0,objDraw.width,objDraw.height);
					objSprite.setTextureRect(r);
					objSprite.setPosition(objDraw.x,objDraw.y);
					//Scaling
					objSprite.setScale(objDraw.xScale,objDraw.yScale);
					//Transparency
					objSprite.setColor(sf::Color(255,255,255,objDraw.alpha));
					//Make sure the object sprite is the last thing we draw, so that it is at the foreground.
					window->draw(objSprite);
				}
				//Draw text
				if(objDraw.hasText == true){
					//Create text object
					objText = sf::Text(objDraw.textString,objDraw.textFont);	
					//Set font size
					objText.setCharacterSize(objDraw.fontSize);
					//Set text color
					objText.setColor(objDraw.textColor);
					//objText.setOutlineColor(objDraw.textOutlineColor);
					if(objDraw.relativeToObject == true){
						objText.setPosition(objDraw.x+objDraw.textX,objDraw.y+objDraw.textY);
					}else{
						objText.setPosition(objDraw.textX,objDraw.textY);	
					}
					window->draw(objText);
				}
			}
		}
		//Debug drawing
		for(unsigned int j = 0; j < this->objectList.size();j++){
			if(objectList[j]!=NULL){
				//Get data needed to render the object
				objDraw = objectList[j]->_draw();

				//Process View translation
				translation = this->viewList[i]->translate(objDraw.x,objDraw.y);

				objDraw.x = translation.x;
				objDraw.y = translation.y;

				if(objDraw.sprite!=NULL){
					if(objDraw.drawHitBoxes==true){
						hBoxes = objectList[j]->getHitBoxes();
						for(unsigned int k = 0; k < hBoxes.size(); k++){
							rectangle.setSize(sf::Vector2f(hBoxes[k]->width,hBoxes[k]->height));
							rectangle.setOutlineColor(sf::Color::Red);
							rectangle.setFillColor(sf::Color::Transparent);
							rectangle.setOutlineThickness(2);
							rectangle.setPosition(objDraw.x+hBoxes[k]->offsetX,objDraw.y+hBoxes[k]->offsetY);

							window->draw(rectangle);
						}
					}
					//Make sure the object sprite is the last thing we draw, so that it is at the foreground.
					window->draw(objSprite);
				}
			}
		}
	}
	window->display();

	return;
}

std::vector<Object *> Scene::getObjectList(){
	return this->objectList;
}

void Scene::destroyObject(Object *obj){
	for(unsigned int i = 0; i < this->objectList.size(); i++){
		if(this->objectList[i]==obj){
			objectList[i]=NULL;
			delete obj;
		}
	}
	for(unsigned int i = 0; i < this->viewList.size(); i++){
		if(viewList[i]->following==obj){
			viewList[i]->setFollowing(NULL,0,0);
		}
	}
}

void Scene::scaleAllObjects(float xScale, float yScale){
    for(unsigned int i = 0; i < this->objectList.size(); i++){
        objectList[i]->setScale(xScale, yScale);
        for(unsigned int j = 0; j < this->objectList[i]->hitBoxes.size(); j++){
            objectList[i]->hitBoxes[j]->width *= xScale;
            objectList[i]->hitBoxes[j]->height *= yScale;
        }
    }
}

Scene::~Scene(){
	for(unsigned int i = 0; i < this->objectList.size(); i++){
		if(this->objectList[i]!=NULL){
			delete objectList[i];
		}
	}
	for(unsigned int i = 0; i < this->viewList.size(); i++){
		if(this->viewList[i]!=NULL){
			delete viewList[i];
		}
	}
}

