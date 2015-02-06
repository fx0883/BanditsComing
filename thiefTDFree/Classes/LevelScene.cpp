//
//  LevelScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "LevelScene.h"
#include "LevelLayer.h"
#include "LevelSelectLayer1.h"  
#include "LevelSelectLayer2.h"
#include "LevelSelectLayer3.h"
#include "UIScene.h"
#include "SettingLayer.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 

static LevelLayer *levelLayer;  
static LevelScene *sc;  
  
LevelScene *LevelScene::sharedSC(){  
    if(sc != NULL){  
        return sc;  
    }  
    return  NULL;  
}  

LevelScene::LevelScene()  
{    
}  

bool LevelScene::init()  
{  
	sc = this;  
	
    bool bRet = false;  
	 
    do {  
		CC_BREAK_IF(!CCScene::init());  
		levelLayer = LevelLayer::create();  
		
        for (int i=0; i<5; ++i) {  
            if (0==i) {  
                LevelSelectLayer1 *layer = LevelSelectLayer1::create();  
                layer->setTag(i);  
                levelLayer->addPage(layer);  
            }else if(1==i){  
                LevelSelectLayer2 *layer = LevelSelectLayer2::create();  
                layer->setTag(i);  
                levelLayer->addPage(layer);  
            }else if(2==i){  
                LevelSelectLayer3 *layer = LevelSelectLayer3::create();  
                layer->setTag(i);  
                levelLayer->addPage(layer);  
            }else if(3==i){  
                LevelSelectLayer2 *layer = LevelSelectLayer2::create();   
                layer->setTag(i);  
                levelLayer->addPage(layer);  
            }else if(4==i){  
                LevelSelectLayer3 *layer = LevelSelectLayer3::create();    
                layer->setTag(i);  
                levelLayer->addPage(layer);  
            }  
              
        }  
          
        Size size = CCDirector::getInstance()->getWinSize();    
        Sprite* spritebg =Sprite::create("selectBg.png"); 
        spritebg->setPosition(Point(size.width / 2,size.height / 2));  
        addChild(spritebg);  

        
        auto closeItem = MenuItemImage::create(  
                                           "btn_back.png",  
                                           "btn_back_press.png",  
                                           CC_CALLBACK_1(LevelScene::menuCloseCallback, this));  
		closeItem->setPosition(Point(40, 40));  
          
        auto menu = Menu::create(closeItem, NULL);  
        menu->setPosition(Point::ZERO);  
        this->addChild(menu, 1);  
          
        this->addChild(levelLayer);
		
		auto selectHouse =Sprite::create("selectHouse.png");  
        selectHouse->setPosition(Point(size.width / 5 * 4, size.height / 5));  
        addChild(selectHouse);  

		auto width = Sprite::create("page_mark2.png")->getContentSize().width;
		auto posX = (size.width - width * 5) / 2;
		for(int i =0; i < 5; i++)
		{
			Sprite* sprite =Sprite::create("page_mark2.png");  
			sprite->setPosition(Point(posX + i * width, size.height / 7));  
			addChild(sprite);  
		}
          
        Sprite* spriteMark =Sprite::create("page_mark1.png");  
        spriteMark->setPosition(Point(posX, size.height / 7));  
        spriteMark->setTag(888);  
        addChild(spriteMark);  

		ParticleSystem* m_emitter1 = ParticleSystemQuad::create("snow.plist");
		m_emitter1->retain();
		ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
		batch->addChild(m_emitter1);
		m_emitter1->setPosition(Point(size.width/2, size.height));
		addChild(batch, 10);
		m_emitter1->release();

        bRet = true;
        
        
        
        
        //加入 setting 按钮
        Sprite *settingItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
        Sprite *settingItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
        MenuItemSprite *pSettingItem = MenuItemSprite::create(settingItem1, settingItem2, CC_CALLBACK_1(LevelScene::menuSettingCallback, this));
        pSettingItem->setPosition(Point(40, 80));
        pSettingItem->setAnchorPoint(Point(0, 0.5f));
        Menu* pMenu = Menu::create(pSettingItem, NULL);
        pMenu->setPosition(Point::ZERO);
        addChild(pMenu);
        
    } while (0);  
      
    return bRet;  
}

void LevelScene::menuSettingCallback(Ref* pSender)
{
    SettingLayer* popup = SettingLayer::create("600popup.png");
    // ContentSize是可选的设置，可以不设置，如果设置则把它当做9图缩放
    popup->setContentSize(CCSizeMake(300, 180));
//    popup->setTitle("Message");
//    popup->setContentText("Most people... blunder round this city.", 20, 50, 150);
    // 设置回调函数，回调传回一个CCNode以获取tag判断点击的按钮
    // 这只是作为一种封装实现，如果使用delegate那就能够更灵活的控制参数了
    //    popup->setCallBackFunc(this, callfuncN_selector(PlayLayer::menuSettingCallback));
    //添加按钮，设置图片、文字，tag信息
    popup->addButton("btnBack.png", "btnBack.png", "", 0);
//    popup->addButton("start_1.png", "start_1.png", "Cancel", 1);
    this->addChild(popup,1000);
}


  
void LevelScene::menuCloseCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    CCDirector::getInstance()->replaceScene(CCTransitionFade::create(0.5, UIScene::createScene()));  
}