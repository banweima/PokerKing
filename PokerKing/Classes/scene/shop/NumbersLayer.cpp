//
//  NumbersLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-18.
//
//

#include "NumbersLayer.h"
#include "CCBUtility.h"


NumbersLayer* NumbersLayer::sharedNumbersLayer(void)
{
    NumbersLayer *pNumbersLayer = NULL;
    if (!pNumbersLayer)
    {
        pNumbersLayer = new NumbersLayer();
        
        if(pNumbersLayer && pNumbersLayer->init())
        {
        }
    }
    
    return pNumbersLayer;
}


NumbersLayer::NumbersLayer()
:m_bTouchedMenu(false)
,mShower(NULL)
,mNumberMenu(NULL)
,strContent("")
,mTitle(NULL)
{}

NumbersLayer::~NumbersLayer()
{
    CC_SAFE_RELEASE(mShower);
    CC_SAFE_RELEASE(mNumberMenu);
    CC_SAFE_RELEASE(mTitle);
}

bool NumbersLayer::init()
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

void NumbersLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/numbers.ccbi", "NumbersLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    mShower->setString("");
    mTitle->setString("");
    
    this->setTouchEnabled(true);
}

void NumbersLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler NumbersLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCancelClicked", NumbersLayer::onCancelClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onZeroClicked", NumbersLayer::onZeroClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOneClicked", NumbersLayer::onOneClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTwoClicked", NumbersLayer::onTwoClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onThreeClicked", NumbersLayer::onThreeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFourClicked", NumbersLayer::onFourClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFiveClicked", NumbersLayer::onFiveClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSixClicked", NumbersLayer::onSixClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSevenClicked", NumbersLayer::onSevenClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onEightClicked", NumbersLayer::onEightClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNineClicked", NumbersLayer::onNineClicked);
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", NumbersLayer::onBackClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onOKClicked", NumbersLayer::onOKClicked);
    
    return NULL;
}

SEL_CCControlHandler NumbersLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool NumbersLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShower", CCLabelTTF * , mShower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTitle", CCLabelTTF * , mTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNumberMenu", CCMenu * , mNumberMenu);
    
    return false;
}



void NumbersLayer::onCancelClicked(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(true);
    if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(NULL);
            }
}


void NumbersLayer::addNumbersToLayer(std::string title,cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncO callback)
{
    this->removeFromParentAndCleanup(false);
    
    parentLayer->addChild(this, NumbersLayer_Tag);

    mTarget = target;
    mCallFuncO = callback;
    
    mShower->setString("");
    mTitle->setString(title.c_str());
    strContent = "";
}


void NumbersLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority - 100, true);

    CCLayer::registerWithTouchDispatcher(); 
}

bool NumbersLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = mNumberMenu->ccTouchBegan(pTouch, pEvent);
    return true;
}

void NumbersLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mNumberMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void NumbersLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mNumberMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void NumbersLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        mNumberMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}


void NumbersLayer::onZeroClicked(CCObject * pSender)
{
    strContent = strContent + "0";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onOneClicked(CCObject * pSender)
{
    strContent = strContent + "1";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onTwoClicked(CCObject * pSender)
{
    strContent = strContent + "2";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onThreeClicked(CCObject * pSender)
{
    strContent = strContent + "3";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onFourClicked(CCObject * pSender)
{
    strContent = strContent + "4";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onFiveClicked(CCObject * pSender)
{
    strContent = strContent + "5";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onSixClicked(CCObject * pSender)
{
    strContent = strContent + "6";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onSevenClicked(CCObject * pSender)
{
    strContent = strContent + "7";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onEightClicked(CCObject * pSender)
{
    strContent = strContent + "8";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onNineClicked(CCObject * pSender)
{
    strContent = strContent + "9";
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onBackClicked(CCObject * pSender)
{
    
    strContent = strndup(strContent.c_str(), strContent.length() - 1);
    mShower->setString(strContent.c_str());
}

void NumbersLayer::onOKClicked(CCObject * pSender)
{
    this->removeFromParentAndCleanup(true);
    if (mTarget && mCallFuncO) {
                (mTarget->*mCallFuncO)(CCString::create(strContent.c_str()));
            }
}
