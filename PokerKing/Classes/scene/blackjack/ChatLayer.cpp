//
//  ChatLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-8.
//
//

#include "ChatLayer.h"
#include "CCBUtility.h"
#include "GameServerAction.h"


static ChatLayer *pChatLayer = NULL;

ChatLayer* ChatLayer::sharedChatLayer(void)
{
    if (!pChatLayer)
    {
        pChatLayer = new ChatLayer();
        
        if(pChatLayer && pChatLayer->init())
        {
            
        }
    }
    
    return pChatLayer;
}


ChatLayer::ChatLayer()
:m_bTouchedMenu(false)
,mContent(NULL)
, mMenu(NULL)
,m_pCursorTextField(NULL)
,m_bTouchedText(false)
, mSend(NULL)
, mTextBG(NULL)
{}

ChatLayer::~ChatLayer()
{
    CC_SAFE_RELEASE(mContent);
    CC_SAFE_RELEASE(mMenu);
    CC_SAFE_RELEASE(m_pCursorTextField);
    CC_SAFE_RELEASE(mSend);
    CC_SAFE_RELEASE(mTextBG);
}

bool ChatLayer::init()
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

void ChatLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/chat.ccbi", "ChatLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    this->setTouchEnabled(true);
    
    m_pCursorTextField = CursorTextField::textFieldWithPlaceHolder("Input Text", "Thonburi", 18);
//    m_pCursorTextField->setAnchorPoint(ccp(0,0.5));
//    m_pCursorTextField->setPosition(ccp(mTextBG->getPositionX() + mTextBG->getContentSize().width/2, mSend->getPositionY()));
    
//    m_pCursorTextField->setDimensions(CCSizeMake(mSend->getPositionX()-m_pCursorTextField->getPositionX() - 10, m_pCursorTextField->getContentSize().height));
    
//    CCLayerColor * textBgColor = CCLayerColor::create(ccc4(100,100,100,250), m_pCursorTextField->getContentSize().width, m_pCursorTextField->getDimensions().height);
//    
//    textBgColor->setAnchorPoint(ccp(0,0.5));
//    textBgColor->setPosition(ccp(m_pCursorTextField->getPositionX(),mSend->getPositionY()));
//    
//    this->addChild(textBgColor);

    m_pCursorTextField->setAnchorPoint(mTextBG->getAnchorPoint());
    m_pCursorTextField->setPosition(mTextBG->getPosition());
    m_pCursorTextField->setDimensions(CCSizeMake(mTextBG->getContentSize().width * 0.95, mTextBG->getContentSize().height * 0.95));

    m_pCursorTextField->setColor(ccc3(0,0,0));
    this->addChild(m_pCursorTextField);
    
    m_pCursorTextField->setHorizontalAlignment(kCCTextAlignmentLeft);
    
    schedule(schedule_selector(ChatLayer::getChatContent), 5.0f);
    
}

void ChatLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler ChatLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCancelClicked", ChatLayer::onCancelClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSendClicked", ChatLayer::onSendClicked);
    
    return NULL;
}

SEL_CCControlHandler ChatLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool ChatLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenu", CCMenu * , mMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mContent", CCLabelTTF * , mContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSend", CCMenuItemImage * , mSend);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTextBG", CCLayerColor * , mTextBG);
    
    return false;
}



void ChatLayer::onCancelClicked(cocos2d::CCObject *pSender)
{
    pChatLayer->removeFromParentAndCleanup(true);
    if (mTarget && mCallFuncND) {
                (mTarget->*mCallFuncND)(NULL,(void *)true);
            }
}

ChatLayer * ChatLayer::addChatToLayer(cocos2d::CCLayer *parentLayer)
{
    pChatLayer->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(pChatLayer, Child_Order_Mid + 1);

    return pChatLayer;
}

ChatLayer * ChatLayer::addChatToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback)
{
    pChatLayer->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(pChatLayer, Child_Order_Mid + 1);

    mTarget = target;
    mCallFuncND = callback;
    return pChatLayer;
}


void ChatLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(pChatLayer,kCCMenuHandlerPriority - 1 , true);//
    CCLayer::registerWithTouchDispatcher();
    
//    INT_MAX
}

bool ChatLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    m_bTouchedText = m_pCursorTextField->ccTouchBegan(pTouch, pEvent);
    return true;
}

void ChatLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_bTouchedText)
    {
        m_pCursorTextField->ccTouchMoved(pTouch, pEvent);
    }
    
    if (m_bTouchedMenu) {
        mMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void ChatLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
    else
    {
        m_pCursorTextField->ccTouchEnded(pTouch, pEvent);
//        m_bTouchedMenu = false;
    }
}

void ChatLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_bTouchedText)
    {
        m_pCursorTextField->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
    
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void ChatLayer::getEventsInfo()
{
    GameServerAction::sharedGameServerAction()->showEvents(this, callfuncND_selector(ChatLayer::getEventsInfo_Done));
}


void ChatLayer::getEventsInfo_Done(cocos2d::CCNode *pNode, void *data)
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

void ChatLayer::onSendClicked(cocos2d::CCObject *pSender)
{
    GameServerAction::sharedGameServerAction()->sendChatContent(m_pCursorTextField->getString(), this, callfuncO_selector(ChatLayer::onSendContent_Done));
}


void ChatLayer::onSendContent_Done(cocos2d::CCObject *data)
{

    std::string msg = "";
    if(data)
    {
        CCDictionary * dict = (CCDictionary *) data;
        
        CCArray * eventsList = (CCArray *)dict->objectForKey("ItemInfor");
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


void ChatLayer::getChatContent()
{
    GameServerAction::sharedGameServerAction()->getChatContent(this, callfuncO_selector(ChatLayer::getChatContent_Done));
}


void ChatLayer::getChatContent_Done(cocos2d::CCObject *data)
{
    
    std::string msg = "";
    if(data)
    {
        CCDictionary * dict = (CCDictionary *) data;
        
        CCArray * eventsList = (CCArray *)dict->objectForKey("ItemInfor");
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


