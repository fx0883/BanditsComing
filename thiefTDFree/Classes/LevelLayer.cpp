//
//  LevelScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "LevelScene.h"
#include "LevelLayer.h"
USING_NS_CC;

LevelLayer::LevelLayer()  
{  
    m_Page = 0;  
    m_CurPage = 0;  
    m_PageLayer = CCArray::createWithCapacity(5);  
    m_PageLayer->retain();  
      
    init();  
}  
LevelLayer::~LevelLayer()  
{  
    m_PageLayer->removeAllObjects();  
    m_PageLayer->release();  
}  
  
bool LevelLayer::init()  
{  
    bool bRet = false;  
      
    do {  
        CC_BREAK_IF(!CCLayer::init());  
          
        bRet = true;  
    } while (0);  
      
    setTouchEnabled(true);  
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE); 
      
    auto myListener = EventListenerTouchOneByOne::create();  
    myListener->onTouchBegan = CC_CALLBACK_2(LevelLayer::onTouchBegan, this);  
    myListener->onTouchMoved = CC_CALLBACK_2(LevelLayer::onTouchMoved, this);  
    myListener->onTouchEnded = CC_CALLBACK_2(LevelLayer::onTouchEnded, this);  
   // _eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);   
	WINDOW_WIDTH = Director::getInstance()->getWinSize().width;  
	WINDOW_HEIGHT = Director::getInstance()->getWinSize().height;
  
    return bRet;  
}  
  
void LevelLayer::goToPage()  
{  
    MoveTo *moveTo = MoveTo::create(0.4f, Point(-m_CurPage * WINDOW_WIDTH, 0));
      
    this->runAction(moveTo);  
}  
  
void LevelLayer::addPage(cocos2d::Layer *pPageLayer)  
{  
    if (pPageLayer) {  
        pPageLayer->setContentSize(Size(WINDOW_WIDTH, WINDOW_HEIGHT));  
        pPageLayer->setPosition(Point(WINDOW_WIDTH * m_Page, 0));  
        this->addChild(pPageLayer);
        m_PageLayer->addObject(pPageLayer);  
        m_Page = m_PageLayer->count();  
    }  
}  

bool LevelLayer::onTouchBegan(Touch *pTouch, Event  *pEvent)
{  
    m_TouchDownPoint = CCDirector::getInstance()->convertToGL(pTouch->getLocationInView());  
    m_TouchCurPoint = m_TouchDownPoint;  
      
    return true;  
}  
void LevelLayer::onTouchMoved(Touch *pTouch, Event  *pEvent){   
    Point touchPoint = CCDirector::getInstance()->convertToGL(pTouch->getLocationInView());  
    Point posPoint = Point(getPositionX() + touchPoint.x - m_TouchCurPoint.x, getPositionY());  
    setPosition(posPoint);  
    m_TouchCurPoint = touchPoint;  
}  
void LevelLayer::onTouchEnded(Touch *pTouch, Event  *pEvent){  
    m_TouchUpPoint = CCDirector::getInstance()->convertToGL(pTouch->getLocationInView());  
    // 计算按下和抬起的偏移量  
    float offset = (m_TouchUpPoint.x - m_TouchDownPoint.x) * (m_TouchUpPoint.x - m_TouchDownPoint.x) + (m_TouchUpPoint.y - m_TouchDownPoint.y) * (m_TouchUpPoint.y - m_TouchDownPoint.y);  
    Sprite* sprite1 =Sprite::create("page_mark1.png");  
	auto width = sprite1->getContentSize().width;  
    if (offset < (TOUCH_DELTA * TOUCH_DELTA)) {  
    }  
    else {  
        // 滑动结束  
        int offset = getPositionX() - m_CurPage * (-WINDOW_WIDTH);  
        if (offset > width) {  
            // 上一页  
            if (m_CurPage > 0) {  
                --m_CurPage;  
                Sprite *sprite =  (Sprite *)LevelScene::sharedSC()->getChildByTag(888);  
                sprite->setPosition(Point(sprite->getPositionX()-width,sprite->getPositionY()));  
            }  
        }  
        else if (offset < -width) {  
            // 下一页  
            if (m_CurPage < (m_Page - 1)) {  
                ++m_CurPage;  
                Sprite *sprite =  (Sprite *)LevelScene::sharedSC()->getChildByTag(888);  
                sprite->setPosition(Point(sprite->getPositionX()+width,sprite->getPositionY()));  
            }
        }
        goToPage();  
	}
}
