//
//  SettingScene.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-7.
//
//

#include "SettingScene.h"
#include "SettingLayer.h"


SettingScene* SettingScene::create()
{
	SettingScene *scene=new SettingScene();
    
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
    
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool SettingScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCScene::init());
        
        this->setupScene();
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void SettingScene::setupScene()
{
    SettingLayer * settingLayer = SettingLayer::create();
    this->addChild(settingLayer, 0);
}