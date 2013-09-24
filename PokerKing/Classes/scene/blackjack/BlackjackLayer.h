//
//  BlackjackLayer.h
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#ifndef __blackjack__GameLayer__
#define __blackjack__GameLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlayCardHand.h"
#include "CardCount.h"
#include "MatchChip.h"
#include "ResultSprite.h"
#include "RoomLevelInfo.h"
#include "WordBoard.h"
#include "AlertLayer.h"
#include "BattleInfo.h"
#include "Loading.h"
#include "BroadCast.h"
#include "WhiteBoardLayer.h"
#include "SceneControler.h"
#include "BigSmallLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BlackjackLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    PlayCardHand* mDealerHand;
    PlayCardHand* mPlayerHand;
    PlayCardHand* mPlayerSplitHand;
    
    CardCount* mDealerCount;
    CardCount* mPlayerCount;
    
    MatchChip* mChipCount;
    
    ResultSprite* mPlayerResult;
    ResultSprite* mPlayerSplitResult;
    
    CCMenu* mStartMenu;
    CCMenu* mCardMenu;
    
    CCMenuItemImage* mSplitCardBtn;
    CCMenuItemImage* mDoubleBtn;
    
    CCMenuItemImage* mHitButton;
    CCMenuItemImage* mStandButton;
    
    CCSprite* mDealerImageSprite;
    
    
    CCNode* mPlayerHandNode;
    CCNode* mDealerHandNode;
    CCNode* mPlayerSplitHandNode;
    
    CCSprite* mPlayerFrameSprite;
    CCSprite* mDealerFrameSprite;
    
    CCSprite * mCoinAmountSprite;
    CCSprite * mRankSprite;
    
    CCSprite * mInsurance;
    
    CCMenuItemImage * mIncreaseBetButton;
    CCMenuItemImage * mDecreaseBetButton;
    
    CCLabelTTF * mCoinAmountLabel;
    CCLabelTTF * mRankLabel;
    CCLabelTTF * mMagicItemLabel;
        
    CCLabelTTF * mRaidBossGold;
    
    CCSprite * mMagicItemSprite;
    CCMenuItemImage * mMagicTool;
    
    WordBoard * mDealerWords;
    
    WordBoard * mYesNoWords;
    
    CCSprite * mBackground;
    
    CCMenu * mYesNoMenu;
    
    CCLabelTTF * dealerName;
    
    int mConsecutiveWinCount;
    
    bool mHitAllowed;
    bool mStandAllowed;
    bool mIsSplitting;
    bool mIsPlayingFirstSplit;
    bool mDoubleAllowed;
    bool mSplitAllowed;
    bool mIsDoublingDown;
    
    int mRoundWager;
    int mCurrentBet;
    int mInsuranceAmount;
    
    RoomLevelInfo* mRoomLevelInfo;
    
    CCSprite * mBossBackground;
    CCSprite * mBossWord;
        
    bool mSetInsurance;
    
    int mMagicToolTimes;
    
    bool isRaidBoss;
    
    bool isInBattle;
    
    bool hasSharedBoss;
    
    bool hasInsurance;
    
    CCMenu* mGlobalChat;
    
    CCMenuItemSprite* mGlobalChatItem;
    
    bool hadFriendSupport;
    
    int finalBlackJack;
    
    bool needInsurance;
    bool needBigSmall;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BlackjackLayer, create);
    
    bool init();
    
    BlackjackLayer();
    virtual ~BlackjackLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void onEnter();
    
    void onHomeClicked(CCObject * pSender);
    void onFriendsClicked(CCObject * pSender);
    void onSettingClicked(CCObject * pSender);
    void onRankClicked(CCObject * pSender);
    
    void onStartClicked(CCObject * pSender);
    
    void onIncreaseBetClicked(CCObject * pSender);
    void onDecreaseBetClicked(CCObject * pSender);
    
    void setRoomLevelInfo(RoomLevelInfo* RoomLevelInfo);
    
    void showUserInfo();
    
    
    
    void useMagicItem(CCNode *pSender, void *data);
    
    void showMagicTool();
    
    void requestMagicItem();
    
    void onYesClicked(CCObject * pSender);
    void onNoClicked(CCObject * pSender);
    
public:
    void onHitCardsClicked();
    void onStandCardsClicked();
    void onSplitCardClicked();
    void onDoubleClicked();
    void notifyPlayerHitDone();
    void notifyDealerHitDone();
    void notifyDealerToAddNextCard();
    void getPlayerImage(CCNode* node, void* data);
    void getDealerImage(bool isBoss);
    void onMagicToolClicked();
    
private:
    void hideButton(CCNode* node);
    void showStartButton();
    void showHitStandButton();
    void setHideButton(CCNode* node);
    
    void hideSplitDoubleButtons();
    void switchHandPosition();
    void switchHandZPostion();
    
    void showResult();
    ResultType checkResult(PlayCardHand * playerHand, PlayCardHand * dealerHand);
    
    void updateResultToServer();
    void showInsuranceRequirement();
    
    void dealerSays(std::string words);
    
    void startOnlineBattle();
    
    void startOnlineBattle_done(CCNode* pSender, void* data);
    
    void startGame();
    
    float calcMatchResult(ResultType type);
    
    void uploadMatchResult_Done(CCNode* pSender, void* data);
    
    void updateCurrentGold();
    
    void globalChatClicked();
    
    void shareBoss(CCNode* pSender, void* data);
    void shareBoss_Done(CCObject* data);

    void setInsurance(CCNode* pSender, void* data);
    void gotoOtherScene(GameScene otherScene);
    
    void checkFriendSupport();
    
    void friendSupport();
    
    void showDealerCard();
    
    void uploadMatchResult(CCNode* pSender, void* data);
    
    void beforeUploadResult(float result, int isBlackJack);
    
    void showBossImage(CCObject * data);
    
    void gotoShop(CCNode* pSender, void* data);

};

#endif /* defined(__blackjack__BlackjackLayer__) */
