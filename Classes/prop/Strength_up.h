#ifndef __PROP_STRENGTH_UP_H__
#define __PROP_STRENGTH_UP_H__

#include "cocos2d.h"
#include "ConstUtil.h"

USING_NS_CC;

class Strength_up : public Sprite
{
public:
	static Strength_up* create();
	bool init();
	void addItemSpriteFrameCache();
	void onExit();
	CC_SYNTHESIZE(Animate* ,normal_anmi,Normal_anmi);

private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];
	Vector<SpriteFrame*> item_anim_vector;
	void setItemAnimate();

};

#endif