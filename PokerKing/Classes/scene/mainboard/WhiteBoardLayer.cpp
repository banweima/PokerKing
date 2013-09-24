//
//  WhiteBoardLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-5.
//
//

#include "WhiteBoardLayer.h"
#include "CCBUtility.h"


WhiteBoardLayer* WhiteBoardLayer::sharedWhiteBoardLayer(void)
{
    WhiteBoardLayer *pWhiteBoardLayer = NULL;
    if (!pWhiteBoardLayer)
    {
        pWhiteBoardLayer = new WhiteBoardLayer();
        
        if(pWhiteBoardLayer && pWhiteBoardLayer->init())
        {
            
        }
    }
    
    return pWhiteBoardLayer;
}


WhiteBoardLayer::WhiteBoardLayer()
:m_bTouchedMenu(false)
,mContent(NULL)
,mMenu(NULL)
,touchCount(0)
,mTarget(NULL)
, mCallFuncND(NULL)
{}

WhiteBoardLayer::~WhiteBoardLayer()
{
    CC_SAFE_RELEASE(mContent);
    CC_SAFE_RELEASE(mMenu);
}

bool WhiteBoardLayer::init()
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

void WhiteBoardLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/whiteboard.ccbi", "WhiteBoardLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    this->setTouchEnabled(true);
}

void WhiteBoardLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler WhiteBoardLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCancelClicked", WhiteBoardLayer::onCancelClicked);
    
    return NULL;
}

SEL_CCControlHandler WhiteBoardLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool WhiteBoardLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mContent", CCLabelTTF * , mContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenu", CCMenu * , mMenu);
    
    return false;
}



void WhiteBoardLayer::onCancelClicked(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(true);
    if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }        
}



WhiteBoardLayer * WhiteBoardLayer::addWhiteBoardToLayer(cocos2d::CCLayer *parentLayer)
{
    return addWhiteBoardToLayer("", parentLayer);
}


WhiteBoardLayer * WhiteBoardLayer::addWhiteBoardToLayer(std::string contentString, cocos2d::CCLayer *parentLayer)
{
    this->removeFromParentAndCleanup(false);
    
    mContent->setString(contentString.c_str());
    
    parentLayer->addChild(this, Child_Order_Mid + 1);
    
    
    return this;
}

WhiteBoardLayer * WhiteBoardLayer::addWhiteBoardToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    this->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(this, Child_Order_Mid + 1);

    mTarget = target;
    mCallFuncND = callback;

    return this;
}


void WhiteBoardLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
    CCLayer::registerWithTouchDispatcher(); 
}

bool WhiteBoardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    m_bTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
    
}

void WhiteBoardLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void WhiteBoardLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }

}

void WhiteBoardLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void WhiteBoardLayer::getEventsInfo()
{
    GameServerAction::sharedGameServerAction()->showEvents(this, callfuncND_selector(WhiteBoardLayer::getEventsInfo_Done));
}


void WhiteBoardLayer::getEventsInfo_Done(cocos2d::CCNode *pNode, void *data)
{
    std::string msg = "";
    if((bool)data)
    {
        
        CCArray * eventsList = GameInfo::sharedGameInfo()->getEventsList();
        for(int i = 0; i < eventsList->count(); i++)
        {
            msg+= ((EventInfo *)eventsList->objectAtIndex(i))->getTitle() + "\r\n";
            msg+= ((EventInfo *)eventsList->objectAtIndex(i))->getDescription() + "\r\n\r\n";
        }
    
    }
    else
    {
        msg = "国运昌盛，太平无事。。。。。";
    }
    
    mContent->setString(msg.c_str());

}
