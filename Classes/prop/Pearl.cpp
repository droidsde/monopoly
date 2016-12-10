#include "Pearl.h"


Pearl* Pearl::create()
{
	Pearl* pearl = new Pearl();
	pearl->init();
	pearl->autorelease();
	return pearl;
}

void Pearl::onExit()
{
	normal_anmi->release();
}

bool Pearl::init()
{
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("ball_01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

void Pearl::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/ball.plist","images/ball.png");

	memset(name, 0, 20);

	for (int i=1; i<=3; i++) 
	{
		sprintf(name, "ball_%02d.png",i);
		item_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

}

void Pearl::setItemAnimate()
{
	if(!AnimationCache::getInstance()->getAnimation("ball_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_anim_vector,0.4f),"ball_animation");
	}
	 normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("ball_animation"));
	 normal_anmi->retain();
}