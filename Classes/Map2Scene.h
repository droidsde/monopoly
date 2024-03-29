#ifndef __MAP2_SCENE_H__
#define __MAP2_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"

USING_NS_CC;


class Map2Scene: public GameBaseScene
{
public:
     static Scene* createScene();
	 void addMap();
	 void initTiledGrid();
	 void initPropTiledID();
     virtual bool init();  
   
	CREATE_FUNC(Map2Scene);

private:

};

#endif