#include "Emergency.h"

Emergency* Emergency::create()
{
	Emergency* emergency = new Emergency();
	emergency->init();
	emergency->autorelease();
	return emergency;
}

void Emergency::onExit()
{
	car_go_anmi2->release();
	car_stop_anmi->release();
}

bool Emergency::init()
{
	memset(name, 0, 20);
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("car_01.png");
	setItemAnimate();
	Sprite::initWithSpriteFrame(spf);
	
	return true;
}

void Emergency::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/car.plist","images/car.png");
	memset(name, 0, 20);
	for (int i=1; i<=2; i++) 
	{
		sprintf(name, "car_%02d.png",i);
		item_cargo_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

	for (int i=3; i<=4; i++) 
	{
		sprintf(name, "car_%02d.png",i);
		item_carstop_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}
}

void Emergency::setItemAnimate()
{
	
	if(!AnimationCache::getInstance()->getAnimation("car_go_animation2"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_cargo_anim_vector,0.1f),"car_go_animation2");
	}
	 car_go_anmi2 = Animate::create(AnimationCache::getInstance()->getAnimation("car_go_animation2"));
	 car_go_anmi2->retain();


	if(!AnimationCache::getInstance()->getAnimation("car_stop_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_carstop_anim_vector,0.5f),"car_stop_animation");
	}
	 car_stop_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("car_stop_animation"));
	 car_stop_anmi->retain();
}