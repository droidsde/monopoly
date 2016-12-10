#ifndef __PROP_PEARL_H__
#define __PROP_PEARL_H__

#include "cocos2d.h"
#include "ConstUtil.h"

USING_NS_CC;


class Pearl : public Sprite
{
public:
	static Pearl* create();
	bool init();
	void onExit();
	void addItemSpriteFrameCache();
	CC_SYNTHESIZE(Animate* ,normal_anmi,Normal_anmi);
private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];
	Vector<SpriteFrame*> item_anim_vector;
	void setItemAnimate();
};

#endif