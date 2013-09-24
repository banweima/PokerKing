//
//  LotteryLayer.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-4-8.
//
//

#ifndef __blackjack__LotteryLayer__
#define __blackjack__LotteryLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlayCardHand.h"
#include "GameLevelInfo.h"
#include "SceneControler.h"

USING_NS_CC;
USING_NS_CC_EXT;


class LotteryLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:    
    CCLabelTTF * mRedBalls;
    CCLabelTTF * mBlueBalls;

    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LotteryLayer, create);
    
    bool init();
    
    LotteryLayer();
    virtual ~LotteryLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    
    void onHomeClicked(CCObject * pSender);
    void onFriendsClicked(CCObject * pSender);
    void onSettingClicked(CCObject * pSender);
    void onRankClicked(CCObject * pSender);
    
    void onStartClicked(CCObject * pSender);
    
    void gotoOtherScene(GameScene other);
    
private:
    void didAccelerate(CCAcceleration *pAccelerationValue);
};


#endif /* defined(__blackjack__LotteryLayer__) */
