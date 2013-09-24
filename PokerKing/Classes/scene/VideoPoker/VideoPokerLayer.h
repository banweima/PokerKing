//
//  VideoPokerLayer.h
//  
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__VideoPokerLayer__
#define __blackjack__VideoPokerLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlayCardHand.h"
#include "CardCount.h"
#include "RoomLevelInfo.h"
#include "GameInfo.h"
#include "SceneControler.h"
#include "AlertLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;


class VideoPokerLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public CCTouchDelegate
{
private:
    PlayCardHand* mPlayerHand;
    CardCount* mPlayerCount;
    
    CCLabelTTF* mTotalBonus;
    CCLabelTTF* mGold;
    CCLabelTTF* mLevel;

    CCMenuItemImage * mDeal;
    
    CCNode* mPlayerHandNode;
    CCNode* mPlayerCountNode;

    CCParticleSystemQuad * mFX;
    
    RoomLevelInfo * mRoomLevelInfo;
    CCLabelTTF * mWinChipsSprite;
    
    
    
    int mConsecutiveWinCount;
    int fiveCards;
    
    int betCount;
    int winCount;
    
    long totalBonus;
    
    PokerHand   mPlayerPokerHand;
    
    
    
    bool mIsFirstHit;
    
    bool hadFriendSupport;
    
public:


    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(VideoPokerLayer, create);

    
    bool init();
    
    VideoPokerLayer();
    virtual ~VideoPokerLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void onEnter();
    
    void onHomeClicked(CCObject * pSender);
    void onFriendsClicked(CCObject * pSender);
    void onRankClicked(CCObject * pSender);
    void onSettingClicked(CCObject * pSender);
    
    void onDealClicked(CCObject * pSender);
    
public:
    void onBetClicked();
    void onMaxClicked();
    void getPlayerImage(CCNode* node, void* data);
    void dealCard();
    void checkPokerHand();
    void setRoomLevelInfo(RoomLevelInfo* RoomLevelInfo);
    
private:
    void hideButton(CCNode* node);
    void showButton(CCNode* node);
    void setHideButton(CCNode* node);
    void winCalc();
    void startOnlineBattle();
    
    void startOnlineBattle_done(CCNode* pSender, void* data);
    
    void startGame();
    
    void uploadMatchResult(float result);
    
    void uploadMatchResult_Done(CCNode* pSender, void* data);
    
    void gotoOtherScene(GameScene otherScene);
    
    void showUserInfo();
    
    void friendSupport();
    
    void showFriendSupportMessage();
    
    void gotoShop(CCNode* pSender, void* data);

};

#endif /* defined(__blackjack__VideoPokerLayer__) */
