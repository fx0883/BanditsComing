

#include "LoadLevelInfo.h"
#include "GameManager.h"

LoadLevelinfo::LoadLevelinfo()
{
}
LoadLevelinfo::~LoadLevelinfo()
{
}

LoadLevelinfo *LoadLevelinfo::createLoadLevelinfo(const char *plistpath)
{
    LoadLevelinfo *pRet = new LoadLevelinfo();
    if (pRet && pRet->setPlist(plistpath))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool LoadLevelinfo::setPlist(const char *plistpath)
{
    bool bRet = false;
    do
    {
        __Dictionary *ccd = __Dictionary::createWithContentsOfFile(plistpath);
        CC_BREAK_IF(!ccd);

        s_NeedToLoadImages = dynamic_cast<__Dictionary *>(ccd->objectForKey(NEEDTOLOADIMAGES));
        CC_BREAK_IF(!s_NeedToLoadImages);

        s_LevelParameter = dynamic_cast<__Dictionary *>(ccd->objectForKey(LEVELPARAMETER));
        CC_BREAK_IF(!s_LevelParameter);

        bRet = true;
    }
    while (0);
    return bRet;
}

void LoadLevelinfo::clearAll()
{
    s_NeedToLoadImages->removeAllObjects();
    s_LevelParameter->removeAllObjects();
}

void LoadLevelinfo::initLevelInfo()
{
	GameManager *instance = GameManager::getInstance();

    auto blood =   s_LevelParameter->valueForKey("blood")->floatValue();
	instance->setBlood(blood);
	auto money =   s_LevelParameter->valueForKey("money")->floatValue();
	instance->setMoney(money);
	auto currlevel =   s_LevelParameter->valueForKey("currlevel")->getCString();
	instance->setCurrLevelFile(currlevel);
	auto nextlevel =   s_LevelParameter->valueForKey("nextlevel")->getCString();
	instance->setNextLevelFile(nextlevel);


	__Dictionary *groupDict = (__Dictionary*)s_LevelParameter->objectForKey("wave");
	auto groupTotle = groupDict->count();
	instance->setGroupNum(groupTotle);

	DictElement* tempGroup = NULL;

	CCDICT_FOREACH(groupDict, tempGroup)
	{
		__Dictionary* smallGroup = (__Dictionary*)tempGroup->getObject();

		auto type1Num =   smallGroup->valueForKey("type1Num")->intValue();
		auto type2Num =   smallGroup->valueForKey("type2Num")->intValue();
		auto type3Num =   smallGroup->valueForKey("type3Num")->intValue();
		auto type1Hp =   smallGroup->valueForKey("type1Hp")->intValue();
		auto type2Hp =   smallGroup->valueForKey("type2Hp")->intValue();
		auto type3Hp =   smallGroup->valueForKey("type3Hp")->intValue();

		GroupEnemy* group = GroupEnemy::create()->initGroupEnemy(type1Num, type1Hp, type2Num, type2Hp, type3Num, type3Hp, 5);
		instance->groupVector.pushBack(group);
		group = NULL;
	}
	auto curMapName =   s_NeedToLoadImages->valueForKey("1")->getCString();	
	instance->setCurMapName(curMapName);
	auto curBgName =   s_NeedToLoadImages->valueForKey("2")->getCString();	
	instance->setCurBgName(curBgName);
}