//
//  UIScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "UIScene.h"
#include "LevelScene.h"

#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 

USING_NS_CC;

Scene* UIScene::createScene()
{
    auto scene = Scene::create();
    auto layer = UIScene::create();

    scene->addChild(layer);
    return scene;
}

bool UIScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size size = CCDirector::getInstance()->getWinSize();  

    Sprite* sprite =Sprite::create("main.jpg");  
    sprite->setPosition(Point(size.width / 2,size.height / 2));  
    addChild(sprite, -1);

	auto titleSprite = Sprite::create("title.png");
	titleSprite->setPosition(Point(size.width / 4,size.height / 6 * 5));  
	this->addChild(titleSprite);
	auto move = MoveBy::create(1.4f, Point(0, 10));
	titleSprite->runAction(RepeatForever::create(Sequence::create( move, move->reverse(), NULL)));

	//CCMenuItemSprite *pPauseItem = MenuItemSprite::create( CCSprite::createWithSpriteFrame(""), pPauseItem2, this,....

    auto closeItem = MenuItemImage::create(  
                                           "start_1.png",  
                                           "start_2.png",  
                                           CC_CALLBACK_1(UIScene::menuCloseCallback, this));  
    closeItem->setPosition(Point((size.width -  closeItem->getContentSize().width)/ 2, size.height / 6));  
	closeItem->setAnchorPoint(Point(0, 0));
    auto menu = Menu::create(closeItem, NULL);  
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1); 
	
	auto starSprite = Sprite::create("star1.png");
	starSprite->setScale(0.8f);
	this->addChild(starSprite, 11);

	auto _emitter = ParticleSystemQuad::create("button.plist");
    _emitter->retain();
    ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(_emitter->getTexture());
    batch->addChild(_emitter);
	starSprite->setPosition(Point(closeItem->getPosition().x + closeItem->getContentSize().height / 2 , closeItem->getPosition().y));	
	
	_emitter->setPosition(Point(closeItem->getPosition().x + closeItem->getContentSize().height / 2 , closeItem->getPosition().y ));
	float X = closeItem->getContentSize().height / 2;
	auto path = MyPathFun( X + 6, closeItem->getContentSize().height, closeItem->getContentSize().width - X * 2 /*+ starSprite->getContentSize().width*/);
	starSprite->runAction(path);
	_emitter->runAction(path->clone());
    addChild(batch, 10);
    _emitter->release();

    return true;
}

ParticleSystem* UIScene::particleInit(){
	auto _emitter = ParticleSystemQuad::createWithTotalParticles(50);
	addChild(_emitter, 10);
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("point.png"));
	_emitter->setAnchorPoint(Point(0, 0));
	// duration
	_emitter->setDuration(ParticleSystem::DURATION_INFINITY);

	// radius mode
	_emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);

	// radius mode: start and end radius in pixels
	_emitter->setStartRadius(4);
	_emitter->setStartRadiusVar(1);
	_emitter->setEndRadius(ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS);
	_emitter->setEndRadiusVar(0);

	// radius mode: degrees per second
	_emitter->setRotatePerSecond(100);
	_emitter->setRotatePerSecondVar(0);

	// angle
	_emitter->setAngle(90);
	_emitter->setAngleVar(0);

	// emitter position
	auto size = Director::getInstance()->getWinSize();
	_emitter->setPosVar(Point::ZERO);

	// life of particles
	_emitter->setLife(0.5);
	_emitter->setLifeVar(0);

	// spin of particles
	_emitter->setStartSpin(0);
	_emitter->setStartSpinVar(0);
	_emitter->setEndSpin(0);
	_emitter->setEndSpinVar(0);

	// color of particles
	Color4F startColor(0.0f, 0.8f, 0.9f, 1.0f);
	_emitter->setStartColor(startColor);

	Color4F startColorVar(0, 0, 0, 1.0f);
	_emitter->setStartColorVar(startColorVar);

	Color4F endColor(1.0f, 1.0f, 1.0f, 0.1f);
	_emitter->setEndColor(endColor);

	Color4F endColorVar(0, 0, 0, 0.1f);
	_emitter->setEndColorVar(endColorVar);
    
	// size, in pixels
	_emitter->setStartSize(10);
	_emitter->setStartSizeVar(1);
	_emitter->setEndSize(0);

	// emits per second
	_emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());

	// additive
	_emitter->setBlendAdditive(false);

	return _emitter;
}

RepeatForever* UIScene::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(-controlX, 0);
	bezier1.controlPoint_2 = Point(-controlX, controlY);
	bezier1.endPosition = Point(0, controlY);
	auto bezierBy1 = BezierBy::create(0.6f, bezier1);

	auto move1 = MoveBy::create(0.7f, Point(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	auto bezierBy2 = BezierBy::create(0.6f, bezier2);
	auto move2 = MoveBy::create(0.7f, Point(-w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}

void UIScene::menuCloseCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
}