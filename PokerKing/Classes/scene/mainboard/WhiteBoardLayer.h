//
//  WhiteBoardLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-5.
//
//

#ifndef __PokerKing__WhiteBoardLayer__
#define __PokerKing__WhiteBoardLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"
#include "GameServerAction.h"


USING_NS_CC;
USING_NS_CC_EXT;


class WhiteBoardLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
        
    CCLabelTTF * mContent;
    bool m_bTouchedMenu;
    CC_SYNTHESIZE_RETAIN(CCMenu*, mMenu, Menu);
    
    int touchCount;
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(WhiteBoardLayer, create);
    static WhiteBoardLayer* sharedWhiteBoardLayer(void);
    
    bool init();
    
    WhiteBoardLayer();
    virtual ~WhiteBoardLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    WhiteBoardLayer * addWhiteBoardToLayer(std::string contentString, cocos2d::CCLayer *parentLayer);
    
    WhiteBoardLayer * addWhiteBoardToLayer(cocos2d::CCLayer *parentLayer);
    
    WhiteBoardLayer * addWhiteBoardToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback);
    
    void getEventsInfo();

private:

    
    void onCancelClicked(CCObject *pSender);
    
    virtual void registerWithTouchDispatcher();
  
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    
    
    void getEventsInfo_Done(cocos2d::CCNode *pNode, void *data);

private:
    CCObject *mTarget;
    SEL_CallFuncND mCallFuncND;

};


#endif /* defined(__PokerKing__WhiteBoardLayer__) */
