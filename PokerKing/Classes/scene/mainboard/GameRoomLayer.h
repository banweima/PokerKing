//
//  GameRoomLayer.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__GameRoomLayer__
#define __blackjack__GameRoomLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "RoomLevelInfo.h"
#include "CaribbeanScene.h"
#include "VideoPokerScene.h"
#include "MainBoardScene.h"
#include "RoomLevelInfo.h"

USING_NS_CC;
USING_NS_CC_EXT;



class GameRoomLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    CCMenuItemImage* mHongKong;
    CCMenuItemImage* mMacau;
    CCMenuItemImage* mLasVegas;
    CCMenuItemImage* mMonteCarlo;
    
    float mDuration;

    CCSprite * mMaleFrame;
    
    CCLabelTTF * mUserName;
    CCLabelTTF * mUserLevel;
    CCLabelTTF * mUserGold;
    CCLabelTTF * mUserDiamond;
    CCLabelTTF * mUserMedal;
    
    CCArray * roomLevelList;

    CCMenuItemImage* mShopButton;

public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameRoomLayer, create);
    
    bool init();
    
    GameRoomLayer();
    virtual ~GameRoomLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void getGameRoomInfo();
    
    bool checkRoomLevel(RoomType roomType);
    
    void goToHongkong(CCNode *pSender);
    void goToMacau(CCNode *pSender);
    void goToLasVegas(CCNode *pSender);
    void goToMonteCarlo(CCNode *pSender);
    
    void setRoomLevelList();
    
private:
    void onHongKongClicked(CCObject *pSender);
    void onMacauClicked(CCObject *pSender);
    void onLasVegasClicked(CCObject *pSender);
    void onMonteCarloClicked(CCObject *pSender);
    
    void onHomeClicked(CCObject *pSender);
    void onLeaderBoarderClicked(CCObject *pSender);
    void onShopButtonClicked(CCObject *pSender);
    void onFriendsClicked(CCObject *pSender);
    void onSettingClicked(CCObject *pSender);
    
    void getGameRoomInfo_Done(cocos2d::CCNode *pSender, void *data);
    
    void goToGameScene(RoomLevelInfo* levelInfo);
    void getPlayerImage();
    
    void showUserBoss();
    
    void showUserBoss_Done(cocos2d::CCNode *pNode, void *data);
    
};

#endif /* defined(__blackjack__MainMenuLayer__) */
