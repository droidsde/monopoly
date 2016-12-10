#ifndef __Richer_PopupLayer__
#define __Richer_PopupLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "lottery/LotteryCard.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"

USING_NS_CC;
using namespace cocos2d::extension;
const int Pop_FontSize = 20;
const int save_map1_tag = 1;
const int save_map2_tag = 2;
const int save_map3_tag = 3;

enum POP_TYPE
{
	NORMAL,
	LOTTERY,
	LOTTERY_PUBLISH,
	LOADGAME
};

class PopupLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PopupLayer);

	POP_TYPE pop_type;
	void setPopType(POP_TYPE type);
	void setPopModalDialog(bool mD);
	static PopupLayer * create(const char* backgroundImage);
	void setTitle(const char* title ,int fontsize=Pop_FontSize);
	void setContentText(const char* text ,int fontsize=Pop_FontSize ,int padding=50 ,int paddintTop=100);
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag=0);
	virtual void onEnter();
	virtual void onExit();

	void setLotteryContext(Size size);
	Vector<LotteryCard*> lotteryVector;
	void refreshBallBackGround(Node *pNode);
	int lottery_selected;
	std::vector<int> selected_number_vector;
	void setHasSelectedLotteryNumber(std::vector<int> _vector);
	void setPlayerVector(Vector<RicherPlayer*> _vector);
	Vector<RicherPlayer*> players_vector;
private:
	void buttonCallback(Object* pSender);
	int m_contentPadding = 0;
	int m_contentPaddingTop = 0;;
    Object* m_callbackListener;
    SEL_CallFuncN m_callback;
    CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);
	CC_SYNTHESIZE(int, dataTag, DataTag);

	Sprite* m_turnBg;
	void setPublishLotteryContext(Size size);
	void addPlayersInfo(Size size);
	void onTurnEnd();
	void dismissFromParent(float dt);
	void addPlayersLottery();
	Vector<LabelTTF*> playerLotteryVector;
	void runPublishAnmi();
	void realRunPublishAnmi(float dt);
	int lottNumber;
	LabelTTF* labelLotteryMoney;
	Sprite* lottery_win_1;
	Sprite* lottery_win_2;
	int lottery_total_money;
	MenuItemImage* map1LoadGameMenuItem;
	MenuItemImage* map2LoadGameMenuItem;
	MenuItemImage* map3LoadGameMenuItem;
	void setLoadGameContext(Size size);
	void loadGameButtonCallback(cocos2d::CCObject *pSender);
	void sendLoadGameMSG();
	int mapLevelTag;
	void playParticle(Point point, char* plistName);
};

#endif