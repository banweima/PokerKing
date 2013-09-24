//
//  CaribbeanLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 9/11/12.
//
//

#include "CaribbeanLayer.h"
#include "RankingScene.h"
#include "CCBUtility.h"
#include "PlayCard.h"
#include "Constants.h"
#include "CardDeck.h"
#include "HttpImageLoader.h"
#include "platform.h"
#include "SimpleAudioEngine.h"
#include "GameRoomScene.h"


CaribbeanLayer::CaribbeanLayer()
: mStartMenu(NULL)
, mCardMenu(NULL)
, mGameMenu(NULL)
, mGlobalNotification(NULL)
, mChooseRoomLabel(NULL)
, mFriendsLabel(NULL)
, mRankingLabel(NULL)
, mShopLabel(NULL)
, mSettingLabel(NULL)
, mPlayerHandNode(NULL)
, mDealerHandNode(NULL)
, mPlayerSplitHandNode(NULL)
, mPlayerCountNode(NULL)
, mDealerCountNode(NULL)
, mHitAllowed(true)
, mStandAllowed(false)
, mPlayerFrameSprite(NULL)
, mDealerFrameSprite(NULL)
, betCount(0)
, winCount(0)
, totalBonus(0)
, itemImageHeight(80)
, itemImageWidth(80)
, itemSpace(10)
, mFriendSupportImage(NULL)
, mFirendSupportLabel(NULL)
, mFriendsSupportRate(2)
{}

CaribbeanLayer::~CaribbeanLayer()
{
    CC_SAFE_RELEASE_NULL(mStartMenu);
    CC_SAFE_RELEASE_NULL(mCardMenu);
    CC_SAFE_RELEASE_NULL(mGameMenu);
    CC_SAFE_RELEASE_NULL(mGlobalNotification);
    CC_SAFE_RELEASE_NULL(mChooseRoomLabel);
    CC_SAFE_RELEASE_NULL(mFriendsLabel);
    CC_SAFE_RELEASE_NULL(mRankingLabel);
    CC_SAFE_RELEASE_NULL(mShopLabel);
    CC_SAFE_RELEASE_NULL(mSettingLabel);
    CC_SAFE_RELEASE_NULL(mPlayerHandNode);
    CC_SAFE_RELEASE_NULL(mDealerHandNode);
    CC_SAFE_RELEASE_NULL(mPlayerSplitHandNode);
    CC_SAFE_RELEASE_NULL(mPlayerCountNode);
    CC_SAFE_RELEASE_NULL(mDealerCountNode);
    CC_SAFE_RELEASE_NULL(mPlayerFrameSprite);
    CC_SAFE_RELEASE_NULL(mDealerFrameSprite);
    CC_SAFE_RELEASE_NULL(mGameItems);
}

bool CaribbeanLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setupLayer();
        
        bRet = true;
    } while (0);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("guitar3.wav", true);
    
    return bRet;
}

void CaribbeanLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/caribbean.ccbi", "GameRoomLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    
    mDealerHand = PlayCardHand::create(true);
    mPlayerHand = PlayCardHand::create(false);
    mPlayerSplitHand = PlayCardHand::create(false);
    
    int w = getContentSize().width;
    int h = getContentSize().height;
    int handH = h/3;
    mDealerHand->setPosition(ccp(w/2, h/2 + handH));
    mPlayerHand->setPosition(ccp(w/2, h/2 - handH));
    mPlayerSplitHand->setPosition(ccp(w/2, h/2 - handH));
    
    mPlayerHandNode->addChild(mPlayerHand);
    
    mDealerHandNode->addChild(mDealerHand);
    mPlayerSplitHandNode->addChild(mPlayerSplitHand);
    
    mDealerCount = CardCount::create();
    mPlayerCount = CardCount::create();
    
    mDealerCount->setPosition(ccp(w/2, h/2 + handH*0.35));
    mPlayerCount->setPosition(ccp(w/2, h/2 - handH*0.35));
    
    mDealerCountNode->addChild(mDealerCount);
    mPlayerCountNode->addChild(mPlayerCount);
    
    mDealerCount->setVisible(false);
    mDealerCount->setVisible(false);
    
    mStartMenu->getParent()->reorderChild(mStartMenu, 1000);
    mCardMenu->getParent()->reorderChild(mCardMenu, 1000);
    mGameMenu->getParent()->reorderChild(mGameMenu, 1000);
    
    mGlobalNotification->getParent()->reorderChild(mGlobalNotification, 1000);
    
    mChooseRoomLabel->getParent()->reorderChild(mChooseRoomLabel, 1000);
    mFriendsLabel->getParent()->reorderChild(mFriendsLabel, 1000);
    mRankingLabel->getParent()->reorderChild(mRankingLabel, 1000);
    mShopLabel->getParent()->reorderChild(mShopLabel, 1000);
    mSettingLabel->getParent()->reorderChild(mSettingLabel, 1000);
    
    mCardMenu->setVisible(false);
    
    // Setup user profile info
//    HttpImageLoader *imageLoader1 = HttpImageLoader::create();
//    imageLoader1->retrieveImageData("http://app1-c.mobage.cn/image/13000251/534dc72c32388d6e39c511c0e59b946b.png", this, callfuncND_selector(CaribbeanLayer::getPlayerImage));
//    
//    HttpImageLoader *imageLoader2 = HttpImageLoader::create();
//    imageLoader2->retrieveImageData("http://app1-c.mobage.cn/image/12000108/da860d9b57cb98a5b66852e5294fdcfe.png", this, callfuncND_selector(CaribbeanLayer::getDealerImage));

//Need get from Server
    int itemCount = 2;
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    mGameItems = CCArray::create();
    mGameItems->retain();
    
    CCSprite * itemSprite   = NULL;

    for(int i = 0; i < itemCount; i++)
    {
    //Need get the Image from server, and cache in AppData
        itemSprite = CCSprite::create(CCString::createWithFormat("img/Cat%d.png", i)->getCString());

        
        mGameItems->addObject(itemSprite);

        this->addChild(itemSprite);
    }
    
    
    
    
    // create and initialize a label
    mFirendSupportLabel = CCLabelTTF::create("xxx前来帮忙", "Thonburi", 16);

    // position the label on the center of the screen
    mFirendSupportLabel->setPosition( ccp(size.width + 50, size.height/2 + 20 + itemImageHeight/2) );

    // add the label as a child to this layer
    this->addChild(mFirendSupportLabel);
    
    
    //    // add "FriendsSupportScene" splash screen"
    mFriendSupportImage = CCSprite::create("img/Cat2.png");

    // position the sprite on the center of the screen
    mFriendSupportImage->setPosition( ccp(size.width + itemImageWidth/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(mFriendSupportImage);
    
    
    this->beforeStartAction();

}

void CaribbeanLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
    
}


SEL_MenuHandler CaribbeanLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChooseRoom", CaribbeanLayer::onChooseRoomClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFriends", CaribbeanLayer::onFriendsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRanking", CaribbeanLayer::onRankingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShop", CaribbeanLayer::onShopClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSetting", CaribbeanLayer::onSettingClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStart", CaribbeanLayer::onStartClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHitCardsClicked", CaribbeanLayer::onHitCardsClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStandCardsClicked", CaribbeanLayer::onStandCardsClicked);
    
    return NULL;
}

SEL_CCControlHandler CaribbeanLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool CaribbeanLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStartMenu", CCMenu *, mStartMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCardMenu", CCMenu *, mCardMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGameMenu", CCMenu *, mGameMenu);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGlobalNotification", CCLayerColor *, mGlobalNotification);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mChooseRoomLabel", CCLabelTTF *, mChooseRoomLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFriendsLabel", CCLabelTTF *, mFriendsLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRankingLabel", CCLabelTTF *, mRankingLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShopLabel", CCLabelTTF *, mShopLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingLabel", CCLabelTTF *, mSettingLabel);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerHandNode", CCNode *, mPlayerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDealerHandNode", CCNode *, mDealerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerSplitHandNode", CCNode *, mPlayerSplitHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerCountNode", CCNode *, mPlayerCountNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDealerCountNode", CCNode *, mDealerCountNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerFrameSprite", CCSprite *, mPlayerFrameSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDealerFrameSprite", CCSprite *, mDealerFrameSprite);
    
    return false;
}

void CaribbeanLayer::onChooseRoomClicked(CCObject * pSender)
{
    GameRoomScene *scene = GameRoomScene::create();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
}

void CaribbeanLayer::onFriendsClicked(CCObject * pSender)
{
//    MainMenuScene *scene = MainMenuScene::create();    
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
}

void CaribbeanLayer::onRankingClicked(CCObject * pSender)
{
    RankingScene *scene = RankingScene::create();
    
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
}

void CaribbeanLayer::getPlayerImage(CCNode* node, void* data)
{
    CCPoint pos = ccp(mPlayerFrameSprite->getPosition().x + mPlayerFrameSprite->getContentSize().width/2, mPlayerFrameSprite->getPosition().y);
    float factor = 0.86;
    CCSize size = CCSizeMake(mPlayerFrameSprite->getContentSize().width*factor, mPlayerFrameSprite->getContentSize().height*factor);
    
    CCSprite* sprite = CCSprite::createWithTexture((CCTexture2D*)data);
    sprite->setScale(factor);
    sprite->setPosition(pos);
    this->addChild(sprite);
}

void CaribbeanLayer::getDealerImage(CCNode* node, void* data)
{
    CCPoint pos = ccp(mDealerFrameSprite->getPosition().x + mDealerFrameSprite->getContentSize().width/2, mDealerFrameSprite->getPosition().y);
    float factor = 0.86;
    CCSize size = CCSizeMake(mDealerFrameSprite->getContentSize().width*factor, mDealerFrameSprite->getContentSize().height*factor);
    
    CCSprite* sprite = CCSprite::createWithTexture((CCTexture2D*)data);
    sprite->setScale(factor);
    sprite->setPosition(pos);
    this->addChild(sprite);
}

void CaribbeanLayer::onShopClicked(CCObject * pSender)
{
//    MainMenuScene *scene = MainMenuScene::create();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
    
    
//    mWebView = CCWebView::create(CCSizeMake(this->getContentSize().width*0.8, this->getContentSize().height*0.6));
//    mWebView->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
//    mWebView->loadURL(CCString::createWithFormat("http://mobage.cn"));
//    mWebView->retain();
//    this->addChild(mWebView);
}

void CaribbeanLayer::onSettingClicked(CCObject * pSender)
{
//    MainMenuScene *scene = MainMenuScene::create();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
}

void CaribbeanLayer::setHideButton(CCNode* node)
{
    node->setVisible(false);
}

void CaribbeanLayer::hideButton(CCNode* node)
{
    if (node==NULL) {
        return;
    }
    
    node->runAction(CCSequence::create(
                            CCSpawn::create(
                                CCScaleTo::create(HideButtonTime, 0.1),
                               CCFadeOut::create(HideButtonTime),
                                    NULL),
                           CCCallFuncN::create(this, callfuncN_selector(CaribbeanLayer::setHideButton)),
                           NULL));
}

void CaribbeanLayer::showButton(CCNode* node)
{
    if (node==NULL) {
        return;
    }
    
    node->setVisible(true);
    node->setScale(0.1);
    node->runAction(CCSpawn::create(
                                    CCScaleTo::create(HideButtonTime, 1.0),
                                    CCFadeIn::create(HideButtonTime),
                                    NULL));
}

void CaribbeanLayer::onStartClicked(CCObject * pSender)
{
    this->hideButton(mStartMenu);

//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Click_01.wav");

        // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    //float xStart = size.width;
    float xEnd = size.width + itemImageWidth / 2;
    
    // srand( TimGetTicks() );
    int actualDuration = 1.0;

    // Create the actions
    CCFiniteTimeAction* actionMove = NULL;
    
    CCSprite * sprite = NULL;
    
    int itemCount = mGameItems->count();
    
    for(int i = 0; i < itemCount; i++)
    {
        sprite = (CCSprite *) mGameItems->objectAtIndex(i);
        
        actionMove = CCMoveTo::create( actualDuration,
                    ccp(xEnd, sprite->getPositionY()) );
        
        sprite->runAction( CCSequence::create(actionMove, NULL) );
    }
    
    // Clear the hand before starting a new game:
    mPlayerHand->clearHand();
    mDealerHand->clearHand();
    mPlayerSplitHand->clearHand();
    
    // Reset the counts and hide them:
    mPlayerCount->setCount(0);
    mDealerCount->setCount(0);
    
    mPlayerCount->setVisible(true);
    mDealerCount->setVisible(true);

    
    CardDeck::sharedCardDeck()->shuffleCardDeck();


    mPlayerHand->setVisible(true);
    mDealerHand->setVisible(true);
    
    CCDelayTime *delayAction = CCDelayTime::create(0.5f);
    
    CCCallFunc *callSelectorAction = CCCallFunc::create(this,callfunc_selector(CaribbeanLayer::dealCard));
    
    fiveCards = 0;
    
    this->runAction(CCSequence::create(delayAction,callSelectorAction,NULL));
    
    this->reorderChild(mStartMenu, -600);
    this->reorderChild(mCardMenu, -600);
    this->reorderChild(mPlayerHand, 0);
}
////////////////////////////////////////////////////////////////
//
// Deal the cards with delay time.
//
void CaribbeanLayer::dealCard()
{
    CCDelayTime *delayAction = CCDelayTime::create(0.5f);
    
    CCCallFunc *callSelectorAction = CCCallFunc::create(this,callfunc_selector(CaribbeanLayer::dealCard));
    
    if(fiveCards < 5)
    {
        this->runAction(CCSequence::create(delayAction,callSelectorAction,NULL));
        
        //Only for test
//        switch (fiveCards) {
//            case 0:
//            mPlayerHand->addCardToHand(Diamonds, Six, false, 0);
//            mDealerHand->addNextCardToHand(true,0);
//            break;
//            case 1:
//            mPlayerHand->addCardToHand(Clubs, Four, false, 0);
//            mDealerHand->addNextCardToHand(true,0);
//            break;
//            case 2:
//            mPlayerHand->addCardToHand(Spades, Nine, false, 0);
//            mDealerHand->addNextCardToHand(true,0);
//            break;
//            case 3:
//            mPlayerHand->addCardToHand(Hearts, Four, false, 0);
//            mDealerHand->addNextCardToHand(true,0);
//            break;
//            case 4:
//            mPlayerHand->addCardToHand(Clubs, Nine, false, 0);
//            mDealerHand->addNextCardToHand(true,0);
//            break;
//        }
        mPlayerHand->addNextCardToHand(false,0);
        mDealerHand->addNextCardToHand(true,0);
        
    }
    else if(fiveCards == 5)
    {
       this->runAction(CCSequence::create(delayAction,CCCallFunc::create(this,callfunc_selector(CaribbeanLayer::afterStartAction)),NULL));
    }
    
    fiveCards++;
}

void CaribbeanLayer::checkPokerHand()
{
    mPlayerPokerHand = mPlayerHand->getPokerHand(true,false);
    
    mPlayerCount->setPokerHand(mPlayerPokerHand);
    
    mDealerPokerHand = mDealerHand->getPokerHand(true,true);
    
    mDealerCount->setPokerHand(mDealerPokerHand);
    
    this->showButton(mCardMenu);
}

////////////////////////////////////////////////////////////////
//
// Hit.
//

void CaribbeanLayer::onHitCardsClicked()
{
    //this->afterStartAction();
}
////////////////////////////////////////////////////////////////
//
// Start.
void CaribbeanLayer::onStandCardsClicked()
{
    this->hideButton(mCardMenu);
    
    this->showButton(mStartMenu);

    mDealerHand->flipCards();
    this->winCalc();
    
    this->beforeStartAction();
}

void CaribbeanLayer::beforeStartAction()
{
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    float xStart = size.width;
    float xEnd = size.width - itemImageWidth /2;
    float y = 0;
    
    // srand( TimGetTicks() );
    int actualDuration = 1.0;

    // Create the actions
    CCFiniteTimeAction* actionMove = NULL;
    
    CCSprite * sprite = NULL;
    
    int itemCount = mGameItems->count();
    
    for(int i = 0; i < itemCount; i++)
    {
        sprite = (CCSprite *) mGameItems->objectAtIndex(i);
        
        y = (size.height - itemImageHeight * itemCount - (itemCount - 1) * itemSpace) / 2
            + i * (itemImageHeight + itemSpace) + itemImageHeight / 2;
        
        // position the sprite on the center of the screen
        sprite->setPosition( ccp(xStart, y) );
        
        actionMove = CCMoveTo::create( actualDuration,
                    ccp(xEnd, y) );
        
        sprite->runAction( CCSequence::create(actionMove, NULL) );
    }
    
}

//Friend Support

void CaribbeanLayer::afterStartAction()
{
    if(arc4random() % mFriendsSupportRate != 0)
    {
        this->checkPokerHand();
        return;
    }

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // srand( TimGetTicks() );
    int actualDuration = 1.0;

    // Create the actions
    CCFiniteTimeAction* actionMove =
    CCMoveTo::create( actualDuration,
    ccp(size.width - 50, mFirendSupportLabel->getPositionY()) );
    
    mFirendSupportLabel->runAction( CCSequence::create(actionMove, NULL) );
    
    actionMove =
    CCMoveTo::create( actualDuration,
    ccp(size.width - itemImageWidth/2, mFriendSupportImage->getPositionY()) );
    
    mFriendSupportImage->runAction( CCSequence::create(actionMove, NULL) );
    
    mDealerHand->getCard(0)->flipCard(1.5);
    mDealerHand->getCard(1)->flipCard(1.5);
    mDealerHand->getCard(2)->flipCard(1.5);
    
    mDealerHand->getCard(0)->flipCard(4.0);
    mDealerHand->getCard(1)->flipCard(4.0);
    mDealerHand->getCard(2)->flipCard(4.0);
    
    CCDelayTime *delayAction = CCDelayTime::create(4.0);
    
    actionMove =
    CCMoveTo::create( actualDuration,
    ccp(size.width + 50, mFirendSupportLabel->getPositionY()) );
    
    mFirendSupportLabel->runAction( CCSequence::create(delayAction, actionMove, NULL) );
    
    actionMove =
    CCMoveTo::create( actualDuration,
    ccp(size.width + itemImageWidth/2, mFriendSupportImage->getPositionY()) );
    
    mFriendSupportImage->runAction( CCSequence::create(delayAction, actionMove, NULL) );
    
    delayAction = CCDelayTime::create(5.0);
        
    this->runAction(CCSequence::create(delayAction,CCCallFunc::create(this,callfunc_selector(CaribbeanLayer::checkPokerHand)),NULL));

}

void CaribbeanLayer::NotifyBusted()
{
    onStandCardsClicked();
}

void CaribbeanLayer::winCalc()
{
    //All the Odds is base on the basic bet count 'ante', so if OnePair wins, the Odds is 3.
    int isPlayerWin = comparePokerHand();
    
    if(isPlayerWin == 1)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Cheer3.wav");
        
    }
    else
    {
    
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Loser.wav");
    }
    
    
    mPlayerCount->setWin(isPlayerWin);
    
    int Odds = 0;
    long extraBonus = 0;
    if(isPlayerWin == 1)
    {
        if( mDealerPokerHand == Mass)
        {
            Odds = 1;
        }
        else
        {
            switch (mPlayerPokerHand)
            {
            case AK:
            case OnePair:
            Odds = 3 * 1;
            break;
            case TwoPair:
            Odds = 3 * 2;
            break;
            case ThreeOfOneKind:
            Odds = 3 * 3;
            break;
            case Straight:
            Odds = 3 * 4;
            break;
            case Flush:
            Odds = 3 * 5;
            extraBonus = 5000;
            break;
            case FullHouse:
            Odds = 3 * 7;
            extraBonus = 10000;
            break;
            case FourOfOneKind:
            Odds = 3 * 20;
            extraBonus = 50000;
            break;
            case StraightFlush:
            Odds = 3 * 50;
            extraBonus = (long)(totalBonus * 0.1);
            break;
            case RoyalStraightFlush:
            Odds = 3 * 100;
            extraBonus = totalBonus;
            break;

            }
        }
        
        
    }
    else if(isPlayerWin == -1)
    {
        Odds = -3;
    }
    else
    {
        Odds = 0;
    }
    
    winCount = betCount * Odds + extraBonus;

}


int CaribbeanLayer::comparePokerHand()
{
    int isPlayerWin = 0;
    int iPlayerCardType = 0;
    int iDealerCardType = 0;
    
//    CCLOG("mPlayerPokerHand: %d",(int)mPlayerPokerHand);
//    CCLOG("mDealerPokerHand: %d",(int)mDealerPokerHand);
    
    if((int)mPlayerPokerHand == (int)mDealerPokerHand)
    {
        for(int i = 4; i >= 0; i --)
        {
            iPlayerCardType = (int)mPlayerHand->getCard(i)->getCardType();
            iDealerCardType = (int)mDealerHand->getCard(i)->getCardType();
            
//            CCLOG("iPlayerCardType: %d",iPlayerCardType);
//            CCLOG("iDealerCardType: %d",iDealerCardType);
            
            if(i == 4 && iPlayerCardType == 1 && iDealerCardType > 1)
            {
                isPlayerWin = 1;
                break;
            }
            else if(iPlayerCardType > iDealerCardType)
            {
                isPlayerWin = 1;
                break;
            }
            else if(iPlayerCardType < iDealerCardType)
            {
                isPlayerWin = -1;
                break;
            }
        }
    }
    else if((int)mPlayerPokerHand > (int)mDealerPokerHand)
    {
        isPlayerWin = 1;
    }
    else
    {
        isPlayerWin = -1;
    }
    return isPlayerWin;
}
