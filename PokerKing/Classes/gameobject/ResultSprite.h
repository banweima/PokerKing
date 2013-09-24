//
//  ResultSprite.h
//  blackjack
//
//  Created by Banson Niu on 10/16/12.
//
//

#ifndef __blackjack__ResultSprite__
#define __blackjack__ResultSprite__

#include "cocos2d.h"

USING_NS_CC;

enum ResultType {
    Equal,
    Win,
    Lose,
    BJ
};

class ResultSprite : public CCSprite
{
private:
    CC_SYNTHESIZE_RETAIN(CCSprite*, mEqualSprite, EqualSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, mWinSprite, WinSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, mLoseSprite, LoseSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBlackjackSprite, BlackjackSprite);
    
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBossWinSprite, BossWinSprite);
    CC_SYNTHESIZE_RETAIN(CCSprite*, mBossLoseSprite, BossLoseSprite);
    
    CCSpriteBatchNode* mSpriteBatchNode;
    
    ResultType mType;
    
public:
    ResultSprite();
    ~ResultSprite();
    static ResultSprite* create();
    bool init();
    
    void setType(ResultType type);
    const CCSize & getContentSize();
    
    ResultType getType();
};

#endif /* defined(__blackjack__ResultSprite__) */
