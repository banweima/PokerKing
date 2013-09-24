//
//  MatchChip.h
//  blackjack
//
//  Created by Banson Niu on 10/15/12.
//
//

#ifndef __blackjack__MatchChip__
#define __blackjack__MatchChip__

#include "cocos2d.h"

USING_NS_CC;

class MatchChip : public CCSprite
{
private:
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBgSprite1, BgSprite1);
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBgSprite2, BgSprite2);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, mCountText, CountText);
    
    CCSpriteBatchNode* mSpriteBatchNode;
    
public:
    ~MatchChip();
    static MatchChip* create();
    bool init();
    
    void setCount(int newCount);
    int  getCount();
private:
    void setNormal();
    void setBusted();
    void setPingVisible(bool newPingIsVisible);
};

#endif /* defined(__blackjack__MatchChip__) */
