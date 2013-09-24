//
//  SettingLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-5-7.
//
//

#ifndef __PokerKing__SettingLayer__
#define __PokerKing__SettingLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServerAction.h"
#include "IAPProductInfo.h"
#include "Constants.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define kTagLoading 1

class SettingLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    
    CCMenuItemImage * mHome;
    CCMenuItemImage * mInsurance;
    CCMenuItemImage * mBigSmall;
    CCMenuItemImage * mWhiteBoard;
    CCMenuItemImage * mWeibo;
    
    bool needInsurance;
    bool needBigSmall;

public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SettingLayer, create);
    bool init();
    
    SettingLayer();
    virtual ~SettingLayer();
    
    void setupLayer();
    
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

private:

    void onHomeClicked(CCObject *pSender);
    void onInsuranceClicked(CCObject *pSender);
    void onBigSmallClicked(CCObject *pSender);
    void onWhiteBoardClicked(CCObject *pSender);
    void onWeiboClicked(CCObject *pSender);
    
    void changeInsuranceCheck();
    void changeBigSmallCheck();
};


#endif /* defined(__PokerKing__SettingLayer__) */
