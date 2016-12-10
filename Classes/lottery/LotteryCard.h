#ifndef __LOTTERY_CARD_H__
#define __LOTTERY_CARD_H__
 
#include "cocos2d.h"
#include "Util.h"
USING_NS_CC;

class LotteryCard : public Sprite
{
public:
    //��ʼ������ֵ����ȣ��߶ȣ���ƬX�ᣬ��ƬY��
    static LotteryCard* createCardSprite(int numbers,int width,int height,float CardSpriteX,float CardSpriteY);
    virtual bool init();
    CREATE_FUNC(LotteryCard);
 
    //��ȡ����
    int getLotteryNumber();
    //��������
   // void setLotteryNumber(int num);
	void lotteryCardCallback(Object* pSender);
	void setUnSelected();
	void setLotteryCardCallback(Object* target, SEL_CallFuncN callfun);
private:
    //��ʾ�ڽ����е�����
    int lotteryNumber;
    void cardInit(int numbers,int width,int height,float CardSpriteX,float CardSpriteY);
    MenuItemImage* ballMenuImage;
    //������ʾ���ֵĿؼ�
    LabelTTF* labelLotteryNumber;
    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
    //��ʾ����
    LayerColor* layerColorBG;
	 CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;
};
 
#endif 