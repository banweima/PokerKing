//
//  TaskScene.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-5.
//
//

#include "TaskScene.h"
#include "TaskLayer.h"
#include "RankingLayer.h"

TaskScene* TaskScene::create()
{
	TaskScene *layer=new TaskScene();
    
	if (layer && layer->init())
	{
		layer->autorelease();
		return layer;
	}
    
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool TaskScene::init()
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

void TaskScene::setupScene()
{
    TaskLayer *taskLayer = TaskLayer::create();
    this->addChild(taskLayer, 0);
}