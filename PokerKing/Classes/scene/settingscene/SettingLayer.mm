//
//  SettingLayer.cpp
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-7.
//
//

#include "SettingLayer.h"
#include "CCBUtility.h"
#include "GameKitFactory.h"
#include "Constants.h"
#include "MainBoardScene.h"
#include "WeiboFactory.h"
#include "StoreKitFactory.h"
#include "UserInfo.h"
#include "WhiteBoardLayer.h"
#include "SceneControler.h"
#include "Banner.h"

SettingLayer::SettingLayer()
: mHome(NULL)
, mInsurance(NULL)
, mBigSmall(NULL)
, mWhiteBoard(NULL)
, mWeibo(NULL)
{}

SettingLayer::~SettingLayer()
{
    CC_SAFE_RELEASE(mHome);
    CC_SAFE_RELEASE(mInsurance);
    CC_SAFE_RELEASE(mBigSmall);
    CC_SAFE_RELEASE(mWhiteBoard);
    CC_SAFE_RELEASE(mWeibo);
    
}

bool SettingLayer::init()
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

void SettingLayer::setupLayer()
{
    CCNode * node = CCBUtility::loadCCB("ccbi/setting.ccbi", "SettingLayer", CCLayerLoader::loader(), this);

    this->addChild(node);
    
    int h = getWinH();
    if(h>480)
    {
        Banner * banner = Banner::create();
        banner->retain();
        this->addChild(banner,-100);
    }
    
    if(LoadStringFromXML(NeedBJInsurance) == "No")
    {
        needInsurance = false;
    }
    else
    {
        needInsurance = true;
    }
    
    if(LoadStringFromXML(NeedBJBigSmall) == "No")
    {
        needBigSmall = false;
    }
    else
    {
        needBigSmall = true;
    }
    
    changeBigSmallCheck();
    changeInsuranceCheck();
}

void SettingLayer::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
}


SEL_MenuHandler SettingLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onHomeClicked", SettingLayer::onHomeClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onInsuranceClicked", SettingLayer::onInsuranceClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBigSmallClicked", SettingLayer::onBigSmallClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onWhiteBoardClicked", SettingLayer::onWhiteBoardClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onWeiboClicked", SettingLayer::onWeiboClicked);
    
    return NULL;
}

SEL_CCControlHandler SettingLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

bool SettingLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHome", CCMenuItemImage *, mHome);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInsurance", CCMenuItemImage *, mInsurance);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBigSmall", CCMenuItemImage *, mBigSmall);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWhiteBoard", CCMenuItemImage *, mWhiteBoard);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWeibo", CCMenuItemImage *, mWeibo);

    
    return false;
}


void SettingLayer::onHomeClicked(cocos2d::CCObject *pSender)
{
    SceneControler::sharedSceneControler()->goBackScene();
}

void SettingLayer::onWhiteBoardClicked(cocos2d::CCObject *pSender)
{
    WhiteBoardLayer::sharedWhiteBoardLayer()->addWhiteBoardToLayer(this);
}

void SettingLayer::onInsuranceClicked(cocos2d::CCObject *pSender)
{
    needInsurance = !needInsurance;
    changeInsuranceCheck();
}

void SettingLayer::onBigSmallClicked(cocos2d::CCObject *pSender)
{
    needBigSmall = !needBigSmall;
    changeBigSmallCheck();
}

void SettingLayer::onWeiboClicked(cocos2d::CCObject *pSender)
{
    
    [[WeiboFactory sharedWeiboFactory] logoutWeibo];

    
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"设定"
                                message:@"已登出，请退出重进游戏！"
                               delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];

        [alerView show];
        [alerView release];
}

void SettingLayer::changeInsuranceCheck()
{
    if(needInsurance)
    {
        SaveStringToXML(NeedBJInsurance,"Yes");
        mInsurance->setNormalImage(CCSprite::createWithSpriteFrameName("btn_checkbox_on"));
    }
    else
    {
        SaveStringToXML(NeedBJInsurance,"No");
        mInsurance->setNormalImage(CCSprite::createWithSpriteFrameName("btn_checkbox"));
    }
}

void SettingLayer::changeBigSmallCheck()
{
    if(needBigSmall)
    {
        SaveStringToXML(NeedBJBigSmall,"Yes");
        mBigSmall->setNormalImage(CCSprite::createWithSpriteFrameName("btn_checkbox_on"));
    }
    else
    {
        SaveStringToXML(NeedBJBigSmall,"No");
        mBigSmall->setNormalImage(CCSprite::createWithSpriteFrameName("btn_checkbox"));
    
    }
}
