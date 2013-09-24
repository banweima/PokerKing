//
//  RankInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-7-25.
//
//

#ifndef __PokerKing__RankInfo__
#define __PokerKing__RankInfo__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Constants.h"

USING_NS_CC;


class RankInfo : public CCObject
{
public:
    CC_SYNTHESIZE(long, mDrawTime, DrawTime);
    CC_SYNTHESIZE(long, mLoseMoney, LoseMoney);
    CC_SYNTHESIZE(long, mLoseTime, LoseTime);
    CC_SYNTHESIZE(long, mTotalMoney, TotalMoney);
    CC_SYNTHESIZE(long, mUserId, UserId);
    CC_SYNTHESIZE(long, mWinMoney, WinMoney);
    CC_SYNTHESIZE(long, mWinTime, WinTime);


public:
    static RankInfo* create();
    void parseRankInfo(CCDictionary * RankInfoDic);
    bool init();

};


#endif /* defined(__PokerKing__RankInfo__) */
