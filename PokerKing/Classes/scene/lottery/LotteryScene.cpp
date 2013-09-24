//
//  LotteryScene.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-8.
//
//

#include "LotteryScene.h"


LotteryScene* LotteryScene::create()
{
	LotteryScene *scene=new LotteryScene();
    
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
    
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool LotteryScene::init()
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

void LotteryScene::setupScene()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/porkerlist.plist");
    
    LotteryLayer *LotteryLayer = LotteryLayer::create();
 
    
    this->addChild(LotteryLayer, 0);
}