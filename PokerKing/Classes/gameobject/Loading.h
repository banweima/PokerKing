//
//  Loading.h
//  blackjack
//
//  Created by ruan.xiaoyu on 2012/08/18.
//
//

#ifndef __blackjack__Loading__
#define __blackjack__Loading__

#include "cocos2d.h"
#include "PlayCard.h"
#include "RotateY.h"

USING_NS_CC;

class Loading : public CCLayerColor
{
public:
    void showLoading(const char* loadingMsg);
    
    void removeLoading();
    
    static Loading* sharedLoading(void);
    
    Loading();
    virtual ~Loading();
    
    Loading * addLoadingToLayer(CCLayer * parentLayer);
    
    Loading * addLoadingToLayer(CCLayer * parentLayer,GLubyte var);

private:
//    Loading* create();
    virtual void registerWithTouchDispatcher();
  
  virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};


#endif /* defined(__blackjack__Loading__) */
