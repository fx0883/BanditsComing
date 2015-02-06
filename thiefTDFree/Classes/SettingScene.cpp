//
//  SettingScene.cpp
//  thiefTD
//
//  Created by 冯璇 on 15/2/4.
//
//
//#include "CCPlatformConfig.h"
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "SettingScene.h"
#include "ui/CocosGUI.h"
#include "SettingScene.h"
//#include "/workCode/BanditsComing/thiefTDFree/cocos2d/cocos/ui/UISlider.h"
#include "SimpleAudioEngine.h"
#include "extensions/GUI/CCControlExtension/CCControlSlider.h"
#include "VisibleRect.h"
using namespace cocos2d;
using namespace cocos2d::ui;
//using namespace cocos2d::experimental;

class AudioSlider : public Node
{
public:
    enum Direction {
        Vertical,
        Horizontal
    };
    
    static AudioSlider *create(Direction direction)
    {
        auto ret = new AudioSlider(direction);
        if (ret && !ret->init()) {
            delete ret;
            ret = NULL;
        }
        return ret;
    }
    
    float getValue() const
    {
        return _slider->getValue();
    }
    
    void setValue(float minValue, float maxValue, float value)
    {
        _slider->setMinimumValue(minValue);
        _slider->setMaximumValue(maxValue);
        _slider->setValue(value);
        
        char buffer[32];
        
        sprintf(buffer, "%.2f", minValue);
        if (!_lblMinValue) {
            _lblMinValue = LabelTTF::create(buffer, "Arial", 8);
            addChild(_lblMinValue);
            if (_direction == Vertical)
                _lblMinValue->setPosition(Point(12.0, -50.0));
            else
                _lblMinValue->setPosition(Point(-50, 12.0));
        } else {
            _lblMinValue->setString(buffer);
        }
        
        sprintf(buffer, "%.2f", maxValue);
        if (!_lblMaxValue) {
            _lblMaxValue = LabelTTF::create(buffer, "Arial", 8);
            addChild(_lblMaxValue);
            if (_direction == Vertical)
                _lblMaxValue->setPosition(Point(12.0, 50.0));
            else
                _lblMaxValue->setPosition(Point(50, 12.0));
        } else {
            _lblMaxValue->setString(buffer);
        }
    }
    
private:
    AudioSlider(Direction direction)
    : _direction(direction)
    , _slider(NULL)
    , _lblMinValue(NULL)
    , _lblMaxValue(NULL)
    {
    }
    
    bool init()
    {
        _slider = extension::ControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
        _slider->setScale(0.5);
        if (_direction == Vertical)
            _slider->setRotation(-90.0);
        addChild(_slider);
        return true;
    }
    
    Direction _direction;
    extension::ControlSlider *_slider;
    LabelTTF *_lblMinValue;
    LabelTTF *_lblMaxValue;
};


void SettingScene::addChildAt(Node *node, float percentageX, float percentageY)
{
    const Size size = VisibleRect::getVisibleRect().size;
    node->setPosition(Point(percentageX * size.width, percentageY * size.height));
    addChild(node);
}

void SettingScene::addSliders()
{
    auto lblPitch = LabelTTF::create("Music", "Arial", 14);
    addChildAt(lblPitch, 0.67f, 0.4f);
    _sliderMusic = AudioSlider::create(AudioSlider::Horizontal);
    _sliderMusic->setValue(0, 1, 0.5);
    addChildAt(_sliderMusic, 0.85f, 0.4f);
    
    auto lblPan = LabelTTF::create("Effect", "Arial", 14);
    addChildAt(lblPan, 0.67f, 0.3f);
    _sliderEffect = AudioSlider::create(AudioSlider::Horizontal);
    _sliderEffect->setValue(0, 1, 0.5);
    addChildAt(_sliderEffect, 0.85f, 0.3f);
}

SettingScene::SettingScene()
:_sliderMusic(NULL),
_sliderEffect(NULL)
{
    
}

Scene* SettingScene::createScene()
{
    Scene *scene = Scene::create();
    SettingScene *layer = SettingScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool SettingScene::init()
{
    
    addSliders();
    return true;
}

void SettingScene::update(float dt)
{

}
SettingScene::~SettingScene()
{
    
}
