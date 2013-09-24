//
//  MainBoardLayer.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-3-23.
//
//

#ifndef __blackjack__MainBoardLayer__
#define __blackjack__MainBoardLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CardDeck.h"
#include "RankingScene.h"
#include "Loading.h"
#include "GameServerAction.h"
#include "ShopScene.h"
#include "BroadCast.h"
#include "AlertLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainBoardLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    CCMenuItemImage* mBlackJack;
    CCMenuItemImage* mCaribbean;
    CCMenuItemImage* mVideoPoker;
    CCMenuItemImage* mLottery;
    
    CCMenuItemImage* mShopButton;
    
    CCSprite * mMaleFrame;
    
    CCLabelTTF * mUserName;
    CCLabelTTF * mUserLevel;
    CCLabelTTF * mUserGold;
    CCLabelTTF * mUserDiamond;
    CCLabelTTF * mUserMedal;
    
    float mDuration;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainBoardLayer, create);
    
    bool init();
    
    MainBoardLayer();
    virtual ~MainBoardLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

private:
    void onBlackJackClicked(CCObject *pSender);
    void onCaribbeanClicked(CCObject *pSender);
    void onVideoPokerClicked(CCObject *pSender);
    void onLotteryClicked(CCObject *pSender);
    
    void goToBlackjack(CCNode *pSender);
    void goToCaribbean(CCNode *pSender);
    void goToVideoPoker(CCNode *pSender);
    void goToLottery(CCNode *pSender);
    void goToInvitation(CCNode *pSender);
    
    void onLeaderBoarderClicked(CCObject *pSender);
    void onFriendsClicked(CCObject * pSender);
    void onSettingClicked(CCObject * pSender);
    
    void startOnlineGame();
    void getPlayerImage(CCNode* node, void* data);
    void onShopButtonClicked(CCObject * object);
    
    void retrieveIAPProductList_Done(cocos2d::CCNode *pNode, void *data);
    
    void showUserInfo(cocos2d::CCNode *pNode, void *data);
    

    
};



#endif /* defined(__blackjack__MainBoardLayer__) */
