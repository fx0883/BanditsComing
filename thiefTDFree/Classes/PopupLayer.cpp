//
//  PopupLayer.cpp
//  thiefTD
//
//  Created by 冯璇 on 15/2/5.
//
//

#include "PopupLayer.h"
#include "ui/CocosGUI.h"
//#include "/workCode/BanditsComing/thiefTDFree/cocos2d/cocos/ui/UISlider.h"
#include "SimpleAudioEngine.h"
#include "extensions/GUI/CCControlExtension/CCControlSlider.h"
#include "VisibleRect.h"
#include "GameManager.h"
using namespace cocos2d;
using namespace cocos2d::ui;
//using namespace cocos2d::experimental;






// 构造函数中变量设初值
PopupLayer::PopupLayer()
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
PopupLayer::~PopupLayer()
{
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE(m_sfBackGround);
    CC_SAFE_RELEASE(m_s9BackGround);
    CC_SAFE_RELEASE(m_ltContentText);
    CC_SAFE_RELEASE(m_ltTitle);
}

//初始化
bool PopupLayer::init()
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
bool PopupLayer::onTouchBegan( Touch *pTouch, Event *pEvent ){
    return true;
}

//创建一个弹出层，给背景精灵变量赋值
PopupLayer* PopupLayer::create( const char* backgroundImage ){
    PopupLayer* popup = PopupLayer::create();
    popup->setSpriteBackGround(CCSprite::create(backgroundImage));
    popup->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return popup;
}

//给标题变量赋值
void PopupLayer::setTitle( const char* title, int fontsize ){
    CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "Arial", fontsize);
    ltfTitle->setColor(ccc3(0, 0, 0));
    setLabelTitle(ltfTitle);
}

//给文本变量赋值
void PopupLayer::setContentText( const char* text, int fontsize, int padding, int paddingTop ){
    CCLabelTTF* content = CCLabelTTF::create(text, "Arial", fontsize);
    content->setColor(ccc3(0, 0, 0));
    setLabelContentText(content);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}

//给下层层变量和回调函数变量赋值
void PopupLayer::setCallBackFunc( CCObject* target, SEL_CallFuncN callfun ){
    m_callbackListener = target;
    m_callback = callfun;
}

//给menu菜单变量添加Item
bool PopupLayer::addButton( const char* normalImage, const char* selectedImage, const char* title, int tag ){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint center = ccp(winSize.width/2, winSize.height/2);
    
    // 创建图片菜单按钮
    CCMenuItemImage* menuImage = CCMenuItemImage::create(
                                                         normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallBack));
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
void PopupLayer::buttonCallBack( CCObject* pSender ){
    CCNode* node = dynamic_cast<CCNode*>(pSender);
    CCLog("touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener)
    {
        //执行HelloWorld层的回调函数，传递node参数
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParentAndCleanup(true);
}

void PopupLayer::addChildAt(Node *node, float percentageX, float percentageY)
{
    const Size size = VisibleRect::getVisibleRect().size;
    node->setPosition(Point(percentageX * size.width, percentageY * size.height));
    this->addChild(node);
}



//全部参数都设定好后，在运行时动态加载
void PopupLayer::onEnter(){
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
    float btnHeight = contentSize.height / (getMenuButton()->getChildrenCount()+1);
    Vector<Node*>& array = getMenuButton()->getChildren();
    //CCObject* pObj = NULL;
    int i = 0;
    
    
    Vector<Node*>::iterator it;
    for(auto pObj : array){
        pObj->setPosition(ccp(winSize.width/2,
                              winSize.height/2 - contentSize.height/2+btnHeight*(i+1)));
        i++;
        
    }
    
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




//退出
void PopupLayer::onExit(){
    CCLayer::onExit();
}