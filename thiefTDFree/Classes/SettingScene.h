//
//  SettingScene.h
//  thiefTD
//
//  Created by 冯璇 on 15/2/4.
//
//

#ifndef __thiefTD__SettingScene__
#define __thiefTD__SettingScene__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class AudioSlider;
class SettingScene : public Layer
{
public:
    
    SettingScene();
    CREATE_FUNC(SettingScene);
    static Scene * createScene();
    bool init();
    virtual void update(float dt);
    ~SettingScene();
    void addChildAt(Node *node, float percentageX, float percentageY);
    void addSliders();
private:
    AudioSlider *_sliderMusic;
    AudioSlider *_sliderEffect;
};
#endif /* defined(__thiefTD__SettingScene__) */