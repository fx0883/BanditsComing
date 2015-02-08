//
//  PopupLayer.cpp
//  thiefTD
//
//  Created by 冯璇 on 15/2/5.
//
//

#include "SettingLayer.h"
#include "ui/CocosGUI.h"
//#include "/workCode/BanditsComing/thiefTDFree/cocos2d/cocos/ui/UISlider.h"
#include "SimpleAudioEngine.h"
#include "extensions/GUI/CCControlExtension/CCControlSlider.h"
#include "VisibleRect.h"
#include "GameManager.h"
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
        
//        char buffer[32];
//        
//        sprintf(buffer, "%.2f", minValue);
//        if (!_lblMinValue) {
//            _lblMinValue = LabelTTF::create(buffer, "Arial", 8);
//            addChild(_lblMinValue);
//            if (_direction == Vertical)
//                _lblMinValue->setPosition(Point(12.0, -50.0));
//            else
//                _lblMinValue->setPosition(Point(-50, 12.0));
//        } else {
//            _lblMinValue->setString(buffer);
//        }
//        
//        sprintf(buffer, "%.2f", maxValue);
//        if (!_lblMaxValue) {
//            _lblMaxValue = LabelTTF::create(buffer, "Arial", 8);
//            addChild(_lblMaxValue);
//            if (_direction == Vertical)
//                _lblMaxValue->setPosition(Point(12.0, 50.0));
//            else
//                _lblMaxValue->setPosition(Point(50, 12.0));
//        } else {
//            _lblMaxValue->setString(buffer);
//        }
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
        _slider->setScale(2);
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




// 构造函数中变量设初值
SettingLayer::SettingLayer()
{
    m_contentPadding = 0;
    m_contentPaddingTop = 0;
    m_pMenu = NULL;
    m_callbackListener = NULL;
    m_callback = NULL;
    m_sfBackGround = NULL;
    m_s9BackGround = NULL;
    m_ltContentText = NULL;
    m_ltTitle = NULL;
}

//释放
SettingLayer::~SettingLayer()
{
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE(m_sfBackGround);
    CC_SAFE_RELEASE(m_s9BackGround);
    CC_SAFE_RELEASE(m_ltContentText);
    CC_SAFE_RELEASE(m_ltTitle);
}

//初始化
bool SettingLayer::init()
{
    if ( !CCLayer::init() ){
        return false;
    }
    
    this->setContentSize(CCSizeZero);
    //初始化需要的Menu
    CCMenu* menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    setMenuButton(menu);  //set()方法
    
    setTouchEnabled(true);  //开启触摸响应
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
//    setTouchPriority
   // _touchListener->setSwallowTouches(false);
    
    
    return true;
}

//重写触摸注册函数，重新给定触摸级别
//void PopupLayer::registerWithTouchDispatcher(){
//    // 这里的触摸优先级设置为-128，与CCMenu同级，保证了屏蔽下方的触摸
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
//}

//触摸函数ccTouchBegan，返回true
bool SettingLayer::onTouchBegan( Touch *pTouch, Event *pEvent ){
    return true;
}

//创建一个弹出层，给背景精灵变量赋值
SettingLayer* SettingLayer::create( const char* backgroundImage ){
    SettingLayer* popup = SettingLayer::create();
    popup->setSpriteBackGround(CCSprite::create(backgroundImage));
    popup->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return popup;
}

//给标题变量赋值
void SettingLayer::setTitle( const char* title, int fontsize ){
    CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "Arial", fontsize);
    ltfTitle->setColor(ccc3(0, 0, 0));
    setLabelTitle(ltfTitle);
}

//给文本变量赋值
void SettingLayer::setContentText( const char* text, int fontsize, int padding, int paddingTop ){
    CCLabelTTF* content = CCLabelTTF::create(text, "Arial", fontsize);
    content->setColor(ccc3(0, 0, 0));
    setLabelContentText(content);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}

//给下层层变量和回调函数变量赋值
void SettingLayer::setCallBackFunc( CCObject* target, SEL_CallFuncN callfun ){
    m_callbackListener = target;
    m_callback = callfun;
}

//给menu菜单变量添加Item
bool SettingLayer::addButton( const char* normalImage, const char* selectedImage, const char* title, int tag ){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(winSize.width/2, winSize.height/2);
    
    // 创建图片菜单按钮
    CCMenuItemImage* menuImage = CCMenuItemImage::create(
                                                         normalImage, selectedImage, this, menu_selector(SettingLayer::buttonCallBack));
    menuImage->setTag(tag);
    menuImage->setPosition(center);
    
    // 添加文字说明并设置位置
    CCSize menuSize = menuImage->getContentSize();
    CCLabelTTF* ttf = CCLabelTTF::create(title, "Arial", 15);
    ttf->setColor(ccc3(0, 0, 0));
    ttf->setPosition(ccp(menuSize.width/2, menuSize.height/2));
    menuImage->addChild(ttf);
    
    getMenuButton()->addChild(menuImage);
    return true;
}

//销毁弹出框，传递参数node给下层
void SettingLayer::buttonCallBack( CCObject* pSender ){
    CCNode* node = dynamic_cast<CCNode*>(pSender);
    CCLog("touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener)
    {
        //执行HelloWorld层的回调函数，传递node参数
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParentAndCleanup(true);
}

void SettingLayer::addChildAt(Node *node, float percentageX, float percentageY)
{
    const Size size = VisibleRect::getVisibleRect().size;
    node->setPosition(Point(percentageX * size.width, percentageY * size.height));
    this->addChild(node);
}

void SettingLayer::addSliders()
{
    float fMusicVolume = GameManager::getInstance()->getMusicVolume();
    float fEffectVolume = GameManager::getInstance()->getEffectVolume();
    
    if (fMusicVolume<0.0f) {
        fMusicVolume=0.5f;
    }
    if (fEffectVolume<0.0f) {
        fEffectVolume=0.5f;
    }
    
    
    
    const char *strChr=FSLocalizedNSStringByKey("Music");
    std::string strMusic(strChr);
    auto lblPitch = LabelTTF::create(strMusic, "Arial", 14);
    addChildAt(lblPitch, 0.34f, 0.6f);
    _sliderMusic = AudioSlider::create(AudioSlider::Horizontal);
    _sliderMusic->setValue(0, 1.0f, fMusicVolume);
    addChildAt(_sliderMusic, 0.55f, 0.6f);
    
    std::string strEffect(FSLocalizedNSStringByKey("Effect"));
    auto lblPan = LabelTTF::create(strEffect, "Arial", 14);
    addChildAt(lblPan, 0.34f, 0.5f);
    _sliderEffect = AudioSlider::create(AudioSlider::Horizontal);
    _sliderEffect->setValue(0, 1.0f, fEffectVolume);
    addChildAt(_sliderEffect, 0.55f, 0.5f);
}

//全部参数都设定好后，在运行时动态加载
void SettingLayer::onEnter(){
    CCLayer::onEnter();
    
   
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(winSize.width/2, winSize.height/2);
    CCSize contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(CCSizeZero)){
        getSpriteBackGround()->setPosition(center);
        this->addChild(getSpriteBackGround(),0,0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    }
    else{
        Scale9Sprite* background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(center);
        this->addChild(background, 0);
        contentSize = getContentSize();
    }
    
    //添加按钮，并根据Item的个数设置其位置
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount()+1);
    Vector<Node*>& array = getMenuButton()->getChildren();
    //CCObject* pObj = NULL;
    int i = 0;
    
    
    Vector<Node*>::iterator it;
    for(auto pObj : array){
        pObj->setPosition(ccp(winSize.width/2 - contentSize.width/2 + btnWidth*(i+1),
                                                    winSize.height/2 - contentSize.height/3));
        i++;

    }
     addSliders();
    
    
    schedule(schedule_selector(SettingLayer::updateVolumes));
    
//    CCARRAY_FOREACH(array, pObj)
//    {
//        CCNode* node = dynamic_cast<CCNode*>(pObj);
//        node->setPosition(ccp(winSize.width/2 - contentSize.width/2 + btnWidth*(i+1),
//                              winSize.height/2 - contentSize.height/3));
//        i++;
//    }
    
    // 显示对话框标题
//    if (getLabelTitle()){
//        getLabelTitle()->setPosition(ccpAdd(center, ccp(0, contentSize.height/2 - 25.0f)));
//        this->addChild(getLabelTitle());
//    }
//    
//    //显示文本内容
//    if (getLabelContentText()){
//        CCLabelTTF* ltf = getLabelContentText();
//        ltf->setPosition(center);
//        ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding*2, contentSize.height - m_contentPaddingTop));
//        ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
//        this->addChild(ltf);
//    }
    
    //弹出效果
    CCSequence *popupActions = CCSequence::create(
                                                  CCScaleTo::create(0.0, 0.0), 
                                                  CCScaleTo::create(0.06, 1.05),
                                                  CCScaleTo::create(0.08, 0.95),
                                                  CCScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupActions);
}

void SettingLayer::updateVolumes(float)
{
    const float musicVolume = _sliderMusic->getValue();
    if (fabs(musicVolume - _musicVolume) > 0.001) {
        _musicVolume = musicVolume;
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_musicVolume);
        GameManager::getInstance()->setMusicVolume(_musicVolume);
    }
    
    const float effectsVolume = _sliderEffect->getValue();
    if (fabs(effectsVolume - _effectsVolume) > 0.001) {
        _effectsVolume = effectsVolume;
        SimpleAudioEngine::getInstance()->setEffectsVolume(_effectsVolume);
        GameManager::getInstance()->setEffectVolume(_effectsVolume);
    }

}


//退出
void SettingLayer::onExit(){
    CCLayer::onExit();
    this->unscheduleAllSelectors();
}