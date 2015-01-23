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
                                                                                              
    //���ɱ�����logo��
    virtual void addBackGround(){};
                                                                                          
    //���һ��progress
    virtual ProgressTimer * addProgress(){return NULL;};
                                                                                          
    //����Ҫ���ص���Դ������������У���update����.�������л�������
    virtual void loadResources();
                                                                                          
    //����������Դ
    void update(float dt);
                                                                                          
    //������Դ��ݷ���
    void loadingPVR(const char * plist);
    //������Դ��ݷ���2
    void loadingPVRs(const char * plist,...);
                                                                                          
public:
    //������
    ProgressTimer * _pross;
};
#endif /* defined(__thiefTD__ThiefBase__) */
