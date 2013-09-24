//
//  ChatLayer.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-8.
//
//

#ifndef __PokerKing__ChatLayer__
#define __PokerKing__ChatLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"
#include "GameServerAction.h"
#include "CursorTextField.h"

USING_NS_CC;
USING_NS_CC_EXT;


class ChatLayer : public CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
        
    CCLabelTTF * mContent;
    CCMenu * mMenu;
    bool m_bTouchedMenu;
    bool m_bTouchedText;
    CursorTextField *m_pCursorTextField;
    CCLayerColor * mTextBG;
    
    CCMenuItemImage * mSend;
    
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChatLayer, create);
    static ChatLayer* sharedChatLayer(void);
    
    bool init();
    
    ChatLayer();
    virtual ~ChatLayer();
    
    void setupLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    ChatLayer * addChatToLayer(cocos2d::CCLayer *parentLayer);
    
    ChatLayer * addChatToLayer(cocos2d::CCLayer *parentLayer, cocos2d::CCObject *target, SEL_CallFuncND callback);
    
    void getEventsInfo();

private:

    
    void onCancelClicked(CCObject *pSender);
    
    virtual void registerWithTouchDispatcher();
  
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    
    
    void getEventsInfo_Done(cocos2d::CCNode *pNode, void *data);

    void onSendClicked(CCObject * pSender);
    void onSendContent_Done (CCObject * data);
    
    void getChatContent();
    void getChatContent_Done(CCObject * data);
    
private:
    CCObject *mTarget;
    SEL_CallFuncND mCallFuncND;

};


#endif /* defined(__PokerKing__ChatLayer__) */
