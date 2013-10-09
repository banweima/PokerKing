//
//  LoginLayer.h
//  blackjack
//
//  Created by Banson Niu on 10/17/12.
//
//

#ifndef __blackjack__LoginLayer__
#define __blackjack__LoginLayer__

#include "cocos2d.h"
#include "Constants.h"
#include "AlertLayer.h"
#include "cocos-ext.h"
#include "Loading.h"
#include "Constants.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    CCLabelTTF* mText;
    CCSprite * mWarning;
    CCMenuItemImage * mWeibo;
    CCSprite * mBackground;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoginLayer, create);
    
    bool init();
    
    LoginLayer();
    virtual ~LoginLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
private:
    void setupLoginLayer();
    void doLogin();
    void onWeiboClicked(CCObject * object);
    
//    void setupRegisterLayer();
//    void setupConnText();
//    
//    void registration(CCObject* object);
//    void doRegistration(CCObject* object);
//    void cancelRegistration(CCObject* object);
//    void showLoginMessage();
//    void hideLoginMessage();
//    void showMessage();
    
    void startSA(CCObject * object);
    void startMainBoard(CCNode* pSender, void* data);
    void gameCenterLogin(CCObject * object);
    void weiboLogin(CCObject * object);

};

#endif /* defined(__blackjack__LoginLayer__) */
