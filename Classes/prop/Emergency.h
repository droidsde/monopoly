#ifndef __PROP_EMERGENCY_H__
#define __PROP_EMERGENCY_H__

#include "cocos2d.h"
#include "ConstUtil.h"

USING_NS_CC;

class Emergency : public Sprite
{
public:
	bool init();
	void addItemSpriteFrameCache();
	static Emergency* create();
	CC_SYNTHESIZE(Animate* ,car_go_anmi2,Car_go_anmi);
	CC_SYNTHESIZE(Animate* ,car_stop_anmi,Car_stop_anmi);
	void onExit();
	Vector<SpriteFrame*> item_cargo_anim_vector;
	Vector<SpriteFrame*> item_carstop_anim_vector;

private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];
	void setItemAnimate();
};

#endif