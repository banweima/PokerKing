//
//  AlertLayer.h
//  blackjack
//
//  Created by Banson Niu on 10/18/12.
//
//

#ifndef __blackjack__AlertLayer__
#define __blackjack__AlertLayer__

#include "cocos2d.h"
#include <stdarg.h>


USING_NS_CC;

#define kTagAlertViewOk 1
#define kTagAlertViewCancel 0
#define kTagAlertViewZoom 1000000
class AlertLayer: public CCLayerColor
{
    // 模态对话框菜单
    //CCMenu *m_pMenu;
    // 记录菜单点击
    bool m_bTouchedMenu;
    int  m_bIndex;
    CCArray *itemButtonArray;
    CC_SYNTHESIZE_RETAIN(CCMenu*, m_pMenu, Menu);
    
public:
    AlertLayer(const char * pszTitle, const char * pszMsg, bool bHasCancel, CCObject *target, SEL_MenuHandler selector);
    
    AlertLayer(const char * pszTitle, const char * pszMsg, bool bHasCancel, CCObject *target, SEL_CallFuncND selector);
    
    ~AlertLayer();
    virtual bool init();
    virtual bool initWithColor(const ccColor4B &color);

    
    // 初始化对话框内容
    void initDialog();
    
    static AlertLayer* create(const char * pszTitle, const char * pszMsg, bool bHasCancel, CCObject *target, SEL_CallFuncND selector);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    // callback func
    void AlertLayerDidSelected(CCNode *pSender);
    void doCancel(CCNode *pSender);
    
public:
    std::string m_sTitle;
    std::string m_sMessage;
    int tag;
    bool m_bHasCancel;
    
protected:
    CCObject*       m_pListener;
    SEL_MenuHandler    m_pMenuHandler;
    SEL_CallFuncND      m_pCallFuncND;
    
};


#endif /* defined(__blackjack__AlertLayer__) */
