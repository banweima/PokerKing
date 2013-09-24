//
//  SceneControler.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-25.
//
//

#ifndef __PokerKing__SceneControler__
#define __PokerKing__SceneControler__

#include "cocos2d.h"
#include "Constants.h"


USING_NS_CC;


enum GameScene
{
    MainBoard_Scene,
    GameRoom_Scene,
    Shop_Scene,
    Rank_Scene,
    Blackjack_Scene,
    Friends_Scene,
    Task_Scene,
    Setting_Scene,
    Invitation_Scene,
    VideoPoker_Scene,
    Lottery_Scene,
    Texas_Scene
};


class SceneControler : public CCObject
{
private:
    
    CC_SYNTHESIZE(std::string, mLoginServerUrl, LoginServerUrl);

    
    
public:
    static SceneControler * sharedSceneControler();
    
    void gotoScene(GameScene gameScene);
    
    void goBackScene();
    
    void gotoSceneWithAlert(GameScene gameScene, std::string title, std::string contentString, CCLayer * targetLayer);
private:
    void afterAlert(CCNode * pNode, void * data);

};


#endif /* defined(__PokerKing__SceneControler__) */
