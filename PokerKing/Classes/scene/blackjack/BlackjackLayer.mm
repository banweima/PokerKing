//
//  GameLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "BlackjackLayer.h"
#include "GameRoomScene.h"
#include "RankingScene.h"
#include "CCBUtility.h"
#include "PlayCard.h"
#include "Constants.h"
#include "CardDeck.h"
#include "HttpImageLoader.h"
#include "GameInfo.h"
#include "GameServer.h"
#include "MainBoardScene.h"
#include "UserInfo.h"
#include "ChatLayer.h"
#include "platform.h"
#include "SimpleAudioEngine.h"
#include "ImageController.h"
#include "Banner.h"
#include "WeiboFactory.h"


#define TopHeight 40;

BlackjackLayer::BlackjackLayer()
: mStartMenu(NULL)
, mCardMenu(NULL)
, mPlayerHandNode(NULL)
, mDealerHandNode(NULL)
, mPlayerSplitHandNode(NULL)
, mHitAllowed(true)
, mStandAllowed(false)
, mIsSplitting(false)
, mIsPlayingFirstSplit(false)
, mDoubleAllowed(false)
, mSplitAllowed(false)
, mIsDoublingDown(false)
, mPlayerFrameSprite(NULL)
, mDealerFrameSprite(NULL)
, mSplitCardBtn(NULL)
, mDoubleBtn(NULL)
, mRoomLevelInfo(NULL)
, mCurrentBet(0)
, mCoinAmountSprite(NULL)
, mRankSprite(NULL)
, mCoinAmountLabel(NULL)
, mDealerWords(NULL)
, mMagicItemSprite(NULL)
, mMagicTool(NULL)
, mMagicItemLabel(NULL)
, mBackground(NULL)
, mDecreaseBetButton(NULL)
, mIncreaseBetButton(NULL)
, mHitButton(NULL)
, mStandButton(NULL)
, isRaidBoss(false)
, isInBattle(false)
, hasSharedBoss(false)
, mInsurance(NULL)
, hasInsurance(false)
, mInsuranceAmount(0)
, dealerName(NULL)
, mBossWord(NULL)
, mBossBackground(NULL)
, mDealerImageSprite(NULL)
{}

BlackjackLayer::~BlackjackLayer()
{
    CC_SAFE_RELEASE(mStartMenu);
    CC_SAFE_RELEASE(mCardMenu);
    CC_SAFE_RELEASE(mPlayerHandNode);
    CC_SAFE_RELEASE(mDealerHandNode);
    CC_SAFE_RELEASE(mPlayerSplitHandNode);
    CC_SAFE_RELEASE(mPlayerFrameSprite);
    CC_SAFE_RELEASE(mDealerFrameSprite);

    CC_SAFE_RELEASE(mSplitCardBtn);
    CC_SAFE_RELEASE(mDoubleBtn);
    CC_SAFE_RELEASE(mRoomLevelInfo);
    CC_SAFE_RELEASE(mIncreaseBetButton);
    CC_SAFE_RELEASE(mDecreaseBetButton);
    CC_SAFE_RELEASE(mCoinAmountSprite);
    CC_SAFE_RELEASE(mRankSprite);
    CC_SAFE_RELEASE(mMagicItemSprite);
    CC_SAFE_RELEASE(mMagicTool);
    CC_SAFE_RELEASE(mBackground);
    
    CC_SAFE_RELEASE(mHitButton);
    CC_SAFE_RELEASE(mStandButton);
    
    CC_SAFE_RELEASE(mInsurance);
}

bool BlackjackLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        if(LoadStringFromXML(NeedBJInsurance) == "Yes")
        {
            needInsurance = true;
        }
        else
        {
            needInsurance = false;
        }
        
        if(LoadStringFromXML(NeedBJBigSmall) == "No")
        {
            needBigSmall = false;
        }
        else
        {
            needBigSmall = true;
        }
        
        this->setupLayer();
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void BlackjackLayer::setupLayer()
{
    CCLOG("setupLayer");
    CCNode * node = CCBUtility::loadCCB("ccbi/blackjack.ccbi", "BlackjackLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    
    int wh = getWinH();
    if(wh>480)
    {
        Banner * banner = Banner::create();
        banner->retain();
        this->addChild(banner,-100);
    }
    
    mDealerHand = PlayCardHand::create(true);
    mDealerHand->retain();
    mPlayerHand = PlayCardHand::create(false);
    mPlayerHand->retain();
    mPlayerSplitHand = PlayCardHand::create(false);
    mPlayerSplitHand->retain();
    
    mDealerHand->setCardScale(0.8);
    mPlayerHand->setCardScale(0.8);
    
    int w = mBackground->getContentSize().width;
    int h = mBackground->getContentSize().height;
    
    int menuH = 0;
    int notifyH = TopHeight;
    int tmpH = (h-menuH-notifyH)/2 + menuH;
    int handH = h/3;
    
    mDealerHand->setPosition(ccp(w/2, tmpH + handH));
    mPlayerHand->setPosition(ccp(w/2, tmpH - handH));
    mPlayerSplitHand->setPosition(ccp(w/2, tmpH - handH));
    
    mPlayerHandNode->addChild(mPlayerHand);
    mDealerHandNode->addChild(mDealerHand);
    mPlayerSplitHandNode->addChild(mPlayerSplitHand);
    
    mPlayerResult = ResultSprite::create();
    mPlayerResult->retain();
    mPlayerSplitResult = ResultSprite::create();
    mPlayerSplitResult->retain();
    
    this->addChild(mPlayerResult, 1000);
    this->addChild(mPlayerSplitResult, 1000);
    
    mChipCount = MatchChip::create();
    mChipCount->retain();

    this->addChild(mChipCount);
    mChipCount->setCount(mCurrentBet);
    mChipCount->setVisible(true);
    mChipCount->setPosition(ccp(w/2, tmpH - 60));
    
    mDealerWords = WordBoard::create();
    mDealerWords->retain();
    this->addChild(mDealerWords);

    mSplitCardBtn->setVisible(false);
    mDoubleBtn->setVisible(false);
    
    mStartMenu->getParent()->reorderChild(mStartMenu, 1000);
    mStartMenu->setPosition(ccp(w/2, tmpH));
    mCardMenu->getParent()->reorderChild(mCardMenu, 1000);
    
    
    mCardMenu->setVisible(false);
    
    mMagicTool->setPositionY(mPlayerFrameSprite->getPositionY());
    mMagicTool->setVisible(false);
    
    this->getDealerImage(false);
    
    mCoinAmountLabel = CCLabelTTF::create("0", "Helvetica", 18);
    this->addChild(mCoinAmountLabel);
    mCoinAmountLabel->retain();
    
    mRankLabel = CCLabelTTF::create("0", "Helvetica", 18);
    this->addChild(mRankLabel);
    mRankLabel->retain();
    
    mMagicItemLabel = CCLabelTTF::create("0", "Helvetica", 18);
    this->addChild(mMagicItemLabel);
    mMagicItemLabel->retain();
    
    mRaidBossGold = CCLabelTTF::create("0", "Helvetica", 18);
    this->addChild(mRaidBossGold);
    mRaidBossGold->retain();
    mRaidBossGold->setVisible(false);
    
    mCoinAmountLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    mCoinAmountLabel->setAnchorPoint(ccp(0,0.5));
    mCoinAmountLabel->setPosition(ccp(mCoinAmountSprite->getPositionX() + mCoinAmountSprite->getContentSize().width/2 + 5,mCoinAmountSprite->getPositionY()));
    
    mRankLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    mRankLabel->setAnchorPoint(ccp(0,0.5));
    mRankLabel->setPosition(ccp(mRankSprite->getPositionX() + mRankSprite->getContentSize().width/2 + 5,mRankSprite->getPositionY()));
    
    mMagicItemLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    mMagicItemLabel->setAnchorPoint(ccp(0,0.5));
    mMagicItemLabel->setPosition(ccp(mMagicItemSprite->getPositionX() + mMagicItemSprite->getContentSize().width/2 + 5,mMagicItemSprite->getPositionY()));
    
    showUserInfo();
 
 
    mIncreaseBetButton->setPositionY(mChipCount->getPositionY());
    mIncreaseBetButton->setPositionX(mChipCount->getPositionX() + mChipCount->getBgSprite1()->getContentSize().width/2 + mIncreaseBetButton->getContentSize().width/2 + 20);
    
    mDecreaseBetButton->setPositionY(mChipCount->getPositionY());
    mDecreaseBetButton->setPositionX(mChipCount->getPositionX() - mChipCount->getBgSprite1()->getContentSize().width/2 - mDecreaseBetButton->getContentSize().width/2 - 20);
    
    dealerSays("请下注。。");
    
    CCSprite *yesBtn1 = CCSprite::createWithSpriteFrameName("gamecenter");
    
    mGlobalChatItem = CCMenuItemSprite::create(yesBtn1, yesBtn1,yesBtn1, this, menu_selector(BlackjackLayer::globalChatClicked));
    mGlobalChat = CCMenu::create(mGlobalChatItem,NULL);
    mGlobalChat->setAnchorPoint(ccp(0,0));
    mGlobalChat->setPosition(10,10);
    mGlobalChat->setOpacity(100);
    mGlobalChatItem->setAnchorPoint(ccp(0,0));
    
    mGlobalChat->setVisible(false);

    
    this->addChild(mGlobalChat);
    
    BroadCast::sharedBroadCast()->addBCToLayer(this);
    

    mInsurance->setVisible(false);
    CCLOG("onSteup");
}

void BlackjackLayer::showUserInfo()
{
    long userCoinAmount = UserInfo::sharedUserInfo()->getGold();
    
    CCString * userCoinString = NULL;
    
    if(userCoinAmount < 99999)
    {
        userCoinString = CCString::createWithFormat("%d",userCoinAmount);
    }
    else if(userCoinAmount < 9999999)
    {
        userCoinString = CCString::createWithFormat("%d 万",userCoinAmount / 10000);
    }
    else
    {
        userCoinString = CCString::createWithFormat("%d 百万",userCoinAmount / 1000000);
    }
    
    mCoinAmountLabel->setString(userCoinString->getCString());
    
    mRankLabel->setString(CCString::createWithFormat("%d",
                UserInfo::sharedUserInfo()->getMedal())->getCString());
    
    mMagicItemLabel->setString(CCString::createWithFormat("%d",UserInfo::sharedUserInfo()->getMagicItemAmount(MagicItem_Switch_ID))->getCString());
    
    // Setup user profile info
    UserInfo::sharedUserInfo()->retrieveAvartaImage(this, callfuncND_selector(BlackjackLayer::getPlayerImage));
}

void BlackjackLayer::setRoomLevelInfo(RoomLevelInfo* RoomLevelInfo)
{
    mRoomLevelInfo = RoomLevelInfo;
    mRoomLevelInfo->retain();
    
    mChipCount->setCount(mRoomLevelInfo->getMinHand());
    mCurrentBet = mRoomLevelInfo->getMinHand();
    
}

void BlackjackLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler BlackjackLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriendsClicked", BlackjackLayer::onFriendsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSettingClicked", BlackjackLayer::onSettingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", BlackjackLayer::onHomeClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRankClicked", BlackjackLayer::onRankClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStart", BlackjackLayer::onStartClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHitCardsClicked", BlackjackLayer::onHitCardsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStandCardsClicked", BlackjackLayer::onStandCardsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSplitCardClicked", BlackjackLayer::onSplitCardClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDoubleClicked", BlackjackLayer::onDoubleClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onIncreaseBetClicked", BlackjackLayer::onIncreaseBetClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDecreaseBetClicked", BlackjackLayer::onDecreaseBetClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMagicToolClicked", BlackjackLayer::onMagicToolClicked);
    
    return NULL;
}

SEL_CCControlHandler BlackjackLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool BlackjackLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIncBetButton", CCMenuItemImage *, mIncreaseBetButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDecBetButton", CCMenuItemImage *, mDecreaseBetButton);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStartMenu", CCMenu *, mStartMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCardMenu", CCMenu *, mCardMenu);
    

    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSplitCardButton", CCMenuItemImage *, mSplitCardBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDoubleButton", CCMenuItemImage *, mDoubleBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHitButton", CCMenuItemImage *, mHitButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStandButton", CCMenuItemImage *, mStandButton);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerHandNode", CCNode *, mPlayerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDealerHandNode", CCNode *, mDealerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerSplitHandNode", CCNode *, mPlayerSplitHandNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerFrameSprite", CCSprite *, mPlayerFrameSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDealerFrameSprite", CCSprite *, mDealerFrameSprite);

    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoinAmountSprite", CCSprite *, mCoinAmountSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRankSprite", CCSprite *, mRankSprite);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMagicItemSprite", CCSprite *, mMagicItemSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMagicTool", CCMenuItemImage *, mMagicTool);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackground", CCSprite *, mBackground);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInsurance", CCSprite *, mInsurance);

    return false;
}

void BlackjackLayer::onHomeClicked(CCObject * pSender)
{
    gotoOtherScene(BackScene);
}

void BlackjackLayer::onFriendsClicked(CCObject * pSender)
{
    gotoOtherScene(Friends_Scene);
}


void BlackjackLayer::onRankClicked(CCObject * pSender)
{
    gotoOtherScene(Rank_Scene);
}

void BlackjackLayer::getPlayerImage(CCNode* node, void* data)
{
    CCSprite* sprite = UserInfo::sharedUserInfo()->addAvartaToLayer(this);
    sprite->setScale(getWinW()*0.2f/sprite->getContentSize().width);
    sprite->setPosition(mPlayerFrameSprite->getPosition());
    sprite->setAnchorPoint(ccp(0,0.5));
    mPlayerFrameSprite->setVisible(false);
}

void BlackjackLayer::getDealerImage(bool isBoss)
{
    if(mDealerImageSprite && mDealerImageSprite->getParent())
    {
        mDealerImageSprite->removeFromParentAndCleanup(true);
    }
    
    CCString * dealerImage = NULL;
    CCString * dealerNM = NULL;
    
    int dealerIndex = arc4random() % 16 + 1;
    if(isBoss || BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle)
    {
        dealerNM = CCString::create(BattleInfo::sharedBattleInfo()->getRaidBoss()->getOnlineBossName());
    }
    else
    {
        dealerImage = CCString::createWithFormat("Dealer%d",dealerIndex);
        dealerNM = CCString::createWithFormat("荷官 %d",dealerIndex);
    }
    
    
    if(dealerName)
    {
        dealerName->setString(dealerNM->getCString());
    }
    else
    {
        dealerName = CCLabelTTF::create(dealerNM->getCString(), "Helvetica", 12);
        
        dealerName->setAnchorPoint(ccp(0.5,0.5));
        
        this->addChild(dealerName);
    }
    
    if(isBoss || BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle)
    {
        std::string bossImageUrl = BattleInfo::sharedBattleInfo()->getRaidBoss()->getOnlineBossImageUrl();
        if(bossImageUrl.length() < 3)
        {
            showBossImage(CCSprite::createWithSpriteFrameName(BattleInfo::sharedBattleInfo()->getRaidBoss()->getOnlineBossImageUrl().c_str()));
        }
        else
        {
            ImageController * imageController = new ImageController();
            imageController->retrieveAvartaImage(bossImageUrl, this, callfuncO_selector(BlackjackLayer::showBossImage));
        }
    }
    else
    {
        showBossImage(CCSprite::createWithSpriteFrameName(dealerImage->getCString()));
    }
    
    
}

void BlackjackLayer::showBossImage(cocos2d::CCObject *data)
{
    if(data)
    {
        mDealerImageSprite = (CCSprite *) data;
        
        
        float imageScale = getWinW()*0.2f/mDealerImageSprite->getContentSize().width;

        mDealerImageSprite->setAnchorPoint(ccp(1,0.5));
        mDealerImageSprite->setScale(imageScale);
        mDealerImageSprite->setPosition(mDealerFrameSprite->getPosition());
        
        if (dealerName) {
            dealerName->cocos2d::CCNode::setAnchorPoint(ccp(0.5,0.5));
            dealerName->setPosition(ccp(mDealerImageSprite->getPositionX() - mDealerImageSprite->getContentSize().width * imageScale/2,
            mDealerImageSprite->getPositionY() - mDealerImageSprite->getContentSize().height * imageScale/2 - dealerName->getContentSize().height/2 - 5));
        }
        
        this->addChild(mDealerImageSprite);
        
        mDealerWords->setAnchorPoint(ccp(0.5,0.5));
        mDealerWords->setPosition(ccp(mDealerImageSprite->getPositionX() - mDealerImageSprite->getContentSize().width * imageScale - mDealerWords->getBgSprite1()->getContentSize().width * mDealerWords->getBgSprite1()->getScaleX()/2,
            mDealerImageSprite->getPositionY()
            ));
    }
}


void BlackjackLayer::onSettingClicked(CCObject * pSender)
{
    gotoOtherScene(Setting_Scene);
}

void BlackjackLayer::onIncreaseBetClicked(CCObject *pSender)
{
    if(((mCurrentBet + mRoomLevelInfo->getMinHand() ) <=
    mRoomLevelInfo->getMaxHand() ||  mRoomLevelInfo->getMaxHand() == 0)&&
    (mCurrentBet + mRoomLevelInfo->getMinHand() ) <=
    UserInfo::sharedUserInfo()->getGold()
    )
    {
        mCurrentBet = mCurrentBet + mRoomLevelInfo->getMinHand();
        mChipCount->setCount(mCurrentBet);
    }
}

void BlackjackLayer::onDecreaseBetClicked(CCObject *pSender)
{
    if((mCurrentBet - mRoomLevelInfo->getMinHand() ) >=
    mRoomLevelInfo->getMinHand())
    {
        mCurrentBet = mCurrentBet - mRoomLevelInfo->getMinHand();
        mChipCount->setCount(mCurrentBet);
    }
}

void BlackjackLayer::setHideButton(CCNode* node)
{
    node->setVisible(false);
}

void BlackjackLayer::hideButton(CCNode* node)
{
    if (node==NULL) {
        return;
    }
    
    node->runAction(CCSequence::create(
                            CCSpawn::create(
                                CCScaleTo::create(HideButtonTime, 0.1),
                               CCFadeOut::create(HideButtonTime),
                                    NULL),
                           CCCallFuncN::create(this, callfuncN_selector(BlackjackLayer::setHideButton)),
                           NULL));
}

void BlackjackLayer::showStartButton()
{
    if (mStartMenu==NULL) {
        return;
    }
    
    mStartMenu->setVisible(true);
    mStartMenu->setScale(0.1);
    mStartMenu->runAction(CCSpawn::create(
                                    CCScaleTo::create(HideButtonTime, 1.0),
                                    CCFadeIn::create(HideButtonTime),
                                    NULL));
    
    mChipCount->setPositionY(mChipCount->getPositionY() - 60);
    mChipCount->setVisible(true);
    
    mCurrentBet = MIN(mCurrentBet,mRoomLevelInfo->getMaxHand() == 0? mCurrentBet : mRoomLevelInfo->getMaxHand());
    mChipCount->setCount(mCurrentBet);
    
    mIncreaseBetButton->setVisible(true);
    mDecreaseBetButton->setVisible(true);
    dealerSays("请下注。。");
}

void BlackjackLayer::showHitStandButton()
{
    if (mCardMenu==NULL) {
        return;
    }
    
    mCardMenu->setVisible(true);
    mHitButton->setVisible(true);
    mStandButton->setVisible(true);
    mCardMenu->setScale(0.1);
    mCardMenu->runAction(CCSpawn::create(
                                          CCScaleTo::create(HideButtonTime, 1.0),
                                          CCFadeIn::create(HideButtonTime),
 
                                         NULL));
}

void BlackjackLayer::onStartClicked(CCObject * pSender)
{
    if(UserInfo::sharedUserInfo()->getGold() < mCurrentBet)
    {
        AlertLayer * shareAlert = AlertLayer::create("21点", "您金币不足，请去兑换", true, this, (SEL_CallFuncND)callfuncND_selector(BlackjackLayer::gotoShop));
        this->addChild(shareAlert, Child_Order_Top);
    }
    else
    {
        // Clear the hand before starting a new game:
        mPlayerHand->clearHand();
        mDealerHand->clearHand();
        mPlayerSplitHand->clearHand();

        
        CardDeck::sharedCardDeck()->shuffleCardDeck();
        if(GameInfo::sharedGameInfo()->getEnv() == Standalone)
        {
            startGame();
        }
        else
        {
            startOnlineBattle();
        }
    }
}

void BlackjackLayer::showInsuranceRequirement()
{
    AlertLayer * shareAlert = AlertLayer::create("21点", "庄家可能是Blackjack，需要保险吗？", true, this, (SEL_CallFuncND)callfuncND_selector(BlackjackLayer::setInsurance));
    this->addChild(shareAlert, Child_Order_Top);
}

// Hit.
void BlackjackLayer::onHitCardsClicked()
{
    if (!mHitAllowed) {
        return;
    }
    
    if (mDoubleAllowed || mSplitCardBtn) {
        hideSplitDoubleButtons();
    }
    
    mHitAllowed	= false;
    mStandAllowed = false;
    
    // Split the first hand in split mode
    if (mIsSplitting) {
        if (mIsPlayingFirstSplit) {
            if(mPlayerHand->getCardCount() < 21)
            {
                mPlayerHand->addNextCardToHand(false, 0.2, this, callfunc_selector(BlackjackLayer::notifyPlayerHitDone));
            }
        } else {
            if(mPlayerSplitHand->getCardCount() < 21)
            {
                // Add another card for the player:
                mPlayerSplitHand->addNextCardToHand(false, 0.2, this, callfunc_selector(BlackjackLayer::notifyPlayerHitDone));
                
            }
        }
    }
    else
    {
        if(mPlayerHand->getCardCount() < 21)
        {
            mPlayerHand->addNextCardToHand(false, 0.2, this, callfunc_selector(BlackjackLayer::notifyPlayerHitDone));
        }
    }
}

// Stand cards.
void BlackjackLayer::onStandCardsClicked()
{
    if(!mStandAllowed)
        return;
    
    // No other actions are allowed:
    if (mDoubleAllowed || mSplitCardBtn) {
        hideSplitDoubleButtons();
    }
    
    // See if the player is either not splitting or has played the second hand already:
    if (mIsSplitting == false)
    {
        // The player is not allowed to hit, stand, split or double down now:
        mHitAllowed = false;
        mStandAllowed = false;
        
        // Flip the dealer's hole card:
        mDealerHand->flipCards();
        
//        // If the player is splitting cards, move the main hand back into a more normal position:
//        mPlayerHand->startSwitchingMotion(0.0,								// delta X
//                                      0.0,								// delta Y
//                                      100,                              // target depth
//                                      100,                              // target depth
//                                      0.8,								// target scale
//                                      1.0,								// target darkening
//                                      0.2);								// movement time (ms)
    } else {
        if (mIsPlayingFirstSplit) {
            this->switchHandPosition();
            mIsPlayingFirstSplit = false;
            
            return;
        } else {
            // The player is not allowed to hit, stand, split or double down now:
            mHitAllowed = false;
            mStandAllowed = false;
            
            // Flip the dealer's hole card:
            mDealerHand->flipCards();
        }
    }
    
    this->hideButton(mCardMenu);
    
    this->scheduleOnce(schedule_selector(BlackjackLayer::notifyDealerToAddNextCard), 0.3);
    
    mMagicTool->setVisible(false);
}

void BlackjackLayer::onSplitCardClicked()
{
    //After Split, no Double allowed
    hideSplitDoubleButtons();
    
    // Do split
    PlayCard* card = mPlayerHand->getSplitCard();
    
    mPlayerSplitHand->setVisible(true);
    mPlayerSplitHand->addCardToHand(card->getCardSuit(), card->getCardType(), false, 0);
    
    int h = getContentSize().height/8;
    mPlayerSplitHand->runAction(CCSpawn::create(
                                        CCMoveBy::create(0.5, ccp(0, -h)),
                                        NULL
                                ));
    
    mPlayerHandNode->getParent()->reorderChild(mPlayerHandNode, 100);
    mPlayerSplitHandNode->getParent()->reorderChild(mPlayerSplitHandNode, 80);
    
    mPlayerHand->popLastCard();
    mPlayerHand->addNextCardToHand(false, 0.2);
    mPlayerHand->runAction(CCSpawn::create(
                                        CCMoveBy::create(0.5, ccp(0, h)),
                                        NULL
                                        ));
    
    // Split is done, in split mode
    mIsSplitting = true;
    mIsPlayingFirstSplit = true;
}

void BlackjackLayer::onDoubleClicked()
{
    hideSplitDoubleButtons();
    
    mCurrentBet = mCurrentBet * 2;
    // Do double
    mChipCount->setCount(mCurrentBet);
    
    // Hit automatically
    onHitCardsClicked();
    
    // Double is done, in double mode
    mIsDoublingDown = true;
}

void BlackjackLayer::hideSplitDoubleButtons()
{
    if (mDoubleAllowed) {
        mDoubleBtn->runAction(CCSequence::create(
                                                 CCDelayTime::create(HideButtonTime*0.25),
                                                 CCSpawn::create(
                                                                 CCMoveTo::create(HideButtonTime*0.75, ccp(mDoubleBtn->getContentSize().width + getWinW(), mDoubleBtn->getPosition().y)),
                                                                 CCFadeOut::create(HideButtonTime*0.75),
                                                                 NULL),
                                                 NULL));
        mDoubleAllowed = false;
    }
    
    if (mSplitAllowed) {
        mSplitCardBtn->runAction(CCSequence::create(
                                                    CCDelayTime::create(HideButtonTime*0.25),
                                                    CCSpawn::create(
                                                                    CCMoveTo::create(HideButtonTime*0.75, ccp(mSplitCardBtn->getContentSize().width + getWinW(), mSplitCardBtn->getPosition().y)),
                                                                    CCFadeOut::create(HideButtonTime*0.75),
                                                                    NULL),
                                                    NULL));
        mSplitAllowed = false;
    }
}

void BlackjackLayer::switchHandZPostion()
{
    mPlayerHandNode->getParent()->reorderChild(mPlayerHandNode, 80);
    mPlayerSplitHandNode->getParent()->reorderChild(mPlayerSplitHandNode, 100);
}

void BlackjackLayer::switchHandPosition()
{    
    int h = getContentSize().height/8;
    
    mPlayerSplitHand->runAction(CCSequence::create(
                                               CCMoveBy::create(0.2, ccp(0, h*-0.5)),
                                               CCCallFunc::create(this, callfunc_selector(BlackjackLayer::switchHandZPostion)),
                                               CCMoveBy::create(0.3, ccp(0, h*1.9)),
                                               CCCallFunc::create(this, callfunc_selector(BlackjackLayer::onHitCardsClicked)),
                                               NULL
                                               ));

}

void BlackjackLayer::notifyPlayerHitDone()
{
    mHitAllowed = true;
    mStandAllowed = true;
    
    if(BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle)
    {
        if (mIsSplitting)
        {
            if((mPlayerHand->getNumberOfCards() > 2 && mIsPlayingFirstSplit) ||
            (!mIsPlayingFirstSplit && mPlayerSplitHand->getNumberOfCards() > 2))
            {
                showMagicTool();
            }
            
            if((mIsPlayingFirstSplit && mPlayerHand->getCardCount()>21) ||
                (!mIsPlayingFirstSplit && mPlayerSplitHand->getCardCount()>21))
            {
                mHitButton->setVisible(false);
            }
        }
        else
        {
            if(mPlayerHand->getNumberOfCards() > 2)
            {
                showMagicTool();
            }
            
            if(mPlayerHand->getCardCount()>21)
            {
                mHitButton->setVisible(false);
            }

            if ((mPlayerHand->getNumberOfCards()>2 && mIsDoublingDown) || mPlayerHand->getCardCount() == 21)
           {
                onStandCardsClicked();
               return;
           }
        }
    }
    else
    {
        if (mIsSplitting) {
            if ((mIsPlayingFirstSplit && mPlayerHand->getCardCount()>=21) ||
                (!mIsPlayingFirstSplit && mPlayerSplitHand->getCardCount()>=21)) {
                onStandCardsClicked();
                return;
            }
        } else {
           if ((mPlayerHand->getNumberOfCards()>2 && mIsDoublingDown) || mPlayerHand->getCardCount() >= 21)
           {
                onStandCardsClicked();
               return;
           }
        }
    }
}

void BlackjackLayer::notifyDealerHitDone()
{
    if(mHitAllowed && mPlayerHand->getNumberOfCards() == 2)
    {
        //No insurance
        if (mDealerHand->getCard(1)->getCardType() == Ace && needInsurance)
        {
            this->showInsuranceRequirement();
        }
    }
}

void BlackjackLayer::notifyDealerToAddNextCard()
{
    if(mPlayerHand->getCardCount() >= 21)
    {
        showResult();
    } else if(! mDealerHand->getDealerWouldHit())
    {
        showResult();
    }
    else
    {
        mDealerHand->addNextCardToHand(false, 0.3, this, callfunc_selector(BlackjackLayer::notifyDealerToAddNextCard));
    }
}

void BlackjackLayer::showResult()
{
//    int dealerCount, playerCount, playerSplitCount;
//
//    dealerCount = mDealerHand->getCardCount();
//    playerCount = mPlayerHand->getCardCount();
////    playerSplitCount = mPlayerSplitHand->getCardCount();
    
    ResultType type1, type2;
    int w = getWinW();
    int h = getWinH();
    int menuH = 0;
    int notifyH = TopHeight;
    int tmpH = (h-menuH-notifyH)/2 + menuH;
    
    if (!mIsSplitting) {
        // Unsplit mode
        type1 = checkResult(mPlayerHand, mDealerHand);
        
        mPlayerResult->setType(type1);
        
        mPlayerResult->setPosition(ccp(w/2, -mPlayerResult->getContentSize().height/2));
        mPlayerResult->runAction(CCSequence::create(
                                                    CCSpawn::create(CCFadeIn::create(0.3),
                                                                    CCMoveTo::create(0.3, ccp(w/2, tmpH)),
                                                                    NULL),
                                                    CCDelayTime::create(1.0),
                                                    CCSpawn::create(CCFadeOut::create(0.3),
                                                                    CCMoveTo::create(0.3, ccp(w/2, -mPlayerResult->getContentSize().height*2)),
                                                                    NULL),
                                                    CCCallFunc::create(this, callfunc_selector(BlackjackLayer::showStartButton)),
                                                    NULL));
        
        this->beforeUploadResult(calcMatchResult(type1), (type1 == BJ)?1:0);
        
        
    } else {
        // Split mode
        type1 = checkResult(mPlayerHand, mDealerHand);
        type2 = checkResult(mPlayerSplitHand, mDealerHand);
        
        mPlayerResult->setType(type1);
        mPlayerSplitResult->setType(type2);
        
        mPlayerResult->setPosition(ccp(w/2, -mPlayerResult->getContentSize().height/2));
        mPlayerSplitResult->setPosition(ccp(w/2, -mPlayerResult->getContentSize().height-mPlayerSplitResult->getContentSize().height/2));
        mPlayerResult->runAction(CCSequence::create(
                                                    CCSpawn::create(CCFadeIn::create(0.3),
                                                                    CCMoveTo::create(0.3, ccp(w/2, tmpH)),
                                                                    NULL),
                                                    CCDelayTime::create(1),
                                                    CCSpawn::create(CCFadeOut::create(0.3),
                                                                    CCMoveTo::create(0.3, ccp(w/2, -mPlayerResult->getContentSize().height*2)),
                                                                    NULL),
                                                    NULL));
        
        mPlayerSplitResult->runAction(CCSequence::create(
                                                    CCSpawn::create(CCFadeIn::create(0.3),
                                                                    CCMoveTo::create(0.3, ccp(w/2, tmpH-mPlayerResult->getContentSize().height/2-mPlayerSplitResult->getContentSize().height/2)),
                                                                    NULL),
                                                    CCDelayTime::create(1),
                                                    CCSpawn::create(CCFadeOut::create(0.3),
                                                                    CCMoveTo::create(0.3, ccp(w/2, -mPlayerResult->getContentSize().height-mPlayerSplitResult->getContentSize().height*2)),
                                                                    NULL),
                                                    CCCallFunc::create(this, callfunc_selector(BlackjackLayer::showStartButton)),
                                                    NULL));
        
        this->beforeUploadResult(calcMatchResult(type1) + calcMatchResult(type2),((type1 == BJ)?1:0) + ((type2 == BJ)?1:0) );
    }
}

ResultType BlackjackLayer::checkResult(PlayCardHand * playerHand, PlayCardHand * dealerHand)
{
    ResultType type = Lose;
//    dealerHand->hasBlackjack();
    
    if (playerHand->getCardCount() >21) {
            type = Lose;
    } else if (playerHand->hasBlackjack())
    {
        if(dealerHand->hasBlackjack())
        {
            type = Equal;
        }
        else
        {
            type = BJ;
        }
    }
    else if(playerHand->getCardCount() == 21)
    {
        if(dealerHand->getCardCount() == 21)
        {
            type = Equal;
        }
        else
        {
            type = Win;
        }

    } else {
        if (dealerHand->getCardCount() > 21 || dealerHand->getCardCount() < playerHand->getCardCount())
        {
            type = Win;
            
        } else if (dealerHand->getCardCount() > playerHand->getCardCount()){
            type = Lose;
            
        } else {
            type = Equal;
        }
    }
    
    return type;
}

void BlackjackLayer::dealerSays(std::string words)
{
    mDealerWords->setText(words);
    
    mDealerWords->setVisible(true);
}

float BlackjackLayer::calcMatchResult(ResultType type)
{
    long coinChange = 0;
    int  isWinLoseEqual = 0;
    long result = 0;
    
    switch (type) {
      case Win:
        coinChange = mCurrentBet;
        isWinLoseEqual = 1;
//        [[GameKitFactory sharedGameKitFactory] submitScore:LeaderBoard_BlackjackWinner :coinChange];
//        [[GameKitFactory sharedGameKitFactory] submitAchievement:Achievement_Blackjack_FirstWin :100];
        
        break;
        
        case Lose:
        //Because hasInsurance, if Dealer has BJ, only insuranceAmount lost
        //insuranceAmount will be cost in func "uploadMatchResult"
        if(hasInsurance && mDealerHand->hasBlackjack())
        {
            coinChange = 0;
        }
        else
        {
            coinChange = mCurrentBet;
        }
        isWinLoseEqual = -1;
        break;
        
        case Equal:
        isWinLoseEqual = 0;
        break;
        
        case BJ:
        coinChange = mCurrentBet * 1.5;
        isWinLoseEqual = 1;
//        [[GameKitFactory sharedGameKitFactory] submitScore:LeaderBoard_BlackjackWinner :coinChange];
//        [[GameKitFactory sharedGameKitFactory] submitAchievement:Achievement_Blackjack_FirstWin :100];
        break;
    }
    
    std::string wavName = "";
    switch (type)
    {
        case Win:
        wavName = "cheer.mp3";
        break;
        
        case Lose:
        wavName = "Loser.wav";
        break;
        
        case BJ:
        wavName = "BJ.mp3";
        break;
    
    }
    
    if(wavName.length() > 3)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(wavName.c_str());
    }

    result = isWinLoseEqual * coinChange;
    
    return result;
}



void BlackjackLayer::beforeUploadResult(float result, int isBlackJack)
{
    isInBattle = false;

    finalBlackJack = isBlackJack;
    
    if(hasInsurance)
    {
        result = result - mInsuranceAmount;
    }
    
    if (result >0 && BattleInfo::sharedBattleInfo()->getBattleType() != BossBattle && needBigSmall)
    {
        BigSmallLayer::sharedBigSmallLayer(result)->addBigSmallToLayer(this,this, callfuncND_selector(BlackjackLayer::uploadMatchResult));
    }
    else
    {
        uploadMatchResult(NULL, (void*) (long)result);
    }
}

void BlackjackLayer::uploadMatchResult(CCNode* pSender, void* data)
{
    long finalResult = (long)data;
    GameServerAction::sharedGameServerAction()->endBattle(finalResult, finalBlackJack, mRoomLevelInfo->getRoomLevel() , this, callfuncND_selector(BlackjackLayer::uploadMatchResult_Done));
}

void BlackjackLayer::uploadMatchResult_Done(CCNode* pSender, void* data)
{
    if((bool)data)
    {
        showUserInfo();
                
        if(BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle)
        {
            CCString * msg = NULL;
            bool needCancel = false;
            RaidBossInfo * bossInfo = BattleInfo::sharedBattleInfo()->getRaidBoss();
            mRaidBossGold->setString(CCString::createWithFormat("%d",BattleInfo::sharedBattleInfo()->getRaidBoss()->getCurrentHP())->getCString());
            
            std::string bossName = bossInfo->getOnlineBossName();
            
            AlertLayer * shareAlert =NULL;
            
            switch (bossInfo->getStatus()) {
                  case BossStatus_Active:
                     //Just not support share boss now -- 2013.8.14 Banson
//                    msg = CCString::createWithFormat("%s 还有%d，找朋友来帮忙吧！",bossName.c_str(), bossInfo->getCurrentHP());
//                    needCancel = true;
//                    if(!hasSharedBoss)
//                    {
//                        shareAlert = AlertLayer::create("赌神通缉令",msg->getCString() , needCancel, this, callfuncND_selector(BlackjackLayer::shareBoss));
//                    }
                    
                    break;

                  case BossStatus_End:
                  {
                    msg = CCString::createWithFormat("%s 已经被打败了！\r你获得了 %d 块优胜奖牌！", bossName.c_str(), bossInfo->getBossReward());
                    
                    
                    shareAlert = AlertLayer::create("赌神通缉令",msg->getCString() , needCancel, NULL, NULL);
                    
                    //Share weibo
                    NSString * value = [[NSString alloc] initWithFormat:@"祝贺 %s 打败了 %s，获得了 %d 块优胜奖牌！", UserInfo::sharedUserInfo()->getUserName().c_str() ,bossName.c_str(), bossInfo->getBossReward() ];
    
                    [[WeiboFactory sharedWeiboFactory] uploadStatus:value];
                    
                    bossInfo->release();
                    BattleInfo::sharedBattleInfo()->setRaidBoss(NULL);
                    
                    break;
                   }
                  case BossStatus_Escape:
                    msg = CCString::createWithFormat("%s 已经逃跑了！", bossName.c_str());
                    bossInfo->release();
                    BattleInfo::sharedBattleInfo()->setRaidBoss(NULL);
                    shareAlert = AlertLayer::create("赌神通缉令",msg->getCString() , needCancel, NULL, NULL);
                    break;
                }
            
            if(shareAlert)
            {
                this->addChild(shareAlert, Child_Order_Top);
            }
        }
    }
    else
    {
        
        NSString * msg = @"非常抱歉，服务器未能正常处理该次牌局的结果.";
        
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"BlackJack"
                                message:msg
                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

        [alerView show];
        [alerView release];
    }
    
}

void BlackjackLayer::onMagicToolClicked()
{
    
    AlertLayer * shareAlert =NULL;
    shareAlert = AlertLayer::create("魔法道具",CCString::createWithFormat("消耗 %d 个魔法道具，可以更换最后一张牌！",  mMagicToolTimes)->getCString() , true, this, callfuncND_selector( BlackjackLayer::requestMagicItem));
    
    this->addChild(shareAlert, Child_Order_Top);

    
}

void BlackjackLayer::requestMagicItem(CCNode *pSender, void *data)
{
    //mMagicToolTimes
    if(mMagicToolTimes > UserInfo::sharedUserInfo()->getMagicItemAmount(MagicItem_Switch_ID))
    {
        AlertLayer * shareAlert = AlertLayer::create("21点", "大侠，道具不够，买几个吧！", true, this, (SEL_CallFuncND)callfuncND_selector(BlackjackLayer::gotoShop));
        this->addChild(shareAlert, Child_Order_Top);
    }
    else
    {
        GameServerAction::sharedGameServerAction()->useMagicItem(MagicItem_Switch_ID, mMagicToolTimes, this, callfuncND_selector(BlackjackLayer::useMagicItem));
    }
}

void BlackjackLayer::useMagicItem(CCNode *pSender, void *data)
{
    if((bool)data)
    {
        showUserInfo();
        
        
        // See if the player is either not splitting or has played the second hand already:
        if (!mIsSplitting || mIsPlayingFirstSplit)
        {
            CCLog("Current count:%d",mPlayerHand->getCardCount());
            mPlayerHand->removeLastCard();
        } else{
            CCLog("Current count:%d",mPlayerSplitHand->getCardCount());
            mPlayerSplitHand->removeLastCard();
        }

        onHitCardsClicked();
        
        mMagicToolTimes++;
        
    }
}

void BlackjackLayer::showMagicTool()
{
    mMagicTool->setVisible(true);
    mMagicTool->setEnabled(true);
}

void BlackjackLayer::startOnlineBattle()
{
    Loading::sharedLoading()->addLoadingToLayer(this,10);
    if(BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle && BattleInfo::sharedBattleInfo()->getRaidBoss())
    {
        GameServerAction::sharedGameServerAction()->startBattle(BlackJack,BossBattle,mCurrentBet,mRoomLevelInfo->getRoomLevel(),
        this, callfuncND_selector(BlackjackLayer::startOnlineBattle_done));
    }
    else
    {
        GameServerAction::sharedGameServerAction()->startBattle(BlackJack,SingleBattle,mCurrentBet,mRoomLevelInfo->getRoomLevel(),
        this, callfuncND_selector(BlackjackLayer::startOnlineBattle_done));
    }
}

void BlackjackLayer::startOnlineBattle_done(CCNode* pSender, void* data)
{
    if((bool)data)
    {
        if(BattleInfo::sharedBattleInfo()->getBattleID() == 0 && BattleInfo::sharedBattleInfo()->getRaidBoss())
        {
            CCString * msg = NULL;
            bool needCancel = false;
            RaidBossInfo * bossInfo = BattleInfo::sharedBattleInfo()->getRaidBoss();
            mRaidBossGold->setString(CCString::createWithFormat("%d",BattleInfo::sharedBattleInfo()->getRaidBoss()->getCurrentHP())->getCString());
            
            std::string bossName = bossInfo->getOnlineBossName();
            
            switch (bossInfo->getStatus()) {
//                  case BossStatus_Active:
//                    msg = CCString::createWithFormat("%s 还有%d，找朋友来帮忙吧！",bossName.c_str(), bossInfo->getCurrentHP());
//                    needCancel = true;
//                    break;

                  case BossStatus_End:
                    msg = CCString::createWithFormat("%s 已经被打败了！", bossName.c_str());
                    bossInfo->release();
                    BattleInfo::sharedBattleInfo()->setRaidBoss(NULL);
                    break;
                    
                  case BossStatus_Escape:
                    msg = CCString::createWithFormat("%s 已经逃跑了！", bossName.c_str());
                    bossInfo->release();
                    BattleInfo::sharedBattleInfo()->setRaidBoss(NULL);
                    break;
                }
            
            bossInfo->release();
            BattleInfo::sharedBattleInfo()->setRaidBoss(NULL);
            Loading::sharedLoading()->removeLoading();
            
            AlertLayer * shareAlert =NULL;
            shareAlert = AlertLayer::create("赌神通缉令",msg->getCString() , needCancel, NULL, NULL);
            this->addChild(shareAlert, Child_Order_Top);
            return;
        }
        
        if(BattleInfo::sharedBattleInfo()->getBattleType() == BossBattle)
        {
            if(!   isRaidBoss)
            {
                getDealerImage(true);
                mRaidBossGold->setPositionX(dealerName->getPositionX());
                mRaidBossGold->setPositionY(dealerName->getPositionY() - dealerName->getContentSize().height/2 - mRaidBossGold->getContentSize().height - 5);
                mRaidBossGold->setString(CCString::createWithFormat("%d",BattleInfo::sharedBattleInfo()->getRaidBoss()->getCurrentHP())->getCString());
                mRaidBossGold->setVisible(true);
                
                
                
                if(mBossWord == NULL)
                {
                    mBossWord = CCSprite::createWithSpriteFrameName("art_boss_chuxian_001");
                    this->addChild(mBossWord, Child_Order_Top);
                }
                mBossWord->setPosition(ccp(getWinW() + mBossWord->getContentSize().width/2, getWinH()/2));
                mBossWord->setVisible(true);
                
                mBossWord->runAction(CCSequence::create(
                                    CCMoveTo::create(0.5, ccp(getWinW()/2,getWinH()/2)),
                                    CCBlink::create(0.5, 3),
                                    CCFadeOut::create(2),
                                    CCMoveTo::create(0.1, ccp(getWinW() + mBossWord->getContentSize().width/2,getWinH()/2)),
                                    CCFadeIn::create(0.1),
                                    NULL));
                
                if(mBossBackground == NULL)
                {
                    mBossBackground = CCSprite::createWithSpriteFrameName("Game_BK_Blue");
                    this->addChild(mBossBackground, -100);
                }
                
                mBackground->setVisible(false);
                mBossBackground->setVisible(true);
                mBossBackground->setAnchorPoint(ccp(0,0));
                mBossBackground->setPosition(mBackground->getPosition());
            }
            isRaidBoss = true;
        }
        else
        {
            if(isRaidBoss)
            {
                getDealerImage(false);
                mRaidBossGold->setVisible(false);
                if(mBossBackground)
                {
                    mBackground->setVisible(false);
                }
                mBackground->setVisible(true);
            }
            
            isRaidBoss = false;
            hasSharedBoss = false;
        }
        
        UserInfo::sharedUserInfo()->setGold(UserInfo::sharedUserInfo()->getGold() - mCurrentBet);
        showUserInfo();
        startGame();
    }
    else
    {
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"BlackJack"
                                message:@"大侠，网络不给力请重试！"
                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

        [alerView show];
        [alerView release];
        Loading::sharedLoading()->removeLoading();
    }
    
}

void BlackjackLayer::startGame()
{

    isInBattle = true;
    int w = getContentSize().width;
    int h = 480;//getContentSize().height;
    int menuH = 0;
    int notifyH = TopHeight;
    int tmpH = (h-menuH-notifyH)/2 + menuH;
    int handH = h/3;
    
        
    // Add first two cards to player hand
    mPlayerHand->addNextCardToHand(false,0);
//    mPlayerHand->addNextCardToHand(false,0.2,this,callfunc_selector(BlackjackLayer::notifyPlayerHitDone));
    mPlayerHand->addNextCardToHand(false,0.2);
    
    // Add first two cards to dealer hand
    mDealerHand->addNextCardToHand(true,0.2);
//    mDealerHand->addNextCardToHand(false,0.3,this,callfunc_selector(BlackjackLayer::notifyDealerHitDone));
    mDealerHand->addNextCardToHand(false,0.3);
    
    mDealerHand->setPosition(ccp(w/2, h-100- mDealerHand->getCard(0)->getCardHeight()/2));
    mPlayerHand->setPosition(ccp(w/2, tmpH - handH));
    mPlayerSplitHand->setPosition(ccp(w/2, tmpH - handH));
    
    
    // Set player & dealer hand visible
    mPlayerHand->setVisible(true);
    mDealerHand->setVisible(true);
    
    
    // Set split hand invisible
    mPlayerSplitHand->setVisible(false);
    
    
    mChipCount->setCount(mCurrentBet);
    
    mChipCount->setPositionY(mChipCount->getPositionY() + 60);
    
    mIncreaseBetButton->setVisible(false);
    mDecreaseBetButton->setVisible(false);

    mDealerWords->setVisible(false);
    
    // Hide start menu
    this->hideButton(mStartMenu);
    
    // Show hit/stand menu
    this->showHitStandButton();
    
    // Set game status
    mHitAllowed = true;
    mSplitAllowed = true;
    mIsSplitting = false;
    mIsPlayingFirstSplit = true;
    mDoubleAllowed = true;
    mIsDoublingDown = false;
    
    mMagicToolTimes = 1;
    
    //Set Insurance disable
    hasInsurance = false;
    mInsurance->setVisible(false);
    mInsuranceAmount = 0;
    
    
    // show split button if first two cards are same
    if (mPlayerHand->canSplitCards()) {
        mSplitCardBtn->setVisible(true);
        mSplitCardBtn->setPosition(ccp(mSplitCardBtn->getContentSize().width + getWinW(), mSplitCardBtn->getPosition().y));
        mSplitCardBtn->runAction(CCSpawn::create(
                                             CCMoveTo::create(HideButtonTime, ccp(mHitButton->getPositionX(), mSplitCardBtn->getPosition().y)),
                                             CCFadeIn::create(HideButtonTime),
                                             NULL));
        
        
    }
    
    // show double button if have two cards
    if (mPlayerHand->getNumberOfCards()==2 && UserInfo::sharedUserInfo()->getGold() >= mCurrentBet * 2) {
        mDoubleBtn->setVisible(true);

        mDoubleBtn->setPosition(ccp(mDoubleBtn->getContentSize().width + getWinW(), mDoubleBtn->getPosition().y));
        mDoubleBtn->runAction(CCSpawn::create(
                                          CCMoveTo::create(HideButtonTime, ccp(mHitButton->getPositionX(), mDoubleBtn->getPosition().y)),
                                          CCFadeIn::create(HideButtonTime),
                                          NULL));
    }
    
    Loading::sharedLoading()->removeLoading();
    
    this->notifyPlayerHitDone();
    this->notifyDealerHitDone();
    
    if(!mPlayerHand->hasBlackjack() && mDealerHand->getCard(1)->getCardType() != 1)
    {
        friendSupport();
    }
}

void BlackjackLayer::globalChatClicked()
{
    ChatLayer * wbLayer = ChatLayer::sharedChatLayer();
    wbLayer->addChatToLayer(this);
}

void BlackjackLayer::shareBoss(cocos2d::CCNode *pSender, void *data)
{
    if((bool)data)
    {
       
        hasSharedBoss = true;
        GameServerAction::sharedGameServerAction()->shareBoss(BattleInfo::sharedBattleInfo()->getRaidBoss()->getBossInstance(), this, callfuncO_selector(BlackjackLayer::shareBoss_Done));
    }
    else
    {
    
    
    }
}

void BlackjackLayer::shareBoss_Done(CCObject* data)
{
    if(data)
    {
        //CCDictionary * dic = ()
    }
    else
    {
        
    
    }
}

void BlackjackLayer::gotoOtherScene(GameScene otherScene)
{
    if(isInBattle && otherScene == BackScene)
    {
        SceneControler::sharedSceneControler()->gotoSceneWithAlert(otherScene, "21点", "您已经在牌局中，现在离开无法收回已下注的金币。\r\n确定要离开吗？", this);
    }
    else
    {
        SceneControler::sharedSceneControler()->gotoScene(otherScene);
    }
}

void BlackjackLayer::setInsurance(cocos2d::CCNode *pSender, void *data)
{
    if((bool)data)
    {
        
        hasInsurance = true;
        mInsurance->setVisible(true);
        mInsuranceAmount = mCurrentBet / 2;
        CCLOG("Set Insurance: %d", mInsuranceAmount);
    }
    
    if(mDealerHand->hasBlackjack())
    {
        onStandCardsClicked();
    }
}

void BlackjackLayer::friendSupport()
{
    int supportRand = arc4random() % 100 + 1;
    
    int friendsCount = UserInfo::sharedUserInfo()->getFriendsList()->count();
    
    int friendSupportValue = FriendSupportRate + friendsCount;
    
    friendSupportValue = (friendSupportValue > 40)?40:friendSupportValue;
    
    if(supportRand < friendSupportValue)
    {
        hadFriendSupport = true;
        
        CCSprite * friendSprite = CCSprite::createWithSpriteFrameName("bet_blue");
        friendSprite->setAnchorPoint(ccp(0,0.5));
        friendSprite->setPosition(ccp(getWinW(),getWinH()/2));
        
        CCSprite * friendHead = NULL;
        CCLabelTTF *cellNameLabel = CCLabelTTF::create("", "Arial", 18, CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        cellNameLabel->setAnchorPoint(ccp(0,0));

        if(friendsCount > 0)
        {
            int friendIndex = arc4random() % friendsCount;
            SimpleUserInfo * friendInfo = (SimpleUserInfo *)UserInfo::sharedUserInfo()->getFriendsList()->objectAtIndex(friendIndex);
            
            if(friendInfo->getGender() == "m")
            {
                friendHead = CCSprite::createWithSpriteFrameName("crown_king");
            }
            else
            {
                friendHead = CCSprite::createWithSpriteFrameName("crown_queen");
            }
            
            cellNameLabel->setString(friendInfo->getUserName().c_str());
        
        }
        else
        {
            friendHead = CCSprite::createWithSpriteFrameName("crown_queen");
            cellNameLabel->setString("好友越多，助力越多");
        }
        
        friendHead->setAnchorPoint(ccp(0,0.5));
        friendHead->setPosition(ccp(5.0,friendSprite->getContentSize().height/2));
        

        cellNameLabel->setAnchorPoint(ccp(0,0.5));
        cellNameLabel->setPosition(ccp(friendHead->getPositionX() + friendHead->getContentSize().width + 2,friendHead->getPositionY()));
        
        friendSprite->addChild(friendHead);
        friendSprite->addChild(cellNameLabel);
        
        this->addChild(friendSprite);

        friendSprite->runAction(CCSequence::create(
                                    CCMoveTo::create(1, ccp(getWinW() - friendSprite->getContentSize().width,friendSprite->getPositionY())),
                                    CCCallFunc::create(this, callfunc_selector(BlackjackLayer::showDealerCard)),
                                    CCDelayTime::create(0.5),
                                    CCMoveTo::create(1, ccp(getWinW(),friendSprite->getPositionY())),
                                    CCCallFunc::create(this, callfunc_selector(BlackjackLayer::showDealerCard)),
                                    NULL));
    }
}

void BlackjackLayer::showDealerCard()
{
    mDealerHand->getCard(0)->flipCard(0.1);
}

void BlackjackLayer::gotoShop(cocos2d::CCNode *pSender, void *data)
{
    if((bool)data)
    {
        gotoOtherScene(Shop_Scene);
    }
}

void BlackjackLayer::onEnter()
{
    CCLOG("onEnter");
    showUserInfo();
    CCLayer::onEnter();
}