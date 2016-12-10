#include "Stretcher.h"

Stretcher* Stretcher::create()
{
	Stretcher* stretcher = new Stretcher();
	stretcher->init();
	stretcher->autorelease();
	return stretcher;
}

void Stretcher::onExit()
{

	stretcher_empty_anmi->release();
	stretcher_full_anmi->release();
}

bool Stretcher::init()
{
	memset(name, 0, 20);
	addItemSpriteFrameCache();
	SpriteFrame* spf;
	spf = itemSpriteFrameCache->getSpriteFrameByName("stretcher01_empty.png");
	setItemAnimate();
	Sprite::initWithSpriteFrame(spf);
	
	return true;
}

void Stretcher::addItemSpriteFrameCache()
{
	itemSpriteFrameCache = SpriteFrameCache::getInstance();
	itemSpriteFrameCache->addSpriteFramesWithFile("images/stretcher_empty.plist","images/stretcher_empty.png");
	itemSpriteFrameCache->addSpriteFramesWithFile("images/stretcher.plist","images/stretcher.png");

	memset(name, 0, 20);

	for (int i=1; i<=8; i++) 
	{
		sprintf(name, "stretcher%02d_empty.png",i);
		item_stretcher_empty_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}

	for (int i=1; i<=8; i++) 
	{
		sprintf(name, "stretcher%02d.png",i);
		item_stretcher_full_anim_vector.pushBack(itemSpriteFrameCache->getSpriteFrameByName(name));
	}
}

void Stretcher::setItemAnimate()
{
	

	if(!AnimationCache::getInstance()->getAnimation("stretcher_empty_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_stretcher_empty_anim_vector,0.1f),"stretcher_empty_animation");
	}
	 stretcher_empty_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("stretcher_empty_animation"));
	 stretcher_empty_anmi->retain();


	if(!AnimationCache::getInstance()->getAnimation("stretcher_full_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(item_stretcher_full_anim_vector,0.1f),"stretcher_full_animation");
	}
	 stretcher_full_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("stretcher_full_animation"));
	 stretcher_full_anmi->retain();
}