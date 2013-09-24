//
//  BlackjackScene.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "BlackjackScene.h"
#include "BlackjackLayer.h"
#include "SimpleAudioEngine.h"

BlackjackScene* BlackjackScene::create(RoomLevelInfo* RoomLevelInfo)
{
	BlackjackScene *scene=new BlackjackScene();
    
	if (scene && scene->init(RoomLevelInfo))
	{
		scene->autorelease();
		return scene;
	}
    
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool BlackjackScene::init(RoomLevelInfo* RoomLevelInfo)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCScene::init());

        this->setupScene(RoomLevelInfo);
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void BlackjackScene::setupScene(RoomLevelInfo* RoomLevelInfo)
{
    BlackjackLayer *blackjackLayer = BlackjackLayer::create();
    blackjackLayer->setRoomLevelInfo(RoomLevelInfo);
    
    this->addChild(blackjackLayer, 0);
}