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
//USING_NS_CC;
#include "SimpleAudioEngine.h"
#include "C2DXShareSDK.h"
using namespace CocosDenshion; 
using namespace cn::sharesdk;
static LevelLayer *levelLayer;  
static LevelScene *sc;


void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error);

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error);

  
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
        pSettingItem->setAnchorPoint(Point(0.5, 0.5f));
        Menu* pMenu = Menu::create(pSettingItem, NULL);
        pMenu->setPosition(Point::ZERO);
        addChild(pMenu);
        
        
        //加入 分享 按钮
        Sprite *shareSdkItem1 = CCSprite::createWithSpriteFrameName("playbutton1.png");
        Sprite *shareSdkItem2 = CCSprite::createWithSpriteFrameName("playbutton2.png");
        MenuItemSprite *pShareSDKItem = MenuItemSprite::create(shareSdkItem1, shareSdkItem2, CC_CALLBACK_1(LevelScene::menuShareSDKCallback, this));
        pShareSDKItem->setPosition(Point(40, 120));
        pShareSDKItem->setAnchorPoint(Point(0.5, 0.5f));
        Menu* pMenuShareSdk = Menu::create(pShareSDKItem, NULL);
        pMenuShareSdk->setPosition(Point::ZERO);
        addChild(pMenuShareSdk);
        
        
    } while (0);  
      
    return bRet;  
}


void LevelScene::menuShareSDKCallback(Ref* pSender)
{
    shareMenuItemClick(NULL);
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



//sharesdk

void LevelScene::authMenuItemClick(CCObject* pSender)
{
    //    C2DXShareSDK::authorize(C2DXPlatTypeFacebook, authResultHandler);
}

void LevelScene::cancelAuthMenuItemClick(CCObject* pSender)
{
    //    C2DXShareSDK::cancelAuthorize(C2DXPlatTypeSinaWeibo);
}

void LevelScene::hasAuthMenuItemClick(CCObject* pSender)
{
    if (C2DXShareSDK::hasAutorized(C2DXPlatTypeSinaWeibo))
    {
        CCLog("用户已授权");
    }
    else
    {
        CCLog("用户尚未授权");
    }
}

void LevelScene::getUserInfoMenuItemClick(CCObject* pSender)
{
    C2DXShareSDK::getUserInfo(C2DXPlatTypeSinaWeibo, getUserResultHandler);
}

void LevelScene::shareMenuItemClick(CCObject* pSender)
{
    CCDictionary *content = CCDictionary::create();
    content -> setObject(CCString::create("这是一条测试内容"), "content");
    content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
    content -> setObject(CCString::create("测试标题"), "title");
    content -> setObject(CCString::create("测试描述"), "description");
    content -> setObject(CCString::create("http://sharesdk.cn"), "url");
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(CCString::create("ShareSDK"), "site");
    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(CCString::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
    //    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error)
{
    if (state == C2DXResponseStateSuccess)
    {
        //输出用户信息
        try
        {
            CCArray *allKeys = userInfo -> allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys -> count(); i++)
            {
                CCString *key = (CCString *)allKeys -> objectAtIndex(i);
                CCObject *obj = userInfo -> objectForKey(key -> getCString());
                
                CCLog("key = %s", key -> getCString());
                if (dynamic_cast<CCString *>(obj))
                {
                    CCLog("value = %s", dynamic_cast<CCString *>(obj) -> getCString());
                }
                else if (dynamic_cast<CCInteger *>(obj))
                {
                    CCLog("value = %d", dynamic_cast<CCInteger *>(obj) -> getValue());
                }
                else if (dynamic_cast<CCDouble *>(obj))
                {
                    CCLog("value = %f", dynamic_cast<CCDouble *>(obj) -> getValue());
                }
            }
            allKeys->release();
        }
        catch(...)
        {
            CCLog("==============error");
        }
        
    }
}

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            break;
        default:
            break;
    }
}
