//
//  FailedScene.h
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#ifndef __thiefTD__FailedScene__
#define __thiefTD__FailedScene__

#include <iostream>
#include "cocos2d.h"

class FailedScene : public cocos2d::Scene
{
public:  
    FailedScene();  
    virtual bool init();  
    CREATE_FUNC(FailedScene);  
    void menuCloseCallback(Ref* pSender);
    ~FailedScene();
 

private:

}; 
#endif /* defined(__thiefTD__FailedScene__) */
