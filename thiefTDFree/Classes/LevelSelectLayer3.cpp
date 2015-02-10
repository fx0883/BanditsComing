#include "LevelSelectLayer3.h"  
#include "LevelInfoScene.h"

#include "SimpleAudioEngine.h" 
using namespace CocosDenshion; 

#define LEVEL_ROW (3)
#define LEVEL_COL (2)


LevelSelectLayer3::LevelSelectLayer3()  
{  
}  
  
LevelSelectLayer3::~LevelSelectLayer3()  
{  
}  
  
bool LevelSelectLayer3::init()  
{  
    bool bRet = false;  
      
    do {  
        Size size = CCDirector::getInstance()->getWinSize();  
          
        Sprite* sprite =Sprite::create("selectLevelBg3.png");  
		sprite->setPosition(Point(size.width / 2,size.height / 2));  
		addChild(sprite,-2);  
        
		Vector<MenuItem*> menuItemVector;
		auto buttonSize = Sprite::create("card_1.png")->getContentSize();
		auto gap = buttonSize.width / 4;
		auto startWidth =( size.width -  LEVEL_ROW* buttonSize.width - (LEVEL_ROW - 1)*gap ) /2 ;
		auto startHeight = ( size.height + (LEVEL_COL - 1) * gap + buttonSize.height * LEVEL_COL ) /2 - buttonSize.height;
		for ( int row = 0; row < LEVEL_COL; row++ )
		{
			auto height = startHeight - ( buttonSize.height + gap ) * row ;			
			for ( int col = 0; col < LEVEL_ROW; col++)
			{
				auto width = startWidth + ( buttonSize.width + gap ) * col ;
				auto item = MenuItemImage::create(  
                                           "card_1.png",
                                           "card_2.png",
										   "card_3.png",
                                           CC_CALLBACK_1(LevelSelectLayer3::menuCloseCallback0, this)); 
				
				item->setAnchorPoint(Point(0 ,0));
				item->setPosition(Point(width, height)); 
				item->setTag(row * LEVEL_ROW + col + 12);
				menuItemVector.pushBack( item );
				auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum");
				//item->setEnabled(false);
				if(levelNum < row * LEVEL_ROW + col + 12 )
				{
					item->setEnabled(false);
				}
			}
		}
		auto levelMenu = Menu::createWithArray(menuItemVector);  
        levelMenu->setPosition(Point::ZERO);  
        this->addChild(levelMenu, -1);          
          
        bRet = true;  
    } while (0);  
      
    return bRet;  
}  
  
void LevelSelectLayer3::menuCloseCallback0(Ref* pSender)
{  
	auto button = (Sprite *)pSender;
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/enemy0_down.mp3").c_str(), false);
	log("button tag : %d" ,button->getTag());

	char buffer[20] = { 0 };
    sprintf(buffer, "levelInfo_%d_%d.plist", 1, button->getTag()%6);
    std::string strName =  buffer;
	UserDefault::getInstance()->setStringForKey("nextLevelFile", strName);
	log("strName : %s" ,strName.c_str());

	Scene *scene = Scene::create();
	auto layer = LevelInfoScene::create();
	//layer->initLoadInfo(1, button->getTag());
	scene->addChild(layer);
	auto sence = TransitionFade::create(0.5, scene);

    Director::getInstance()->replaceScene(sence); 

}  
