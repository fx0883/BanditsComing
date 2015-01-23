#ifndef __thiefTD__LevelSelectLayer1__  
#define __thiefTD__LevelSelectLayer1__  
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class LevelSelectLayer1: public Layer  
{  
public:  
    LevelSelectLayer1();  
    ~LevelSelectLayer1();  
      
    virtual bool init();  
      
    CREATE_FUNC(LevelSelectLayer1);  
      
    void menuCloseCallback0(Ref* pSender);    
      
};  
  
#endif /* defined(__thiefTD__ScorllMainLayer0101__) */