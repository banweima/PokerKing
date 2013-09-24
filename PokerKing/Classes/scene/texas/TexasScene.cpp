//
//  TexasScene.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-12.
//
//

#include "TexasScene.h"
#include "TexasLayer.h"


TexasScene* TexasScene::create(RoomLevelInfo * mRoomLevelInfo)
{
	TexasScene *layer=new TexasScene();
    
	if (layer && layer->init(mRoomLevelInfo))
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool TexasScene::init(RoomLevelInfo * mRoomLevelInfo)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCScene::init());
        
        this->setupScene(mRoomLevelInfo);
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void TexasScene::setupScene(RoomLevelInfo * mRoomLevelInfo)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/porkerlist.plist");
    
    TexasLayer *TexasLayer = TexasLayer::create();
    TexasLayer->setRoomLevelInfo(mRoomLevelInfo);
    this->addChild(TexasLayer, 0);
}