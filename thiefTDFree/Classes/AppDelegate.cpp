#include "AppDelegate.h"
#include "LevelInfoScene.h"
#include "UIScene.h"
#include "LoadingResScene.h"
USING_NS_CC;

extern"C"{
    
    size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
    
    {
        
        return fwrite(a, b, c, d);
        
    }
    
    char* strerror$UNIX2003( int errnum )
    
    {
        
        return strerror(errnum);
        
    }
    
}

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director 
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("TD Game");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    glview->setDesignResolutionSize(480.0f, 320.0f, ResolutionPolicy::FIXED_HEIGHT);
    

    #warning 这里能否获取当前语言，然后设置资源？
    
    std::vector<std::string> searchPath;
    
    LanguageType langtype = CCApplication::getInstance()->getCurrentLanguage();
    
    
    std::string strResourceFolder="height_864";
    switch (langtype) {
        case LanguageType::CHINESE:
            strResourceFolder="height_864_cn";
            break;
        case LanguageType::ENGLISH:
            strResourceFolder="height_864";
            break;
        default:
            strResourceFolder="height_864";
            break;
    }
    
    
    searchPath.push_back(strResourceFolder);
    CCFileUtils::getInstance()->setSearchPaths(searchPath);
    director->setContentScaleFactor(864.0f / 320.0f);
    
    // create a scene. it's an autorelease object
    auto scene = LoadingResScene::createScene();
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
