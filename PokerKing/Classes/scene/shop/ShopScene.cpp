//
//  ShopScene.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-26.
//
//

#include "ShopScene.h"
#include "ShopLayer.h"

ShopScene* ShopScene::create()
{
	ShopScene *layer=new ShopScene();
    
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool ShopScene::init()
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

void ShopScene::setupScene()
{
    ShopLayer *ShopLayer = ShopLayer::create();
    this->addChild(ShopLayer, 0);
}