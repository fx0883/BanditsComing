//
//  LevelScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__LevelLayer__
#define __thiefTD__LevelLayer__

#include <iostream>
#include "cocos2d.h"  
  
USING_NS_CC; 

  
// 触摸误差  
const int TOUCH_DELTA = 20;  
  
class LevelLayer: public Layer  
{  
private:  
    // 按下点  
    Point m_TouchDownPoint;  
    // 抬起点 配合使用判断是否为点击事件  
    Point m_TouchUpPoint;  
    // 当前触摸点  
    Point m_TouchCurPoint;  
      
private:  
    // 总页数  
    int m_Page;  
    // 当前显示页  
    int m_CurPage;  
    float WINDOW_WIDTH;  
	float WINDOW_HEIGHT; 
private:  
    // 存储所有页层  
    __Array *m_PageLayer;  
      
private:  
    // 跳转页  
    void goToPage();  
      
public:  
    LevelLayer();  
    ~LevelLayer();  
      
    virtual bool init();  
	static cocos2d::Scene* createScene();
    CREATE_FUNC(LevelLayer);  
  
public:  

	void menuCloseCallback(Ref* pSender); 
    // 触摸事件相关  
    bool onTouchBegan(Touch *pTouch, Event  *pEvent);  
    void onTouchMoved(Touch *pTouch, Event  *pEvent);  
    void onTouchEnded(Touch *pTouch, Event  *pEvent);  
      
public:  
    // 添加页  
    void addPage(Layer *pPageLayer);  
  
};  
  
#endif /* defined(__thiefTD__LevelLayer__) */
