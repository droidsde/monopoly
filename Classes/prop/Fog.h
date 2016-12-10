#ifndef __PROP_FOG_H__
#define __PROP_FOG_H__

#include "cocos2d.h"
#include "ConstUtil.h"
USING_NS_CC;

class Fog : public Sprite
{
public:
	static Fog* create();
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