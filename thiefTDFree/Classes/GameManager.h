//
//  GameManager.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#ifndef __thiefTD__GameManager__
#define __thiefTD__GameManager__

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "GroupEnemy.h"
#include "SimpleAudioEngine.h"  

USING_NS_CC;
using namespace CocosDenshion; 


#define FSLocalizedNSStringByKey(key) \
GameManager::getInstance()->getStringByKey(key)
//return type:const char*

#define kMusicVolume "MusicVolume"
#define kEffectVolume "EffectVolume"
class GameManager
{
public:
    
    Vector<EnemyBase*> enemyVector;
    Vector<Sprite*> bulletVector;
    Vector<TowerBase*> towerVector;
    Vector<GroupEnemy*> groupVector;

	CC_SYNTHESIZE(float, blood, Blood);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	CC_SYNTHESIZE(const char*, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
	CC_SYNTHESIZE(const char*, curBgName, CurBgName);
	
	//CC_SYNTHESIZE(int, enemyType, EnemyType);
	//CC_SYNTHESIZE(int, enemyCount, EnemyCount);

	//GroupEnemy* initGroup(int type, int count);
    GameManager();
    
    
	int _curMapId;
	void setCurMapID(int curID);
    int getCurMapID();

	static GameManager* getInstance();
    const char* getStringByKey(const std::string& key);
    bool init();
	void clear();
    
    
    float getMusicVolume();
    float getEffectVolume();
    
    void setMusicVolume(float volume);
    void setEffectVolume(float volume);
    
    
    
    //本地化数据存储文件
    Dictionary *localDic;
private:
	static GameManager *instance;
};
#endif /* defined(__thiefTD__GameManager__) */
