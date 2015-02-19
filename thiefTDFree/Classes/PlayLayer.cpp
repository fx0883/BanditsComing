//
//  PlayLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//
#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "PlayLayer.h"
#include "GameManager.h"
#include "SuccessfulScene.h"
#include "FailedScene.h"
#include "LevelScene.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h" 
#include "SettingScene.h"
#include "LoadLevelinfo.h"
#include "PopupLayer.h"
#include <string>

using namespace std;
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
template<typename T>
string to_string(const T& t) {
    ostringstream os;
    os << t;
    return os.str();
}
#endif

USING_NS_CC_EXT;
using namespace CocosDenshion; 

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
,chooseTowerpanle(NULL)
,towerMatrix(NULL)
,groupCounter(0)
,money(0)
,playHpBar(NULL)
,playHpPercentage(100)
,moneyLabel(NULL)
,groupLabel(NULL)
,groupTotalLabel(NULL)
,isSuccessful(false)
{
}

PlayLayer::~PlayLayer()
{
	if (towerMatrix) {
        free(towerMatrix);
    }
	pointsVector.clear();
    this->unscheduleAllSelectors();
}

Scene *PlayLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

bool PlayLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    instance = GameManager::getInstance();
    
	auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);

    map = TMXTiledMap::create(instance->getCurMapName());
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    this->addChild(map, -10);
	
	initToolLayer();

    offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
	//addGroupEnemy();
    schedule(schedule_selector(PlayLayer::logic), 2.0f);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
//    unscheduleUpdate();
//    scheduleUpdate();

	int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
    towerMatrix = (TowerBase **)malloc(arraySize);
    memset((void*)towerMatrix, 0, arraySize);

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
            towerMatrix[row * MAP_WIDTH + col] = NULL;
        }
    }
    return true;
}

void PlayLayer::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}

void PlayLayer::onExit()
{
    Node::onExit();
    unscheduleUpdate();
}


void PlayLayer::initToolLayer()
{
	//¥¥Ω®tool≤„
	auto size = Director::getInstance()->getWinSize();
	toolLayer = Layer::create();
	addChild(toolLayer);

	auto spritebg = Sprite::createWithSpriteFrameName("toolbg.png");
	spritebg->setAnchorPoint(Point(0.5f, 1));
	spritebg->setPosition (Point(size.width / 2, size.height));
	toolLayer->addChild(spritebg);

	auto spritetool = Sprite::createWithSpriteFrameName("tool.png");
	spritetool->setPosition (Point(spritebg->getContentSize().width / 2, spritebg->getContentSize().height /2));
	spritebg->addChild(spritetool);

	// «Æ
	money = instance->getMoney();
	moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", "abdd");
    moneyLabel->setPosition(Point(spritetool->getContentSize().width / 9, spritetool->getContentSize().height / 2));
	moneyLabel->setAnchorPoint(Point(0, 0.5f));
    auto moneyText = to_string(money);
	moneyLabel->setString(moneyText);
    spritetool->addChild(moneyLabel);

	// ÕÊº“—™Ãı
	playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
	playHpBar->setType(ProgressTimer::Type::BAR);
	playHpBar->setMidpoint(Point(0, 0.5f));
	playHpBar->setBarChangeRate(Point(1, 0));
	playHpBar->setPercentage(playHpPercentage);
    playHpBar->setPosition(Point(spritetool->getContentSize().width / 4 *3, spritetool->getContentSize().height / 2));
    spritetool->addChild(playHpBar);

	auto star = Sprite::createWithSpriteFrameName("playstar.png");
    star->setPosition(Point(spritetool->getContentSize().width / 4 *3, spritetool->getContentSize().height / 2));
	spritetool->addChild(star);
	
	// ≈˙¥Œ–≈œ¢
	int groupTotal = instance->getGroupNum();
	groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    groupLabel->setPosition(Point(spritetool->getContentSize().width / 8 * 3, spritetool->getContentSize().height / 2 ));
	groupLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupInfoText = to_string(groupCounter + 1);
	groupLabel->setString(groupInfoText);
    spritetool->addChild(groupLabel);

	groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 2 - 10, spritetool->getContentSize().height / 2 ));
	groupTotalLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupTotalText = to_string(groupTotal);
	groupTotalLabel->setString(groupTotalText);
    spritetool->addChild(groupTotalLabel);

    
    //Modify by FX begin
	// back
//	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
//	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
//	MenuItemSprite *pPauseItem = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(PlayLayer::menuBackCallback, this));
//	pPauseItem->setPosition(Point(spritetool->getContentSize().width - backItem1->getContentSize().width, spritetool->getContentSize().height / 2));
//	pPauseItem->setAnchorPoint(Point(0, 0.5f));
//	Menu* pMenu = Menu::create(pPauseItem, NULL);
//	pMenu->setPosition(Point::ZERO);
//	spritetool->addChild(pMenu);
    
    Sprite *settingItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
    Sprite *settingItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
    MenuItemSprite *pPauseItem = MenuItemSprite::create(settingItem1, settingItem2, CC_CALLBACK_1(PlayLayer::menuSettingCallback, this));
    pPauseItem->setPosition(Point(spritetool->getContentSize().width - settingItem1->getContentSize().width, spritetool->getContentSize().height / 2));
    pPauseItem->setAnchorPoint(Point(0, 0.5f));
    Menu* pMenu = Menu::create(pPauseItem, NULL);
    pMenu->setPosition(Point::ZERO);
    spritetool->addChild(pMenu);
}

void PlayLayer::menuPauseCallback(Ref* pSender)
{
	this->unscheduleAllSelectors();
	for (Node* nodeTemp : this->getChildren())
	{
		for (Node* nodeTemp1 : nodeTemp->getChildren())
			nodeTemp1->unscheduleAllSelectors();
	}
}

void PlayLayer::menuSettingCallback(Ref* pSender)
{
    //Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, SettingScene::createScene()));
    
    
    PopupLayer* popup = PopupLayer::create("600popup.png");
    // ContentSize是可选的设置，可以不设置，如果设置则把它当做9图缩放
    popup->setContentSize(CCSizeMake(300, 180));
//    popup->setTitle("Message");
//    popup->setContentText("Most people... blunder round this city.", 20, 50, 150);
    // 设置回调函数，回调传回一个CCNode以获取tag判断点击的按钮
    // 这只是作为一种封装实现，如果使用delegate那就能够更灵活的控制参数了
    popup->setCallBackFunc(this, callfuncN_selector(PlayLayer::controlCallback));
    //添加按钮，设置图片、文字，tag信息
//    popup->addButton("start_1.png", "start_1.png", "Ok", 0);
//    popup->addButton("start_1.png", "start_1.png", "Cancel", 1);
    popup->addButton("btnBack.png", "btnBack.png", "", 0);//返回
    popup->addButton("btnSelectPass.png", "btnSelectPass.png", "", 1);//选关
    popup->addButton("btnRestart.png", "btnRestart.png", "", 2);//重新开始

    
    this->addChild(popup,1000);
    
    CCDirector::getInstance()->pause();
    
   // pause()和resume()
    
}
void PlayLayer::controlCallback(Node* pSender)
{
    CCDirector::getInstance()->resume();
    switch (pSender->getTag()) {
        case 0:

            break;
        case 1:
            menuBackCallback(NULL);
            break;
        case 2:
        {
            SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
            string fileName =  UserDefault::getInstance()->getStringForKey("nextLevelFile");
            if( fileName ==""){
                fileName = "levelInfo_1_0.plist";
            }
            LoadLevelinfo* info = LoadLevelinfo::createLoadLevelinfo(fileName.c_str());
            info->initLevelInfo();
            Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
            break;
        }
        default:
            break;
    }
}


void PlayLayer::menuBackCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
    instance->clear();
    
}

GroupEnemy* PlayLayer::currentGroup()
{
    GroupEnemy* groupEnemy;
    if(instance->groupVector.size() != 0)
    {
        groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
    }
    else{
        groupEnemy =NULL;
    }
    return groupEnemy;
}

GroupEnemy* PlayLayer::nextGroup()
{
	if(instance->groupVector.size() == 0)
	{
		return NULL;
	}

	if (groupCounter < instance->getGroupNum() - 1)
	{
		groupCounter++;
	}
	else{
		// ”Œœ∑…˝º∂£¨œ¬“ªπÿ”Œœ∑ ˝æ›
		//groupCounter = 0;
		isSuccessful = true;
	}
		GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
		return groupEnemy;

}

void PlayLayer::initPointsVector(float offX)
{
    Node *runOfPoint = NULL;
	int count = 0;
	ValueMap point;
	point = objects->getObject(to_string(count));
	while (point.begin()!= point.end())
	{
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		runOfPoint = Node::create();
		runOfPoint->setPosition(Point(x - offX , y  ));
		this->pointsVector.pushBack(runOfPoint);
		count++;
		point = objects->getObject( to_string(count));
	}
	runOfPoint = NULL;
}

void PlayLayer::addEnemy()
{
    SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
	GroupEnemy* groupEnemy = this->currentGroup();
	if(groupEnemy == NULL)
	{
		return;
	}
	auto restEnemyNum = groupEnemy->getEnemyTotal();
    if( restEnemyNum <= 0){
		groupEnemy->setIsFinishedAddGroup(true);
		return;
	}

	restEnemyNum--;
	groupEnemy->setEnemyTotal(restEnemyNum);

	EnemyBase* enemy = NULL;
	
	if(groupEnemy->getType1Total() > 0){
		enemy = Thief::createThief(pointsVector, groupEnemy->getType1Hp());
		groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
	}
	else if(groupEnemy->getType2Total() > 0){
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Pirate::createPirate(pointsVector, groupEnemy->getType2Hp());
		groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
	}
	else if(groupEnemy->getType3Total() > 0){
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Bandit::createBandit(pointsVector, groupEnemy->getType3Hp());
		groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
	}

	this->addChild(enemy, 10);
    instance->enemyVector.pushBack(enemy);
}

void PlayLayer::logic(float dt){
	GroupEnemy* groupEnemy = this->currentGroup();

	if(groupEnemy == NULL)
	{
		return;
	}
	if(groupEnemy->getIsFinishedAddGroup() ==true  && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum()/*groupEnemy->getCurrEnemyNum() <= 0*/)
	{
		groupEnemy = this->nextGroup();
		int groupTotal = instance->getGroupNum();
		auto groupInfoText =to_string(groupCounter + 1);
		groupLabel->setString(groupInfoText);
		auto groupTotalText = to_string(groupTotal);
		groupTotalLabel->setString(groupTotalText);
	}
	static long lastTimeTargetAdded = 0;
	long now = 0;
	if(lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= 10 * 1000){
		this->addEnemy();
		lastTimeTargetAdded = now;
	}
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
	this->removeChild(chooseTowerpanle);
	chooseTowerpanle = NULL;
    auto location = touch->getLocation();

	checkAndAddTowerPanle(location);
	return true;
}

void PlayLayer::addTowerChoosePanle(Point point)
{
    chooseTowerpanle = TowerPanleLayer::create();
    chooseTowerpanle->setPosition(point);
    this->addChild(chooseTowerpanle);
}

Point PlayLayer::convertTotileCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;

	return Point(x, y);	
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y = position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);	
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{
	Point towerCoord = convertTotileCoord(position);
	Point matrixCoord = convertToMatrixCoord(position);
	int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );

	int gid = bgLayer->getTileGIDAt(towerCoord);
	auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
	auto tileWidth = map->getContentSize().width /	map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
	int TouchVaule;
	if (tileTemp.size() == 0)
	{
		TouchVaule = 0;
	}
	else
	{
		TouchVaule = tileTemp.at("canTouch").asInt();
	}
	towerPos = Point((towerCoord.x * tileWidth) + tileWidth/2 -offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
	if (1 == TouchVaule && towerMatrix[MatrixIndex]==NULL)
	{		
		addTowerChoosePanle(towerPos);	
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
		auto tips = Sprite::createWithSpriteFrameName("no.png");
		tips->setPosition(towerPos);
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.8f),
										CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), 
										NULL));
	}
}

void PlayLayer::CollisionDetection()
{
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;

	if(bulletVector.size() == 0 || enemyVector.size() == 0 ){
		return;
	}

	Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
    for (int i = 0; i < bulletVector.size(); i++)
	{
		auto  bullet = bulletVector.at(i);
		auto  bulletRect = Rect(bullet->getPositionX() +bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        
		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//auto enemyRect = enemy->sprite->getBoundingBox();
			// Àı–°“ª∞Î
            auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
                                enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 4,
                                enemy->sprite->getContentSize().width / 2,
                                enemy->sprite->getContentSize().height / 2 );
			if (bulletRect.intersectsRect(enemyRect))
			{
				if( ATTACK_BULLET == bullet->getTag()){
					auto currHp = enemy->getCurrHp();
					currHp--;
					enemy->setCurrHp( currHp );
                
					auto currHpPercentage = enemy->getHpPercentage();
					auto offHp = 100 / enemy->getMaxHp();
					currHpPercentage -= offHp;
					if(currHpPercentage < 0){
						currHpPercentage = 0;
					}
					enemy->setHpPercentage(currHpPercentage);
					enemy->getHpBar()->setPercentage(currHpPercentage);
                
					if(currHp <= 0)
					{
						enemyNeedToDelete.pushBack(enemy);
                        auto valueMoney = enemy->getVaule();
                        money += valueMoney;
                        auto moneyText = to_string(money);
                        moneyLabel->setString(moneyText);
					}
				}
				else if(DECELERATE_BULLET == bullet->getTag())
				{
					enemy->decelerate();
				}
                bulletNeedToDelete.pushBack( bullet);
				break;
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)
		{
            enemyTemp->enemyExpload();
            instance->enemyVector.eraseObject(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}
	
	for (Sprite* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}

void PlayLayer::enemyIntoHouse()
{
    auto enemyVector = instance->enemyVector;
    for (int i = 0; i < enemyVector.size(); i++)
    {
        auto enemy = enemyVector.at(i);
        if( enemy->getEnemySuccessful() == true)
        {
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.mp3").c_str(), false);
            instance->enemyVector.eraseObject(enemy);
            enemy->removeFromParent();
			auto playHp = getPlayHpPercentage() - 10;
			setPlayHpPercentage(playHp);
			playHpBar->setPercentage(playHp);
        }
    }

	if(getPlayHpPercentage() <= 0)
	{
		
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, FailedScene::create()));
		instance->clear();
        this->unscheduleUpdate();
	}
}

void PlayLayer::update(float dt)
{
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    auto towerVector = instance->towerVector;
    
    if(chooseTowerpanle != NULL )
	{
		auto type = chooseTowerpanle->getChooseTowerType();
		Point matrixCoord = convertToMatrixCoord(towerPos);
		int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
		bool noMoneyTips = false;
		if( type == TowerType::ARROW_TOWER )
        {
			if( money >= 200 )
			{
				TowerBase* tower = ArrowTower::create();
				tower->setPosition(towerPos);
				tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
				this->addChild(tower);
				instance->towerVector.pushBack(tower);
				towerMatrix[MatrixIndex] =  tower;
				money -= 200;
			}else{
				noMoneyTips = true;
			}
			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            this->removeChild(chooseTowerpanle);
            chooseTowerpanle = NULL;		
		}
        else if( type == TowerType::DECELERATE_TOWER )
        {
			if( money >= 150 )
			{
				DecelerateTower* tower = DecelerateTower::create();
				tower->setPosition(towerPos);
				tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
				this->addChild(tower);
				instance->towerVector.pushBack(tower);
				towerMatrix[MatrixIndex] =  tower;
				money -= 150;
			}else{
				noMoneyTips = true;
			}

			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            this->removeChild(chooseTowerpanle);
            chooseTowerpanle = NULL;			
		}
		else if( type == TowerType::MULTIDIR_TOWER )
        {
			if( money >= 300 )
			{
				MultiDirTower* tower = MultiDirTower::create();
				tower->setPosition(towerPos);
				tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
				this->addChild(tower);
				instance->towerVector.pushBack(tower);          
				towerMatrix[MatrixIndex] =  tower;
				money -= 300;
			}else{
				noMoneyTips = true;
			}
			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            this->removeChild(chooseTowerpanle);
            chooseTowerpanle = NULL;	
		}

		auto moneyText = to_string(money);
        moneyLabel->setString(moneyText);

		if( noMoneyTips == true )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
			auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
			tips->setPosition(towerPos);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.5f),
											CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), 
											NULL));
		}
	}
    CollisionDetection();
    enemyIntoHouse();
    if(isSuccessful)
	{
		//scheduleOnce(schedule_selector(XX::startGame), 0.3);
		auto star = 0;
		auto playHp = this->getPlayHpPercentage();

		if( playHp > 0 && playHp <= 30){ star = 1;}
		else if(playHp > 30 && playHp <= 60 ){ star = 2;}
		else if(playHp > 60 && playHp <= 100 ){ star = 3;}

		if( star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str()))
		{
			UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
			auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum") + 1;
			UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum);
		}

		auto nextlevel = instance->getNextLevelFile();
		log("nextlevel: %s" ,nextlevel.c_str());
		UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);

		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SuccessfulScene::create()));
		instance->clear();
        this->unscheduleUpdate();
	}
}


