//
//  RankingScene.cpp
//  blackjack
//
//  Created by Banson Niu on 9/12/12.
//
//

#include "RankingScene.h"
#include "RankingLayer.h"

RankingScene* RankingScene::create()
{
	RankingScene *layer=new RankingScene();
    
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool RankingScene::init()
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

void RankingScene::setupScene()
{
    RankingLayer *rankingLayer = RankingLayer::create();
    this->addChild(rankingLayer, 0);
}