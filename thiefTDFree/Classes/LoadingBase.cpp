//
//  LoadingBase.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "LoadingBase.h"

LoadingBase::LoadingBase():_pross(NULL)
{
}

LoadingBase::~LoadingBase()
{
}

bool LoadingBase::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//生成背景和logo等
	addBackGround();                                                                                    
	//添加进度条
	_pross = addProgress();

	if (_pross!= NULL)
		this->addChild(_pross);
	//0.5秒后加载资源
	this->scheduleOnce(schedule_selector(LoadingBase::update),0.5f);

	return true;
}


void LoadingBase::loadResources()
{
    loadingPVRs("111","222");
    //TODO: 切换场景
}
void LoadingBase::update(float dt)
{
    loadResources();
}
void LoadingBase::loadingPVR(const char * plist)
{
    Texture2D::PVRImagesHavePremultipliedAlpha(true);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}
 //加载资源快捷方法2
void LoadingBase::loadingPVRs(const char * plist,...)
{
    //进度条
    float t_loading ;
    //------------获取个数--------------
    int num= 0 ;
    //需先定义参数列表变量
    va_list argp;
    //初始化，使用argp指向可变参数的第一个参数，
    va_start(argp, plist);
    //其后省略的参数是根据函数第一个参数的偏移量来获得
    while (true)
    {
                                                                                            
        if(va_arg(argp, const char *)== NULL)
            break;
        num++;
                                                                                            
    }
    //结束可变参数获取
    va_end(argp);
    //-------------进行装载-------
                                                                                        
    //加载头一个资源
    t_loading = 100.0f*1/(num+1);
    _pross->setPercentage(t_loading);
    loadingPVR(plist);
                                                                                        
    va_list argp2;
    va_start(argp2,plist);
                                                                                        
    for (int i=1; i<=num; i++)
    {
        //修改进度条
        t_loading = 100.0f*(i+1)/(num+1);
        _pross->setPercentage(t_loading);
        loadingPVR(va_arg(argp2, const char *));
    }
    va_end(argp2);
}