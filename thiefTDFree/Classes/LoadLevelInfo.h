#ifndef __thiefTD__LoadLevelInfo__
#define __thiefTD__LoadLevelInfo__

#include "cocos2d.h"
using namespace cocos2d;

#define NEEDTOLOADIMAGES "needtoloadimages"
#define LEVELPARAMETER "levelparameter"

class LoadLevelinfo: public Ref
{
public:

    LoadLevelinfo();
    ~LoadLevelinfo();
    static LoadLevelinfo * createLoadLevelinfo(const char *plistpath);

    bool setPlist(const char * plistpath);

    float f_GetLevelInfo(const char * key);

	void initLevelInfo();
    void clearAll();

private:

    __Dictionary * s_NeedToLoadImages;
    __Dictionary * s_LevelParameter;

};
#endif /* defined(__thiefTD__LoadLevelInfo__) */
