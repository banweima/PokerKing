//
//  CaribbeanScene.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "CaribbeanScene.h"
#include "CaribbeanLayer.h"

CaribbeanScene* CaribbeanScene::create(RoomLevelInfo * mRoomLevelInfo)
{
	CaribbeanScene *layer=new CaribbeanScene();
    
	if (layer && layer->init(mRoomLevelInfo))
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool CaribbeanScene::init(RoomLevelInfo * mRoomLevelInfo)
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

void CaribbeanScene::setupScene(RoomLevelInfo * mRoomLevelInfo)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/porkerlist.plist");
    
    CaribbeanLayer *CaribbeanLayer = CaribbeanLayer::create();
    CaribbeanLayer->setRoomLevelInfo(mRoomLevelInfo);
    this->addChild(CaribbeanLayer, 0);
}