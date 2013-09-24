//
//  BossBoardLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-19.
//
//

#ifndef __PokerKing__BossBoardLayer__
#define __PokerKing__BossBoardLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"
#include "GameServerAction.h"


USING_NS_CC;
USING_NS_CC_EXT;


class BossBoardLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
        
    CCLabelTTF * mContent;
    bool m_bTouchedMenu;
    CC_SYNTHESIZE_RETAIN(CCMenu*, mMenu, Menu);
    
    CCLabelTTF * mLabel1;
    CCLabelTTF * mLabel2;
    CCLabelTTF * mLabel3;
    CCLabelTTF * mLabel4;
    CCLabelTTF * mLabel5;
    
    CCMenuItemImage * mMenuGo1;
    CCMenuItemImage * mMenuGo2;
    CCMenuItemImage * mMenuGo3;
    CCMenuItemImage * mMenuGo4;
    CCMenuItemImage * mMenuGo5;
    
    bool hasBoss1;
    bool hasBoss2;
    bool hasBoss3;
    bool hasBoss4;
    bool hasBoss5;
    

    CCObject *mTarget;
    SEL_CallFuncND mCallFuncND;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BossBoardLayer, create);
    static BossBoardLayer* sharedBossBoardLayer(void);
    
    bool init();
    
    BossBoardLayer();
    virtual ~BossBoardLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    BossBoardLayer * addBossBoardToLayer(cocos2d::CCLayer *parentLayer);
    
    void getBossInfo(cocos2d::CCObject *target, SEL_CallFuncND callback);
    
    void getBossInfo();

private:

    
    void onCancelClicked(CCObject *pSender);
    
    virtual void registerWithTouchDispatcher();
  
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void getBossInfo_Done(cocos2d::CCObject *pNode, void *data);
    
    void onBossSelected1(CCObject * pSender);
    
    void onBossSelected2(CCObject * pSender);
    
    void onBossSelected3(CCObject * pSender);
    
    void onBossSelected4(CCObject * pSender);
    
    void onBossSelected5(CCObject * pSender);
    
    void gotoGame();
    
    void gotoGame_Done(cocos2d::CCNode *pNode, void *data);

};


#endif /* defined(__PokerKing__BossBoardLayer__) */
