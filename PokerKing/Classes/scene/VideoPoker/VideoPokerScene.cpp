//
//  VideoPokerScene.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "VideoPokerScene.h"
#include "VideoPokerLayer.h"
#include "SimpleAudioEngine.h"

VideoPokerScene* VideoPokerScene::create(RoomLevelInfo * mRoomLevelInfo)
{
	VideoPokerScene *layer=new VideoPokerScene();
    
	if (layer && layer->init(mRoomLevelInfo))
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool VideoPokerScene::init(RoomLevelInfo * mRoomLevelInfo)
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

void VideoPokerScene::setupScene(RoomLevelInfo * mRoomLevelInfo)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plist/porkerlist.plist");
    
    VideoPokerLayer *VideoPokerLayer = VideoPokerLayer::create();
    VideoPokerLayer->setRoomLevelInfo(mRoomLevelInfo);
    this->addChild(VideoPokerLayer, 0);
}