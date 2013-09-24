//
//  CaribbeanLayer.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__CaribbeanLayer__
#define __blackjack__CaribbeanLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlayCardHand.h"
#include "CardCount.h"
#include "RoomLevelInfo.h"

USING_NS_CC;
USING_NS_CC_EXT;


class CaribbeanLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    PlayCardHand* mDealerHand;
    PlayCardHand* mPlayerHand;
    PlayCardHand* mPlayerSplitHand;
    
    PokerHand   mPlayerPokerHand;
    PokerHand   mDealerPokerHand;
    
    CardCount* mDealerCount;
    CardCount* mPlayerCount;
    
    CCMenu* mStartMenu;
    CCMenu* mCardMenu;
    CCMenu* mGameMenu;
    
    CCLayerColor* mGlobalNotification;
    
    CCLabelTTF* mChooseRoomLabel;
    CCLabelTTF* mFriendsLabel;
    CCLabelTTF* mRankingLabel;
    CCLabelTTF* mShopLabel;
    CCLabelTTF* mSettingLabel;
    
    CCNode* mPlayerHandNode;
    CCNode* mDealerHandNode;
    CCNode* mPlayerSplitHandNode;
    CCNode* mPlayerCountNode;
    CCNode* mDealerCountNode;
    
    CCSprite* mPlayerFrameSprite;
    CCSprite* mDealerFrameSprite;
    
    int mConsecutiveWinCount;
    int fiveCards;
    bool mHitAllowed;
    bool mStandAllowed;
    
    int betCount;
    int winCount;
    
    long totalBonus;
    
    CC_SYNTHESIZE(CCArray*, mGameItems, GameItems);
    
    CCSprite * mFriendSupportImage;
    CCSprite * mFirendSupportLabel;
    
    float itemImageWidth;
    float itemImageHeight;
    float itemSpace;
    
    int mFriendsSupportRate;
    
    CC_SYNTHESIZE(RoomLevelInfo *, mRoomLevelInfo, RoomLevelInfo);
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CaribbeanLayer, create);
    
    bool init();
    
    CaribbeanLayer();
    virtual ~CaribbeanLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    
    void onChooseRoomClicked(CCObject * pSender);
    void onFriendsClicked(CCObject * pSender);
    void onRankingClicked(CCObject * pSender);
    void onShopClicked(CCObject * pSender);
    void onSettingClicked(CCObject * pSender);
    
    void onStartClicked(CCObject * pSender);
    
public:
    void onHitCardsClicked();
    void onStandCardsClicked();
    void NotifyBusted();
    void getPlayerImage(CCNode* node, void* data);
    void getDealerImage(CCNode* node, void* data);
    void dealCard();
    void checkPokerHand();
    
private:
    void hideButton(CCNode* node);
    void showButton(CCNode* node);
    void setHideButton(CCNode* node);
    int comparePokerHand();
    void winCalc();
    void afterStartAction();
    void beforeStartAction();
};

#endif /* defined(__blackjack__CaribbeanLayer__) */
