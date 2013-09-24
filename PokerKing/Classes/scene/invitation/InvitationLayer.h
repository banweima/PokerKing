//
//  InvitationLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-13.
//
//

#ifndef __PokerKing__InvitationLayer__
#define __PokerKing__InvitationLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameServerAction.h"
#include "CursorTextField.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define kTagLoading 1

class InvitationLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    
    CCMenuItemImage * mAccept;
    CCMenuItemImage * mSend;
    CCLabelTTF * mCode;
    CCLabelTTF * mNumber;
    CCLabelTTF * mCodeInput;
    CCLabelTTF * mInviteCode;

public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(InvitationLayer, create);
    bool init();
    
    InvitationLayer();
    virtual ~InvitationLayer();
    
    void setupLayer();
    
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

private:

    void onHomeClicked(CCObject *pSender);
    void onAcceptClicked(CCObject * pSender);
    void onSendClicked(CCObject * pSender);
    
    void onInviteCodeClicked(CCObject * pSender);
    
    void onInputNumber(CCObject * data);
    
    void acceptCode_Done(CCObject * data);
};



#endif /* defined(__PokerKing__InvitationLayer__) */
