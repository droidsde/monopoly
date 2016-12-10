#include "Fog.h"


Fog* Fog::create()
{
	Fog* fog = new Fog();
	fog->init();
	fog->autorelease();
	return fog;
}

void Fog::onExit()
{
	normal_anmi->release();
}

bool Fog::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("fog_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Fog::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/fog.plist","images/fog.png");

	memset(name, 0, 20);

	for (int i=1; i<=7; i++) 
	{
		sprintf(name, "fog_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Fog::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("fog_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.2f),"fog_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("fog_animation"));
	 normal_anmi->retain();
}