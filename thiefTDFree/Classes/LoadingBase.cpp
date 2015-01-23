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
	//���ɱ�����logo��
	addBackGround();                                                                                    
	//��ӽ�����
	_pross = addProgress();

	if (_pross!= NULL)
		this->addChild(_pross);
	//0.5��������Դ
	this->scheduleOnce(schedule_selector(LoadingBase::update),0.5f);

	return true;
}


void LoadingBase::loadResources()
{
    loadingPVRs("111","222");
    //TODO: �л�����
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
 //������Դ��ݷ���2
void LoadingBase::loadingPVRs(const char * plist,...)
{
    //������
    float t_loading ;
    //------------��ȡ����--------------
    int num= 0 ;
    //���ȶ�������б����
    va_list argp;
    //��ʼ����ʹ��argpָ��ɱ�����ĵ�һ��������
    va_start(argp, plist);
    //���ʡ�ԵĲ����Ǹ��ݺ�����һ��������ƫ���������
    while (true)
    {
                                                                                            
        if(va_arg(argp, const char *)== NULL)
            break;
        num++;
                                                                                            
    }
    //�����ɱ������ȡ
    va_end(argp);
    //-------------����װ��-------
                                                                                        
    //����ͷһ����Դ
    t_loading = 100.0f*1/(num+1);
    _pross->setPercentage(t_loading);
    loadingPVR(plist);
                                                                                        
    va_list argp2;
    va_start(argp2,plist);
                                                                                        
    for (int i=1; i<=num; i++)
    {
        //�޸Ľ�����
        t_loading = 100.0f*(i+1)/(num+1);
        _pross->setPercentage(t_loading);
        loadingPVR(va_arg(argp2, const char *));
    }
    va_end(argp2);
}