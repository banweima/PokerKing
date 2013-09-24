//
//  MainBoardScene.cpp
//  blackjack
//
//  Created by Niu Xiaoming on 13-3-23.
//
//

#include "MainBoardScene.h"
#include "MainBoardLayer.h"


MainBoardScene* MainBoardScene::create()

{
	MainBoardScene *scene=new MainBoardScene();
    
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
    
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool MainBoardScene::init()
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

void MainBoardScene::setupScene()
{
    MainBoardLayer *mainBoardLayer = MainBoardLayer::create();
    this->addChild(mainBoardLayer, 0);
}