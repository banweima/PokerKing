//
//  InvitationScene.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-13.
//
//

#include "InvitationScene.h"
#include "InvitationLayer.h"

InvitationScene* InvitationScene::create()
{
	InvitationScene *layer=new InvitationScene();
    
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool InvitationScene::init()
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

void InvitationScene::setupScene()
{
    InvitationLayer *layer = InvitationLayer::create();
    this->addChild(layer, 0);
}