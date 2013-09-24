//
//  UserInfoLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-2.
//
//

#ifndef __PokerKing__UserInfoLayer__
#define __PokerKing__UserInfoLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"
#include "GameServerAction.h"
#include "SimpleUserInfo.h"


USING_NS_CC;
USING_NS_CC_EXT;


class UserInfoLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
        
    CCSprite * mFrame;
    CCLabelTTF * mLevel;
    CCLabelTTF * mGold;
    CCLabelTTF * mTodayWin;
    CCLabelTTF * mTotalWin;
    CCLabelTTF * mName;

    bool m_bTouchedMenu;
    CCMenu* mMenu;
    
    SimpleUserInfo * mUserInfo;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(UserInfoLayer, create);
    static UserInfoLayer* sharedUserInfoLayer(void);
    
    bool init();
    
    UserInfoLayer();
    virtual ~UserInfoLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    UserInfoLayer * addUserInfoLayerToLayer(cocos2d::CCLayer *parentLayer, SimpleUserInfo * simpleUser);
    
//    UserInfoLayer * addUserInfoLayerToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback);

private:

    
    void onCancelClicked(CCObject *pSender);
    void onWeiboClicked(CCObject *pSender);
    void mFriend(CCObject *pSender);
    
    virtual void registerWithTouchDispatcher();
  
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    void getGameUserInfo(long userId);
    void getGameUserInfo_Done(CCObject *data);
    
    void showUserInfo();
    
    void getPlayerImage(CCNode* node, void* data);
//
//private:
//    CCObject *mTarget;
//    SEL_CallFuncND mCallFuncND;

};


#endif /* defined(__PokerKing__UserInfoLayer__) */
