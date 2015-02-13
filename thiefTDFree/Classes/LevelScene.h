//
//  LevelScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__LevelScene__
#define __thiefTD__LevelScene__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class LevelScene : public cocos2d::Scene
{
public:  
    LevelScene();  
    virtual bool init();  
    CREATE_FUNC(LevelScene);  
      
    void menuCloseCallback(Ref* pSender);  
      
    static LevelScene *sharedSC();  

    void menuSettingCallback(Ref* pSender);
    
    void menuShareSDKCallback(Ref* pSender);
    
    
    //shareSdk
    void authMenuItemClick(CCObject* pSender);
    
    void cancelAuthMenuItemClick(CCObject* pSender);
    
    void hasAuthMenuItemClick(CCObject* pSender);
    
    void getUserInfoMenuItemClick(CCObject* pSender);
    
    void shareMenuItemClick(CCObject* pSender);
private:

}; 
#endif /* defined(__thiefTD__LevelScene__) */
