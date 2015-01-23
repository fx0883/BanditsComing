//
//  LoadingBase.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#ifndef __thiefTD__LoadingBase__
#define __thiefTD__LoadingBase__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class LoadingBase : public Layer
{
                                                                                          
public:
    LoadingBase();
    ~LoadingBase();

    virtual bool init();              
                                                                                              
    //生成背景和logo等
    virtual void addBackGround(){};
                                                                                          
    //添加一个progress
    virtual ProgressTimer * addProgress(){return NULL;};
                                                                                          
    //将需要加载的资源放在这个函数中，倍update调用.别忘了切换场景啊
    virtual void loadResources();
                                                                                          
    //启动加载资源
    void update(float dt);
                                                                                          
    //加载资源快捷方法
    void loadingPVR(const char * plist);
    //加载资源快捷方法2
    void loadingPVRs(const char * plist,...);
                                                                                          
public:
    //进度条
    ProgressTimer * _pross;
};
#endif /* defined(__thiefTD__ThiefBase__) */
