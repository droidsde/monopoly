#include "Strength_up.h"


Strength_up* Strength_up::create()
{
	Strength_up* strength_up = new Strength_up();
	strength_up->init();
	strength_up->autorelease();
	return strength_up;	
}


void Strength_up:: onExit()
{
	normal_anmi->release();
}

bool Strength_up::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("strength_up_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Strength_up::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/strength_up.plist","images/strength_up.png");

	memset(name, 0, 20);

	for (int i=1; i<=14; i++) 
	{
		sprintf(name, "strength_up_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Strength_up::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("strength_up_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.1f),"strength_up_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("strength_up_animation"));
	 normal_anmi->retain();
}