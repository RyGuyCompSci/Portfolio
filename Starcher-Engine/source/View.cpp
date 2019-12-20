#include "headers/View.hpp"
#include "headers/Globals.hpp"
#include <iostream>

using namespace std;

View::View(int winX, int winY, int sceneX, int sceneY, int width, int height){
	this->windowX = winX;
	this->windowY = winY;
	this->sceneX = sceneX;
	this->sceneY = sceneY;
	this->width = width;
	this->height = height;
	this->following = NULL;
	this->followX = this->windowX + (width/2);
	this->followY = this->windowY + (height/2);
	this->followWidth = 3*(width/4);
	this->followHeight = 3 * (height/4);
	this->sceneID = 0;
}

void View::setSceneID(int id){
	this->sceneID = id;
	this->sceneWidth = getSceneWidth(id);
	this->sceneHeight = getSceneHeight(id);
}

void View::setFollowing(Object *follow,int followWidth, int followHeight){
	this->following = follow;
	this->followWidth = followWidth;
	this->followHeight = followHeight;
}

void View::setFollowMiddle(int winX, int winY){
	this->followX = winX;
	this->followY = winY;
}

struct position View::translate(int x, int y){ //NEEDS TESTING
	struct position newPos;

	newPos.x = (x - sceneX) + windowX;
	newPos.y = (y - sceneY) + windowY;

	return newPos;

}

void View::_process(double delta){
	//Get correct width/height of scene
	if(this->sceneWidth < 0){
		this->sceneWidth = getSceneWidth(this->sceneID);
	}
	if(this->sceneHeight < 0){
		this->sceneHeight = getSceneHeight(this->sceneID);
	}
	this->follow();
	return;
}

void View::follow(){ //FIXME
	if(this->following==NULL){
		return;
	}else{
		//Translate object scene position to window position
		int objSceneX = this->following->x;
		int objSceneY = this->following->y;
		struct position winPos = this->translate(objSceneX,objSceneY);
		int objWinX = winPos.x;
		int objWinY = winPos.y;
		//Determine the boundaries for following
		int maxX = this->followX + (followWidth/2);
		int minX = this->followX - (followWidth/2);
		int maxY = this->followY + (followHeight/2);
		int minY = this->followY - (followHeight/2);
		//Move view's position on scene based on object's position on screen
		if(objWinX > maxX){
			if(objWinX - maxX > 2 && (( (sceneX+width) + ((objWinX - maxX)/2)) < sceneWidth)){
				this->sceneX += (objWinX - maxX) / 2;
			}else if((sceneX+width) + 2 < sceneWidth){
				this->sceneX += 2;
			}
	//		std::cout << "SceneX = " << this->sceneX  << endl;
	//		std::cout << "sceneWidth: " << sceneWidth << endl;
		}
		else if(objWinX < minX){
			if(minX - objWinX > 2 && ((sceneX - (minX - objWinX)/2) > 0)){
				this->sceneX -= (minX - objWinX) / 2;
			}else if(sceneX - 2 > 0){
				this->sceneX -= 2;
			}
		}
		if(objWinY > maxY){
			if(objWinY - maxY > 2 && (( (sceneY+height) + ((objWinY - maxY)/2)) < sceneHeight)){
				this->sceneY += (objWinY - maxY) / 2;
			}else if( (sceneY+height) + 2 < sceneHeight){
				this->sceneY += 2;
			}
		}
		else if(objWinY < minY){
			if(minY - objWinY > 2 && ((sceneY - (minY - objWinY)/2) > 0)){
				this->sceneY -= (minY - objWinY) / 2;
			}else if(sceneY - 2 > 0){
				this->sceneY -= 2;
			}
		}
		return; 
	}
}

bool View::inView(Object* obj){
    //Always render things without hitboxes
    if(obj->hitBoxes.size() == 0){
        int x = obj->x + obj->sprite->xOffset;
        int y = obj->y + obj->sprite->yOffset;

        if((x + obj->sprite->width < this->sceneX || x > this->sceneX + this->width || y + obj->sprite->height < this->sceneY || y > this->sceneY + this->height)){
            return false;
        }
    }else{
        for(unsigned int i = 0; i < obj->hitBoxes.size(); i++){
            int x = obj->x + obj->hitBoxes[i]->offsetX;
            int y = obj->y + obj->hitBoxes[i]->offsetY;

            if(x + obj->hitBoxes[i]->width < this->sceneX || x > this->sceneX + this->width || y + obj->hitBoxes[i]->height < this->sceneY || y > this->sceneY + this->height){
                return false;
            }
        }
    }
    return true;
}
