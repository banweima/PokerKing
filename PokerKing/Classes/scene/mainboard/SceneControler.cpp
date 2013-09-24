//
//  SceneControler.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-25.
//
//

#include "SceneControler.h"
#include "MainBoardScene.h"
#include "GameRoomScene.h"
#include "BlackjackScene.h"
#include "FriendsScene.h"
#include "ShopScene.h"
#include "RankingScene.h"
#include "AlertLayer.h"
#include "BroadCast.h"
#include "TaskScene.h"
#include "SettingScene.h"
#include "InvitationScene.h"
#include "VideoPokerScene.h"
#include "LotteryScene.h"
#include "TexasScene.h"

static GameScene targetScene;

SceneControler* SceneControler::sharedSceneControler(void)
{
    SceneControler *pSceneControler = NULL;
    if (!pSceneControler)
    {
        pSceneControler = new SceneControler();
    }
    
    return pSceneControler;
}

void SceneControler::gotoScene(GameScene gameScene)
{
    BroadCast::sharedBroadCast()->pauseRolling();
    
    CCScene * scene = NULL;
    switch (gameScene) {
            case MainBoard_Scene:
            scene = MainBoardScene::create();
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
            break;
            
            case GameRoom_Scene:
            scene = GameRoomScene::create();
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
            break;
            
            case Friends_Scene:
            scene = FriendsScene::create();
            CCDirector::sharedDirector()->pushScene(scene);
            break;
            
            case Shop_Scene:
            scene = ShopScene::create();
            CCDirector::sharedDirector()->pushScene(scene);
            break;
            
            case Rank_Scene:
            scene = RankingScene::create();
            CCDirector::sharedDirector()->pushScene(scene);
            break;
            
            case Task_Scene:
            scene = TaskScene::create();
            CCDirector::sharedDirector()->pushScene(scene);
            break;
            
            case Setting_Scene:
            scene = SettingScene::create();
            CCDirector::sharedDirector()->pushScene(scene);
            break;
            
            case Invitation_Scene:
            scene = InvitationScene::create();
            CCDirector::sharedDirector()->pushScene(scene);
            break;
            
            case Lottery_Scene:
            scene = LotteryScene::create();
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
            break;
        }
    
}

void SceneControler::gotoSceneWithAlert(GameScene gameScene, std::string title, std::string contentString, CCLayer * targetLayer)
{
    targetScene = gameScene;
    
    AlertLayer * shareAlert = AlertLayer::create(title.c_str(), contentString.c_str() , true, this, callfuncND_selector(SceneControler::afterAlert));
    
    targetLayer->addChild(shareAlert, Child_Order_Top);
}

void SceneControler::goBackScene()
{
    CCDirector::sharedDirector()->popScene();
}

void SceneControler::afterAlert(cocos2d::CCNode *pNode, void *data)
{
    if((bool)data)
    {
        gotoScene(targetScene);
    }
}
