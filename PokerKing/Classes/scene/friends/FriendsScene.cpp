//
//  FriendsScene.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-25.
//
//

#include "FriendsScene.h"
#include "FriendsLayer.h"

FriendsScene* FriendsScene::create()
{
	FriendsScene *layer=new FriendsScene();
    
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool FriendsScene::init()
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

void FriendsScene::setupScene()
{
    FriendsLayer *FriendsLayer = FriendsLayer::create();
    this->addChild(FriendsLayer, 0);
}