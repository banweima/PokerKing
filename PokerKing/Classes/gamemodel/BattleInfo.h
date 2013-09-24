//
//  BattleInfo.h
//  blackjack
//
//  Created by Niu Xiaoming on 13-3-28.
//
//

#ifndef __blackjack__BattleInfo__
#define __blackjack__BattleInfo__


#include "cocos2d.h"
#include "GameInfo.h"
#include "cocos-ext.h"
#include "RaidBossInfo.h"

USING_NS_CC;

enum BattleType{
    FreeBattle = 0,
	SingleBattle,
	ArenaBattle,
	BossBattle
};

enum BattleStatus {
	Waiting = 0,
	Fighting,
	End,
};

enum BattleResult {
	BattlePush = 0,
	BattleWin,
	BattleLose,
};

class BattleInfo : public CCObject
{
public:
    CC_SYNTHESIZE(long, mBattleID, BattleID);
    CC_SYNTHESIZE(long, mBattleOwnerUserID, BattleOwnerUserID);
    CC_SYNTHESIZE(CCArray *, mBattlePlayerList, BattlePlayerList);
    CC_SYNTHESIZE(BattleStatus, mBattleStatus, BattleStatus);
    CC_SYNTHESIZE(long, mBattleCreateTime, BattleCreateTime);
    CC_SYNTHESIZE(long, mBattlePrize, BattlePrize);
    CC_SYNTHESIZE(BattleType, mBattleType, BattleType);
    CC_SYNTHESIZE(CCArray *, mDealerCards, DealerCards);
    CC_SYNTHESIZE(BattleResult, mBattleResult, BattleResult);
    CC_SYNTHESIZE(RaidBossInfo *, mRaidBoss, RaidBoss);
    
public:
    static BattleInfo* sharedBattleInfo(void);
    BattleInfo();
    virtual ~BattleInfo();
    void parseBattleInfo(CCDictionary * battleInfoDic);
    virtual bool init(void);
};

#endif /* defined(__blackjack__BattleInfo__) */
