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

  
// �������  
const int TOUCH_DELTA = 20;  
  
class LevelLayer: public Layer  
{  
private:  
    // ���µ�  
    Point m_TouchDownPoint;  
    // ̧��� ���ʹ���ж��Ƿ�Ϊ����¼�  
    Point m_TouchUpPoint;  
    // ��ǰ������  
    Point m_TouchCurPoint;  
      
private:  
    // ��ҳ��  
    int m_Page;  
    // ��ǰ��ʾҳ  
    int m_CurPage;  
    float WINDOW_WIDTH;  
	float WINDOW_HEIGHT; 
private:  
    // �洢����ҳ��  
    __Array *m_PageLayer;  
      
private:  
    // ��תҳ  
    void goToPage();  
      
public:  
    LevelLayer();  
    ~LevelLayer();  
      
    virtual bool init();  
	static cocos2d::Scene* createScene();
    CREATE_FUNC(LevelLayer);  
  
public:  

	void menuCloseCallback(Ref* pSender); 
    // �����¼����  
    bool onTouchBegan(Touch *pTouch, Event  *pEvent);  
    void onTouchMoved(Touch *pTouch, Event  *pEvent);  
    void onTouchEnded(Touch *pTouch, Event  *pEvent);  
      
public:  
    // ���ҳ  
    void addPage(Layer *pPageLayer);  
  
};  
  
#endif /* defined(__thiefTD__LevelLayer__) */
