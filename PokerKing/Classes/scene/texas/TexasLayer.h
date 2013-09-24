//
//  TexasLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-12.
//
//

#ifndef __PokerKing__TexasLayer__
#define __PokerKing__TexasLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlayCardHand.h"
#include "CardCount.h"
#include "RoomLevelInfo.h"
#include "PlayerInfo.h"

USING_NS_CC;
USING_NS_CC_EXT;


class TexasLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    PlayCardHand* mDealerHand;
    PlayCardHand* mPlayerHand;
    PlayCardHand* mEnemyHand;
    
    PokerHand   mPlayerPokerHand;
    PokerHand   mEnemyPokerHand;
    
    CardCount* mEnemyCount;
    CardCount* mPlayerCount;
    
    CCMenu* mStartMenu;
    
    CCNode* mPlayerHandNode;
    CCNode* mDealerHandNode;
    CCNode* mEnemyHandNode;
    
    CCNode* mPlayerCountNode;
    CCNode* mEnemyCountNode;
    
    CCSprite* mPlayerFrameSprite;
    CCSprite* mEnemyFrameSprite;
    
    CCControlButton * mFold;
    CCControlButton * mRaise;
    CCControlButton * mCall;
    
    CCMenuItemImage * mRaisePlus;
    CCMenuItemImage * mRaiseMinus;
    CCMenuItemImage * mScrollDot;
    CCMenuItemImage * mScrollBar;
    
    CCSprite * mPlayerRankSprite;
    CCSprite * mEnemyRankSprite;
    
    int mConsecutiveWinCount;
    int fiveCards;
    
    int betCount;
    int winCount;
    
    long totalBonus;
    
    PlayerInfo * playerInfo;
    PlayerInfo * enemyInfo;
    
    CC_SYNTHESIZE(RoomLevelInfo *, mRoomLevelInfo, RoomLevelInfo);
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TexasLayer, create);
    
    bool init();
    
    TexasLayer();
    virtual ~TexasLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    
    
public:
    void NotifyBusted();
    void getPlayerImage(CCNode* node, void* data);
    void getDealerImage(CCNode* node, void* data);
    void checkPokerHand();
    
private:
    void hideButton(CCNode* node);
    void showButton(CCNode* node);
    void setHideButton(CCNode* node);
    int comparePokerHand();
    void winCalc();
    
    void onHomeClicked(cocos2d::CCObject *pSender);
    
    void onStartClicked(CCObject * pSender);
    void startGame(CCNode* node, void* data);
    
    
    void onFoldClicked();
    void onRaiseClicked();
    void onCallClicked();
    
    void onRaiseMinusClicked();
    void onRaisePlusClicked();
    void onScrollDotClicked();
    
};

#endif /* defined(__PokerKing__TexasLayer__) */
