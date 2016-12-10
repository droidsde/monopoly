#ifndef __PROP__STRETCHER_H__
#define __PROP__STRETCHER_H__

#include "cocos2d.h"
#include "ConstUtil.h"
USING_NS_CC;


class Stretcher : public Sprite
{
public:
	void onExit();
	bool init();
	void addItemSpriteFrameCache();
	static Stretcher* create();

	CC_SYNTHESIZE(Animate* ,stretcher_empty_anmi,Stretcher_empty_anmi);
	CC_SYNTHESIZE(Animate* ,stretcher_full_anmi,Stretcher_full_anmi);

	Vector<SpriteFrame*> item_stretcher_empty_anim_vector;
	Vector<SpriteFrame*> item_stretcher_full_anim_vector;
private:
	SpriteFrameCache* itemSpriteFrameCache;
	char name[20];

	void setItemAnimate();

};

#endif