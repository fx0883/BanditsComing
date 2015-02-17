#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "C2DXShareSDK.h"
using namespace cn::sharesdk;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android codes
#endif



/**
 @brief    The cocos2d Application.
 
 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class  AppDelegate : private cocos2d::Application
{
private:
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //初始化平台配置
    void initPlatformConfig();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android codes
#endif

    
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    /**
     @brief    Implement Director and Scene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();
    
    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground();
    
    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

