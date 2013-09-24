//
//  ConnectionFailedLayer.cpp
//  blackjack
//
//  Created by Banson Niu on 10/18/12.
//
//

#include "AlertLayer.h"
#include "Constants.h"


AlertLayer* AlertLayer::create(const char* pszTitle, const char* pszMsg, bool bHasCancel, CCObject *target, SEL_CallFuncND selector)
{
    AlertLayer * alertLayer = new AlertLayer(pszTitle, pszMsg, bHasCancel, target, selector);
    
    if(alertLayer && alertLayer->init() && alertLayer->initWithColor(ccc4(0, 0, 0, 160)))
    {
        alertLayer->autorelease();
        return alertLayer;
    }
    CC_SAFE_DELETE(alertLayer);
    return NULL;
}


AlertLayer::AlertLayer(const char* pszTitle, const char* pszMsg, bool bHasCancel, CCObject *target, SEL_CallFuncND selector)
{
    m_sTitle = pszTitle;
    m_sMessage = pszMsg;
    m_bHasCancel = bHasCancel;
    
    m_pListener = target;
    m_pCallFuncND = selector;
}

AlertLayer::~AlertLayer()
{
  //CC_SAFE_RELEASE_NULL(m_pMenu);
}

bool AlertLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::init());
        this->initDialog();
        bRet = true;
    } while (0);
    
    return bRet;
}

bool AlertLayer::initWithColor(const ccColor4B &color)
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(color));
        this->initDialog();
        bRet = true;
    } while (0);
    
    return bRet;
}


void AlertLayer::initDialog()
{
    float fScale = 0.75;

    CCSize ScreenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *BGLayer = CCSprite::createWithSpriteFrameName("bg_alert");
    BGLayer->setScaleX(fScale);
    BGLayer->setPosition(ccp(ScreenSize.width/2,ScreenSize.height/2));
    this->addChild(BGLayer);
    
    // title
    CCLabelTTF *cellDesc = CCLabelTTF::create(m_sTitle.c_str(), "Helvetica", 18);
    cellDesc->setPosition(ccp(BGLayer->getPosition().x, BGLayer->getPositionY() + BGLayer->getContentSize().height/2 - cellDesc->getContentSize().height));
    this->addChild(cellDesc);
    
    
    // message
    CCLabelTTF *TLabel = CCLabelTTF::create(m_sMessage.c_str(), "Helvetica", 16,CCSize(fScale * (BGLayer->getContentSize().width) - 20, BGLayer->getContentSize().height/3), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    TLabel->setColor(ccBLACK);
    TLabel->setPosition(ccp(BGLayer->getPosition().x, cellDesc->getPosition().y - cellDesc->getContentSize().height/2 - TLabel->getContentSize().height/2 - 10));

    this->addChild(TLabel);
    
    CCSprite *yesBtn1 = CCSprite::createWithSpriteFrameName("button_ok");
    CCSprite *yesBtn2 = CCSprite::createWithSpriteFrameName("button_ok");
    CCSprite *yesBtn3 = CCSprite::createWithSpriteFrameName("button_ok");
    CCMenuItemSprite* yesItemBtn = CCMenuItemSprite::create(yesBtn1, yesBtn2, yesBtn3, this, menu_selector(AlertLayer::AlertLayerDidSelected));
    
    CCSprite *noBtn1 = CCSprite::createWithSpriteFrameName("button_cancel");
    CCSprite *noBtn2 = CCSprite::createWithSpriteFrameName("button_cancel");
    CCSprite *noBtn3 = CCSprite::createWithSpriteFrameName("button_cancel");
    CCMenuItemSprite* noItemBtn = CCMenuItemSprite::create(noBtn1, noBtn2, noBtn3, this, menu_selector(AlertLayer::doCancel));
    
    if (m_bHasCancel) {
        m_pMenu = CCMenu::create(yesItemBtn, noItemBtn, NULL);
    } else {
        m_pMenu = CCMenu::create(yesItemBtn, NULL);
    }
    m_pMenu->setPosition(ccp(TLabel->getPosition().x, TLabel->getPosition().y  - TLabel->getContentSize().height));//cellDesc->getContentSize().height/2
    m_pMenu->alignItemsHorizontallyWithPadding((ScreenSize.width - noBtn1->getContentSize().width * 2)/3);
    this->addChild(m_pMenu);
}

void AlertLayer::doCancel(CCNode *pSender)
{
    this->removeFromParentAndCleanup(true);
    
    if (m_pListener != NULL && m_pCallFuncND != NULL)
    {
        (m_pListener->*m_pCallFuncND)(NULL,(void *)false);
    }
}

void AlertLayer::AlertLayerDidSelected(CCNode *pSender)
{
    this->removeFromParentAndCleanup(true);
    
    if (m_pListener != NULL && m_pCallFuncND != NULL)
    {
        (m_pListener->*m_pCallFuncND)(NULL,(void *)true);
    }
}

void AlertLayer::onEnter()
{
    CCLayerColor::onEnter();
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority - 100, true);
}

void AlertLayer::onExit()
{
    CCLayerColor::onExit();
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->removeDelegate(this);
}

bool AlertLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    return true;

}

void AlertLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void AlertLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void AlertLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}