//
//  LoginScene.cpp
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#include "LoginScene.h"
#include "LoginLayer.h"
#include "cocos-ext.h"
#include "JSONValueUtil.h"
#include "MainBoardScene.h"
#include "GameInfo.h"
#include "AlertLayer.h"
#include "Helpers.h"

USING_NS_CC_EXT;

LoginScene* LoginScene::create()
{
	LoginScene *scene=new LoginScene();
    
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
    
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool LoginScene::init()
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

void LoginScene::setupScene()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res/21Images_UntitledSheet.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("res/PokerKing_UntitledSheet.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/porkerlist.plist");
    
    LoginLayer *loginLayer = LoginLayer::create();
    this->addChild(loginLayer, 0);
    
}
