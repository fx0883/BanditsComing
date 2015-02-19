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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "C2DXShareSDK.h"
using namespace cn::sharesdk;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android codes
#endif




#include "GameManager.h"

#include "FSUtil.h"
using namespace CocosDenshion; 

static LevelLayer *levelLayer;  
static LevelScene *sc;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error);

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android codes
#endif



  
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
        Sprite *settingItem1 = CCSprite::create("settings.png");
        Sprite *settingItem2 = CCSprite::create("settings.png");
        MenuItemSprite *pSettingItem = MenuItemSprite::create(settingItem1, settingItem2, CC_CALLBACK_1(LevelScene::menuSettingCallback, this));
        pSettingItem->setPosition(Point(40, 90));
        pSettingItem->setAnchorPoint(Point(0.5, 0.5f));
        Menu* pMenu = Menu::create(pSettingItem, NULL);
        pMenu->setPosition(Point::ZERO);
        addChild(pMenu);
        
        
        
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //加入 分享 按钮
        Sprite *shareSdkItem1 = CCSprite::create("shared.png");
        Sprite *shareSdkItem2 = CCSprite::create("shared.png");
        MenuItemSprite *pShareSDKItem = MenuItemSprite::create(shareSdkItem1, shareSdkItem2, CC_CALLBACK_1(LevelScene::menuShareSDKCallback, this));
        pShareSDKItem->setPosition(Point(40, 140));
        pShareSDKItem->setAnchorPoint(Point(0.5, 0.5f));
        Menu* pMenuShareSdk = Menu::create(pShareSDKItem, NULL);
        pMenuShareSdk->setPosition(Point::ZERO);
        addChild(pMenuShareSdk);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        //Android codes
#endif
        

        
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



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void LevelScene::menuShareSDKCallback(Ref* pSender)
    {
        shareMenuItemClick(NULL);
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
        CCLog("11111用户已授权");
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

std::string LevelScene::getShareImagePath()
{
    
    
    std::vector<std::string> listImagePath;
    listImagePath.push_back("http://a.hiphotos.baidu.com/image/h%3D360/sign=984de4228418367ab28979db1e738b68/0b46f21fbe096b63de38775b0e338744ebf8ac93.jpg");
    listImagePath.push_back("http://d.hiphotos.baidu.com/image/h%3D360/sign=6dc6980d8494a4c21523e12d3ef41bac/a8773912b31bb0514357ca2a357adab44aede045.jpg");
    listImagePath.push_back("http://e.hiphotos.baidu.com/image/h%3D360/sign=7d7b0123223fb80e13d167d106d02ffb/4034970a304e251fe958e9eaa486c9177f3e5370.jpg");

        listImagePath.push_back("http://g.hiphotos.baidu.com/image/h%3D200/sign=cb073b61f1deb48fe469a6dec01e3aef/c9fcc3cec3fdfc03a4b842b8d63f8794a5c226e9.jpg");
        listImagePath.push_back("http://image.s1979.com/allimg/131228/25-13122Q54631.jpg");

        listImagePath.push_back("http://a.hiphotos.baidu.com/image/pic/item/9d82d158ccbf6c814884f9b9be3eb13533fa4034.jpg");
    
        listImagePath.push_back("http://e.hiphotos.baidu.com/image/pic/item/b999a9014c086e06e1652a6f01087bf40bd1cbc1.jpg");
        listImagePath.push_back("http://a.hiphotos.baidu.com/image/pic/item/1b4c510fd9f9d72a80f8481ad62a2834349bbb1d.jpg");
//        listImagePath.push_back("http://img0.imgtn.bdimg.com/it/u=3959729808,1330752766&fm=23&gp=0.jpg");
//        listImagePath.push_back("http://img2.imgtn.bdimg.com/it/u=1488062681,3317039875&fm=21&gp=0.jpg");
    
    int count = (int)listImagePath.size();
    srand((int)time(0));

    int j=rand()%count;
    if (j>=count) {
        j--;
    }
    
    
    
    
    std::string imagePath = listImagePath.at(j);
    return imagePath;
}


void LevelScene::shareMenuItemClick(CCObject* pSender)
{
    CCDictionary *content = CCDictionary::create();
    
//    std::string searchPath=    CCFileUtils::getInstance()->getSearchPaths()[0];
    std::string imagePath = this->getShareImagePath();
    
    content -> setObject(CCString::create(FSLocalizedStdStringByKey("ShareContent")), "content");
    content -> setObject(CCString::create(imagePath), "image");
    content -> setObject(CCString::create(FSLocalizedNSStringByKey("ShareTitle")), "title");
    content -> setObject(CCString::create(FSLocalizedNSStringByKey("ShareDescription")), "description");
    content -> setObject(CCString::create(SHARESDKREDIRECT_URI), "url");
//    content -> setObject(CCString::create(FSLocalizedNSStringByKey("ShareTitle")), "site");
    
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create(SHARESDKREDIRECT_URI), "siteUrl");
//    content -> setObject(CCString::create("ShareSDK"), "site");
//    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
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

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android codes
#endif
