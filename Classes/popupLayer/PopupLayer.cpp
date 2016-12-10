#include "PopupLayer.h"
#include "Map1Scene.h"
#include "Map2Scene.h"
#include "Map3Scene.h"


bool PopupLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m__pMenu = NULL;
	m_callbackListener = NULL;
	m_callback = NULL;
	m__sfBackGround = NULL;
	m__s9BackGround = NULL;
	m__ltContentText = NULL;
	m__ltTitle = NULL;
	this->setContentSize(Size::ZERO);

	Menu* menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenuButton(menu);
	lottery_selected = 0;
	lottery_total_money = LOTTERY_WIN_MONEY;
	return true;
}

void PopupLayer::setPopModalDialog(bool mD)
{
	if (mD)
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = [](Touch *t, Event *e){
			log("PopupLayer touch");
			return true;
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
}

PopupLayer* PopupLayer::create(const char *backgroundImage)
{
	PopupLayer* ml = PopupLayer::create();
	ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	return ml;
}

void PopupLayer::setPopType(POP_TYPE type)
{
	pop_type = type;
}

void PopupLayer::setTitle(const char *title, int fontsize)
{
	LabelTTF* ltfTitle = LabelTTF::create(title, "", fontsize);
	setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}





void PopupLayer::setCallbackFunc(cocos2d::Object *target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = ccp(winSize.width / 2, winSize.height / 2);

	MenuItemImage* menuImage = MenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);

	Size imenu = menuImage->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
	menuImage->addChild(ttf);

	getMenuButton()->addChild(menuImage);
	return true;
}

void PopupLayer::buttonCallback(cocos2d::CCObject *pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);
	log("touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)(node);
	}
}

void PopupLayer::onEnter()
{
	
	Layer::onEnter();
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = ccp(winSize.width / 2, winSize.height / 2);
	Size contentSize;
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(getContentSize());
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);
	contentSize = getContentSize();

	this->addChild(getMenuButton());
	float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	Vector<Node*> vecArray = getMenuButton()->getChildren();

	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width / 2 - contentSize.width / 2 + btnWidth*(j + 1), winSize.height / 2 - contentSize.height / 3));
		j++;
	}

	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 20)));
		getLabelTitle()->setColor(ccc3(0, 0, 0));
		this->addChild(getLabelTitle());
	}

	switch (pop_type)
	{
		case LOTTERY:
		{
			setLotteryContext(contentSize);
			break;
		}
		case LOTTERY_PUBLISH:
		{
							
			setPublishLotteryContext(contentSize);
			break;
		}
		case LOADGAME:
		{
			setLoadGameContext(contentSize);
			break;
		}
		default:
		{
			   if (getLabelContentText())
			   {
				   LabelTTF* ltf = getLabelContentText();
				   ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
				   ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
				   ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
				   ltf->setColor(ccc3(0, 0, 0));
				   this->addChild(ltf);
			   }
		}
	}


	Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.15, 1.05),
		ScaleTo::create(0.08, 0.95),
		ScaleTo::create(0.08, 1.0),
		NULL);
	this->runAction(popupLayer);

}

void PopupLayer::onExit()
{
	Layer::onExit();
	log("popup on exit");
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}

void PopupLayer::setLotteryContext(Size size)
{
	Size winSize = Director::getInstance()->getWinSize();
	Size center = (winSize - size) / 2;
	//9*2的单元格
	for (int row = 0; row<9; row++)
	{
		for (int col = 0; col<(LOTTERY_BALL_COUNT/9); col++)
		{
			LotteryCard* card = LotteryCard::createCardSprite((row + 1) + col * 9, 40, 40, center.width + 20 + row*(size.width / 10), (winSize.height / 2 + 20) - 40 * col);
			card->setTag((row + 1) + col * 9);
			card->setLotteryCardCallback(this, callfuncN_selector(PopupLayer::refreshBallBackGround));

			addChild(card);
			lotteryVector.pushBack(card);

			for (int i = 0; i<selected_number_vector.size(); i++)
			{
				if (selected_number_vector.at(i) == (row + 1) + col * 9)
				{
					card->setVisible(false);
				}
			}
		}
	}
}
void PopupLayer::setHasSelectedLotteryNumber(std::vector<int> _vector)
{
	for (int i = 0; i<_vector.size(); i++)
	{
		selected_number_vector.push_back(_vector.at(i));
	}

}

void PopupLayer::refreshBallBackGround(Node *pNode)
{
	for (auto it = lotteryVector.begin(); it != lotteryVector.end(); it++)
	{
		LotteryCard* node = (LotteryCard*)(*it);
		if (node->getTag() != pNode->getTag())
		{
			node->setUnSelected();
		}
	}
	lottery_selected = pNode->getTag();

	Vector<Node*> menuItemVector = getMenuButton()->getChildren();
	for (int i = 0; i< getMenuButton()->getChildrenCount(); i++)
	{
		if (menuItemVector.at(i)->getTag() != 0)
		{
			menuItemVector.at(i)->setTag(lottery_selected);
			break;
		}
	}
}
void PopupLayer::setPlayerVector(Vector<RicherPlayer*> _vector)
{
	for (int i = 0; i<_vector.size(); i++)
	{
		players_vector.pushBack(_vector.at(i));
	}
}

void PopupLayer::addPlayersLottery()
{
	labelLotteryMoney->setString(String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(POOL_FUNDS)->getCString(),lottery_total_money)->getCString());
	for (int i = 1; i <= LOTTERY_BALL_COUNT*2; i++)
	{
		if (this->getChildByTag(1000 + i) != NULL)
		{
			this->removeChildByTag(1000 + i);
		}

	}
	Size winSize = Director::getInstance()->getWinSize();
	Size size = this->getContentSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		playerLotteryVector.clear();
		for (int i = 0; i < player->lottery_vector.size(); i++)
		{
			LabelTTF* labelLotteryNumber = LabelTTF::create(String::createWithFormat("%i", player->lottery_vector.at(i))->getCString(), "", 15);
			labelLotteryNumber->setPosition(ccp(center.width + 30 + (i + 1) * 20, (winSize.height / 2 - size.height / 2 + 30) + j * 50));
			labelLotteryNumber->setColor(Color3B(255, 100, 100));
			labelLotteryNumber->setTag(1000 + j * 18 + player->lottery_vector.at(i));
			playerLotteryVector.pushBack(labelLotteryNumber);
		}
		for (int i = 0; i < playerLotteryVector.size(); i++)
		{
			addChild(playerLotteryVector.at(i));
		}
		j++;
	}
}

void PopupLayer::runPublishAnmi()
{
	Util::playAudioEffect(MASHANGKAIJIANG, false);
	scheduleOnce(schedule_selector(PopupLayer::realRunPublishAnmi), 3.0f);
}

void PopupLayer::realRunPublishAnmi(float dt)
{
	srand(unsigned(time(NULL)));
	lottNumber = rand() % (LOTTERY_BALL_COUNT)+1;
	float angleRotate = (LOTTERY_BALL_COUNT - lottNumber + 1) * (360 / LOTTERY_BALL_COUNT) + 7200;
	log("****lottNumberis %d :**", lottNumber);
	auto pAction = EaseExponentialOut::create(RotateBy::create(6, angleRotate));
	m_turnBg->runAction(Sequence::create(pAction, CallFunc::create(CC_CALLBACK_0(PopupLayer::onTurnEnd, this)), NULL));
}

void PopupLayer::setPublishLotteryContext(Size size)
{
	Size winSize = Director::getInstance()->getWinSize();
	//添加转盘
	m_turnBg = Sprite::create("images/turn_bg.png");
	m_turnBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(m_turnBg);

	//添加指针
	auto arrNor = Sprite::create("images/turn_arrow.png");
	arrNor->setPosition(Vec2(winSize.width / 2, winSize.height * 0.557));
	arrNor->setScale(0.5);
	addChild(arrNor);

	//添加奖池资金数额

	labelLotteryMoney = LabelTTF::create(String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(POOL_FUNDS)->getCString(), lottery_total_money)->getCString(), "", 20);
	labelLotteryMoney->setPosition(ccp(winSize.width /2 -size.width/2+10, (winSize.height / 2 +size.height/2)-50));
	labelLotteryMoney->setColor(Color3B(255, 100, 100));
	labelLotteryMoney->setAnchorPoint(ccp(0, 1));
	addChild(labelLotteryMoney);


	addPlayersInfo(size);

}

void PopupLayer::addPlayersInfo(Size size)
{
	Size winSize = Director::getInstance()->getWinSize();
	Size center =(winSize-size)/2;
	int j=0;
	for(auto it=players_vector.begin();it!=players_vector.end();it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		char* playerLog;
		switch (player->getTag())
		{
		case PLAYER_1_TAG:
			{
				playerLog = "map/player1.png";
				break;
			}
		case PLAYER_2_TAG:
			{
				playerLog = "map/player2.png";
				break;
			}
		}

		Sprite* playerSprite = Sprite::create(playerLog);
		playerSprite->setPosition( center.width+20, (winSize.height/2-size.height/2+30)+j*50);
		playerSprite->setScale(0.8);
		addChild(playerSprite);
		j++;
	}
	lottery_win_1 = Sprite::create("images/lottery_win.png");
	lottery_win_1->setPosition(center.width + 150, (winSize.height / 2 - size.height / 2 + 30));

	lottery_win_1->setVisible(false);
	addChild(lottery_win_1);
	lottery_win_2 = Sprite::create("images/lottery_win.png");
	lottery_win_2->setPosition(center.width + 150, (winSize.height / 2 - size.height / 2 + 30) + 50);

	lottery_win_2->setVisible(false);
	addChild(lottery_win_2);
}

void PopupLayer::onTurnEnd()
{
	Size winSize = Director::getInstance()->getWinSize();
	scheduleOnce(schedule_selector(PopupLayer::dismissFromParent), 4.0f);
	int j = 0;
	int winLotteryPlayerCount = 0;
	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		for (int i = 0; i < player->lottery_vector.size(); i++)
		{
			if (player->lottery_vector.at(i) == lottNumber)
			{
				winLotteryPlayerCount++;
				//player->setMoney(player->getMoney() + LOTTERY_WIN_MONEY);
				if (j == 0)
				{
					lottery_win_1->setVisible(true);
					playParticle(lottery_win_1->getPosition(), PLAYER1_1_PARTICLE_PLIST);
					//lottery_win_1->runAction(Sequence::create(ScaleBy::create(0.1, 1.5), ScaleBy::create(0.5, 0.3), NULL));
				}
				if (j == 1)
				{
					lottery_win_2->setVisible(true);
					playParticle(lottery_win_1->getPosition(), PLAYER2_1_PARTICLE_PLIST);
					//lottery_win_2->runAction(Sequence::create(ScaleBy::create(0.1, 1.5), ScaleBy::create(0.5, 0.3), NULL));
				}
			}
		}	
		j++;
	}

	if (winLotteryPlayerCount == 0)
	{
		lottery_total_money += LOTTERY_WIN_MONEY;
		Util::playAudioEffect(P1_meirendejiang, false);
		return;
	}

	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		if (winLotteryPlayerCount == 1)
		{
			for (int i = 0; i < player->lottery_vector.size(); i++)
			{
				if (player->lottery_vector.at(i) == lottNumber)
				{
					player->setMoney(player->getMoney()+lottery_total_money);
					lottery_total_money = LOTTERY_WIN_MONEY;
					break;
				}
			}
		}
		if (winLotteryPlayerCount == 2)
		{
			player->setMoney(player->getMoney() + lottery_total_money / winLotteryPlayerCount);
			lottery_total_money = LOTTERY_WIN_MONEY;
		}
		j++;
	}
	
}

void PopupLayer::dismissFromParent(float dt)
{
	lottery_win_1->setVisible(false);
	lottery_win_2->setVisible(false);
	//lottery_win_1->runAction(Sequence::create(ScaleBy::create(0, 1.5), ScaleBy::create(0, 0.3), NULL)->reverse());
	//lottery_win_2->runAction(Sequence::create(ScaleBy::create(0, 1.5), ScaleBy::create(0, 0.3), NULL)->reverse());
	m_turnBg->runAction(RotateBy::create(0, -(LOTTERY_BALL_COUNT - lottNumber + 1) * 360 / LOTTERY_BALL_COUNT));

	for (auto it = players_vector.begin(); it != players_vector.end(); it++)
	{
		RicherPlayer* player = dynamic_cast<RicherPlayer*>(*it);
		player->lottery_vector.clear();
	}

	Util::sendCustomEvent(RICHER_MSG, String::createWithFormat("%d", MSG_DIMISS_DIALOG_PUBLISH_LOTTERY_TAG));
	this->setVisible(false);
}

void PopupLayer::setLoadGameContext(Size size)
{
	Size winSize = Director::getInstance()->getWinSize();

	Menu* menu = Menu::create();
	menu->setPosition(Point::ZERO);

	auto map1_path = FileUtils::getInstance()->getWritablePath();
	map1_path.append(SAVE_MAP1_JSON);
	FILE* map1_file = fopen(map1_path.c_str(), "r");
	if (map1_file)
	{
		map1LoadGameMenuItem = MenuItemImage::create("map/map1_load_normal.png", "map/map1_load_pressed.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		map1LoadGameMenuItem->setPosition(winSize / 2 + Size(0, 120));
		map1LoadGameMenuItem->setTag(save_map1_tag);
		menu->addChild(map1LoadGameMenuItem);
		fclose(map1_file);
	}
	else
	{
		map1LoadGameMenuItem = MenuItemImage::create("map/blank.png", "map/blank.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		map1LoadGameMenuItem->setPosition(winSize / 2 + Size(0, 120));
		menu->addChild(map1LoadGameMenuItem);
	}





	auto map2_path = FileUtils::getInstance()->getWritablePath();
	map2_path.append(SAVE_MAP2_JSON);
	FILE* map2_file = fopen(map2_path.c_str(), "r");
	if (map2_file)
	{
		map2LoadGameMenuItem = MenuItemImage::create("map/map2_load_normal.png", "map/map2_load_pressed.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		map2LoadGameMenuItem->setPosition(winSize / 2 + Size(0, 20));
		map2LoadGameMenuItem->setTag(save_map2_tag);
		menu->addChild(map2LoadGameMenuItem);
		fclose(map2_file);
	}
	else
	{
		map2LoadGameMenuItem = MenuItemImage::create("map/blank.png", "map/blank.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		map2LoadGameMenuItem->setPosition(winSize / 2 + Size(0, 20));
		menu->addChild(map2LoadGameMenuItem);
	}

	auto map3_path = FileUtils::getInstance()->getWritablePath();
	map3_path.append(SAVE_MAP3_JSON);
	FILE* map3_file = fopen(map3_path.c_str(), "r");
	if (map3_file)
	{
		map3LoadGameMenuItem = MenuItemImage::create("map/map3_load_normal.png", "map/map3_load_pressed.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		map3LoadGameMenuItem->setPosition(winSize / 2 + Size(0, -80));
		map3LoadGameMenuItem->setTag(save_map3_tag);
		menu->addChild(map3LoadGameMenuItem);
		fclose(map3_file);
	}
	else
	{
		map3LoadGameMenuItem = MenuItemImage::create("map/blank.png", "map/blank.png", this, menu_selector(PopupLayer::loadGameButtonCallback));
		map3LoadGameMenuItem->setPosition(winSize / 2 + Size(0, -80));
		menu->addChild(map3LoadGameMenuItem);
	}

	addChild(menu);

}


void PopupLayer::loadGameButtonCallback(cocos2d::CCObject *pSender)
{
	mapLevelTag = ((Node*)pSender)->getTag();
	if (mapLevelTag == save_map1_tag)
	{
		
		TransitionFadeBL* scene = TransitionFadeBL::create(1, Map1Scene::createScene());
		Director::getInstance()->pushScene(scene);
		removeFromParent();
	}
	if (mapLevelTag == save_map2_tag)
	{
		TransitionFadeBL* scene = TransitionFadeBL::create(1, Map2Scene::createScene());
		Director::getInstance()->pushScene(scene);
		removeFromParent();
	}
	if (mapLevelTag == save_map3_tag)
	{
		TransitionFadeBL* scene = TransitionFadeBL::create(1, Map3Scene::createScene());
		Director::getInstance()->pushScene(scene);
		removeFromParent();
	}
	sendLoadGameMSG();
}

void PopupLayer::sendLoadGameMSG()
{
	String * str = String::createWithFormat("%d-%d", MSG_LOAD_GAME_TAG, mapLevelTag);
	NotificationCenter::getInstance()->postNotification(MSG_LOAD_GAME, str);
}

void  PopupLayer::playParticle(Point point, char* plistName)
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