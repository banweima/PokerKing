//
//  Loading.cpp
//  blackjack
//
//  Created by ruan.xiaoyu on 2012/08/18.
//
//

#include "Loading.h"
#include "Constants.h"

USING_NS_CC;

static Loading *pLoading = NULL;
PlayCard * card;
CCRepeatForever * repeatAction = NULL;

Loading* Loading::sharedLoading(void)
{
    if (!pLoading)
    {
        pLoading = new Loading();
        
        if(pLoading && pLoading->initWithColor((ccc4(0, 0, 0, 200))))
        {
            //int dealerIndex = arc4random() % 16 + 1;
            //CCString * dealer = CCString::createWithFormat("Dealer%d",dealerIndex);
            //CCSprite * sprite = CCSprite::createWithSpriteFrameName(dealer->getCString());
            card = PlayCard::create(HongKong_Card, Diamonds, King, false);
    
            card->setPosition(ccp(getWinW()/2, getWinH()/2));
            card->setScale(0.4f);
            pLoading->addChild(card);
            pLoading->setTouchEnabled(true);
            repeatAction = CCRepeatForever::create(
                        RotateY::create(0.6, 6));
            repeatAction->retain();
            card->setRotation(30);
        }
    }
    
    return pLoading;
}

Loading::Loading()
{

}

Loading::~Loading()
{

}


void Loading::showLoading(const char *loadingMsg)
{
    CCLabelTTF *msg = CCLabelTTF::create(loadingMsg, "Arial", 18);
    msg->setPosition(ccp(getWinW()/2, getWinH()/2));
    this->addChild(msg);
}

void Loading::removeLoading()
{
    card->resumeSchedulerAndActions();
    this->removeFromParentAndCleanup(false);
}

void Loading::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
    CCLayer::registerWithTouchDispatcher(); 
}

bool Loading::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void Loading::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void Loading::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void Loading::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}


Loading * Loading::addLoadingToLayer(cocos2d::CCLayer *parentLayer)
{
    return addLoadingToLayer(parentLayer, 200);
}

Loading * Loading::addLoadingToLayer(cocos2d::CCLayer *parentLayer, GLubyte var)
{
    pLoading->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(pLoading, Child_Order_Top, kTagLoading);
    
    pLoading->setOpacity(var);
    
    card->getActionManager()->removeAction(repeatAction);
    
    card->runAction(repeatAction);
    
    
    return pLoading;
}


