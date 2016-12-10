#ifndef __GAME_BASE_SCENE_H__
#define __GAME_BASE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"
#include "RouteNavigation.h"
#include "Util.h"
#include "popupLayer\PopupLayer.h"
#include "popupLayer\CocosToast.h"
#include "prop\Strength_up.h"
#include "prop\Bee.h"
#include "prop\Fog.h"
#include "prop\Stretcher.h"
#include "prop\Emergency.h"
#include "prop\Pearl.h"
#include "stock\LineChart.h"
#include "skill\SkillCard.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace  rapidjson;

const int tableStartPosition_x = 650;
const int tableStartPosition_y = 450;
const int tableWidth = 50;
const int tableHeight = 40;
const int tiledWidth = 32;
const int tiledHeight = 32;

const int goButtonTag = 700;
const int skillButtonTag = 701;
const int skillStormTag = 702;
const int skillStepTag = 703;
const int skillTransferTag = 704;
const int saveButtonTag = 705;
const int audioButtonTag = 706;
const int backButtonTag = 707;
const int stepBaseTag = 800;
const int step1_tag = stepBaseTag + 1;
const int step2_tag = stepBaseTag + 2;
const int step3_tag = stepBaseTag + 3;
const int step4_tag = stepBaseTag + 4;
const int step5_tag = stepBaseTag + 5;
const int step6_tag = stepBaseTag + 6;

const int skillSpriteCardWidth = 150;
const int skillSpriteCardHeight = 100;
const float stepSkillAnimaTime = 0.1;

class GameBaseScene: public Layer
{
public:
    static Scene* createScene();
  	static TMXTiledMap* _map;
    virtual bool init();  

    CREATE_FUNC(GameBaseScene);

	static int tiledColsCount;
	static int tiledRowsCount;
	static bool** canPassGrid;
	static TMXLayer* landLayer;
	static TMXLayer* wayLayer;
	std::vector<Vec2> wayLayerPass_vector;
	CC_SYNTHESIZE(Menu*, _menu, Menu);
	CC_SYNTHESIZE(LabelTTF *, player1_money_label, Player1_money_label);
	CC_SYNTHESIZE(LabelTTF *, player2_money_label, Player2_money_label);
	CC_SYNTHESIZE(LabelTTF *, player1_strength_label, Player1_strength_label);
	CC_SYNTHESIZE(LabelTTF *, player2_strength_label, Player2_strength_label);
	MenuItemImage* goMenuItemButton;
	int randStepsNumber;

	void setWayPassToGrid();
	void onExit();
	void addGoButton();
	void menuButtonCallback(Object* pSender);
	void onReceiveCustomEvent(EventCustom* event);
	EventListenerCustom* customListener;
	RicherPlayer* player1;
	RicherPlayer* player2;

	static Vector<RicherPlayer*> players_vector;
	static Vector<Sprite*> pathMarkVector;
	static void drawPathColor(std::vector<int> rowVector, std::vector<int> colVector);
	static int blank_land_tiledID;
	static int strength_30_tiledID;
	static int strength_50_tiledID;
	static int strength_80_tiledID;

	static int randomEvent_tiledID;
	static int lottery_tiledID;
	static int stock_tiledID;

	static int player1_building_1_tiledID;
	static int player1_building_2_tiledID;
	static int player1_building_3_tiledID;

	static int player2_building_1_tiledID;
	static int player2_building_2_tiledID;
	static int player2_building_3_tiledID;
	int map_level;
	char* saveJsonName;
	bool reloadGame(int map_level);
private:

	void drawTable(int playerNumber);
	void addPlayer();
	void addRightBanner();
	void addNotificationObserver();
	void receivedNotificationMsg(Object* data);
	void addDigiteRoundSprite();
	int gameRoundCount;
	Vector<SpriteFrame*>  digiteRoundVector;
	Vector<Sprite*> refreshRoundVector;
	void refreshRoundDisplay();
	void addPathMark();
	PopupLayer* popDialog;
	void initPopDialog();
	void initLandLayerFromMap();
	int buy_land_x;
	int buy_land_y;
	void  showBuyLandDialog(int landTag);
	void buyLandCallback(Node *pNode);
	void doSomeForParticle();
	FadeOut* landFadeOut;
	FadeIn* landFadeIn;
	Sprite* foot1Sprite;
	Sprite* foot2Sprite;
	Sprite* starFish1Sprite;
	Sprite* starFish2Sprite;
	Sprite* heart1Sprite;
	Sprite* heart2Sprite;
	ActionInterval * scaleby1ForBuyLand;
	ActionInterval * scaleby2ForBuyLand;
	void playParticle(Point point, char* plistName);
	void buyLand(int buyTag, float x, float y, Sprite* landSprite, int landLevel, RicherPlayer* player, char* particlelistName);
	void refreshMoneyLabel(RicherPlayer* player, int money);
	char money1[20];
	char money2[20];
	void payTolls(int payTag, float x, float y, int playerTag);
	RicherPlayer* getPlayerByTiled(float x, float y);
	Vector<Sprite*> displayVector;
	int displayArea(float x, float y, RicherPlayer* player, int building_1_tiledID, int building_2_tiledID, int building_3_tiledID);
	void sendMSGPickOneToGO();
	Map<int, __String*> randomAskEventMap;
	void initRandomAskEvent();
	void sendMSGDealAroundLand();
	void doRandomAskEvent(RicherPlayer* player);
	char strength1[20];
	char strength2[20];
	void refreshStrengthLabel(RicherPlayer* player, int strength);
	void initPropSprite();
	void doItemStrengthUp(int strengthUp, int playerTag);
	Strength_up* _strength_up;
	Bee* _bee;
	Fog* _fog;
	Stretcher* _stretcher;
	Emergency* _emergency;
	Pearl* _pearl;
	void registerBlockWaySchedule();
	void updateBlockWaySprites(float dt);
	void doBlockWayEvent(RicherPlayer* player);
	void endCarGo(int tag);
	void setPlayerAndFogInVisible(int tag);
	void startCarGoAgain();
	void sendMSGDealProp();
	int moveTag;
	void sendMSGMoveOneStep();
	void lotteryBuyOrCancelCallback(Node *pNode);
	void popPublishLottery(float dt);
	PopupLayer* popDialogLottery;
	void initPopPublishLottery();
	vector<int> stock_pointvec1;
	vector<int> stock_pointvec2;
	vector<int> stock_pointvec3;
	vector<int> stock_pointvec4;
	vector<int> stock_pointvec5;
	Vector<Stock*> stockVector;
	void updateStockVec();
	void doStockDeal(RicherPlayer* player, int moveTag);
	void initStockVector(RicherPlayer* player);

	void addMenuButton();
	void addStepButton(MenuItemImage* stepItem,  int tag);
	void addSkillMenuButton();
	MenuItemImage* skillMenuItemButton;
	MenuItemImage* step1Button;
	MenuItemImage* step2Button;
	MenuItemImage* step3Button;
	MenuItemImage* step4Button;
	MenuItemImage* step5Button;
	MenuItemImage* step6Button;

	SkillCard* skillStorm;
	SkillCard* skillStep;
	SkillCard* skillTransfer;
	bool isSkillLayerShow;
	bool isStepLayerShow;
	void skillClick(Node *pNode);
	void showSkillSprites();
	void showStepButton(bool show);
	Sprite* rainSprite;
	Sprite* transferSprite;
	int transferLandTag;
	void showGoButton();
	MenuItemImage* saveMenuItemButton;
	void addSaveMenuButton();
	bool saveGame();
	void receivedNotificationOMsg(Object* data);
	void playerBgMusic(float fDelta);
	vector<char*> bgMusicVector;
	void initAudioEffect();


	Vector<String*> player1EffectVec_1;//交过路费声音
	Vector<String*> player1EffectVec_2;//抢夺别人地块
	Vector<String*> player1EffectVec_3;//房屋被抢夺
	Vector<String*> player1EffectVec_4;//摧毁别人房屋
	Vector<String*> player1EffectVec_5;//房屋被摧毁
	Vector<String*> player1EffectVec_6;//螃蟹伤人

	Vector<String*> player1EffectVec_7;//看到别人住院
	Vector<String*> player1EffectVec_8; // 收取过路费
	Vector<String*> player1EffectVec_9;//升级房子
	Vector<String*> player1EffectVec_10; // 不交过路费
	Vector<String*> player1EffectVec_11; // 买地
	Vector<String*> player1EffectVec_12;//捡到珍珠
	Vector<String*> player1EffectVec_13;//对方被罚收税



	Vector<String*> player2EffectVec_1;//交过路费声音
	Vector<String*> player2EffectVec_2;//抢夺别人地块
	Vector<String*> player2EffectVec_3;//房屋被抢夺
	Vector<String*> player2EffectVec_4;//摧毁别人房屋
	Vector<String*> player2EffectVec_5;//房屋被摧毁
	Vector<String*> player2EffectVec_6;//螃蟹伤人

	Vector<String*> player2EffectVec_7;//看到别人住院
	Vector<String*> player2EffectVec_8; // 收取过路2
	Vector<String*> player2EffectVec_9;//升级房子
	Vector<String*> player2EffectVec_10; // 不交过路费
	Vector<String*> player2EffectVec_11; // 买地
	Vector<String*> player2EffectVec_12;//捡到珍珠
	Vector<String*> player2EffectVec_13;//对方被罚收税
	Vector<String*> nextPlayerEffectVec;
	void playNextEffectVec(float t);
	void addAudioMenuButton();
	void addBackMenuButton();
	MenuItemImage* audioMenuItemButton;
	MenuItemImage* backMenuItemButton;
	void quitButtonCallback(Node *pNode);
	int priceIndex;
	void raisePriceIndex();
	CC_SYNTHESIZE(LabelTTF *, priceIndex_label, PriceIndex_label);
	void addPriceIndexLabel();
	void refreshPriceIndexLabel();
};

#endif