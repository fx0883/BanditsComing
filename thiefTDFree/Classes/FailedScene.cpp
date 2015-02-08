//
//  FailedScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "FailedScene.h"
#include "LevelScene.h"
USING_NS_CC;
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion; 

FailedScene::FailedScene()  
{  
}  

bool FailedScene::init()  
{  
	if ( !Scene::init() )
    {
        return false;
    }
    Size size = CCDirector::getInstance()->getWinSize();  
     
    Sprite* spriteBg =Sprite::create("failedBg.jpg");  
    spriteBg->setPosition(Point( size.width / 2,size.height / 2));  
    addChild(spriteBg, -1);

	auto sprite = Sprite::create("failedPanel.png");
    sprite->setPosition(Point(-size.width/2 , size.height / 2 ));
    this->addChild(sprite, -1);

    auto closeItem = MenuItemImage::create(  
                                           "btnBack.png",  
                                           "btnBack.png",  
                                           CC_CALLBACK_1(FailedScene::menuCloseCallback, this));  
    closeItem->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height / 6));  

    auto menu = Menu::create(closeItem, NULL);  
    menu->setPosition(Point::ZERO);  
    sprite->addChild(menu);  

    sprite->runAction(CCSequence::create(DelayTime::create( 0.5f ),
										EaseElasticOut::create(MoveBy::create(0.8f, Point( size.width, 0)), 0.5f),
										NULL) 
					);

//	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("changjing.plist");
//	m_emitter1->retain();
//	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
//	batch->addChild(m_emitter1);
//	m_emitter1->setPosition(Point(size.width/2, 0));
//	addChild(batch, 10);
//	m_emitter1->release();

    return true;  
}  
  
void FailedScene::menuCloseCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
     this->removeAllChildren();
    CCDirector::getInstance()->replaceScene(TransitionFade::create(0.5, LevelScene::create()));  
}

FailedScene::~FailedScene()
{
    //this->unscheduleAllSelectors();
   
}