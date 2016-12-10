#include "GameBaseScene.h"

int GameBaseScene::tiledColsCount;
int GameBaseScene::tiledRowsCount;
bool** GameBaseScene::canPassGrid;
TMXLayer* GameBaseScene::wayLayer;
Vector<RicherPlayer*>  GameBaseScene::players_vector;
Vector<Sprite*> GameBaseScene::pathMarkVector;
TMXTiledMap* GameBaseScene::_map;
TMXLayer* GameBaseScene::landLayer;
int  GameBaseScene::blank_land_tiledID;
int  GameBaseScene::strength_30_tiledID;
int  GameBaseScene::strength_50_tiledID;
int  GameBaseScene::strength_80_tiledID;

int  GameBaseScene::randomEvent_tiledID;
int  GameBaseScene::lottery_tiledID;
int  GameBaseScene::stock_tiledID;

int GameBaseScene::player1_building_1_tiledID;
int GameBaseScene::player1_building_2_tiledID;
int GameBaseScene::player1_building_3_tiledID;

int GameBaseScene::player2_building_1_tiledID;
int GameBaseScene::player2_building_2_tiledID;
int GameBaseScene::player2_building_3_tiledID;

Scene* GameBaseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameBaseScene::create();

	scene->addChild(layer);

	return scene;

}

bool GameBaseScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	addRightBanner();
	drawTable(2);
	setWayPassToGrid();
	addPathMark();
	priceIndex = 1;
	addPriceIndexLabel();
	addPlayer();
	addMenuButton();
	addNotificationObserver();
	addDigiteRoundSprite();
	refreshRoundDisplay();
	initLandLayerFromMap();
	initPropSprite();
	initPopDialog();
	doSomeForParticle();
	initRandomAskEvent();
	registerBlockWaySchedule();
	initPopPublishLottery();
	initAudioEffect();

	return true;
}

void  GameBaseScene::addRightBanner()
{
	Sprite* rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setAnchorPoint(ccp(0,0));
	rightBanner->setPosition( ccp(tableStartPosition_x, 0));
	addChild(rightBanner);
}


void GameBaseScene:: addPlayer()
{
	Sprite* player_1 = Sprite::create(PLAYER_1);
	player_1->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - tableHeight);
	addChild(player_1);

	player1_money_label = LabelTTF::create();
	player1_money_label->setString("$");
	player1_money_label->setAnchorPoint(ccp(0, 0.5));
	player1_money_label->setFontSize(20);
	player1_money_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2);
	addChild(player1_money_label);

	player1_strength_label = LabelTTF::create();
	player1_strength_label->setString("+");
	player1_strength_label->setAnchorPoint(ccp(0, 0.5));
	player1_strength_label->setFontSize(20);
	player1_strength_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3);
	addChild(player1_strength_label);

	Sprite* player_2 = Sprite::create(PLAYER_2);
	player_2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
	addChild(player_2);

	player2_money_label = LabelTTF::create();
	player2_money_label->setString("$");
	player2_money_label->setAnchorPoint(ccp(0, 0.5));
	player2_money_label->setFontSize(20);
	player2_money_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5);
	addChild(player2_money_label);

	player2_strength_label = LabelTTF::create();
	player2_strength_label->setString("+");
	player2_strength_label->setAnchorPoint(ccp(0, 0.5));
	player2_strength_label->setFontSize(20);
	player2_strength_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7);
	addChild(player2_strength_label);


	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
	player1 = RicherPlayer::create(PLAYER_1_NAME, PLAYER_1_TAG);
	int _rand1 = rand() % (wayLayerPass_vector.size());
	log("rand %d", _rand1);
	Vec2 vec2ForPlayer1 = wayLayerPass_vector.at(_rand1);
	vec2ForPlayer1.y += tiledHeight;
	player1->setPosition(vec2ForPlayer1);
	player1->setAnchorPoint(ccp(0, 0.5));
	addChild(player1);
	players_vector.pushBack(player1);

	player2 = RicherPlayer::create(PLAYER_2_NAME, PLAYER_2_TAG);
	int _rand2 = rand() % (wayLayerPass_vector.size());
	log("rand %d", _rand2);
	Vec2 vec2ForPlayer2 = wayLayerPass_vector.at(_rand2);
	vec2ForPlayer2.y += tiledHeight;
	player2->setPosition(vec2ForPlayer2);
	player2->setAnchorPoint(ccp(0, 0.5));
	addChild(player2);
	players_vector.pushBack(player2);

	memset(money1, 0, 20);
	sprintf(money1, "$ %d", player1->getMoney());
	getPlayer1_money_label()->setString(money1);

	memset(money2, 0, 20);
	sprintf(money2, "$ %d", player1->getMoney());
	getPlayer2_money_label()->setString(money2);


	memset(strength1, 0, 20);
	sprintf(strength1, "+ %d", player1->getStrength());
	getPlayer1_strength_label()->setString(strength1);

	memset(strength2, 0, 20);
	sprintf(strength2, "+ %d", player1->getStrength());
	getPlayer2_strength_label()->setString(strength2);
}

void GameBaseScene:: drawTable(int playerNumber)
{
	auto s = Director::getInstance()->getWinSize();
	
	auto draw = DrawNode::create();
	this->addChild(draw);

	for(int i=0;i<playerNumber;i++)
	{
		draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y-2*i*tableHeight), 
						  Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y-2*i*tableHeight), 1, 
						  Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y - 2*(i+1)*tableHeight), 
						  Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - 2*(i+1)*tableHeight), 1, 
						  Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 
						  Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 1, 
						  Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2*i*tableHeight), 
						  Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2* tableHeight-2*i*tableHeight), 1, 
						  Color4F(0, 1, 0, 1));
	}
}

void  GameBaseScene::setWayPassToGrid()
{
	wayLayer = _map->layerNamed("way");

	Size _mapSize = wayLayer->getLayerSize();
	for (int j = 0; j < _mapSize.width; j++) {
		for (int i = 0; i < _mapSize.height; i++) {
			Sprite* _sp = wayLayer->tileAt(Point(j, i));
			if (_sp)
			{
				float x = _sp->getPositionX();
				float y = _sp->getPositionY();
				int col = x / tiledWidth;
				int row = y / tiledHeight;
				canPassGrid[row][col] = true;
				Vec2 p = _sp->getPosition();
				wayLayerPass_vector.push_back(p);
				log("canPassGrid row=  %d ,col =%d ,canpass = %d", row, col, canPassGrid[row][col]);
			}

		}
	}
	log("setWayPassToGrid finished");
}

void  GameBaseScene::addGoButton()
{
	Menu* menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenu(menu);
	goMenuItemButton = MenuItemImage::create("button/go_normal.png", "button/go_press.png", this, menu_selector(GameBaseScene::menuButtonCallback));

	goMenuItemButton->setPosition(ccp(tableStartPosition_x + 2 * tableWidth, tableStartPosition_y - tableHeight * 6));
	goMenuItemButton->setTag(goButtonTag);
	menu->addChild(goMenuItemButton);
	addChild(menu);
}

void GameBaseScene::menuButtonCallback(Object *pSender)
{
	Util::playAudioEffect(click_effect, false);
	Size winSize = Director::getInstance()->getWinSize();
	int tag = ((Node*)pSender)->getTag();
	if (tag == goButtonTag)
	{
		if (isSkillLayerShow)
		{
			showSkillSprites();
		}
		log("go button clicked");
		randStepsNumber = rand() % 6 + 1;
		RouteNavigation::getInstance()->getPath(player1, randStepsNumber, canPassGrid, tiledRowsCount, tiledColsCount);
		std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
		std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRow_vector();

		for (int i = 0; i < rowVector.size(); i++)
		{
			log(" rowVector row is %d --- colVector col is %d", rowVector[i], colVector[i]);
		}
		Util::sendCustomEvent(RICHER_MSG, String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		player1->startGo(rowVector, colVector);
		log("go button clicked over");
	}
	
	if (tag == skillButtonTag)
	{
		//String::createWithFormat("%s: %d /5",LanguageString::getInstance()->getLanguageString(GRADE),player1->skillMap.at(0));
		skillStorm->updateGradeLabel(player1->skill_vector.at(0));
		skillStep->updateGradeLabel(player1->skill_vector.at(1));
		skillTransfer->updateGradeLabel(player1->skill_vector.at(2));

		skillStorm->updateStengthLabel(80 - player1->skill_vector.at(0) * 10);
		skillStep->updateStengthLabel(60 - player1->skill_vector.at(1) * 10);
		skillTransfer->updateStengthLabel(110 - player1->skill_vector.at(2) * 10);

		showSkillSprites();

	}

	if (tag == step1_tag || tag == step2_tag || tag == step3_tag || tag == step4_tag || tag == step5_tag || tag == step6_tag)
	{

		int needLostStrength = 60 - player1->skill_vector.at(1) * 10;
		if (player1->getStrength() >= needLostStrength)
		{
			player1->setStrength(player1->getStrength() - needLostStrength);
			refreshStrengthLabel(player1, 0);
			showSkillSprites();

			int steps = tag - stepBaseTag;
			RouteNavigation::getInstance()->getPath(player1, steps, canPassGrid, tiledRowsCount, tiledColsCount);
			std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
			std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRow_vector();
			Util::sendCustomEvent(RICHER_MSG, String::createWithFormat("%d", MSG_GO_HIDE_TAG));
			player1->startGo(rowVector, colVector);
		}
		else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
				TOAST_SHOW_TIME,
				winSize / 2);
		}

	}
	if (tag == saveButtonTag)
	{
		if (saveGame())
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(SAVE_SUCESS)->getCString(),
				TOAST_SHOW_TIME,
				winSize / 2);
		}
		else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(SAVE_FAIL)->getCString(),
				TOAST_SHOW_TIME,
				winSize / 2);
		}

	}
	if (tag == audioButtonTag)
	{
		bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);

		if (music_on)
		{
			Util::stopAudioPlay();
			UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY, false);
			audioMenuItemButton->selected();
		}
		else
		{
			Util::playBgMusic(bgMusicVector.at(rand() % bgMusicVector.size()), false);
			UserDefault::getInstance()->setBoolForKey(MUSIC_ON_KEY, true);
			audioMenuItemButton->unselected();
		}
	}
	if (tag == backButtonTag)
	{
		PopupLayer* popDialog = PopupLayer::create(DIALOG_BG);
		popDialog->setContentSize(CCSizeMake(400, 200));
		popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
		popDialog->setContentText(LanguageString::getInstance()->getLanguageString(DIALOG_CONTENT)->getCString(), 20, 60, 250);
		popDialog->setPopModalDialog(true);
		popDialog->setCallbackFunc(this, callfuncN_selector(GameBaseScene::quitButtonCallback));
		popDialog->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(OK)->getCString(), Quit_OK_TAG);
		popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Quit_Cancel_TAG);
		this->addChild(popDialog);
	}
}

void GameBaseScene::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(customListener);
	CC_SAFE_DELETE(canPassGrid);
	scaleby1ForBuyLand->release();
	scaleby2ForBuyLand->release();
	landFadeOut->release();
	landFadeIn->release();
	NotificationCenter::getInstance()->removeObserver(this,MSG_LOAD_GAME);
	players_vector.clear();
	Layer::onExit();

}

void GameBaseScene::addNotificationObserver()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	customListener = EventListenerCustom::create(RICHER_MSG, CC_CALLBACK_1(GameBaseScene::onReceiveCustomEvent, this));
	dispatcher->addEventListenerWithFixedPriority(customListener, 1);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationOMsg),
		MSG_LOAD_GAME,
		NULL);
}

void GameBaseScene::receivedNotificationOMsg(Object* data)
{
	String * srcDate = (String*)data;
	Vector<String*> messageVector = Util::splitString(srcDate->getCString(), "-");
	int map_level = messageVector.at(1)->intValue();
	reloadGame(map_level);		
}

void GameBaseScene::onReceiveCustomEvent(EventCustom* event)
{
	String* srcDate = (String*)event->getUserData();
	Vector<String*> messageVector = Util::splitString(srcDate->getCString(), "-");
	int retMsgType = messageVector.at(0)->intValue();
	log("received go message is: %d", retMsgType);
	log("onCustomEvent data = %d", srcDate);
	if(messageVector.size()>3)
	{
		//stop_x = messageVector.at(1)->floatValue();
		//stop_y = messageVector.at(2)->floatValue();
		
		int playerTag = messageVector.at(3)->intValue();

		switch(playerTag)
		{
			case PLAYER_1_TAG:
			{
				player1->stop_x = messageVector.at(1)->floatValue();
				player1->stop_y = messageVector.at(2)->floatValue();
				break;
			}
			case PLAYER_2_TAG:
			{
				player2->stop_x = messageVector.at(1)->floatValue();
				player2->stop_y = messageVector.at(2)->floatValue();
				break;
			}
		}
		
	}

	switch (retMsgType)
	{
		case MSG_GO_SHOW_TAG:
		{
			if (gameRoundCount != 0 && gameRoundCount % PUBLISH_LOTTERY_FREQUENTLY == 0)
			{
				scheduleOnce(schedule_selector(GameBaseScene::popPublishLottery), 2.0f);

			}
			else
			{
				showGoButton();
			}
			break;
		}
		case  MSG_GO_HIDE_TAG:
		{
			goMenuItemButton->runAction(MoveBy::create(0.3, ccp((goMenuItemButton->getContentSize().width) * 2, 0)));
			skillMenuItemButton->runAction(MoveBy::create(0.3, ccp((skillMenuItemButton->getContentSize().width) * 2, 0)));
			break;
		}

		case MSG_BUY_BLANK_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					transferLandTag = 0;
					showBuyLandDialog(MSG_BUY_BLANK_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_11, false);
					buyLand(MSG_BUY_BLANK_TAG, buy_land_x, buy_land_y, foot2Sprite, player2_building_1_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
					break;
				}				
			}
			break;
		}

		case MSG_BUY_LAND_1_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();
			
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					transferLandTag = 0;
					showBuyLandDialog(MSG_BUY_LAND_1_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_9, false);
					buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,starFish2Sprite,player2_building_2_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);				
					break;
				}				
			}
			break;
		}	
		case MSG_BUY_LAND_2_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();
			
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					transferLandTag = 0;
					showBuyLandDialog(MSG_BUY_LAND_2_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					Util::playAudioEffectRandom(player2EffectVec_9, false);
					buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart2Sprite,player2_building_3_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					break;
				}				
			}
			break;
		}
		case MSG_PAY_TOLLS_1_TAG:		
		case MSG_PAY_TOLLS_2_TAG:
		case MSG_PAY_TOLLS_3_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();
			payTolls(retMsgType, buy_land_x, buy_land_y, playerTag);
			break;
		}
		case MSG_RANDOM_ASK_EVENT_TAG:
		{
		
			int playerTag = messageVector.at(1)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					doRandomAskEvent(player1);
					break;
				}
				case PLAYER_2_TAG:
				{
					doRandomAskEvent(player2);
					break;
				}				
			}
			
			break;
		}
		case MSG_STRENGTH_UP30_TAG:
		case MSG_STRENGTH_UP50_TAG:
		case MSG_STRENGTH_UP80_TAG:
		{
			doItemStrengthUp(retMsgType, messageVector.at(1)->intValue());
			break;
		}
		case MSG_BLOCK_WAY_EVENT_TAG:
		{
			int playerTag = messageVector.at(1)->intValue();
			int steps = messageVector.at(2)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					refreshStrengthLabel(player1, steps);
					doBlockWayEvent(player1);				
					break;
				}
				case PLAYER_2_TAG:
				{
					refreshStrengthLabel(player2, steps);
					doBlockWayEvent(player2);					
					break;
				}				
			}
			
			break;
		}
		case MSG_ROUND_COUNT_TAG:
		{
			gameRoundCount++;
			refreshRoundDisplay();		
			break;
		}	

		case MSG_REST_TAG:
		{
			int playerTag = messageVector.at(1)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					player1->setIsMyTurn(false);									
					CocosToast::createToast(this, String::createWithFormat("%s %d %s",LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(),player1->restTimes,LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);		
					refreshStrengthLabel(player1, 20);
					break;
				}
				case PLAYER_2_TAG:
				{
					player2->setIsMyTurn(false);
					CocosToast::createToast(this, String::createWithFormat("%s %d %s",LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(),player2->restTimes,LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
					refreshStrengthLabel(player2, 20);
					break;
				}				
			}
			
			break;
		}
		case MSG_LOTTERY_TAG:
		{
			int playerTag = messageVector.at(1)->intValue();
			moveTag = messageVector.at(2)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					Util::playAudioEffect(P1_need1000, false);
					PopupLayer* popDialogLottery = PopupLayer::create(DIALOG_BG);	
					popDialogLottery->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height)); 
					popDialogLottery->setTitle(LanguageString::getInstance()->getLanguageString(SELECT_LOTTERY_TITLE)->getCString());
					popDialogLottery->setContentText("", 20, 60, 250);
					popDialogLottery->setPopType(LOTTERY);
					popDialogLottery->setPopModalDialog(false);
					popDialogLottery->setCallbackFunc(this, callfuncN_selector(GameBaseScene::lotteryBuyOrCancelCallback));
					popDialogLottery->setHasSelectedLotteryNumber(player1->lottery_vector);
					popDialogLottery->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(BUY_OK)->getCString(), Btn_OK_TAG);
					popDialogLottery->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Cancel_TAG);
					this->addChild(popDialogLottery);				
					break;
				}
				case PLAYER_2_TAG:
				{
					int random_lottery_number = rand() % (LOTTERY_BALL_COUNT)+1;
					bool isBuyAllLottery = false;
					repeatForCheck:
					for(int i=0;i<player2->lottery_vector.size();i++)
					{
						if (player2->lottery_vector.size() >= 18)
						{
							isBuyAllLottery = true;
							break;
						}
						if(player2->lottery_vector.at(i) == random_lottery_number)
						{				
							random_lottery_number = rand() % (LOTTERY_BALL_COUNT)+1;
							goto repeatForCheck;
						}
						
					}
					if (!isBuyAllLottery)
					{
						player2->lottery_vector.push_back(random_lottery_number);
						refreshMoneyLabel(player2, -BUY_LOTTERY_MONEY);
						if (moveTag == GOEND)
						{
							CocosToast::createToast(this, String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(), BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand);
						}
						else if (moveTag == MOVEPASS)
						{
							CocosToast::createToast(this, String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(), BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
						}
					}else
					{
						if (moveTag == GOEND)
						{
							sendMSGDealAroundLand();
						}
						else if (moveTag == MOVEPASS)
						{
							sendMSGMoveOneStep();
						}

					}

					break;
				}				
			}
			break;
		}
		case MSG_DIMISS_DIALOG_PUBLISH_LOTTERY_TAG:
		{
			for(auto it=players_vector.begin();it!=players_vector.end();it++)
			{
				RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
				refreshMoneyLabel(player,0);
			}
			showGoButton();
			break;
		}

		case MSG_STOCK_TAG:
		{
			int playerTag = messageVector.at(1)->intValue();
			moveTag = messageVector.at(2)->intValue();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					auto lineView = LineChart::createChart(player1,stock_pointvec1,stock_pointvec2,stock_pointvec3,stock_pointvec4,stock_pointvec5);   
					lineView->setPosition(Point(0, 0));
					lineView->moveTag = moveTag;				
					addChild(lineView);
					break;
				}
				case PLAYER_2_TAG:
				{
					doStockDeal(player2,moveTag);
					break;
				}
			}			
			break;
		}	
		case MSG_STOCK_LAYER_DISMISS_TAG:
		{
			for(auto it=players_vector.begin();it!=players_vector.end();it++)
			{
				RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
				refreshMoneyLabel(player,0);
			}
			break;
		}

		case MSG_USE_SKILL_TAG:
		{
			int playerTag = messageVector.at(3)->intValue();
			int kill_index =  messageVector.at(4)->intValue();
			int needLostStrength = messageVector.at(5)->intValue();
			int landLevel = messageVector.at(6)->intValue();
			if(playerTag == PLAYER_2_TAG)
			{
				player2->setStrength(player2->getStrength()-needLostStrength);
				refreshStrengthLabel(player2,0);
				Point pointOfGL = Util::map2GL(ccp(player2->stop_x,player2->stop_y),_map);
				switch(kill_index)
				{
					case 0:
					{
						Util::playAudioEffect(STORM_EFFECT, false);
						Util::playAudioEffectRandom(player2EffectVec_4, false);
						nextPlayerEffectVec = player1EffectVec_5;
						scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);

						rainSprite = Sprite::createWithSpriteFrame(player2->getRainSkill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
						addChild(rainSprite);
						rainSprite->setAnchorPoint(ccp(0,0));
						rainSprite->setPosition(pointOfGL+ccp(-tiledWidth/2,tiledHeight/2));
						rainSprite->runAction(Sequence::create(player2->getRainSkill(),CallFunc::create([this]()
						{
							landLayer->setTileGID(blank_land_tiledID,ccp(player2->stop_x,player2->stop_y));	
							rainSprite->removeFromParent();
							Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
						}),NULL));
						break;
					}
						case 1:
						{
							
						}
						case 2:
						{
							 Util::playAudioEffect(youismine, false);
							 Util::playAudioEffectRandom(player2EffectVec_2, false);
							 nextPlayerEffectVec = player1EffectVec_3;
							 scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
							
							transferSprite = Sprite::createWithSpriteFrame(player2->getTransfer_skill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
							addChild(transferSprite);
			
							transferSprite->setAnchorPoint(ccp(0,0));
							transferSprite->setPosition(pointOfGL);
			
							transferSprite->runAction(Sequence::create(player2->getTransfer_skill(),CallFunc::create([this,landLevel]()
							{
								landLayer->setTileGID(landLevel,ccp(player2->stop_x,player2->stop_y));	
								transferSprite->removeFromParent();
								Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
							}),NULL));						
							break;
						}
				}
			}
			break;
		}

		case MSG_GAME_OVER_TAG:
		{
			int playerTag = messageVector.at(1)->intValue();
			Size winSize = Director::getInstance()->getWinSize();
			switch(playerTag)
			{
				case PLAYER_1_TAG:
				{
					Sprite* gameOver = Sprite::create("images/lose.png");
					gameOver->setPosition(winSize/2);
					addChild(gameOver);
					break;
				}
				case PLAYER_2_TAG:
				{
					playParticle(winSize/2,"images/win_particle.plist");
					Sprite* gameOver = Sprite::create("images/win.png");
					gameOver->setPosition(winSize/2);
					addChild(gameOver);
					
					break;
				}				
			}			
			break;
		}
	}
}

void GameBaseScene::addDigiteRoundSprite()
{
	gameRoundCount = 0;
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("images/digital_round.plist");

	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_0));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_1));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_2));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_3));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_4));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_5));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_6));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_7));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_8));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_9));

}
void GameBaseScene::refreshRoundDisplay()
{

	for (auto it = refreshRoundVector.begin(); it != refreshRoundVector.end(); it++)
	{
		((Sprite*)*it)->setVisible(false);
	}

	refreshRoundVector.clear();
	int count = gameRoundCount;
	Sprite* st;

	if (count == 0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(0));
		addChild(st);
		refreshRoundVector.pushBack(st);
	}
	while (count != 0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(count % 10));
		addChild(st);
		refreshRoundVector.pushBack(st);
		count = count / 10;

	}
	refreshRoundVector.reverse();

	for (int i = 0; i< refreshRoundVector.size(); i++)
	{
		Sprite * sp = refreshRoundVector.at(i);
		sp->setPosition(ccp((tableStartPosition_x + 50) + (i * 25), 50));
		sp->setVisible(true);
	}
	updateStockVec();
	raisePriceIndex();
}

void GameBaseScene::addPathMark()
{

	Sprite* mark1 = Sprite::create(PATH_MARK_1);
	Sprite* mark2 = Sprite::create(PATH_MARK_2);
	Sprite* mark3 = Sprite::create(PATH_MARK_3);
	Sprite* mark4 = Sprite::create(PATH_MARK_4);
	Sprite* mark5 = Sprite::create(PATH_MARK_5);
	Sprite* mark6 = Sprite::create(PATH_MARK_6);


	mark1->setAnchorPoint(ccp(0, 0));
	mark2->setAnchorPoint(ccp(0, 0));
	mark3->setAnchorPoint(ccp(0, 0));
	mark4->setAnchorPoint(ccp(0, 0));
	mark5->setAnchorPoint(ccp(0, 0));
	mark6->setAnchorPoint(ccp(0, 0));

	mark1->setVisible(false);
	mark2->setVisible(false);
	mark3->setVisible(false);
	mark4->setVisible(false);
	mark5->setVisible(false);
	mark6->setVisible(false);


	addChild(mark1);
	addChild(mark2);
	addChild(mark3);
	addChild(mark4);
	addChild(mark5);
	addChild(mark6);

	pathMarkVector.pushBack(mark1);
	pathMarkVector.pushBack(mark2);
	pathMarkVector.pushBack(mark3);
	pathMarkVector.pushBack(mark4);
	pathMarkVector.pushBack(mark5);
	pathMarkVector.pushBack(mark6);
}
void GameBaseScene::drawPathColor(std::vector<int> rowVector, std::vector<int> colVector)
{
	int stepsCount = rowVector.size() - 1;

	for (int i = 1; i<rowVector.size(); i++)
	{
		pathMarkVector.at(i - 1)->setPosition(ccp(colVector[i] * 32, rowVector[i] * 32));
		pathMarkVector.at(i - 1)->setVisible(true);
	}
}

void GameBaseScene::initPopDialog()
{
	popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setPopModalDialog(false);
	popDialog->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height));
	popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
	popDialog->setContentText("", 20, 60, 250);
	popDialog->setCallbackFunc(this, callfuncN_selector(GameBaseScene::buyLandCallback));

	popDialog->addButton(BUTTON_BG1, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(OK)->getCString(), Btn_OK_TAG);
	popDialog->addButton(BUTTON_BG2, BUTTON_BG3, LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(), Btn_Cancel_TAG);
	this->addChild(popDialog);
	popDialog->setVisible(false);
}

void GameBaseScene::initLandLayerFromMap()
{
	landLayer = _map->layerNamed("land");
}

void  GameBaseScene::showBuyLandDialog(int landTag)
{
	String showMessage = "";
	switch(landTag)
	{
		case MSG_BUY_BLANK_TAG:
		{
			showMessage = String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(), LAND_BLANK_MONEY * priceIndex)->getCString();
			break;
		}
		case MSG_BUY_LAND_1_TAG:
		{
			showMessage = String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(), LAND_LEVEL_1_MONEY* priceIndex)->getCString();
			break;
		}
		case MSG_BUY_LAND_2_TAG:
		{
			showMessage = String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(), LAND_LEVEL_2_MONEY* priceIndex)->getCString();
			break;
		}
	}
	popDialog->setDataTag(landTag);
	popDialog->getLabelContentText()->setString(showMessage.getCString());
	popDialog->setVisible(true);

}

void GameBaseScene::buyLandCallback(Node *pNode)
{
	if (pNode->getTag() == Btn_OK_TAG)
	{
		switch (popDialog->getDataTag())
		{
			case MSG_BUY_BLANK_TAG:
			{
				 Util::playAudioEffectRandom(player1EffectVec_11, false);
				 buyLand(MSG_BUY_BLANK_TAG, buy_land_x, buy_land_y, foot1Sprite, player1_building_1_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
				 log("need $1000 ");
				 break;
			}
			case MSG_BUY_LAND_1_TAG:
			{
				Util::playAudioEffectRandom(player1EffectVec_9, false);
				buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,starFish1Sprite,player1_building_2_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
				log( "need $2000 ");					
				break;
			}
			case MSG_BUY_LAND_2_TAG:
			{
				Util::playAudioEffectRandom(player1EffectVec_9, false);
				buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart1Sprite,player1_building_3_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
				log( "need $3000 ");					
				break;
			}
		}
		popDialog->setVisible(false);
	}
	else
	{
		popDialog->setVisible(false);
		Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}
	
}

void GameBaseScene::doSomeForParticle()
{
	landFadeOut = FadeOut::create(0.1);
	landFadeIn = FadeIn::create(0.1);
	landFadeOut->retain();
	landFadeIn->retain();

	scaleby1ForBuyLand = ScaleBy::create(0.1, 1.5);
	scaleby2ForBuyLand = ScaleBy::create(0.5, 0.7);
	scaleby1ForBuyLand->retain();
	scaleby2ForBuyLand->retain();
	foot1Sprite = Sprite::create(PLAYER1_1_PARTICLE_PNG);
	addChild(foot1Sprite);
	foot1Sprite->setAnchorPoint(ccp(0, 0));

	foot2Sprite = Sprite::create(PLAYER2_1_PARTICLE_PNG);
	addChild(foot2Sprite);
	foot2Sprite->setAnchorPoint(ccp(0, 0));

	starFish1Sprite = Sprite::create(PLAYER1_2_PARTICLE_PNG);
	addChild(starFish1Sprite);
	starFish1Sprite->setAnchorPoint(ccp(0, 0));

	starFish2Sprite = Sprite::create(PLAYER2_2_PARTICLE_PNG);
	addChild(starFish2Sprite);
	starFish2Sprite->setAnchorPoint(ccp(0, 0));

	heart1Sprite = Sprite::create(PLAYER1_3_PARTICLE_PNG);
	addChild(heart1Sprite);
	heart1Sprite->setAnchorPoint(ccp(0, 0));

	heart2Sprite = Sprite::create(PLAYER2_3_PARTICLE_PNG);
	addChild(heart2Sprite);
	heart2Sprite->setAnchorPoint(ccp(0, 0));
}
void  GameBaseScene::playParticle(Point point, char* plistName)
{
	ParticleSystem* particleSystem_foot = ParticleSystemQuad::create(plistName);
	particleSystem_foot->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(particleSystem_foot->getTexture());
	batch->addChild(particleSystem_foot);
	addChild(batch);

	particleSystem_foot->setPosition(point + ccp(tiledWidth / 2, tiledHeight / 2));
	particleSystem_foot->release();
	particleSystem_foot->setAutoRemoveOnFinish(true);
}
void GameBaseScene::buyLand(int buyTag, float x, float y, Sprite* landSprite, int landLevel, RicherPlayer* player, char* particlelistName)
{
	int money = 0;

	if (buyTag == MSG_BUY_BLANK_TAG)
	{
		money = LAND_BLANK_MONEY* priceIndex;
	}
	if (buyTag == MSG_BUY_LAND_1_TAG)
	{
		money = LAND_LEVEL_1_MONEY* priceIndex;
	}
	if (buyTag == MSG_BUY_LAND_2_TAG)
	{
		money = LAND_LEVEL_2_MONEY* priceIndex;
	}

	Point pointOfGL = Util::map2GL(ccp(x, y), GameBaseScene::_map);
	landSprite->setVisible(true);
	landSprite->setPosition(pointOfGL);
	Point pointOfMap = ccp(x, y);
	landSprite->runAction(Sequence::create(scaleby1ForBuyLand, scaleby2ForBuyLand, CallFunc::create([this, pointOfMap, pointOfGL, landSprite, landLevel, x, y, player, money, particlelistName]()
	{
		playParticle(pointOfGL, particlelistName);
		landSprite->setVisible(false);
		landLayer->setTileGID(landLevel, ccp(x, y));
		refreshMoneyLabel(player, -money);
		Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}), NULL));
}

void  GameBaseScene::refreshMoneyLabel(RicherPlayer* player, int money)
{
	int tag = player->getTag();
	player->setMoney(player->getMoney() + money);

	if (tag == PLAYER_1_TAG)
	{
		memset(money1, 0, 20);
		sprintf(money1, "$ %d", player->getMoney());
		getPlayer1_money_label()->setString(money1);
	}
	if (tag == PLAYER_2_TAG)
	{
		memset(money2, 0, 20);
		sprintf(money2, "$ %d", player->getMoney());
		getPlayer2_money_label()->setString(money2);
	}
}
void GameBaseScene::payTolls(int payTag,float x,float y ,int playerTag)
{
	int money =0;
	if(payTag == MSG_PAY_TOLLS_1_TAG)
	{
		money = LAND_BLANK_MONEY* priceIndex;
	}
	if(payTag == MSG_PAY_TOLLS_2_TAG)
	{
		money = LAND_LEVEL_1_MONEY* priceIndex;
	}
	if(payTag == MSG_PAY_TOLLS_3_TAG)
	{
		money = LAND_LEVEL_2_MONEY* priceIndex;
	}
			
	displayVector.clear();

	RicherPlayer* landOwner = getPlayerByTiled(buy_land_x,buy_land_y);

	switch(playerTag)
	{
		case PLAYER_1_TAG:
		{
			Util::playAudioEffectRandom(player1EffectVec_1, false);
			if(landOwner->restTimes > 0)
			{
				Util::playAudioEffectRandom(player1EffectVec_10, false);
				CocosToast::createToast(this, LanguageString::getInstance()->getLanguageString(IN_HOSPITAL)->getCString(), TOAST_SHOW_TIME,player1->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
				return;
			}
			int retMoney = displayArea(x,y,player1,player2_building_1_tiledID,player2_building_2_tiledID,player2_building_3_tiledID);
			refreshMoneyLabel(landOwner,money + retMoney);
			refreshMoneyLabel(player1,-(money + retMoney));
			CocosToast::createToast(this, String::createWithFormat("+%d", money + retMoney)->getCString(), TOAST_SHOW_TIME+1, landOwner->getPosition());
			CocosToast::createToast(this, String::createWithFormat("-%d", money + retMoney)->getCString(), TOAST_SHOW_TIME, player1->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
			transferLandTag = payTag;
			nextPlayerEffectVec = player2EffectVec_8;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			break;
		}
		case PLAYER_2_TAG:
		{
			Util::playAudioEffectRandom(player2EffectVec_1, false);
			if(landOwner->restTimes > 0)
			{
				Util::playAudioEffectRandom(player2EffectVec_10, false);
				CocosToast::createToast(this, LanguageString::getInstance()->getLanguageString(IN_HOSPITAL)->getCString(), TOAST_SHOW_TIME,player2->getPosition(),(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
				return;
			}
			int retMoney = displayArea(x,y,player2,player1_building_1_tiledID,player1_building_2_tiledID,player1_building_3_tiledID);
			refreshMoneyLabel(landOwner,money + retMoney);
			refreshMoneyLabel(player2,-(money + retMoney));
			CocosToast::createToast(this, String::createWithFormat("+%d", money + retMoney)->getCString(), TOAST_SHOW_TIME+1, landOwner->getPosition());
			CocosToast::createToast(this, String::createWithFormat("-%d", money + retMoney)->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGPickOneToGO);
			nextPlayerEffectVec = player1EffectVec_8;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			break;
		}				
	}
}
RicherPlayer* GameBaseScene::getPlayerByTiled(float x, float y)
{
	int gid = landLayer->getTileGIDAt(ccp(x, y));
	if (gid == player1_building_1_tiledID || gid == player1_building_2_tiledID || gid == player1_building_3_tiledID)
	{
		return player1;
	}
	if (gid == player2_building_1_tiledID || gid == player2_building_2_tiledID || gid == player2_building_3_tiledID)
	{
		return player2;
	}
}
int GameBaseScene::displayArea(float x, float y, RicherPlayer* player, int building_1_tiledID, int building_2_tiledID, int building_3_tiledID)
{
	Util::playAudioEffect(block_effect, false);
	int sumMoney = 0;
	float retX = Util::GL2map(player->getPosition(), _map).x;
	if (x == retX)
	{
		float leftX = x - 1;
		float rightX = x + 1;
		int leftGID = landLayer->getTileGIDAt(ccp(leftX, y));
		int rightGID = landLayer->getTileGIDAt(ccp(rightX, y));
		displayVector.pushBack(landLayer->getTileAt(ccp(x, y)));
		while (leftGID != 0 && (leftGID == building_1_tiledID || leftGID == building_2_tiledID || leftGID == building_3_tiledID))
		{
			if (leftGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY* priceIndex;
			}
			if (leftGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY* priceIndex;
			}
			if (leftGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY* priceIndex;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(leftX, y)));
			leftX -= 1;
			leftGID = landLayer->getTileGIDAt(ccp(leftX, y));

			if (leftGID == 0)
			{
				break;
			}
			log("leftGID: %d", leftGID);
		}
		while (rightGID != 0 && (rightGID == building_1_tiledID || rightGID == building_2_tiledID || rightGID == building_3_tiledID))
		{
			if (rightGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY* priceIndex;
			}
			if (rightGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY* priceIndex;
			}
			if (rightGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY* priceIndex;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(rightX, y)));
			rightX += 1;
			rightGID = landLayer->getTileGIDAt(ccp(rightX, y));

			if (rightGID == 0)
			{
				break;
			}
			log("rightGID: %d", rightGID);
		}
	}

	float retY = Util::GL2map(player->getPosition(), _map).y;
	if (y == retY)
	{
		float upY = y - 1;
		float downY = y + 1;
		int upGID = landLayer->getTileGIDAt(ccp(x, upY));
		int downGID = landLayer->getTileGIDAt(ccp(x, downY));
		displayVector.pushBack(landLayer->getTileAt(ccp(x, y)));
		while (upGID != 0 && (upGID == building_1_tiledID || upGID == building_2_tiledID || upGID == building_3_tiledID))
		{
			if (upGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY* priceIndex;
			}
			if (upGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY* priceIndex;
			}
			if (upGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY* priceIndex;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(x, upY)));
			upY -= 1;
			upGID = landLayer->getTileGIDAt(ccp(x, upY));

			if (upGID == 0)
			{
				break;
			}
			log("leftGID: %d", upGID);
		}
		while (downGID != 0 && (downGID == building_1_tiledID || downGID == building_2_tiledID || downGID == building_3_tiledID))
		{
			if (downGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY* priceIndex;
			}
			if (downGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY* priceIndex;
			}
			if (downGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY* priceIndex;
			}
			displayVector.pushBack(landLayer->getTileAt(ccp(x, downY)));
			downY += 1;
			downGID = landLayer->getTileGIDAt(ccp(x, downY));

			if (downGID == 0)
			{
				break;
			}
			log("rightGID: %d", downGID);
		}
	}
	for (auto it = displayVector.begin(); it != displayVector.end(); it++)
	{
		(Sprite*)(*it)->runAction(Sequence::create(landFadeOut->clone(), landFadeIn->clone(), NULL));
	}
	return sumMoney;
}

void GameBaseScene::sendMSGPickOneToGO()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
}

void GameBaseScene::initRandomAskEvent()
{
	randomAskEventMap.insert(TAX_REBATES_KEY, LanguageString::getInstance()->getLanguageString(TAX_REBATES));
	randomAskEventMap.insert(PAY_TAXES_KEY, LanguageString::getInstance()->getLanguageString(PAY_TAXES));
	randomAskEventMap.insert(LOSS_STRENGTH_KEY, LanguageString::getInstance()->getLanguageString(LOSS_STRENGTH));
	randomAskEventMap.insert(PHYSICAL_RECOVERY_KEY, LanguageString::getInstance()->getLanguageString(PHYSICAL_RECOVERY));
	randomAskEventMap.insert(INVESTMENT_DIVIDENDS_KEY, LanguageString::getInstance()->getLanguageString(INVESTMENT_DIVIDENDS));
	randomAskEventMap.insert(INVESTMENT_LOSS_KEY, LanguageString::getInstance()->getLanguageString(INVESTMENT_LOSS));

	randomAskEventMap.insert(STORM_UP_KEY, LanguageString::getInstance()->getLanguageString(STORM_SKILL_UP));
	randomAskEventMap.insert(STEP_UP_KEY, LanguageString::getInstance()->getLanguageString(STEP_SKILL_UP));
	randomAskEventMap.insert(TRANSFER_UP_KEY, LanguageString::getInstance()->getLanguageString(TRANSFER_SKILL_UP));
}

void GameBaseScene::sendMSGDealAroundLand()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_AROUND_LAND_TAG));
}

void GameBaseScene::doRandomAskEvent(RicherPlayer* player)
{
	int randomNumber = rand()%(randomAskEventMap.size()) + 1; 
	__String * str = randomAskEventMap.at(randomNumber);

	switch(randomNumber)
	{
		case TAX_REBATES_KEY:
		{
			refreshMoneyLabel(player,10000);					
			break;
		}
		case PAY_TAXES_KEY:
		{
			if (player->getTag() == PLAYER_1_TAG)
			{
				Util::playAudioEffectRandom(player2EffectVec_13,false);
			}
			else if (player->getTag() == PLAYER_2_TAG)
			{
				Util::playAudioEffectRandom(player1EffectVec_13, false);
			}
			refreshMoneyLabel(player,-20000);
			break;
		}

		case LOSS_STRENGTH_KEY:
		{
			refreshStrengthLabel(player,-100);
			break;
		}
		case PHYSICAL_RECOVERY_KEY:
		{
			refreshStrengthLabel(player,100);
			break;
		}
		case INVESTMENT_DIVIDENDS_KEY:
		{
			refreshMoneyLabel(player,20000);
			break;
		}
		case INVESTMENT_LOSS_KEY:
		{
			refreshMoneyLabel(player,-30000);
			break;
		}
		case STORM_UP_KEY:
		{
			player->skill_vector.at(0) ++;
			break;
		}
		case STEP_UP_KEY:
		{
			player->skill_vector.at(1) ++;
			break;
		}
		case TRANSFER_UP_KEY:
		{
			player->skill_vector.at(2) ++;
			break;
		}
	}
	CocosToast::createToast(this, str->getCString(), TOAST_SHOW_TIME, player->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand);
}

void  GameBaseScene::refreshStrengthLabel(RicherPlayer* player, int strength)
{
	int tag = player->getTag();
	int totalStrength = player->getStrength() + strength;
	if (totalStrength > 100) totalStrength = 100;
	if (totalStrength < 0) totalStrength = 0;
	player->setStrength(totalStrength);

	if (tag == PLAYER_1_TAG)
	{
		memset(strength1, 0, 20);
		sprintf(strength1, "+ %d", player->getStrength());
		getPlayer1_strength_label()->setString(strength1);
	}
	if (tag == PLAYER_2_TAG)
	{
		memset(strength2, 0, 20);
		sprintf(strength2, "+ %d", player->getStrength());
		getPlayer2_strength_label()->setString(strength2);
	}
}

void GameBaseScene::initPropSprite()
{
	_strength_up = Strength_up::create();
	addChild(_strength_up);
	_strength_up->setVisible(false);
	_strength_up->setAnchorPoint(ccp(0, 0.5));

	_bee = Bee::create();
	addChild(_bee);
	_bee->runAction(RepeatForever::create(_bee->getNormal_anmi()));
	_bee->setVisible(false);


	_emergency = Emergency::create();
	addChild(_emergency);
	_emergency->setVisible(false);

	_fog = Fog::create();
	addChild(_fog);
	_fog->setVisible(false);

	_stretcher = Stretcher::create();
	addChild(_stretcher);
	_stretcher->setVisible(false);
	_stretcher->setAnchorPoint(ccp(0, 0.9));

	_pearl = Pearl::create();
	addChild(_pearl);
	_pearl->runAction(RepeatForever::create(_pearl->getNormal_anmi()));
	_pearl->setVisible(false);
}

void GameBaseScene::doItemStrengthUp(int strengthUp,int playerTag)
{
	Util::playAudioEffect(PARTICLE_EFFECT, false);
	int strengthValue = 0;
	switch(strengthUp)
	{
		case MSG_STRENGTH_UP30_TAG:
		{
			strengthValue =30;		
			break;
		}
		case MSG_STRENGTH_UP50_TAG:
		{
			strengthValue =50;
			break;
		}
		case MSG_STRENGTH_UP80_TAG:
		{
			strengthValue =80;
			break;
		}
	}
	RicherPlayer* tmp;
	switch(playerTag)
	{
		case PLAYER_1_TAG:
		{
			tmp = player1;
			break;
		}
		case PLAYER_2_TAG:
		{
			tmp = player2;
			break;
		}				
	}
	_strength_up->setVisible(true);
	_strength_up->setPosition(tmp->getPosition() - ccp(5, 0));
	Sequence* action = Sequence::create(_strength_up->getNormal_anmi(),
		CallFunc::create([this](){
		_strength_up->setVisible(false);
		sendMSGDealAroundLand();
	}
	), NULL);
	_strength_up->runAction(action);
	CocosToast::createToast(this,
		String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(), strengthValue)->getCString(),
		TOAST_SHOW_TIME, tmp->getPosition());
	refreshStrengthLabel(tmp, strengthValue);
}

void GameBaseScene::registerBlockWaySchedule()
{
	schedule(schedule_selector(GameBaseScene::updateBlockWaySprites), 10.0f);
}

void GameBaseScene::updateBlockWaySprites(float dt)
{
	int _rand1 = rand() % (wayLayerPass_vector.size());
	Vec2 position = wayLayerPass_vector.at(_rand1);
	position.x += 5;
	position.y += tiledHeight;
	_bee->setVisible(true);
	_bee->setPosition(position);
	_bee->setAnchorPoint(ccp(0, 0.6));

	int _rand2 = rand() % (wayLayerPass_vector.size());
	Vec2 position2 = wayLayerPass_vector.at(_rand2);
	_pearl->setVisible(true);
	_pearl->setPosition(position2);
	_pearl->setAnchorPoint(ccp(0, 0));
}

void GameBaseScene::doBlockWayEvent(RicherPlayer* player)
{
	if (player->getBoundingBox().containsPoint(_bee->getPosition() + ccp(_bee->getContentSize().width / 2, -_bee->getContentSize().height / 2)))
	{
		Util::playAudioEffect(M120, false);
		if (player->getTag() == PLAYER_2_TAG)
		{
			Util::playAudioEffectRandom(player2EffectVec_6, false);
			nextPlayerEffectVec = player1EffectVec_7;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);

		}
		else if (player->getTag() == PLAYER_1_TAG)
		{
			Util::playAudioEffectRandom(player1EffectVec_6, false);
			nextPlayerEffectVec = player2EffectVec_7;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
		}
		_bee->setPosition(ccp(-200, -200));
		player->restTimes = rand() % (5) + 1;

		_emergency->setVisible(true);
		int distance = tableStartPosition_x - player->getPosition().x;
		_emergency->setPosition(player->getPosition() + ccp(distance, 0));

		_fog->setVisible(true);
		_fog->setPosition(player->getPosition());
		Repeat* repeate0 = Repeat::create(_fog->getNormal_anmi(), 2);
		_fog->runAction(repeate0);

		MoveBy* moveBy = MoveBy::create(1.0f, ccp(-distance, 0));
		MoveBy* moveBy2 = MoveBy::create(0.5f, ccp(-60, 0));
		Repeat* repeate = Repeat::create(_emergency->getCar_go_anmi(), 5);
		Repeat* repeate2 = Repeat::create(_emergency->getCar_stop_anmi(), 1);

		Sequence* spawnAction = Sequence::create(Spawn::create(moveBy, repeate, NULL), 
												 Spawn::create(moveBy2, repeate2, NULL),
												 CallFunc::create(std::bind(&GameBaseScene::endCarGo,this,  player->getTag())), NULL);
		spawnAction->retain();
		_emergency->runAction(spawnAction);

		CocosToast::createToast(this, String::createWithFormat("%s %d %s", LanguageString::getInstance()->getLanguageString(PLAYER_HURT)->getCString(), player->restTimes, LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME, player->getPosition());
	}
	else if (player->getBoundingBox().intersectsRect(_pearl->getBoundingBox()))
	{
		if (player->getTag() == PLAYER_2_TAG)
		{
			Util::playAudioEffectRandom(player2EffectVec_12, false);
		}
		else if (player->getTag() == PLAYER_1_TAG)
		{
			Util::playAudioEffectRandom(player1EffectVec_12, false);
		}
		_pearl->setPosition(ccp(-200, -200));
		int money = 20000;
		refreshMoneyLabel(player, money);
		CocosToast::createToast(this, String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(PICK_BALL)->getCString(), money)->getCString(), TOAST_SHOW_TIME, player->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealProp);
	}
	else
	{
		Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_HANDLE_PROP_EVENT_TAG));
	}
}


void GameBaseScene::endCarGo(int tag)
{
	_stretcher->setVisible(true);
	_stretcher->setPosition(_emergency->getPosition());
	MoveBy* moveBy = MoveBy::create(0.5f, ccp(60, 0));
	ScaleBy* scaleBy = ScaleBy::create(0.5f, 0.8);
	Repeat* repeate = Repeat::create(_stretcher->getStretcher_empty_anmi(), 1);
	ScaleBy* scaleBy2 = ScaleBy::create(0.5f, 1.25);
	MoveBy* moveBy2 = MoveBy::create(0.5f, ccp(-60, 0));
	Repeat* repeate2 = Repeat::create(_stretcher->getStretcher_full_anmi(), 1);
	Sequence* spawnAction = Sequence::create(
		Spawn::create(moveBy, scaleBy, repeate, CallFunc::create(CC_CALLBACK_0(GameBaseScene::setPlayerAndFogInVisible, this, tag)), NULL),
		Spawn::create(moveBy2, scaleBy2, repeate2, NULL), CallFunc::create(CC_CALLBACK_0(GameBaseScene::startCarGoAgain, this)), NULL);
	spawnAction->retain();
	_stretcher->runAction(spawnAction);
}

void GameBaseScene::startCarGoAgain()

{
	_stretcher->setVisible(false);
	int distance = _emergency->getPositionX();
	MoveBy* moveBy = MoveBy::create(1.0f, ccp(-distance, 0));
	Repeat* repeate = Repeat::create(_emergency->getCar_go_anmi(), 5);
	Sequence* spawnAction = Sequence::create(Spawn::create(moveBy, repeate, NULL), CallFunc::create([this](){
		_emergency->setVisible(false);
		Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}), NULL);
	spawnAction->retain();
	_emergency->runAction(spawnAction);
}

void GameBaseScene::setPlayerAndFogInVisible(int tag)
{
	if (tag == PLAYER_1_TAG)
	{
		player1->setVisible(false);
	}
	else if (tag == PLAYER_2_TAG)
	{
		player2->setVisible(false);
	}
	_fog->setVisible(false);
}

void GameBaseScene::sendMSGDealProp()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_HANDLE_PROP_EVENT_TAG));
}
void GameBaseScene::sendMSGMoveOneStep()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_MOVE_ONE_STEP_TAG));
}

void GameBaseScene::lotteryBuyOrCancelCallback(Node *pNode)
{
	if (pNode->getTag() != -1 && pNode->getTag() != Btn_Cancel_TAG)
	{
		Util::playAudioEffect(P1_DEYIDEYITIAN, false);
		player1->lottery_vector.push_back(pNode->getTag());
		log("****lottery buy number is %d***", pNode->getTag());
		refreshMoneyLabel(player1, -BUY_LOTTERY_MONEY);

		if (moveTag == GOEND)
		{
			CocosToast::createToast(this, String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(), BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME, player1->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand);
		}
		else if (moveTag == MOVEPASS)
		{
			CocosToast::createToast(this, String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LOTTERY)->getCString(), BUY_LOTTERY_MONEY)->getCString(), TOAST_SHOW_TIME, player1->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
		}
		pNode->getParent()->getParent()->removeFromParent();
	}
	else
	{
		pNode->getParent()->getParent()->removeFromParent();
		if (moveTag == GOEND)
		{
			sendMSGDealAroundLand();
		}
		else if (moveTag == MOVEPASS)
		{
			sendMSGMoveOneStep();
		}
	}
}

void GameBaseScene::initPopPublishLottery()
{
	popDialogLottery = PopupLayer::create(DIALOG_BG);
	popDialogLottery->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height + 180));
	popDialogLottery->setTitle(LanguageString::getInstance()->getLanguageString(PUBLISH_LOTTERY)->getCString());
	popDialogLottery->setContentText("", 20, 60, 250);
	popDialogLottery->setPopType(LOTTERY_PUBLISH);
	popDialogLottery->setPlayerVector(players_vector);
	popDialogLottery->setTag(100);
	this->addChild(popDialogLottery);
	popDialogLottery->setVisible(false);
}

void GameBaseScene::popPublishLottery(float dt)
{
	popDialogLottery->setVisible(true);
	popDialogLottery->addPlayersLottery();
	popDialogLottery->runPublishAnmi();
}

void GameBaseScene::updateStockVec()
{
	int valule1 = rand() % 800 + 10;
	int valule2 = rand() % 800 + 10;
	int valule3 = rand() % 800 + 10;
	int valule4 = rand() % 800 + 10;
	int valule5 = rand() % 800 + 10;

	if (stock_pointvec1.size()>13)
	{
		for (int i = 0; i<13; i++)
		{
			stock_pointvec1.at(i) = stock_pointvec1.at(i + 1);
			stock_pointvec2.at(i) = stock_pointvec2.at(i + 1);
			stock_pointvec3.at(i) = stock_pointvec3.at(i + 1);
			stock_pointvec4.at(i) = stock_pointvec4.at(i + 1);
			stock_pointvec5.at(i) = stock_pointvec5.at(i + 1);

		}
		stock_pointvec1.at(13) = valule1;
		stock_pointvec2.at(13) = valule2;
		stock_pointvec3.at(13) = valule3;
		stock_pointvec4.at(13) = valule4;
		stock_pointvec5.at(13) = valule5;
	}
	else
	{
		stock_pointvec1.push_back(valule1);
		stock_pointvec2.push_back(valule2);
		stock_pointvec3.push_back(valule3);
		stock_pointvec4.push_back(valule4);
		stock_pointvec5.push_back(valule5);
	}
}

void GameBaseScene::doStockDeal(RicherPlayer* player, int moveTag)
{
	initStockVector(player);
	int selectedTag = rand() % 5;
	int buyOrSellTag = rand() % 2;
	if (buyOrSellTag == 1)//buy
	{
		int diffMoney = player->getMoney() - stockVector.at(selectedTag)->getNowPrice() * 100;
		if (diffMoney >= 0)
		{
			Stock* s = player->stockMap.at(selectedTag);
			int storeNumber = s->getStoreNumber() + 100;
			int dealPrice = (s->getMakedealprice()*s->getStoreNumber() + stockVector.at(selectedTag)->getNowPrice() * 100) / (100 + s->getStoreNumber());
			s->setStoreNumber(s->getStoreNumber() + 100);
			s->setMakedealprice(dealPrice);
			stockVector.at(selectedTag)->setStoreNumber(storeNumber);
			player->setMoney(diffMoney);
			if (moveTag == GOEND)
			{
				CocosToast::createToast(this, String::createWithFormat("%s %s 100 %s", LanguageString::getInstance()->getLanguageString(BUY)->getCString(), s->getStockName()->getCString(), LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand);
			}
			else if (moveTag == MOVEPASS)
			{
				CocosToast::createToast(this, String::createWithFormat("%s %s 100 %s", LanguageString::getInstance()->getLanguageString(BUY)->getCString(), s->getStockName()->getCString(), LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
			}
		}
		else
		{
			if (moveTag == GOEND)
			{
				sendMSGDealAroundLand();
			}
			else if (moveTag == MOVEPASS)
			{
				sendMSGMoveOneStep();
			}
		}
	}
	else if (buyOrSellTag == 0)//sell
	{
		Stock* s = player->stockMap.at(selectedTag);
		int storeNumber = s->getStoreNumber();
		if (storeNumber > 0)
		{
			player->setMoney(player->getMoney() + storeNumber * stockVector.at(selectedTag)->getNowPrice());
			s->setMakedealprice(0);
			s->setStoreNumber(0);
			if (moveTag == GOEND)
			{
				CocosToast::createToast(this, String::createWithFormat("%s %s %d %s", LanguageString::getInstance()->getLanguageString(SELL)->getCString(), s->getStockName()->getCString(), storeNumber, LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand);
			}
			else if (moveTag == MOVEPASS)
			{
				CocosToast::createToast(this, String::createWithFormat("%s %s %d %s", LanguageString::getInstance()->getLanguageString(SELL)->getCString(), s->getStockName()->getCString(), storeNumber, LanguageString::getInstance()->getLanguageString(SHARES)->getCString())->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGMoveOneStep);
			}
		}
		else
		{
			if (moveTag == GOEND)
			{
				sendMSGDealAroundLand();
			}
			else if (moveTag == MOVEPASS)
			{
				sendMSGMoveOneStep();
			}
		}
	}
	refreshMoneyLabel(player, 0);
}

void GameBaseScene::initStockVector(RicherPlayer* player)
{
	stockVector.clear();
	float percent = 0;
	if (stock_pointvec1.size()>1)
	{
		percent =((float) (stock_pointvec1.at(stock_pointvec1.size() - 1) - stock_pointvec1.at(stock_pointvec1.size() - 2)) / stock_pointvec1.at(stock_pointvec1.size() - 2)) * 100;
	}
	stockVector.pushBack(Stock::create(800100, LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY), stock_pointvec1.at(stock_pointvec1.size() - 1), player->stockMap.at(0)->getMakedealprice(), percent, player->stockMap.at(0)->getStoreNumber()));

	percent = 0;
	if (stock_pointvec2.size()>1)
	{
		percent = ((float)(stock_pointvec2.at(stock_pointvec2.size() - 1) - stock_pointvec2.at(stock_pointvec2.size() - 2)) / stock_pointvec2.at(stock_pointvec2.size() - 2)) * 100;
	}

	stockVector.pushBack(Stock::create(800200, LanguageString::getInstance()->getLanguageString(RICH_OIL), stock_pointvec2.at(stock_pointvec1.size() - 1), player->stockMap.at(1)->getMakedealprice(), percent, player->stockMap.at(1)->getStoreNumber()));

	percent = 0;
	if (stock_pointvec3.size()>1)
	{
		percent = ((float)(stock_pointvec3.at(stock_pointvec3.size() - 1) - stock_pointvec3.at(stock_pointvec3.size() - 2)) / stock_pointvec3.at(stock_pointvec3.size() - 2)) * 100;
	}
	stockVector.pushBack(Stock::create(800300, LanguageString::getInstance()->getLanguageString(ICBC), stock_pointvec3.at(stock_pointvec1.size() - 1), player->stockMap.at(2)->getMakedealprice(), percent, player->stockMap.at(2)->getStoreNumber()));

	percent = 0;
	if (stock_pointvec4.size()>1)
	{
		percent = ((float)(stock_pointvec4.at(stock_pointvec4.size() - 1) - stock_pointvec4.at(stock_pointvec4.size() - 2)) / stock_pointvec4.at(stock_pointvec4.size() - 2)) * 100;
	}
	stockVector.pushBack(Stock::create(800400, LanguageString::getInstance()->getLanguageString(HUATUO_MEDICINE), stock_pointvec4.at(stock_pointvec1.size() - 1), player->stockMap.at(3)->getMakedealprice(), percent, player->stockMap.at(3)->getStoreNumber()));

	percent = 0;
	if (stock_pointvec5.size()>1)
	{
		percent = ((float)(stock_pointvec5.at(stock_pointvec5.size() - 1) - stock_pointvec5.at(stock_pointvec5.size() - 2)) / stock_pointvec5.at(stock_pointvec5.size() - 2)) * 100;
	}
	stockVector.pushBack(Stock::create(800500, LanguageString::getInstance()->getLanguageString(DEMOLITION_CONSTRUCTION), stock_pointvec5.at(stock_pointvec1.size() - 1), player->stockMap.at(4)->getMakedealprice(), percent, player->stockMap.at(4)->getStoreNumber()));

}

void GameBaseScene::addMenuButton()
{
	addGoButton();

	step1Button = MenuItemImage::create("images/step1_normal.png", "images/step1_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));
	step2Button = MenuItemImage::create("images/step2_normal.png", "images/step2_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));
	step3Button = MenuItemImage::create("images/step3_normal.png", "images/step3_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));
	step4Button = MenuItemImage::create("images/step4_normal.png", "images/step4_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));
	step5Button = MenuItemImage::create("images/step5_normal.png", "images/step5_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));
	step6Button = MenuItemImage::create("images/step6_normal.png", "images/step6_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));

	addStepButton(step1Button, step1_tag);
	addStepButton(step2Button, step2_tag);
	addStepButton(step3Button, step3_tag);
	addStepButton(step4Button, step4_tag);
	addStepButton(step5Button, step5_tag);
	addStepButton(step6Button, step6_tag);
	addSkillMenuButton();
	addSaveMenuButton();
	addBackMenuButton();
	addAudioMenuButton();
}

void  GameBaseScene::addStepButton(MenuItemImage* stepItem,int tag)
{
	Size winSize = Director::getInstance()->getWinSize();
	Menu* menu = getMenu();
	stepItem->setPosition(winSize / 2);
	stepItem->setAnchorPoint(ccp(0.5, 0));
	stepItem->setVisible(false);
	stepItem->setTag(tag);
	menu->addChild(stepItem);
}

void GameBaseScene::addSaveMenuButton()
{
	Size winSize = Director::getInstance()->getWinSize();
	Menu* menu = getMenu();
	saveMenuItemButton = MenuItemImage::create("images/save_normal.png", "images/save_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));

	saveMenuItemButton->setPosition(ccp(winSize.width, 0));
	saveMenuItemButton->setAnchorPoint(ccp(1, 0));
	saveMenuItemButton->setTag(saveButtonTag);
	menu->addChild(saveMenuItemButton);
}

void GameBaseScene::addSkillMenuButton()
{
	Menu* menu = getMenu();
	skillMenuItemButton = MenuItemImage::create("images/skill_button_normal.png", "images/skill_button_pressed.png", this, menu_selector(GameBaseScene::menuButtonCallback));

	skillMenuItemButton->setPosition(ccp(tableStartPosition_x + 2 * tableWidth + 20, tableStartPosition_y - tableHeight * 6 - 80));
	skillMenuItemButton->setTag(skillButtonTag);
	menu->addChild(skillMenuItemButton);

	skillStorm = SkillCard::createCardSprite(LanguageString::getInstance()->getLanguageString(RAIN),
		LanguageString::getInstance()->getLanguageString(GRADE),
		LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		LanguageString::getInstance()->getLanguageString(DOWN_GRADE), skillSpriteCardWidth, skillSpriteCardHeight, 100, -130, skillStormTag, "images/thunderstorm.png");

	addChild(skillStorm, 50);

	skillStep = SkillCard::createCardSprite(LanguageString::getInstance()->getLanguageString(GOBY_HEART),
		LanguageString::getInstance()->getLanguageString(GRADE),
		LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		LanguageString::getInstance()->getLanguageString(GOBY_HEART_INFO), skillSpriteCardWidth, skillSpriteCardHeight, 280, -130, skillStepTag, "images/skill_step.png");
	addChild(skillStep, 50);


	skillTransfer = SkillCard::createCardSprite(LanguageString::getInstance()->getLanguageString(YOURS_IS_MINE),
		LanguageString::getInstance()->getLanguageString(GRADE),
		LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		LanguageString::getInstance()->getLanguageString(YOURS_IS_MINE_INFO), skillSpriteCardWidth, skillSpriteCardHeight, 460, -130, skillTransferTag, "images/skill_transfer.png");
	addChild(skillTransfer, 50);


	skillStorm->setSkillButtonCallback(this, callfuncN_selector(GameBaseScene::skillClick));


	skillStep->setSkillButtonCallback(this, callfuncN_selector(GameBaseScene::skillClick));
	skillTransfer->setSkillButtonCallback(this, callfuncN_selector(GameBaseScene::skillClick));
	isSkillLayerShow = false;
	isStepLayerShow = false;

}

void GameBaseScene::skillClick(Node *pNode)
{
	Util::playAudioEffect(click_effect, false);
	Size winSize = Director::getInstance()->getWinSize();
	int tag = pNode->getTag();
	if (tag == skillStormTag)
	{
		if (player1->stop_x  < 0)
		{
			return;
		}

		int needLostStrength = 80 - player1->skill_vector.at(0) * 10;
		if (player1->getStrength() >= needLostStrength)
		{
			Util::playAudioEffect(STORM_EFFECT, false);
			Util::playAudioEffectRandom(player1EffectVec_4, false);
			nextPlayerEffectVec = player2EffectVec_5;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			showSkillSprites();
			player1->setStrength(player1->getStrength() - needLostStrength);
			refreshStrengthLabel(player1, 0);

			Point pointOfGL = Util::map2GL(ccp(player1->stop_x, player1->stop_y), _map);
			rainSprite = Sprite::createWithSpriteFrame(player1->getRainSkill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
			addChild(rainSprite);

			rainSprite->setAnchorPoint(ccp(0, 0));
			rainSprite->setPosition(pointOfGL + ccp(-tiledWidth / 2, tiledHeight / 2));

			rainSprite->runAction(Sequence::create(player1->getRainSkill(), CallFunc::create([this]()
			{
				landLayer->setTileGID(blank_land_tiledID, ccp(player1->stop_x, player1->stop_y));
				rainSprite->removeFromParent();
			}), NULL));
		}
		else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
				TOAST_SHOW_TIME,
				winSize / 2);
		}



	}

	if (tag == skillStepTag)
	{
		showStepButton(!isStepLayerShow);
		isStepLayerShow = !isStepLayerShow;
	}

	if (tag == skillTransferTag)
	{
		if (player1->stop_x  < 0)
		{
			return;
		}

		int needLostStrength = 110 - player1->skill_vector.at(2) * 10;
		if (player1->getStrength() >= needLostStrength)
		{
			Util::playAudioEffectRandom(player1EffectVec_2, false);
			nextPlayerEffectVec = player2EffectVec_3;
			scheduleOnce(schedule_selector(GameBaseScene::playNextEffectVec), NEXT_EFFECT_DELAY);
			int transferLand = 0;
			if (transferLandTag == MSG_PAY_TOLLS_1_TAG)
			{
				transferLand = player1_building_1_tiledID;
			}
			if (transferLandTag == MSG_PAY_TOLLS_2_TAG)
			{
				transferLand = player1_building_2_tiledID;
			}
			if (transferLandTag == MSG_PAY_TOLLS_3_TAG)
			{
				transferLand = player1_building_3_tiledID;
			}
			transferLandTag = 0;
			if (transferLand != 0)
			{
				showSkillSprites();
				player1->setStrength(player1->getStrength() - needLostStrength);
				refreshStrengthLabel(player1, 0);

				Point pointOfGL = Util::map2GL(ccp(player1->stop_x, player1->stop_y), _map);
				transferSprite = Sprite::createWithSpriteFrame(player1->getTransfer_skill()->getAnimation()->getFrames().at(0)->getSpriteFrame());
				addChild(transferSprite);

				transferSprite->setAnchorPoint(ccp(0, 0));
				transferSprite->setPosition(pointOfGL);

				transferSprite->runAction(Sequence::create(player1->getTransfer_skill(), CallFunc::create([this, transferLand]()
				{
					landLayer->setTileGID(transferLand, ccp(player1->stop_x, player1->stop_y));
					transferSprite->removeFromParent();
				}), NULL));

			}

		}
		else
		{
			CocosToast::createToast(this,
				LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
				TOAST_SHOW_TIME,
				winSize / 2);
		}
	}
}

void GameBaseScene::showSkillSprites()
{
	if (!isSkillLayerShow)
	{
		skillStorm->runAction(MoveBy::create(0.3, ccp(0, 130)));
		skillStep->runAction(MoveBy::create(0.3, ccp(0, 130)));
		skillTransfer->runAction(MoveBy::create(0.3, ccp(0, 130)));
		isSkillLayerShow = true;
	}
	else
	{
		skillStorm->runAction(MoveBy::create(0.3, ccp(0, -130)));
		skillStep->runAction(MoveBy::create(0.3, ccp(0, -130)));
		skillTransfer->runAction(MoveBy::create(0.3, ccp(0, -130)));
		isSkillLayerShow = false;

		if (isStepLayerShow)
		{
			showStepButton(!isStepLayerShow);
			isStepLayerShow = !isStepLayerShow;
		}


	}
}

void  GameBaseScene::showStepButton(bool show)
{
	if (show)
	{
		step1Button->setVisible(true);
		step2Button->setVisible(true);
		step3Button->setVisible(true);
		step4Button->setVisible(true);
		step5Button->setVisible(true);
		step6Button->setVisible(true);

		step2Button->runAction(RotateBy::create(stepSkillAnimaTime, 60));
		step3Button->runAction(RotateBy::create(2 * stepSkillAnimaTime, 120));
		step4Button->runAction(RotateBy::create(3 * stepSkillAnimaTime, 180));
		step5Button->runAction(RotateBy::create(4 * stepSkillAnimaTime, 240));
		step6Button->runAction(RotateBy::create(5 * stepSkillAnimaTime, 300));

	}
	else
	{

		step2Button->runAction(RotateBy::create(stepSkillAnimaTime, -60));
		step3Button->runAction(RotateBy::create(2 * stepSkillAnimaTime, -120));
		step4Button->runAction(RotateBy::create(3 * stepSkillAnimaTime, -180));
		step5Button->runAction(RotateBy::create(4 * stepSkillAnimaTime, -240));
		step6Button->runAction(RotateBy::create(5 * stepSkillAnimaTime, -300));

		step6Button->runAction(Sequence::create(RotateBy::create(5 * stepSkillAnimaTime, -300), CallFunc::create([this](){
			step1Button->setVisible(false);
			step2Button->setVisible(false);
			step3Button->setVisible(false);
			step4Button->setVisible(false);
			step5Button->setVisible(false);
			step6Button->setVisible(false);
		}
		), NULL));
	}
}

void GameBaseScene::showGoButton()
{
	goMenuItemButton->runAction(MoveBy::create(0.3, ccp(-(goMenuItemButton->getContentSize().width) * 2, 0)));
	skillMenuItemButton->runAction(MoveBy::create(0.3, ccp(-(skillMenuItemButton->getContentSize().width) * 2, 0)));
}


bool GameBaseScene::saveGame()
{

	//*** 生成 json 文件，存储在 getWritablePath 文件夹下 ***
	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value players(rapidjson::kArrayType);
	writedoc.AddMember("map_level", map_level, allocator);
	writedoc.AddMember("gameRoundCount", gameRoundCount, allocator);

	int playerNumber = 1;

	rapidjson::Value player1_json(rapidjson::kObjectType);
	rapidjson::Value player2_json(rapidjson::kObjectType);
	rapidjson::Value player3_json(rapidjson::kObjectType);


	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		switch (playerNumber)
		{
		case 1:
		{
				  // json object 格式添加 “名称/值” 对
				  player1_json.AddMember("playerTag", richerPlayer->getTag(), allocator);
				  player1_json.AddMember("playerPosition_x", richerPlayer->getPosition().x, allocator);
				  player1_json.AddMember("playerPosition_y", richerPlayer->getPosition().y, allocator);
				  player1_json.AddMember("restTimes", richerPlayer->restTimes, allocator);
				  player1_json.AddMember("stop_x", richerPlayer->stop_x, allocator);
				  player1_json.AddMember("stop_y", richerPlayer->stop_y, allocator);

				  player1_json.AddMember("money", richerPlayer->getMoney(), allocator);
				  player1_json.AddMember("strength", richerPlayer->getStrength(), allocator);

				  player1_json.AddMember("comeFromeRow", richerPlayer->getComeFromeRow(), allocator);
				  player1_json.AddMember("comeFromCol", richerPlayer->getComeFromCol(), allocator);
				  player1_json.AddMember("isMyTurn", richerPlayer->getIsMyTurn(), allocator);

				  player1_json.AddMember("skill", String::createWithFormat("%d-%d-%d", richerPlayer->skill_vector.at(0), richerPlayer->skill_vector.at(1), richerPlayer->skill_vector.at(2))->intValue(), allocator);

				  std::string tempstr;
				  tempstr = "";
				  for (auto i = 0; i<richerPlayer->lottery_vector.size(); i++)
				  {
					  tempstr.append(String::createWithFormat("%02d", richerPlayer->lottery_vector.at(i))->getCString()).append("_");
				  }
				  player1_json.AddMember("lottery", String::createWithFormat("%s", tempstr.c_str())->intValue(), allocator);

				  rapidjson::Value stocks(rapidjson::kArrayType);
				  for (auto i = 0; i<richerPlayer->stockMap.size(); i++)
				  {
					  rapidjson::Value stock(rapidjson::kObjectType);
					  stock.AddMember("stockCode", richerPlayer->stockMap.at(i)->getCode(), allocator);
					  stock.AddMember("makedealprice", richerPlayer->stockMap.at(i)->getMakedealprice(), allocator);
					  stock.AddMember("storeNumber", richerPlayer->stockMap.at(i)->getStoreNumber(), allocator);
					  stocks.PushBack(stock, allocator);
				  }

				  player1_json.AddMember("stocks", stocks, allocator);
				  // json 加入数组
				  players.PushBack(player1_json, allocator);
				  break;
		}
		case 2:
		{
				  player2_json.AddMember("playerTag", richerPlayer->getTag(), allocator);
				  player2_json.AddMember("playerPosition_x", richerPlayer->getPosition().x, allocator);
				  player2_json.AddMember("playerPosition_y", richerPlayer->getPosition().y, allocator);
				  player2_json.AddMember("restTimes", richerPlayer->restTimes, allocator);
				  player2_json.AddMember("stop_x", richerPlayer->stop_x, allocator);
				  player2_json.AddMember("stop_y", richerPlayer->stop_y, allocator);

				  player2_json.AddMember("money", richerPlayer->getMoney(), allocator);
				  player2_json.AddMember("strength", richerPlayer->getStrength(), allocator);

				  player2_json.AddMember("comeFromeRow", richerPlayer->getComeFromeRow(), allocator);
				  player2_json.AddMember("comeFromCol", richerPlayer->getComeFromCol(), allocator);
				  player2_json.AddMember("isMyTurn", richerPlayer->getIsMyTurn(), allocator);

				  player2_json.AddMember("skill", String::createWithFormat("%d-%d-%d", richerPlayer->skill_vector.at(0), richerPlayer->skill_vector.at(1), richerPlayer->skill_vector.at(2))->intValue(), allocator);

				  std::string tempstr;
				  tempstr = "";
				  for (auto i = 0; i<richerPlayer->lottery_vector.size(); i++)
				  {
					  tempstr.append(String::createWithFormat("%02d", richerPlayer->lottery_vector.at(i))->getCString()).append("_");
				  }
				  player2_json.AddMember("lottery", String::createWithFormat("%s", tempstr.c_str())->intValue(), allocator);

				  rapidjson::Value stocks(rapidjson::kArrayType);
				  for (auto i = 0; i<richerPlayer->stockMap.size(); i++)
				  {
					  rapidjson::Value stock(rapidjson::kObjectType);
					  stock.AddMember("stockCode", richerPlayer->stockMap.at(i)->getCode(), allocator);
					  stock.AddMember("makedealprice", richerPlayer->stockMap.at(i)->getMakedealprice(), allocator);
					  stock.AddMember("storeNumber", richerPlayer->stockMap.at(i)->getStoreNumber(), allocator);
					  stocks.PushBack(stock, allocator);
				  }

				  player2_json.AddMember("stocks", stocks, allocator);
				  players.PushBack(player2_json, allocator);
				  break;
		}
		case 3:
		{
				  player3_json.AddMember("playerTag", richerPlayer->getTag(), allocator);
				  player3_json.AddMember("playerPosition_x", richerPlayer->getPosition().x, allocator);
				  player3_json.AddMember("playerPosition_y", richerPlayer->getPosition().y, allocator);
				  player3_json.AddMember("restTimes", richerPlayer->restTimes, allocator);
				  player3_json.AddMember("stop_x", richerPlayer->stop_x, allocator);
				  player3_json.AddMember("stop_y", richerPlayer->stop_y, allocator);

				  player3_json.AddMember("money", richerPlayer->getMoney(), allocator);
				  player3_json.AddMember("strength", richerPlayer->getStrength(), allocator);

				  player3_json.AddMember("comeFromeRow", richerPlayer->getComeFromeRow(), allocator);
				  player3_json.AddMember("comeFromCol", richerPlayer->getComeFromCol(), allocator);
				  player3_json.AddMember("isMyTurn", richerPlayer->getIsMyTurn(), allocator);

				  player3_json.AddMember("skill", String::createWithFormat("%d-%d-%d", richerPlayer->skill_vector.at(0), richerPlayer->skill_vector.at(1), richerPlayer->skill_vector.at(2))->intValue(), allocator);

				  std::string tempstr;
				  tempstr = "";
				  for (auto i = 0; i<richerPlayer->lottery_vector.size(); i++)
				  {
					  tempstr.append(String::createWithFormat("%02d", richerPlayer->lottery_vector.at(i))->getCString()).append("_");
				  }
				  player3_json.AddMember("lottery", String::createWithFormat("%s", tempstr.c_str())->intValue(), allocator);

				  rapidjson::Value stocks(rapidjson::kArrayType);
				  for (auto i = 0; i<richerPlayer->stockMap.size(); i++)
				  {
					  rapidjson::Value stock(rapidjson::kObjectType);
					  stock.AddMember("stockCode", richerPlayer->stockMap.at(i)->getCode(), allocator);
					  stock.AddMember("makedealprice", richerPlayer->stockMap.at(i)->getMakedealprice(), allocator);
					  stock.AddMember("storeNumber", richerPlayer->stockMap.at(i)->getStoreNumber(), allocator);
					  stocks.PushBack(stock, allocator);
				  }

				  player3_json.AddMember("stocks", stocks, allocator);
				  players.PushBack(player3_json, allocator);
				  break;
		}


		}


		playerNumber++;
	}
	writedoc.AddMember("players", players, allocator);

	// landLayer;


	rapidjson::Value landlayerJson(rapidjson::kArrayType);
	Size _landLayerSize = landLayer->getLayerSize();
	for (int j = 0; j < _landLayerSize.width; j++) {
		for (int i = 0; i < _landLayerSize.height; i++) {
			Sprite* _sp = landLayer->tileAt(Point(j, i));
			if (_sp)
			{
				rapidjson::Value landJson(rapidjson::kObjectType);
				int gid = landLayer->getTileGIDAt(Point(j, i));
				landJson.AddMember("x", j, allocator);
				landJson.AddMember("y", i, allocator);
				landJson.AddMember("gid", gid, allocator);
				landlayerJson.PushBack(landJson, allocator);
			}

		}
	}

	writedoc.AddMember("landlayer", landlayerJson, allocator);



	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	writedoc.Accept(writer);

	auto path = FileUtils::getInstance()->getWritablePath();
	path.append(saveJsonName);
	FILE* file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
	return true;

}

bool GameBaseScene::reloadGame(int map_level)
{
	auto path = FileUtils::getInstance()->getWritablePath();
	switch (map_level)
	{
		case 1:
		{
			 path.append(SAVE_MAP1_JSON);
			 break;
		}
		case 2:
		{
			 path.append(SAVE_MAP2_JSON);
			 break;
		}
		case 3:
		{
			 path.append(SAVE_MAP3_JSON);
			 break;
		}
	}
	//*** 读取 json 文件 ***
	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	std::string load_str;

	// getFileData 如果不指定，读取根目录是 Resource 文件夹
	unsigned char* titlech = FileUtils::getInstance()->getFileData(path, "r", &size);
	load_str = std::string((const char*)titlech, size);


	readdoc.Parse<0>(load_str.c_str());
	if (readdoc.HasParseError())
	{
		CCLOG("GetParseError%s\n", readdoc.GetParseError());
	}

	if (!readdoc.IsObject())
		return 0;

	//回合数载入
	rapidjson::Value& _gameRoundCount = readdoc["gameRoundCount"];
	gameRoundCount = _gameRoundCount.GetInt();
	refreshRoundDisplay();

	//土地等级载人
	rapidjson::Value& _landlayer = readdoc["landlayer"];
	if (_landlayer.IsArray())
	{
		for (int i = 0; i<_landlayer.Capacity(); i++)
		{
			rapidjson::Value& arraydoc = _landlayer[i];

			int x = arraydoc["x"].GetInt();
			CCLOG("x:%d", x);
			int y = arraydoc["y"].GetInt();
			CCLOG("y:%d", y);
			int gid = arraydoc["gid"].GetInt();
			CCLOG("gid:%d", gid);

			landLayer->setTileGID(gid, ccp(x, y));

		}
	}

	//人物载人
	rapidjson::Value& _players = readdoc["players"];
	if (_players.IsArray())
	{
		for (int i = 0; i<_players.Capacity(); i++)
		{
			rapidjson::Value& arraydoc = _players[i];

			RicherPlayer* _richerPY = players_vector.at(i);

			int _restTimes = arraydoc["restTimes"].GetInt();
			float _playerPositionX = arraydoc["playerPosition_x"].GetDouble();
			float _playerPositionY = arraydoc["playerPosition_y"].GetDouble();
			int _stop_x = arraydoc["stop_x"].GetInt();
			int _stop_y = arraydoc["stop_y"].GetInt();
			int _money = arraydoc["money"].GetInt();
			int _strength = arraydoc["strength"].GetInt();
			int _comeFromeRow = arraydoc["comeFromeRow"].GetInt();
			int _comeFromCol = arraydoc["comeFromCol"].GetInt();
			bool _isMyTurn = arraydoc["isMyTurn"].GetBool();
			const char* _skill = arraydoc["skill"].GetString();
			const char* _lottery = arraydoc["lottery"].GetString();

			Vector<String*> lotteryVector = Util::splitString(_lottery, "_");
			for (int i = 0; i<lotteryVector.size(); i++)
			{
				_richerPY->lottery_vector.push_back(lotteryVector.at(i)->intValue());
			}

			_richerPY->restTimes = _restTimes;
			_richerPY->setPosition(ccp(_playerPositionX, _playerPositionY));
			_richerPY->setComeFromeRow(_comeFromeRow);
			_richerPY->setComeFromCol(_comeFromCol);
			_richerPY->setIsMyTurn(_isMyTurn);
			_richerPY->stop_x = _stop_x;
			_richerPY->stop_y = _stop_y;
			_richerPY->setMoney(_money);
			_richerPY->setStrength(_strength);

			Vector<String*> skillVs = Util::splitString(_skill, "-");
			_richerPY->skill_vector.at(0) = skillVs.at(0)->intValue();
			_richerPY->skill_vector.at(1) = skillVs.at(1)->intValue();
			_richerPY->skill_vector.at(2) = skillVs.at(2)->intValue();
			refreshMoneyLabel(_richerPY, 0);
			refreshStrengthLabel(_richerPY, 0);

		}
	}

	//股票载入

	for (int i = 0; i<players_vector.size(); i++)
	{
		RicherPlayer* _richerPY = players_vector.at(i);

		rapidjson::Value& _stocks = _players[i]["stocks"];
		if (_stocks.IsArray())
		{
			for (int i = 0; i<_stocks.Capacity(); i++)
			{
				rapidjson::Value& arraydoc = _stocks[i];
				int _stockCode = arraydoc["stockCode"].GetInt();
				int _makedealprice = arraydoc["makedealprice"].GetInt();
				int _storeNumber = arraydoc["storeNumber"].GetInt();
				_richerPY->stockMap.at(i)->setMakedealprice(_makedealprice);
				_richerPY->stockMap.at(i)->setStoreNumber(_storeNumber);
			}
		}
	}
	return 0;
}


void GameBaseScene::playerBgMusic(float fDelta)
{
	if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		Util::playBgMusic(bgMusicVector.at(rand() % bgMusicVector.size()), false);
	}

}

void GameBaseScene::initAudioEffect()
{
	bgMusicVector.push_back(BG01_MP3);
	bgMusicVector.push_back(BG02_MP3);
	bgMusicVector.push_back(BG03_MP3);

	for (int i = 0; i < bgMusicVector.size(); i++)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bgMusicVector.at(i));
	}
	this->schedule(schedule_selector(GameBaseScene::playerBgMusic), 5.0f);

	//交过路费声音
	player1EffectVec_1.pushBack(String::create(p1_fangpi));
	player1EffectVec_1.pushBack(String::create(p1_goushiyun));
	player1EffectVec_1.pushBack(String::create(p1_lehun));
	player1EffectVec_1.pushBack(String::create(p1_nothing));
	player1EffectVec_1.pushBack(String::create(p1_shebude));
	player1EffectVec_1.pushBack(String::create(p1_smiletolast));
	player1EffectVec_1.pushBack(String::create(p1_jianfei));
	player1EffectVec_1.pushBack(String::create(p1_xiaodaxiaonao));


	//抢夺别人地块
	player1EffectVec_2.pushBack(String::create(p1_huanyibao));

	//房屋被抢夺
	player1EffectVec_3.pushBack(String::create(p1_buruyi89));
	player1EffectVec_3.pushBack(String::create(p1_pei));
	player1EffectVec_3.pushBack(String::create(p1_zhenbuganxin));

	//摧毁别人房屋
	player1EffectVec_4.pushBack(String::create(p1_chaidiao));

	//房屋被摧毁
	player1EffectVec_5.pushBack(String::create(p1_doufu));
	player1EffectVec_5.pushBack(String::create(p1_xinzangbing));

	//蜜蜂伤人

	player1EffectVec_6.pushBack(String::create(p1_aiyouwai));

	//看到别人住院
	player1EffectVec_7.pushBack(String::create(p1_daomeishiba));
	player1EffectVec_7.pushBack(String::create(p1_jintian));
	player1EffectVec_7.pushBack(String::create(p1_kaixin));
	player1EffectVec_7.pushBack(String::create(p1_gouyancanchuan));
	//收取过路费
	player1EffectVec_8.pushBack(String::create(p1_zhushang));
	player1EffectVec_8.pushBack(String::create(p1_goddesign));
	player1EffectVec_8.pushBack(String::create(p1_pigtree));
	//升级房子
	player1EffectVec_9.pushBack(String::create(p1_buyaoxianmuwo));
	player1EffectVec_9.pushBack(String::create(p1_zoushenmeyun));
	player1EffectVec_9.pushBack(String::create(p1_quickup));
	//不交过路费
	player1EffectVec_10.pushBack(String::create(p1_bugeini));
	player1EffectVec_10.pushBack(String::create(p1_sheng));
	//买地
	player1EffectVec_11.pushBack(String::create(p1_likebuy));
	player1EffectVec_11.pushBack(String::create(p1_zanmeigod));


	//捡到珍珠
	player1EffectVec_12.pushBack(String::create(p1_huanjue));
	player1EffectVec_12.pushBack(String::create(p1_thanksgod));
	//对方被罚收税
	player1EffectVec_13.pushBack(String::create(p1_closedoor));
	player1EffectVec_13.pushBack(String::create(p1_baoying));
	player1EffectVec_13.pushBack(String::create(p1_dakuairenxin));


	//交过路费声音
	player2EffectVec_1.pushBack(String::create(p2_buyongzhaole));
	player2EffectVec_1.pushBack(String::create(p2_dazhema));
	player2EffectVec_1.pushBack(String::create(p2_kanbushang));
	player2EffectVec_1.pushBack(String::create(p2_qionggui));
	player2EffectVec_1.pushBack(String::create(p2_xiangnaier));
	player2EffectVec_1.pushBack(String::create(p2_tianna));

	//抢夺别人地块
	player2EffectVec_2.pushBack(String::create(p2_bingmao));
	player2EffectVec_2.pushBack(String::create(p2_bufangguo));
	player2EffectVec_2.pushBack(String::create(p2_huanfang));
	player2EffectVec_2.pushBack(String::create(p2_landisgood));
	player2EffectVec_2.pushBack(String::create(p2_shouduan));

	//房屋被抢夺
	player2EffectVec_3.pushBack(String::create(p2_lihai));
	player2EffectVec_3.pushBack(String::create(p2_pricelow));
	player2EffectVec_3.pushBack(String::create(p2_smiletolast));

	//摧毁别人房屋
	player2EffectVec_4.pushBack(String::create(p2_bieguaiwo));
	player2EffectVec_4.pushBack(String::create(p2_buhaore));
	player2EffectVec_4.pushBack(String::create(p2_chaichu));
	player2EffectVec_4.pushBack(String::create(p2_kanwode));
	player2EffectVec_4.pushBack(String::create(p2_youiquaile));

	//房屋被摧毁
	player2EffectVec_5.pushBack(String::create(p2_rangnideyi));
	player2EffectVec_5.pushBack(String::create(p2_zheyoushenme));
	player2EffectVec_5.pushBack(String::create(p2_yingwo));

	//蜜蜂伤人
	player2EffectVec_6.pushBack(String::create(p2_daomei));
	player2EffectVec_6.pushBack(String::create(p2_hongyan));
	player2EffectVec_6.pushBack(String::create(p2_mamaya));
	player2EffectVec_6.pushBack(String::create(p2_minga));

		
	//看到别人住院
	player2EffectVec_7.pushBack(String::create(p2_jintian));

	//收取过路费
	player2EffectVec_8.pushBack(String::create(p2_chabuduo));
	player2EffectVec_8.pushBack(String::create(p2_saiyafeng));
	player2EffectVec_8.pushBack(String::create(p2_zhuandaole));
	//升级房子
	player2EffectVec_9.pushBack(String::create(p2_gougaoba));

	//不交过路费
	player2EffectVec_10.pushBack(String::create(p2_bugei));

	//买地
	player2EffectVec_11.pushBack(String::create(p2_budongchan));
	player2EffectVec_11.pushBack(String::create(p2_meili));
	player2EffectVec_11.pushBack(String::create(p2_shuaidaile));
	player2EffectVec_11.pushBack(String::create(p2_xinqinghao));
	//捡到珍珠
	player2EffectVec_12.pushBack(String::create(p2_bulaima));
	player2EffectVec_12.pushBack(String::create(p2_zuomeismile));
	player2EffectVec_12.pushBack(String::create(p2_xingyungirl));

	//对方被罚收税
	player2EffectVec_13.pushBack(String::create(p2_diuren));
	player2EffectVec_13.pushBack(String::create(p2_jiaoshui));
}

void GameBaseScene::playNextEffectVec(float t)
{
	Util::playAudioEffectRandom(nextPlayerEffectVec, false);
}

void GameBaseScene::addBackMenuButton()
{
	Size winSize = Director::getInstance()->getWinSize();
	Menu* menu = getMenu();
	backMenuItemButton = MenuItemImage::create("images/back_normal.png", "images/back_pressed.png",
		this, menu_selector(GameBaseScene::menuButtonCallback));
	backMenuItemButton->setTag(backButtonTag);
	backMenuItemButton->setAnchorPoint(ccp(0, 0));
	menu->addChild(backMenuItemButton);

	backMenuItemButton->setPosition(ccp(20, winSize.height - 2 * backMenuItemButton->getContentSize().height));
	backMenuItemButton->setScale(0.8);
}

void GameBaseScene::addAudioMenuButton()
{
	Size winSize = Director::getInstance()->getWinSize();
	Menu* menu = getMenu();
	audioMenuItemButton = MenuItemImage::create(AUDIO_ON, AUDIO_OFF, this, menu_selector(GameBaseScene::menuButtonCallback));

	audioMenuItemButton->setPosition(ccp(20, winSize.height - 2 * backMenuItemButton->getContentSize().height - 1.5*audioMenuItemButton->getContentSize().height));
	audioMenuItemButton->setAnchorPoint(ccp(0, 0));
	audioMenuItemButton->setTag(audioButtonTag);
	audioMenuItemButton->setScale(0.8);
	bool music_on = UserDefault::getInstance()->getBoolForKey(MUSIC_ON_KEY, true);

	if (music_on)
	{
		audioMenuItemButton->unselected();
	}
	else
	{
		audioMenuItemButton->selected();
	}
	menu->addChild(audioMenuItemButton);
}

void GameBaseScene::quitButtonCallback(Node *pNode)
{
	Util::playAudioEffect(click_effect, false);
	if (pNode->getTag() == Quit_OK_TAG)
	{
		Director::getInstance()->popScene();
	}
	else
	{
		pNode->getParent()->getParent()->removeFromParent();
	}

}

void GameBaseScene::raisePriceIndex()
{
	int isCanRaisePriceIndex = 0;
	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		if (player->getMoney() > RAISE_PRICE_INDEX_MONEY * priceIndex)
		{
			isCanRaisePriceIndex++;
		}
		
	}
	if (isCanRaisePriceIndex >= players_vector.size())
	{
		priceIndex++;
		refreshPriceIndexLabel();
	}
	if (gameRoundCount != 0 && gameRoundCount % RAISE_PRICE_INDEX_FREN == 0)
	{
		priceIndex++;
		refreshPriceIndexLabel();
	}
}

void GameBaseScene::addPriceIndexLabel()
{
	String* str = String::createWithFormat("%s: %d", LanguageString::getInstance()->getLanguageString(PRICE_INDEX)->getCString(), priceIndex);
	priceIndex_label = LabelTTF::create();
	priceIndex_label->setString(str->getCString());
	priceIndex_label->setAnchorPoint(ccp(0, 0.5));
	priceIndex_label->setFontSize(15);
	priceIndex_label->setPosition(tableStartPosition_x + 15, tableStartPosition_y +10);
	addChild(priceIndex_label);
}

void GameBaseScene::refreshPriceIndexLabel()
{
	String* str = String::createWithFormat("%s: %d", LanguageString::getInstance()->getLanguageString(PRICE_INDEX)->getCString(), priceIndex);
	priceIndex_label->setString(str->getCString());

}