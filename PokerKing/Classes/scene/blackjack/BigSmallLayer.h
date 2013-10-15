//
//  BigSmallLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-8-10.
//
//

#ifndef __PokerKing__BigSmallLayer__
#define __PokerKing__BigSmallLayer__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"
#include "GameServerAction.h"
#include "PlayCardHand.h"

USING_NS_CC;
USING_NS_CC_EXT;


class BigSmallLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
        
    CCLabelBMFont * mBet;
    bool m_bTouchedMenu;
    CCMenu* mMenu;
    CCMenuItemImage * mBig;
    CCNode* mPlayerHandNode;
    PlayCardHand* mPlayerHand;
    long currentBet;
    
    int selectTarget; //1:Black;-1:Red
    
    bool isFirstTime;
    
    CCLabelTTF * mHistory;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BigSmallLayer, create);
    static BigSmallLayer* sharedBigSmallLayer(long initBet);
    
    bool init();
    
    BigSmallLayer();
    virtual ~BigSmallLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    BigSmallLayer * addBigSmallToLayer(std::string contentString, cocos2d::CCLayer *parentLayer);
    
    BigSmallLayer * addBigSmallToLayer(cocos2d::CCLayer *parentLayer);
    
    BigSmallLayer * addBigSmallToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback);
    

private:
    
    
    void onBigClicked(CCObject *pSender);
    void onSmallClicked(CCObject * pSender);
    void onExitClicked(CCObject * pSender);
    
    void showCard();
    
    virtual void registerWithTouchDispatcher();
  
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    void setCurrentBet(long bet);
    void showResult();
    
private:
    CCObject *mTarget;
    SEL_CallFuncND mCallFunc;

};


#endif /* defined(__PokerKing__BigSmallLayer__) */
