//
//  TexasLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-12.
//
//

#include "TexasLayer.h"
#include "RankingScene.h"
#include "CCBUtility.h"
#include "PlayCard.h"
#include "Constants.h"
#include "CardDeck.h"
#include "HttpImageLoader.h"
#include "platform.h"
#include "SimpleAudioEngine.h"
#include "GameRoomScene.h"
#include "MainBoardScene.h"
#include "GameServerAction.h"

TexasLayer::TexasLayer()
: mStartMenu(NULL)
, mPlayerHandNode(NULL)
, mDealerHandNode(NULL)
, mEnemyHandNode(NULL)
, mPlayerCountNode(NULL)
, mEnemyCountNode(NULL)
, mPlayerFrameSprite(NULL)
, mEnemyFrameSprite(NULL)
, betCount(0)
, winCount(0)
, totalBonus(0)
, playerInfo(NULL)
, enemyInfo(NULL)
, mPlayerRankSprite(NULL)
, mEnemyRankSprite(NULL)
, mFold(NULL)
, mCall(NULL)
, mRaise(NULL)
, mRaisePlus(NULL)
, mRaiseMinus(NULL)
, mScrollDot(NULL)
, mScrollBar(NULL)
{}

TexasLayer::~TexasLayer()
{
    CC_SAFE_RELEASE(mStartMenu);
    CC_SAFE_RELEASE(mPlayerHandNode);
    CC_SAFE_RELEASE(mDealerHandNode);
    CC_SAFE_RELEASE(mEnemyHandNode);
    CC_SAFE_RELEASE(mPlayerCountNode);
    CC_SAFE_RELEASE(mEnemyCountNode);
    CC_SAFE_RELEASE(mPlayerFrameSprite);
    CC_SAFE_RELEASE(mEnemyFrameSprite);
    CC_SAFE_RELEASE(playerInfo);
    CC_SAFE_RELEASE(enemyInfo);
    CC_SAFE_RELEASE(mPlayerRankSprite);
    CC_SAFE_RELEASE(mEnemyRankSprite);
    CC_SAFE_RELEASE(mFold);
    CC_SAFE_RELEASE(mCall);
    CC_SAFE_RELEASE(mRaise);
    CC_SAFE_RELEASE(mRaiseMinus);
    CC_SAFE_RELEASE(mRaisePlus);
    CC_SAFE_RELEASE(mScrollDot);
    CC_SAFE_RELEASE(mScrollBar);
}

bool TexasLayer::init()
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

void TexasLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/texas.ccbi", "TexasLayer", CCLayerLoader::loader(), this);
    this->addChild(node);
    
    mDealerHand = PlayCardHand::create(false);
    mPlayerHand = PlayCardHand::create(false);
    mEnemyHand = PlayCardHand::create(false);
    
    mDealerHand->setCardScale(0.8);
    mPlayerHand->setCardScale(0.8);
    mEnemyHand->setCardScale(0.8);
    
//    int w = getContentSize().width;
//    int h = getContentSize().height;
//    int handH = h/3;
//    mDealerHand->setPosition(ccp(w/2, h/2 + handH));
//    mPlayerHand->setPosition(ccp(w/2, h/2 - handH));
//    mEnemyHand->setPosition(ccp(w/2, h/2 - handH));
    
    mPlayerHandNode->addChild(mPlayerHand);
    
    mDealerHandNode->addChild(mDealerHand);
    mEnemyHandNode->addChild(mEnemyHand);
    
    mEnemyCount = CardCount::create();
    mPlayerCount = CardCount::create();
    
//    mEnemyCount->setPosition(ccp(w/2, h/2 + handH*0.35));
//    mPlayerCount->setPosition(ccp(w/2, h/2 - handH*0.35));
    
    mEnemyCountNode->addChild(mEnemyCount);
    mPlayerCountNode->addChild(mPlayerCount);
    
    mEnemyCount->setVisible(false);
    mPlayerCount->setVisible(false);
    
    mStartMenu->getParent()->reorderChild(mStartMenu, 1000);
    
    // Setup user profile info
//    HttpImageLoader *imageLoader1 = HttpImageLoader::create();
//    imageLoader1->retrieveImageData("http://app1-c.mobage.cn/image/13000251/534dc72c32388d6e39c511c0e59b946b.png", this, callfuncND_selector(TexasLayer::getPlayerImage));
//    
//    HttpImageLoader *imageLoader2 = HttpImageLoader::create();
//    imageLoader2->retrieveImageData("http://app1-c.mobage.cn/image/12000108/da860d9b57cb98a5b66852e5294fdcfe.png", this, callfuncND_selector(TexasLayer::getDealerImage));

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    mRaise->setVisible(false);
    mFold->setVisible(false);
    mCall->setVisible(false);
    
    mRaiseMinus->setVisible(false);
    mRaisePlus->setVisible(false);
    mScrollBar->setVisible(false);
    mScrollDot->setVisible(false);
    
}

void TexasLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
    
}


SEL_MenuHandler TexasLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onStart", TexasLayer::onStartClicked);

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRaiseMinusClicked", TexasLayer::onRaiseMinusClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onRaisePlusClicked", TexasLayer::onRaisePlusClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onScrollDotClicked", TexasLayer::onScrollDotClicked);

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", TexasLayer::onHomeClicked);
    
    return NULL;
}

SEL_CCControlHandler TexasLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFoldClicked", TexasLayer::onFoldClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onRaiseClicked", TexasLayer::onRaiseClicked);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onFoldClicked", TexasLayer::onFoldClicked);
    return NULL;
}

bool TexasLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStartMenu", CCMenu *, mStartMenu);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerHandNode", CCNode *, mPlayerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDealerHandNode", CCNode *, mDealerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnemyHandNode", CCNode *, mEnemyHandNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerCountNode", CCNode *, mPlayerCountNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnemyCountNode", CCNode *, mEnemyCountNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerFrameSprite", CCSprite *, mPlayerFrameSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnemyFrameSprite", CCSprite *, mEnemyFrameSprite);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFold", CCControlButton *, mFold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRaise", CCControlButton *, mRaise);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCall", CCControlButton *, mCall);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRaisePlus", CCMenuItemImage *, mRaisePlus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRaiseMinus", CCMenuItemImage *, mRaiseMinus);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollDot", CCMenuItemImage *, mScrollDot);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mScrollBar", CCMenuItemImage *, mScrollBar);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerRankSprite", CCSprite *, mPlayerRankSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnemyRankSprite", CCSprite *, mEnemyRankSprite);
    return false;
}

void TexasLayer::getPlayerImage(CCNode* node, void* data)
{
    CCPoint pos = ccp(mPlayerFrameSprite->getPosition().x + mPlayerFrameSprite->getContentSize().width/2, mPlayerFrameSprite->getPosition().y);
    float factor = 0.86;
    CCSize size = CCSizeMake(mPlayerFrameSprite->getContentSize().width*factor, mPlayerFrameSprite->getContentSize().height*factor);
    
    CCSprite* sprite = CCSprite::createWithTexture((CCTexture2D*)data);
    sprite->setScale(factor);
    sprite->setPosition(pos);
    this->addChild(sprite);
}

void TexasLayer::getDealerImage(CCNode* node, void* data)
{
    CCPoint pos = ccp(mEnemyFrameSprite->getPosition().x + mEnemyFrameSprite->getContentSize().width/2, mEnemyFrameSprite->getPosition().y);
    float factor = 0.86;
    CCSize size = CCSizeMake(mEnemyFrameSprite->getContentSize().width*factor, mEnemyFrameSprite->getContentSize().height*factor);
    
    CCSprite* sprite = CCSprite::createWithTexture((CCTexture2D*)data);
    sprite->setScale(factor);
    sprite->setPosition(pos);
    this->addChild(sprite);
}

void TexasLayer::setHideButton(CCNode* node)
{
    node->setVisible(false);
}

void TexasLayer::hideButton(CCNode* node)
{
    if (node==NULL) {
        return;
    }
    
    node->runAction(CCSequence::create(
                            CCSpawn::create(
                                CCScaleTo::create(HideButtonTime, 0.1),
                               CCFadeOut::create(HideButtonTime),
                                    NULL),
                           CCCallFuncN::create(this, callfuncN_selector(TexasLayer::setHideButton)),
                           NULL));
}

void TexasLayer::showButton(CCNode* node)
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

void TexasLayer::onStartClicked(CCObject * pSender)
{
    this->hideButton(mStartMenu);
    
    GameServerAction::sharedGameServerAction()->startBattle(Texas,ArenaBattle,0,mRoomLevelInfo->getRoomLevel(),
    this, callfuncND_selector(TexasLayer::startGame));
}


void TexasLayer::checkPokerHand()
{
    mPlayerPokerHand = mPlayerHand->getPokerHand(true,false);
    
    mPlayerCount->setPokerHand(mPlayerPokerHand);
    
    mEnemyPokerHand = mDealerHand->getPokerHand(true,true);
    
    mEnemyCount->setPokerHand(mEnemyPokerHand);

}

////////////////////////////////////////////////////////////////
//
// Start.

void TexasLayer::NotifyBusted()
{

}

void TexasLayer::winCalc()
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
        if( mEnemyPokerHand == Mass)
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


int TexasLayer::comparePokerHand()
{
    int isPlayerWin = 0;
    int iPlayerCardType = 0;
    int iDealerCardType = 0;
    
//    CCLOG("mPlayerPokerHand: %d",(int)mPlayerPokerHand);
//    CCLOG("mEnemyPokerHand: %d",(int)mEnemyPokerHand);
    
    if((int)mPlayerPokerHand == (int)mEnemyPokerHand)
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
    else if((int)mPlayerPokerHand > (int)mEnemyPokerHand)
    {
        isPlayerWin = 1;
    }
    else
    {
        isPlayerWin = -1;
    }
    return isPlayerWin;
}

void TexasLayer::startGame(CCNode* node, void* data)
{

//    CCDictionary *dict = (CCDictionary *)data;
//        
//    CCDictionary* battleInfoDic = (CCDictionary *)dict->objectForKey("battleInfo");

    BattleInfo * batInfo = BattleInfo::sharedBattleInfo();
//    batInfo->parseBattleInfo(battleInfoDic);
    
    
    mDealerHand->prepareCards(batInfo->getDealerCards());
    
    CCArray * playerList = (CCArray *)batInfo->getBattlePlayerList();
    
    for(int i = 0; i < playerList->count(); i ++)
    {
        if( ( (PlayerInfo *)playerList->objectAtIndex(i))->getPlayerID() ==
        UserInfo::sharedUserInfo()->getUserID())
        {
            playerInfo = (PlayerInfo *)playerList->objectAtIndex(i);
        }
        else
        {
            enemyInfo = (PlayerInfo *)playerList->objectAtIndex(i);
        }
    }
    
    mPlayerHand->prepareCards(playerInfo->getPlayerCards());
    mEnemyHand->prepareCards(enemyInfo->getPlayerCards());
    
    


    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Click_01.wav");

        // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // srand( TimGetTicks() );
    int actualDuration = 1.0;

    // Create the actions
    CCFiniteTimeAction* actionMove = NULL;
    
    // Clear the hand before starting a new game:
    mPlayerHand->clearHand();
    mDealerHand->clearHand();
    mEnemyHand->clearHand();
    
    // Reset the counts and hide them:
    mPlayerCount->setCount(0);
    mEnemyCount->setCount(0);
    
    mPlayerCount->setVisible(true);
    mEnemyCount->setVisible(true);


    
    
    CCDelayTime *delayAction = CCDelayTime::create(0.5f);
    
    
    fiveCards = 0;
    
    this->reorderChild(mStartMenu, -600);
    this->reorderChild(mPlayerHand, 0);
    
    
    int w = getContentSize().width;
    int h = getContentSize().height;
    int menuH = 40; //mChooseRoomBtn->getContentSize().height;
    int notifyH = 30;
    int tmpH = (h-menuH-notifyH)/2 + notifyH;
    
    // Add first two cards to player hand
    mPlayerHand->addNextCardToHand(false,0);
    mPlayerHand->addNextCardToHand(false,0.2);

    
    // Add first two cards to dealer hand
    mDealerHand->addNextCardToHand(false,0.2);
    mDealerHand->addNextCardToHand(false,0.3);
    mDealerHand->addNextCardToHand(false,0.4);
    
    mEnemyHand->addNextCardToHand(true,0.2);
    mEnemyHand->addNextCardToHand(true,0.3);
    
    mDealerHand->setPosition(ccp(w/2, tmpH));
    // - mDealerHand->getCard(0)->getCardHeight()/2));
    mPlayerHand->setPosition(ccp(w/2, notifyH + mPlayerHand->getCard(0)->getCardHeight()/2));
    mEnemyHand->setPosition(ccp(w/2, h-menuH - mEnemyHand->getCard(0)->getCardHeight()/2));
    
    mPlayerHand->setVisible(true);
    mDealerHand->setVisible(true);
    mEnemyHand->setVisible(true);
    
    mEnemyCount->setPosition(ccp(w/2, mEnemyHand->getPositionY() - mEnemyHand->getCard(0)->getCardHeight()/2- mEnemyCount->getBgSprite2()->getContentSize().height ));
    
    mPlayerCount->setPosition(ccp(w/2, mPlayerHand->getPositionY() + mPlayerHand->getCard(0)->getCardHeight()/2 + mPlayerCount->getBgSprite2()->getContentSize().height));
    
    mEnemyCount->setVisible(true);
    mPlayerCount->setVisible(true);
    
    mFold->setVisible(true);
    mCall->setVisible(true);
    mRaise->setVisible(true);
    
}


void TexasLayer::onRaiseMinusClicked()
{

}

void TexasLayer::onRaisePlusClicked()
{

}

void TexasLayer::onScrollDotClicked()
{

}

void TexasLayer::onFoldClicked()
{

}

void TexasLayer::onRaiseClicked()
{
    mRaiseMinus->setVisible(true);
    mRaisePlus->setVisible(true);
    mScrollBar->setVisible(true);
    mScrollDot->setVisible(true);
    
}

void TexasLayer::onCallClicked()
{

}


void TexasLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    MainBoardScene *scene = MainBoardScene::create();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene, ccBLACK));
}
