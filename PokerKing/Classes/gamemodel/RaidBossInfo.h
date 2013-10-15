//
//  RaidBossInfo.h
//  PokerKing
//
//  Created by Niu Xiaoming on 13-6-3.
//
//

#ifndef __PokerKing__RaidBossInfo__
#define __PokerKing__RaidBossInfo__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
enum BossStatus
{

    BossStatus_Active = 1,
    BossStatus_End,
    BossStatus_Escape,
};

class RaidBossInfo : public CCObject
{
public:
    CC_SYNTHESIZE(long, mBossInstance, BossInstance);
    CC_SYNTHESIZE(std::string, mOnlineBossName, OnlineBossName);
    CC_SYNTHESIZE(std::string, mOnlineBossImageUrl, OnlineBossImageUrl);
    CC_SYNTHESIZE(int, mBossType, BossType);
    CC_SYNTHESIZE(long, mCurrentHP, CurrentHP);
    CC_SYNTHESIZE(long, mMaxHP, MaxHP);
    CC_SYNTHESIZE(BossStatus, mStatus, Status);
    
public:
    static RaidBossInfo* create();
    void parseRaidBossInfo(CCDictionary * RaidBossInfoDic);
    bool init();
    
//    std::string getBossName();
//    std::string getBossImage();
    int getBossReward();
};



#endif /* defined(__PokerKing__RaidBossInfo__) */
