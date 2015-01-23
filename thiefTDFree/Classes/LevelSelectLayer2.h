#ifndef __thiefTD__LevelSelectLayer2__  
#define __thiefTD__LevelSelectLayer2__  
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class LevelSelectLayer2: public Layer  
{  
public:  
    LevelSelectLayer2();  
    ~LevelSelectLayer2();  
      
    virtual bool init();  
      
    CREATE_FUNC(LevelSelectLayer2);  
      
    void menuCloseCallback0(Ref* pSender);    
      
};  
  
#endif /* defined(__thiefTD__LevelSelectLayer2__) */