//
//  BigSmallLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-8-10.
//
//

#include "BigSmallLayer.h"
#include "SimpleAudioEngine.h"
#include "CCBUtility.h"
#include "RotateY.h"
#include "AlertLayer.h"

BigSmallLayer* BigSmallLayer::sharedBigSmallLayer(long initBet)
{
    BigSmallLayer *pBigSmallLayer = NULL;
    if (!pBigSmallLayer)
    {
        pBigSmallLayer = new BigSmallLayer();
        
        if(pBigSmallLayer && pBigSmallLayer->init())
        {
            pBigSmallLayer->setCurrentBet(initBet);
        }
    }
    
    return pBigSmallLayer;
}


BigSmallLayer::BigSmallLayer()
:m_bTouchedMenu(false)
,mBet(NULL)
,mMenu(NULL)
,mPlayerHandNode(NULL)
,mBig(NULL)
,mTarget(NULL)
,mCallFunc(NULL)
{}

BigSmallLayer::~BigSmallLayer()
{
    CC_SAFE_RELEASE(mBet);
    CC_SAFE_RELEASE(mMenu);
    CC_SAFE_RELEASE(mPlayerHandNode);
    CC_SAFE_RELEASE(mBig);
}

bool BigSmallLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        this->setupLayer();
        
        bRet = true;
    } while (0);
    
	return bRet;
}

void BigSmallLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/bigsmall.ccbi", "BigSmallLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    this->setTouchEnabled(true);
    
    mPlayerHand = PlayCardHand::create(false);
    mPlayerHand->retain();

    mPlayerHand->setCardScale(0.8);

    mPlayerHand->setAnchorPoint(ccp(0.5,0.5));
    mPlayerHand->setPosition(ccp(getWinW()/2, (mBet->getPositionY() + mBig->getPositionY())/2));
    
    mPlayerHandNode->addChild(mPlayerHand);
    
}

void BigSmallLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler BigSmallLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBigClicked", BigSmallLayer::onBigClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSmallClicked", BigSmallLayer::onSmallClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSevenClicked", BigSmallLayer::onSevenClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onExitClicked", BigSmallLayer::onExitClicked);
    
    return NULL;
}

SEL_CCControlHandler BigSmallLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool BigSmallLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBet", CCLabelTTF * , mBet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenu", CCMenu * , mMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPlayerHandNode", CCNode * , mPlayerHandNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBig", CCMenuItemImage *, mBig);
    return false;
}



void BigSmallLayer::onExitClicked(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(true);
    if (mTarget && mCallFunc) {
                (mTarget->*mCallFunc)(NULL,(void *)currentBet);
            }
}


BigSmallLayer * BigSmallLayer::addBigSmallToLayer(cocos2d::CCLayer *parentLayer)
{
    return addBigSmallToLayer("", parentLayer);
}


BigSmallLayer * BigSmallLayer::addBigSmallToLayer(std::string contentString, cocos2d::CCLayer *parentLayer)
{
    this->removeFromParentAndCleanup(false);
    
    mBet->setString(contentString.c_str());
    
    parentLayer->addChild(this, Child_Order_Mid + 1);
    
    
    return this;
}

BigSmallLayer * BigSmallLayer::addBigSmallToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    this->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(this, Child_Order_Mid + 1);

    mTarget = target;
    mCallFunc = callback;

    return this;
}


void BigSmallLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
    CCLayer::registerWithTouchDispatcher(); 
}

bool BigSmallLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    return true;
}

void BigSmallLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void BigSmallLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void BigSmallLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void BigSmallLayer::setCurrentBet(long bet)
{
    currentBet = bet;
    mBet->setString(CCString::createWithFormat("%d",currentBet)->getCString());
}

void BigSmallLayer::onBigClicked(cocos2d::CCObject *pSender)
{
    selectTarget = 1;
    showCard();
}

void BigSmallLayer::onSmallClicked(cocos2d::CCObject *pSender)
{
    selectTarget = -1;
    showCard();
}

void BigSmallLayer::onSevenClicked(cocos2d::CCObject *pSender)
{
    selectTarget = 0;
    showCard();
}

void BigSmallLayer::showCard()
{
    if(currentBet > 0)
    {
        if (mPlayerHand->getCardCount() > 0)
        {
          mPlayerHand->clearHand();
        }
        
        mPlayerHand->addNextCardToHand(false, 0.5);
        mPlayerHand->runAction(CCSequence::create(
                            CCDelayTime::create(1),
                            CCCallFunc::create(this, callfunc_selector(BigSmallLayer::showResult)),
                            NULL));
    }
    else
    {
        AlertLayer * shareAlert = AlertLayer::create("猜大小","金额已为零，欢迎下次再来！" , false, NULL, NULL);
        this->addChild(shareAlert, Child_Order_Top);
    }
}

void BigSmallLayer::showResult()
{
    std::string wavName = "";
    
    if ((mPlayerHand->getCard(0)->getCardType() < 7 && selectTarget == -1)
    || (mPlayerHand->getCard(0)->getCardType() > 7 && selectTarget == 1) )
    {
        setCurrentBet(currentBet * 2);
        wavName = "cheer.mp3";
    }
    else if(mPlayerHand->getCard(0)->getCardType() == 7 && selectTarget == 0)
    {
        setCurrentBet(currentBet * 7);
        wavName = "BJ.mp3";
    }
    else
    {
        setCurrentBet(0);
        wavName = "Loser.wav";
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(wavName.c_str());
}