#ifndef __thiefTD__LevelSelectLayer3__  
#define __thiefTD__LevelSelectLayer3__  
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class LevelSelectLayer3: public Layer  
{  
public:  
    LevelSelectLayer3();  
    ~LevelSelectLayer3();  
      
    virtual bool init();  
      
    CREATE_FUNC(LevelSelectLayer3);  
      
    void menuCloseCallback0(Ref* pSender);    
      
};  
  
#endif /* defined(__thiefTD__LevelSelectLayer3__) */