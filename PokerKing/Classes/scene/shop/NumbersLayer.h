//
//  NumbersLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-18.
//
//

#ifndef __PokerKing__NumbersLayer__
#define __PokerKing__NumbersLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"



USING_NS_CC;
USING_NS_CC_EXT;


class NumbersLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
        
    CCLabelTTF * mShower;
    CCLabelTTF * mTitle;
    bool m_bTouchedMenu;
    CCMenu* mNumberMenu;
    std::string strContent;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(NumbersLayer, create);
    static NumbersLayer* sharedNumbersLayer(void);
    
    bool init();
    
    NumbersLayer();
    virtual ~NumbersLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

    
    void addNumbersToLayer(std::string title, cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncO callback);
    
private:
    CCObject *mTarget;
    SEL_CallFuncO mCallFuncO;

private:

    
    
    
    virtual void registerWithTouchDispatcher();
  
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);


    void onCancelClicked(CCObject *pSender);
    
    void onZeroClicked(CCObject * pSender);
    void onOneClicked(CCObject * pSender);
    void onTwoClicked(CCObject * pSender);
    void onThreeClicked(CCObject * pSender);
    void onFourClicked(CCObject * pSender);
    void onFiveClicked(CCObject * pSender);
    void onSixClicked(CCObject * pSender);
    void onSevenClicked(CCObject * pSender);
    void onEightClicked(CCObject * pSender);
    void onNineClicked(CCObject * pSender);

    void onBackClicked(CCObject * pSender);
    void onOKClicked(CCObject * pSender);
};


#endif /* defined(__PokerKing__NumbersLayer__) */
