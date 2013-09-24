//
//  UserInfoLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-2.
//
//

#include "UserInfoLayer.h"
#include "CCBUtility.h"

static UserInfoLayer *pUserInfoLayer = NULL;

UserInfoLayer* UserInfoLayer::sharedUserInfoLayer(void)
{
    if (!pUserInfoLayer)
    {
        pUserInfoLayer = new UserInfoLayer();
        
        if(pUserInfoLayer && pUserInfoLayer->init())
        {
            
        }
    }
    
    return pUserInfoLayer;
}


UserInfoLayer::UserInfoLayer()
:m_bTouchedMenu(false)
,mFrame(NULL)
,mMenu(NULL)
,mLevel(NULL)
,mGold(NULL)
,mTodayWin(NULL)
,mTotalWin(NULL)
,mName(NULL)
,mUserInfo(NULL)
{}

UserInfoLayer::~UserInfoLayer()
{
    CC_SAFE_RELEASE(mFrame);
    CC_SAFE_RELEASE(mMenu);
    CC_SAFE_RELEASE(mLevel);
    CC_SAFE_RELEASE(mGold);
    CC_SAFE_RELEASE(mTodayWin);
    CC_SAFE_RELEASE(mTotalWin);
    CC_SAFE_RELEASE(mName);
    CC_SAFE_RELEASE(mUserInfo);
}

bool UserInfoLayer::init()
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

void UserInfoLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/userinfo.ccbi", "UserInfoLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    this->setTouchEnabled(true);
}

void UserInfoLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler UserInfoLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCancelClicked", UserInfoLayer::onCancelClicked);
    
    return NULL;
}

SEL_CCControlHandler UserInfoLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool UserInfoLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFrame", CCSprite * , mFrame); 
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelTTF * , mLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenu", CCMenu * , mMenu);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGold", CCLabelTTF * , mGold);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTodayWin", CCLabelTTF * , mTodayWin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTotalWin", CCLabelTTF * , mTotalWin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName", CCLabelTTF * , mName);
    
    return false;
}



void UserInfoLayer::onCancelClicked(cocos2d::CCObject *pSender)
{
    pUserInfoLayer->removeFromParentAndCleanup(true);
//    if (mTarget && mCallFuncND) {
//                (mTarget->*mCallFuncND)(NULL,(void *)true);
//            }
}

UserInfoLayer * UserInfoLayer::addUserInfoLayerToLayer(cocos2d::CCLayer *parentLayer, SimpleUserInfo * simpleUser)
{
    pUserInfoLayer->removeFromParentAndCleanup(false);
    
    mUserInfo = simpleUser;
    mUserInfo->retain();
    
    parentLayer->addChild(pUserInfoLayer, Child_Order_Mid + 1);
    
    showUserInfo();

    return pUserInfoLayer;
}

void UserInfoLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(pUserInfoLayer, kCCMenuHandlerPriority - 100, true);
    CCLayer::registerWithTouchDispatcher(); 
}

bool UserInfoLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    return true;
}

void UserInfoLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void UserInfoLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void UserInfoLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void UserInfoLayer::showUserInfo()
{

    CCLog("User Name: %s",mUserInfo->getUserName().c_str());
    mName->setString(mUserInfo->getUserName().c_str());
    
    mLevel->setString(CCString::createWithFormat("%d",
            mUserInfo->getLevel())->getCString());
    
    mGold->setString(CCString::createWithFormat("%d",
            mUserInfo->getGold())->getCString());
    
    mUserInfo->retrieveAvartaImage(this, callfuncND_selector(UserInfoLayer::getPlayerImage));
    
}

void UserInfoLayer::getPlayerImage(CCNode* node, void* data)
{
    CCSprite* sprite = mUserInfo->addAvartaToLayer(this);
    
    sprite->setScale(2 * mFrame->getContentSize().width/sprite->getContentSize().width);
    sprite->setPosition(mFrame->getPosition());
    sprite->setAnchorPoint(mFrame->getAnchorPoint());
    
    mFrame->getParent()->removeChild(mFrame, false);
    this->addChild(mFrame,Child_Order_Mid);

}

void UserInfoLayer::getGameUserInfo(long userId)
{
    GameServerAction::sharedGameServerAction()->getGameUserInfo(userId, this, callfuncO_selector(UserInfoLayer::getGameUserInfo_Done));
}

void UserInfoLayer::getGameUserInfo_Done(cocos2d::CCObject *data)
{
    if(mUserInfo)
    {
        mUserInfo->release();
        
        mUserInfo = new SimpleUserInfo();
    }
    
    mUserInfo->parseSimpleUserInfo((CCDictionary *)data);
    
    showUserInfo();
}
