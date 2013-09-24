//
//  CardCount.h
//  blackjack
//
//  Created by Banson Niu on 9/18/12.
//
//

#ifndef __blackjack__CardCount__
#define __blackjack__CardCount__

#include "cocos2d.h"
#include "PlayCardHand.h"

USING_NS_CC;

class CardCount : public CCSprite
{
private:
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBgSprite1, BgSprite1);
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBgSprite2, BgSprite2);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, mCountText, CountText);
    
    CCSpriteBatchNode* mSpriteBatchNode;
    
public:
    ~CardCount();
    static CardCount* create();
    bool init();
    
    void setCount(int newCount);
    void setPokerHand(PokerHand pokerHand);
    void setWin(int isPlayerWin);
    
private:
    void setNormal();
    void setBusted();
    void setPingVisible(bool newPingIsVisible);
};

#endif /* defined(__blackjack__CardCount__) */
