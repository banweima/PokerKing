//
//  GameRoomScene.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "GameRoomScene.h"
#include "GameRoomLayer.h"
#include "SimpleAudioEngine.h"

GameRoomScene* GameRoomScene::create()
{
	GameRoomScene *scene=new GameRoomScene();
    
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
    
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool GameRoomScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCScene::init());
        CCDirector::sharedDirector()->setNotificationNode(NULL);
        this->setupScene();
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void GameRoomScene::setupScene()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("cheer.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Loser.wa");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("BJ.mp3");
    
    GameRoomLayer *GameRoomLayer = GameRoomLayer::create();
    this->addChild(GameRoomLayer, 0);
}