//
//  SuccessfulScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "SuccessfulScene.h"
#include "LevelInfoScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"  

USING_NS_CC;
using namespace CocosDenshion; 

SuccessfulScene::SuccessfulScene()  
{  
}  

bool SuccessfulScene::init()  
{  
	if ( !Scene::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("successfulBg.jpg");
    sprite->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(sprite, -1);


	auto nextItem = MenuItemImage::create(
                                           "btnNext.png",  
                                           "btnNext.png",  
                                           CC_CALLBACK_1(SuccessfulScene::menuNextCallback, this));     

	auto backItem = MenuItemImage::create(
                                           "btnBack.png",  
                                           "btnBack.png",  
                                           CC_CALLBACK_1(SuccessfulScene::menuCloseCallback, this));  

    auto menu = Menu::create(nextItem, backItem, NULL);  
	menu->alignItemsHorizontally();

    menu->setPosition(Point(size.width / 2,size.height / 6));  
    this->addChild(menu);  

    return true;  
}  

void SuccessfulScene::menuNextCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5, LevelInfoScene::createScene()));  
}

void SuccessfulScene::menuCloseCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, LevelScene::create()));
}