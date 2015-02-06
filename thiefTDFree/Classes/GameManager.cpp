//
//  GameManager.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-15.
//
//

#include "GameManager.h"

GameManager* GameManager::instance;




GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();
	return instance;
}

bool GameManager::init()
{
	bool bRet = false;
	do
	{


		bRet = true;
	} while (0);
	return bRet;
}
GameManager::GameManager():localDic(NULL)
{
    
}

const char* GameManager::getStringByKey(const std::string& key)
{
    const char *retChr;
    if (this->localDic) {
//        const __String* strRet=this->localDic->valueForKey(key);
        retChr=this->localDic->valueForKey(key)->getCString();
    }
    return retChr;
}

void GameManager::setCurMapID(int curID)
{
    _curMapId = curID;
}

int GameManager::getCurMapID()
{
    return _curMapId;
}

void GameManager::clear()
{
	enemyVector.clear();
	bulletVector.clear();
	//towerVector.clear();
	groupVector.clear();
}


float GameManager::getMusicVolume()
{
    return UserDefault::getInstance()->getFloatForKey(kMusicVolume,-1.0f);
}
float GameManager::getEffectVolume()
{
    return UserDefault::getInstance()->getFloatForKey(kEffectVolume,-1.0f);
}

void GameManager::setMusicVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey(kMusicVolume, volume);
}
void GameManager::setEffectVolume(float volume)
{
    UserDefault::getInstance()->setFloatForKey(kEffectVolume, volume);

}